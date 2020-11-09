// Manifest.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Manifest.h"
#include <Shared/Guard.h>
#include "ManifestProvisioning.pb.h"

#pragma comment(lib, "Iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CManifestApp

BEGIN_MESSAGE_MAP(CManifestApp, CWinApp)
END_MESSAGE_MAP()


// CManifestApp construction

CManifestApp::CManifestApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CManifestApp object

CManifestApp theApp;


// CManifestApp initialization

BOOL CManifestApp::InitInstance()
{
    CWinApp::InitInstance();

    if (!AfxSocketInit())
    {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }
    return TRUE;
}

static void ThrowError(const char* sErr)
{
    OutputDebugString(sErr);
    throw std::runtime_error(sErr);
}

static void ThrowError(int ret, const char* sErr)
{
    if (ret < 0)
    {
        CString sMsg;
        sMsg.Format("Error: %s ret=%d err=%d", sErr, ret, WSAGetLastError());
        ThrowError(sMsg);
    }
}

//https://gist.github.com/hostilefork/f7cae3dc33e7416f2dd25a402857b6c6
std::vector<CString> ReadManifest(const char* sAddr, u_short udpPort, u_short tcpPort)
{
    std::vector<BYTE> manifest;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    int ret = 0;
    // create what looks like an ordinary UDP socket
    int fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    ThrowError(fd, "Init udp socket");

    Guard socketGuard([&] { if (fd > 0) closesocket(fd); });

    // allow multiple sockets to use the same PORT number
    /*
    u_int yes = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
    if (ret < 0)
    {
        OnError("Reusing ADDR failed (%d)\n", ret);
        return false;
    }*/

    // set up destination address    
    sockaddr_in6 addr = { AF_INET6, htons(udpPort) };

    // bind to receive address
    ThrowError(bind(fd, (sockaddr*)&addr, sizeof(addr)), "Calling bind failed");

    // Join membership
    ipv6_mreq group;
    group.ipv6mr_interface = 0;
    inet_pton(AF_INET6, sAddr, &group.ipv6mr_multiaddr);
    ret = setsockopt(fd, IPPROTO_IPV6, IPV6_JOIN_GROUP, (char*)&group, sizeof(group));
    ThrowError(ret, "Call setsockopt failed");
           
    // Wait for UDP frame for 5 seconds.
    fd_set rset;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    timeval timeout = { 5, 0 };
    ret = select(0, &rset, 0, 0, &timeout);
    ThrowError(ret, "Calling select failed");
    if (ret == 0)
        ThrowError("No UDP frame received");

    u_char rxData[1600]; // Buffer to receive udp broadcast
    sockaddr_in6 from;
    int fromlen = sizeof(from);
    int rxLen = recvfrom(fd, (char*)rxData, sizeof(rxData), 0, (sockaddr*)&from, &fromlen);

    closesocket(fd);

    manifest_manager_msg::MM_CollectionVersionAnnounce annouce;
    if (!annouce.ParseFromArray(rxData, rxLen))
        ThrowError("Invalid manifest announce received");
    auto sCollectionVersion = annouce.collectionversion();

    // Create TCP socket to receive manifest data, packed in google protobuf
    fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    ThrowError(fd, "Init tcp socket failed");

    from.sin6_port = htons(tcpPort);
    ThrowError(connect(fd, (sockaddr*)&from, fromlen), "Calling connect failed");

    manifest_manager_msg::MM_ClientRequest_V1 clientRequest;
    clientRequest.set_collectionversion(sCollectionVersion);
    auto sClientRequest = clientRequest.SerializeAsString();
    int length = sClientRequest.length();
    int _size = sClientRequest.size();
    ThrowError(send(fd, sClientRequest.c_str(), sClientRequest.length(), 0), "Calling send failed");  

    // shutdown the connection since no more data will be sent
    ThrowError(shutdown(fd, SD_SEND), "Calling shutdown failed");

    rxLen = 0;
    do
    {
        rxLen = recv(fd, (char*)rxData, sizeof(rxData), 0);
        ThrowError(rxLen, "Calling tcp recv failed");

        auto pos = manifest.size();
        manifest.resize(manifest.size() + rxLen);
        for (int nByte = 0; nByte < rxLen; ++nByte)
            manifest[pos + nByte] = rxData[nByte];

    } while (rxLen > 0);

    if (manifest.empty())
        ThrowError("No manifest received");

    manifest_manager_msg::MM_ManifestCollection_V1 manifestCollection;
    if(!manifestCollection.ParseFromArray(manifest.data(), manifest.size()))
        ThrowError("Invalid manifest received");

    std::vector<CString> manifestVector;
    for (int nManifest = 0; nManifest < manifestCollection.manifests_size(); ++nManifest)
        manifestVector.push_back(manifestCollection.manifests(nManifest).c_str());

    if(manifestVector.empty())
        ThrowError("No manifest received");

    return manifestVector;
}

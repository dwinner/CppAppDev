#include "pch.h"
#include <CanDll/Src/canduserapi.h>
#include <RunTime/RunTimeApi.h>
#include <Database\SharedImpl\CreateHelperDatabase.h>
#include <Database/SharedImpl/GetValueHelper.h>
#include <Database/Namespace/Namespace.h>
#include <Database/API/Names.h>
#include <Database/Database/Database.h>
#include <Database/DatabaseCore/DatabaseCoreApi.h>
#include <Database/EnvVar/EnvVar.h>
#include <ReportMan/IReport.h>
#include "resource.h"
#include <Shared/CBase64.h>
#include <ExternalDependencies/google/protobuf/message.h>

#define USERDLL_API __declspec(dllexport) 
#define USERDLL_CALL __stdcall
#define ANSI_C extern "C"

std::vector<CString> ReadManifest(const char* sAddr, u_short udpPort, u_short tcpPort);

static const char UdpPort[] = "UdpPort";
static const char TcpPort[] = "TcpPort";
static const char BroadCastIP[] = "BroadCastIP";
static const char Manifest[] = "Manifest";

typedef std::map<CString, db::TReference<db::IEnvVar>> ConfigMap;
static ConfigMap& GetConfig()
{
    static ConfigMap config;
    return config;
}

template<class T>
static T GetParam(const char* sName)
{
    return db::GetValueDef<T>(*GetConfig()[sName]);
}

template<>
static CString GetParam(const char* sName)
{
    return GetConfig()[sName]->GetString();
}

template<class T>
static void AddParam(db::IDatabaseItem& parent, const char* sName, const T& val)
{
    if (auto pParam = parent.Children().Find(sName))
    {
        GetConfig()[sName] = pParam;
        return; // We already have a config param.
    }

    auto param = db::GetChildDatabaseItem<db::IEnvVar>(parent, sName);
    db::SetValue(*param, val);
    GetConfig()[sName] = param;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                //
//                                    Exported Standard-Functions                                                 //
//                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL USERDLL_CALL DLL_boInit(HWND hMainWnd)
{    
#ifdef DEBUG
    const u_short udpPortInit = 42515;
    const u_short tcpPortInit = 29801;
    const char sBroadCastIPInit[] = "::1/128";
#else
    const u_short udpPortInit = 42515;
    const u_short tcpPortInit = 29801;
    const char sBroadCastIPInit[] = "ff14::5:0";
#endif


    // Create variables to configure the plugin.
    auto runtime = db::GetRuntime();
    if (!runtime)
        return FALSE;

    auto db = db::GetDatabase();
    auto ns = db::GetChildDatabaseItem<db::INamespaceInternal>(*db, db::VARDB);
    auto nsManifest = db::GetChildDatabaseItem<db::INamespace>(*ns, "Manifest_Config");

    AddParam(*nsManifest, UdpPort, udpPortInit);
    AddParam(*nsManifest, TcpPort, tcpPortInit);
    AddParam(*nsManifest, BroadCastIP, sBroadCastIPInit);
    AddParam(*nsManifest, Manifest, "");

    return TRUE;
}

static void ReadManifest()
{
    try
    {
        CWaitCursor wait;

        CString sCompleteManifest;
        
        auto manifestVector = ReadManifest(GetParam<CString>(BroadCastIP), GetParam<u_short>(UdpPort),
            GetParam<u_short>(TcpPort));

        for (auto& sManifest : manifestVector)
        {
            CBase64 base64;
            auto decodeSize = base64.CalculateRecquiredDecodeOutputBufferSize(sManifest);

            CString sManifestDecoded;
            auto pBuffer = sManifestDecoded.GetBuffer(decodeSize + 1);
            
            base64.DecodeBuffer(sManifest, pBuffer);

            sManifestDecoded.ReleaseBuffer();
            if (!sCompleteManifest.IsEmpty())
                sCompleteManifest += "\n";
            sCompleteManifest += sManifestDecoded;
        }

        GetConfig()[Manifest]->SetString(sCompleteManifest);

        CString sMsg;
        sMsg.Format(IDS_Success, GetConfig()[Manifest]->GetStringRef());
        db::GetRuntime()->Report().MakeReport(report::nenNote, sMsg);
    }
    catch (std::runtime_error& e)
    {
        db::GetRuntime()->Report().MessageBox(e.what(), MB_ICONERROR);
    }
}

void USERDLL_CALL DLL_vDeInit()
{ 
}

void USERDLL_CALL DLL_vStart()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    //ReadManifest();
}

void USERDLL_CALL DLL_vStop()
{     
}

int USERDLL_CALL DLL_iOnLoad(DWORD hFileModule, DWORD dwModulVersion)
{
    return 0;
}

int USERDLL_CALL DLL_iOnSave(DWORD hFileModule, DWORD* pdwModulVersion)
{
    return 0;
}

char* USERDLL_CALL DLL_pcGetSignature(int)
{
    static char desc[] = "Manifest Plugin";
    return desc;
}

DWORD USERDLL_CALL DLL_dwGetAPIVersion()
{
    return CANDLL_API_VERSION;
}

int USERDLL_CALL DLL_iOnEvent(UINT uiEvent, DWORD dwUserData1, DWORD dwUserData2)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int iRet = FALSE;
    switch (uiEvent)
    {
        case CAND_nGetMenu:
        {
            /* context menu */
            CMenu& menu = *(CMenu*)dwUserData1;
            menu.CreatePopupMenu();
            menu.AppendMenu(MF_STRING, (UINT_PTR)IDS_ReadManifest, CString(MAKEINTRESOURCE(IDS_ReadManifest)));
            iRet = FALSE;
            break;
        }
        case CAND_nMenuCommand:
        {
            switch (dwUserData1)
            {
            case IDS_ReadManifest:
                ReadManifest();
                break;
            }
        }
        default:
            /* Nothing to do. iRetVal is FALSE */
            break;
    }

    return iRet;
}
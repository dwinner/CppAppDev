// MediaLAN 02/2013
// CRtspSession
// - Main and streamer master listener socket
// - Client session thread

#include "stdafx.h"

#include <Winsock2.h>
#include <windows.h>  
#pragma comment(lib, "Ws2_32.lib")

#include "CStreamer.h"
#include "CRtspSession.h"

DWORD WINAPI SessionThreadHandler(LPVOID lpParam)
{
    SOCKET Client = *(SOCKET*)lpParam;

    char         RecvBuf[10000];                    // receiver buffer
    int          res;  
    CStreamer    Streamer(Client);                  // our streamer for UDP/TCP based RTP transport
    CRtspSession RtspSession(Client,&Streamer);     // our threads RTSP session and state
    int          StreamID = 0;                      // the ID of the 2 JPEG samples streams which we support
    HANDLE       WaitEvents[2];                     // the waitable kernel objects of our session
    
    HANDLE HTimer = ::CreateWaitableTimerA(NULL,false, NULL);

    WSAEVENT RtspReadEvent = WSACreateEvent();      // create READ wait event for our RTSP client socket
    WSAEventSelect(Client,RtspReadEvent,FD_READ);   // select socket read event
    WaitEvents[0] = RtspReadEvent;
    WaitEvents[1] = HTimer;

    // set frame rate timer
    double T = 40.0;                                       // frame rate
    int iT   = T;
    const __int64 DueTime = - static_cast<const __int64>(iT) * 10 * 1000;
    ::SetWaitableTimer(HTimer,reinterpret_cast<const LARGE_INTEGER*>(&DueTime),iT,NULL,NULL,false);

    bool StreamingStarted = false;
    bool Stop             = false;

    while (!Stop)
    {
        switch (WaitForMultipleObjects(2,WaitEvents,false,INFINITE))
        {
            case WAIT_OBJECT_0 + 0 : 
            {   // read client socket
                WSAResetEvent(WaitEvents[0]);

                memset(RecvBuf,0x00,sizeof(RecvBuf));
                res = recv(Client,RecvBuf,sizeof(RecvBuf),0);

                // we filter away everything which seems not to be an RTSP command: O-ption, D-escribe, S-etup, P-lay, T-eardown
                if ((RecvBuf[0] == 'O') || (RecvBuf[0] == 'D') || (RecvBuf[0] == 'S') || (RecvBuf[0] == 'P') || (RecvBuf[0] == 'T'))
                {
                    RTSP_CMD_TYPES C = RtspSession.Handle_RtspRequest(RecvBuf,res);
                    if (C == RTSP_PLAY)     StreamingStarted = true; else if (C == RTSP_TEARDOWN) Stop = true;
                };
                break;      
            };
            case WAIT_OBJECT_0 + 1 : 
            {
                if (StreamingStarted) Streamer.StreamImage(RtspSession.GetStreamID());
                break;
            };
        };
    };
    closesocket(Client);
    return 0;
};

int main()  
{    
    SOCKET      MasterSocket;                                 // our masterSocket(socket that listens for RTSP client connections)  
    SOCKET      ClientSocket;                                 // RTSP socket to handle an client
    sockaddr_in ServerAddr;                                   // server address parameters
    sockaddr_in ClientAddr;                                   // address parameters of a new RTSP client
    int         ClientAddrLen = sizeof(ClientAddr);   
    WSADATA     WsaData;  
    DWORD       TID;

    int ret = WSAStartup(0x101,&WsaData); 
    if (ret != 0) return 0;  

    ServerAddr.sin_family      = AF_INET;   
    ServerAddr.sin_addr.s_addr = INADDR_ANY;   
    ServerAddr.sin_port        = htons(8554);                 // listen on RTSP port 8554
    MasterSocket               = socket(AF_INET,SOCK_STREAM,0);   

    // bind our master socket to the RTSP port and listen for a client connection
    if (bind(MasterSocket,(sockaddr*)&ServerAddr,sizeof(ServerAddr)) != 0) return 0;  
    if (listen(MasterSocket,5) != 0) return 0;

    while (true)  
    {   // loop forever to accept client connections
        ClientSocket = accept(MasterSocket,(struct sockaddr*)&ClientAddr,&ClientAddrLen);    
        CreateThread(NULL,0,SessionThreadHandler,&ClientSocket,0,&TID);
        printf("Client connected. Client address: %s\r\n",inet_ntoa(ClientAddr.sin_addr));  
    }  

    closesocket(MasterSocket);   
    WSACleanup();   

    return 0;  
} 

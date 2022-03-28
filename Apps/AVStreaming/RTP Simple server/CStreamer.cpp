// MediaLAN 02/2013
// CRtspSession
// - JPEG packetizer and UDP/TCP based streaming

#include "CStreamer.h"
#include "JPEGSamples.h"

#include <stdio.h>

CStreamer::CStreamer(SOCKET aClient):m_Client(aClient)
{
    m_RtpServerPort  = 0;
    m_RtcpServerPort = 0;
    m_RtpClientPort  = 0;
    m_RtcpClientPort = 0;

    m_SequenceNumber = 0;
    m_Timestamp      = 0;
    m_SendIdx        = 0;
    m_TCPTransport   = false;
};

CStreamer::~CStreamer()
{
    closesocket(m_RtpSocket);
    closesocket(m_RtcpSocket);
};

void CStreamer::SendRtpPacket(char * Jpeg, int JpegLen, int Chn)
{
#define KRtpHeaderSize 12           // size of the RTP header
#define KJpegHeaderSize 8           // size of the special JPEG payload header

    char        RtpBuf[2048];
    sockaddr_in RecvAddr;
    int         RecvLen = sizeof(RecvAddr);
    int         RtpPacketSize = JpegLen + KRtpHeaderSize + KJpegHeaderSize;

    // get client address for UDP transport
    getpeername(m_Client,(struct sockaddr*)&RecvAddr,&RecvLen);
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port   = htons(m_RtpClientPort);

    memset(RtpBuf,0x00,sizeof(RtpBuf));
    // Prepare the first 4 byte of the packet. This is the Rtp over Rtsp header in case of TCP based transport
    RtpBuf[0]  = '$';        // magic number
    RtpBuf[1]  = 0;          // number of multiplexed subchannel on RTPS connection - here the RTP channel
    RtpBuf[2]  = (RtpPacketSize & 0x0000FF00) >> 8;
    RtpBuf[3]  = (RtpPacketSize & 0x000000FF);
    // Prepare the 12 byte RTP header
    RtpBuf[4]  = 0x80;                               // RTP version
    RtpBuf[5]  = 0x9a;                               // JPEG payload (26) and marker bit
    RtpBuf[7]  = m_SequenceNumber & 0x0FF;           // each packet is counted with a sequence counter
    RtpBuf[6]  = m_SequenceNumber >> 8;
    RtpBuf[8]  = (m_Timestamp & 0xFF000000) >> 24;   // each image gets a timestamp
    RtpBuf[9]  = (m_Timestamp & 0x00FF0000) >> 16;
    RtpBuf[10] = (m_Timestamp & 0x0000FF00) >> 8;
    RtpBuf[11] = (m_Timestamp & 0x000000FF);
    RtpBuf[12] = 0x13;                               // 4 byte SSRC (sychronization source identifier)
    RtpBuf[13] = 0xf9;                               // we just an arbitrary number here to keep it simple
    RtpBuf[14] = 0x7e;
    RtpBuf[15] = 0x67;
    // Prepare the 8 byte payload JPEG header
    RtpBuf[16] = 0x00;                               // type specific
    RtpBuf[17] = 0x00;                               // 3 byte fragmentation offset for fragmented images
    RtpBuf[18] = 0x00;
    RtpBuf[19] = 0x00;
    RtpBuf[20] = 0x01;                               // type
    RtpBuf[21] = 0x5e;                               // quality scale factor
    if (Chn == 0)
    {
        RtpBuf[22] = 0x06;                           // width  / 8 -> 48 pixel
        RtpBuf[23] = 0x04;                           // height / 8 -> 32 pixel
    }
    else
    {
        RtpBuf[22] = 0x08;                           // width  / 8 -> 64 pixel
        RtpBuf[23] = 0x06;                           // height / 8 -> 48 pixel
    };
    // append the JPEG scan data to the RTP buffer
    memcpy(&RtpBuf[24],Jpeg,JpegLen);
    
    m_SequenceNumber++;                              // prepare the packet counter for the next packet
    m_Timestamp += 3600;                             // fixed timestamp increment for a frame rate of 25fps

    if (m_TCPTransport) // RTP over RTSP - we send the buffer + 4 byte additional header
        send(m_Client,RtpBuf,RtpPacketSize + 4,0);
    else                // UDP - we send just the buffer by skipping the 4 byte RTP over RTSP header
        sendto(m_RtpSocket,&RtpBuf[4],RtpPacketSize,0,(SOCKADDR *) & RecvAddr,sizeof(RecvAddr));
};

void CStreamer::InitTransport(u_short aRtpPort, u_short aRtcpPort, bool TCP)
{
    sockaddr_in Server;  

    m_RtpClientPort  = aRtpPort;
    m_RtcpClientPort = aRtcpPort;
    m_TCPTransport   = TCP;

    if (!m_TCPTransport)
    {   // allocate port pairs for RTP/RTCP ports in UDP transport mode
        Server.sin_family      = AF_INET;   
        Server.sin_addr.s_addr = INADDR_ANY;   
        for (u_short P = 6970; P < 0xFFFE ; P += 2)
        {
            m_RtpSocket     = socket(AF_INET, SOCK_DGRAM, 0);                     
            Server.sin_port = htons(P);
            if (bind(m_RtpSocket,(sockaddr*)&Server,sizeof(Server)) == 0)
            {   // Rtp socket was bound successfully. Lets try to bind the consecutive Rtsp socket
                m_RtcpSocket = socket(AF_INET, SOCK_DGRAM, 0);
                Server.sin_port = htons(P + 1);
                if (bind(m_RtcpSocket,(sockaddr*)&Server,sizeof(Server)) == 0) 
                {
                    m_RtpServerPort  = P;
                    m_RtcpServerPort = P+1;
                    break; 
                }
                else
                {
                    closesocket(m_RtpSocket);
                    closesocket(m_RtcpSocket);
                };
            }
            else closesocket(m_RtpSocket);
        };
    };
};

u_short CStreamer::GetRtpServerPort()
{
    return m_RtpServerPort;
};

u_short CStreamer::GetRtcpServerPort()
{
    return m_RtcpServerPort;
};

void CStreamer::StreamImage(int StreamID)
{
    char  * Samples1[2] = { JpegScanDataCh1A, JpegScanDataCh1B };
    char  * Samples2[2] = { JpegScanDataCh2A, JpegScanDataCh2B };
    char ** JpegScanData;
    int     JpegScanDataLen;

    switch (StreamID)
    {
        case 0:
        {
            JpegScanData    = &Samples1[0]; 
            JpegScanDataLen = KJpegCh1ScanDataLen;
            break;
        };
        case 1: 
        {
            JpegScanData    = &Samples2[0]; 
            JpegScanDataLen = KJpegCh2ScanDataLen;
            break;
        };
    };

    SendRtpPacket(JpegScanData[m_SendIdx],JpegScanDataLen, StreamID);
    m_SendIdx++;
    if (m_SendIdx > 1) m_SendIdx = 0;
};


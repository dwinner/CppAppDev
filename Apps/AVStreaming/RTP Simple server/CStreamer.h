// MediaLAN 02/2013
// CRtspSession
// - JPEG packetizer and UDP/TCP based streaming

#ifndef _CStreamer_H
#define _CStreamer_H

#include <Winsock2.h>
#include <Windows.h>

class CStreamer
{
public:
    CStreamer(SOCKET aClient);
    ~CStreamer();

    void    InitTransport(u_short aRtpPort, u_short aRtcpPort, bool TCP);
    u_short GetRtpServerPort();
    u_short GetRtcpServerPort();
    void    StreamImage(int StreamID);

private:
    void    SendRtpPacket(char * Jpeg, int JpegLen, int Chn);

    SOCKET  m_RtpSocket;          // RTP socket for streaming RTP packets to client
    SOCKET  m_RtcpSocket;         // RTCP socket for sending/receiving RTCP packages

    u_short m_RtpClientPort;      // RTP receiver port on client 
    u_short m_RtcpClientPort;     // RTCP receiver port on client
    u_short m_RtpServerPort;      // RTP sender port on server 
    u_short m_RtcpServerPort;     // RTCP sender port on server

    u_short m_SequenceNumber;
    DWORD   m_Timestamp;
    int     m_SendIdx;
    bool    m_TCPTransport;
    SOCKET  m_Client;
};

#endif
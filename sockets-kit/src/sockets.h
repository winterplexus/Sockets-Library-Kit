//
//  @(#)sockets.h
//
//  sockets kit - sockets interface
//  -------------------------------
//
//  copyright 2014-2020 Code Construct Systems (CCS)
//
#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <winsock.h>

class SocketsInterface {
public:
        SocketsInterface(void);
       ~SocketsInterface(void);
        SOCKET CreateSocket(void);
        SOCKET BindSocket(SOCKET, const int);
        SOCKET ListenConnections(SOCKET, int);
        SOCKET AcceptConnections(const SOCKET);
        SOCKET ConnectServer(SOCKET, const std::string &, const int);
        int SendRequest(const SOCKET, const char *, const int);
        int ReceiveResponse(const SOCKET, char *, const int);
        void CloseSocket(SOCKET);

private:
        WSADATA wsa_data;
};

#endif // __SOCKETS_H
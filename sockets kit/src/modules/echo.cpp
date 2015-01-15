//
//  @(#)echo.cpp
//
//  sockets kit - echo service namespace
//  ------------------------------------
//
//  copyright 2014-2015 Software Constructions (SC)
//
#include <string>
#include "echo.h"

//
//  Echo service namespace.
//
namespace EchoService
{
    //
    //  Handle request.
    //
    void EchoService::HandleRequest(THREAD_ARGUMENTS *arguments)
    {
        char buffer[EchoBufferSize];
        int size;

        if ((size = arguments->ta_sockets->ReceiveRequest(arguments->ta_client_socket, buffer, EchoBufferSize)) < 0) {
            arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
            return;
        }

        if (arguments->ta_server_log_trace_mode) {
            std::string trace_message = "echo service-> received '" + std::string(buffer, size) + "' from client with size " + std::to_string(size);
            arguments->ta_server_log->WriteTraceLog(trace_message);
        }

        while (size > 1) {
            if (arguments->ta_sockets->SendRequest(arguments->ta_client_socket, buffer, size) != size) {
                arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
                return;
            }

            if (arguments->ta_server_log_trace_mode) {
                std::string trace_message = "echo service-> sent '" + std::string(buffer, size) + "' to client";
                arguments->ta_server_log->WriteTraceLog(trace_message);
            }

            if ((size = arguments->ta_sockets->ReceiveRequest(arguments->ta_client_socket, buffer, EchoBufferSize)) < 0) {
                break;
            }

            if (arguments->ta_server_log_trace_mode) {
                std::string trace_message = "echo service-> received '" + std::string(buffer, size) + "' from client with size " + std::to_string(size);
                arguments->ta_server_log->WriteTraceLog(trace_message);
            }
        }

        arguments->ta_sockets->CloseSocket(arguments->ta_client_socket);
    }
}

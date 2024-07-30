#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "httpParser.h"
#include <stdbool.h>
#include "Router.h"

#define PORT 9090




int main() {
    int counter = 0;
    bool run = true;

    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);

    SOCKET s  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(PORT);

    bind(s, (struct sockaddr*) &addr,  sizeof(addr));
    //printf("listening\n");
    listen(s,10);
    //SOCKET client = accept(s, 0,0 );
    SOCKET client;

    // u_long mode = 1;
   
    int timeout = 100; // Timeout in milliseconds

    char request[2048] = {0};
    while(run == true){
        printf("listening\n");
        client = accept(s, (struct sockaddr*)&client_addr,&client_addr_size );
        // printf("client\n");
        //  ioctlsocket(client, FIONBIO, &mode);

        if(client == INVALID_SOCKET) {
            printf("invalid socket");
            shutdown(client, SD_SEND);
            closesocket(client);

            continue;
        }
        

       
       
        setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        int recv_result = recv(client, request , 2048, 0);
        // printf("recieved\n");
        if(recv_result == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if(error == WSAEWOULDBLOCK || error == WSAETIMEDOUT) {
                printf("haha chromium blocking\n");
            }else {
                printf("Receive failed with error: %d\n", error);
            }
           
            shutdown(client, SD_SEND);
            closesocket(client);
            continue;

        } else if (recv_result == 0) {
            printf("Client closed the connection.\n");
            shutdown(client, SD_SEND);
            closesocket(client);
            continue;
        }
        
        //printf("%s", request);   
        // printf("counter: %d\n", counter);        
        // counter +=1;

        if(memcmp(request , "GET / ",6) ==0) {
        
            
            SendFile("headers.txt", client);
            SendFile("src/index.html", client);
            //printf("%s", request);   
        // }else if(memcmp(request , "GET /favicon.ico",16) ==0){
        //     SendFile("headers.txt", client);
        //     SendFile("src/favicon.ico", client);
        }else {
            SendFile("404headers.txt", client);
            SendFile("src/404.html", client);
        }
        
        
        
        shutdown(client, SD_SEND);
        //printf("closing connection\n");
        closesocket(client);
        //printf("connection closed\n");
        //printf("closed\n");
       
            
    }
    // printf("counter: %d\n", counter);        
    //printf("run: %u ", run);
    closesocket(s);
    return 0;
    

    

}
// void map(char* path, void* func) {
//     map("/", &home);
// }
// void home(){};
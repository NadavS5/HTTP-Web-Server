#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "httpParser.h"
#include <stdbool.h>
#include "Router.h"
#define PORT 9090




int main() {

    bool run = true;

    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,2), &wsadata);

    SOCKET s  = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(PORT);

    bind(s, (struct sockaddr*) &addr,  sizeof(addr));
    printf("listening\n");
    listen(s,10);
    SOCKET client = accept(s, 0,0 );


    char request[256] = {0};
    while(run == true){
        ///printf("Connected\n");
        recv(client, request , 256, 0);
        // printf("%u\n", getMethod(request));    


        if(memcmp(request , "GET / ",6) ==0) {
        
            
            SendFile("headers.txt", client);
            SendFile("src/index.html", client);

        }
        
        //printf("%s\n", request);
        
        shutdown(client, SD_SEND);
        listen(s,10);
        client = accept(s, 0,0 );
        
    }
    //printf("run: %u ", run);
    closesocket(s);

    

    

}




// void map(char* path, void* func) {
//     map("/", &home);
// }
// void home(){};
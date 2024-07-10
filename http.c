#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include "FileLib.h"
#include <stdbool.h>
#include "Router.h"
#define PORT 9090
// #define bool UINT8
// #define true 1
// #define false 0



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
        
        if(memcmp(request , "GET / ",6) ==0) {
        
            
            FILE* f = fopen("src/index.html", "r");
            char buffer[512]  = {0};

            long int file_len;
            fseek(f, 0, SEEK_END);
            file_len = ftell(f);
            fseek(f,0,SEEK_SET );
            
            fread(buffer ,1, file_len ,f);
            
            fclose(f);

            //printf("file length: %d \n",file_len);
            send(client , buffer, file_len ,0);
        

        }
        
        //printf("%s\n", request);
        
        listen(s,10);
        client = accept(s, 0,0 );
        
    }
    //printf("run: %u ", run);
    closesocket(s);



    

}
char* FileRead(FILE* f, UINT64* FileLenLP ) {
    
    UINT64 file_len;
    fseek(f, 0, SEEK_END);
    file_len = ftell(f);
    fseek(f,0,SEEK_SET );
    
    char* fileData =  malloc(file_len);
    fread(fileData ,1, file_len ,f);
    fclose(f);
}

void SendFile(char* path, SOCKET client) {
    UINT64 file_len;
    FILE* f = fopen(path, "r");
    char* data = FileRead(f, &file_len);
    send(client,data, file_len, 0);


}


void SendError404() {

}
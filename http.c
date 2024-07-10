#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "httpParser.h"
#include <stdbool.h>
//#include "Router.h"
#define PORT 9090


char* FileRead(FILE* f, UINT32* FileLenOut ) {
    
    UINT32 file_len;
    fseek(f, 0, SEEK_END);
    file_len = ftell(f);
    fseek(f,0,SEEK_SET );

    printf("file size: %u bytes\n",file_len );

    *FileLenOut = file_len;

    char* fileData =  malloc(file_len);
    fread(fileData ,1, file_len ,f);
    fclose(f);
    return fileData;
}

void SendFile(char* path, SOCKET client) {
    UINT32 file_len;
    FILE* f = fopen(path, "r");
    printf("opened: %s\n", path);
    char* data = FileRead(f, &file_len);

    printf("sending %u bytes\n", file_len-10);
    send(client,data, file_len, 0);
    free(data);

}

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
        
            
            //FILE* f = fopen("src/index.html", "r");
            // char buffer[512]  = {0};

            // long int file_len;
            // fseek(f, 0, SEEK_END);
            // file_len = ftell(f);
            // fseek(f,0,SEEK_SET );
            
            // fread(buffer ,1, file_len ,f);
            
            // fclose(f);

            // //printf("file length: %d \n",file_len);
            // send(client , buffer, file_len ,0);
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




void map(char* path, void* func) {
    
}
void home(){};
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>


char* cachedFiles() {

}

void CacheFile(char* file) {

}

void map(char* path, void* func) {
    
}

void getFileByPath(char * request)  {
    
}

char* FileRead(FILE* f, UINT32* FileLenOut ) {
    
    UINT32 file_len;
    fseek(f, 0, SEEK_END);
    file_len = ftell(f);
    fseek(f,0,SEEK_SET );

    

    *FileLenOut = file_len;

    char* fileData =  malloc(file_len);
    fread(fileData ,1, file_len ,f);
    fclose(f);
    return fileData;
}

void SendFile(char* path, SOCKET client) {
    UINT32 file_len;
    FILE* f = fopen(path, "rb");
    //printf("opened: %s length: %u\n" , path , file_len);
    char* data = FileRead(f, &file_len);

    // printf("file length: %u\n",file_len );
    UINT32 code = send(client,data, file_len, 0);
    printf("code is: %u, file len is: %u\n",WSAGetLastError(),file_len);
    free(data);

}
#include <stdlib.h>
#include <stdio.h>
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

    printf("file size: %u bytes\n",file_len );

    *FileLenOut = file_len;

    char* fileData =  malloc(file_len);
    fread(fileData ,1, file_len ,f);
    fclose(f);
    return fileData;
}

void SendFile(char* path, SOCKET client) {
    UINT32 file_len;
    FILE* f = fopen(path, "rb");
    printf("opened: %s\n", path);
    char* data = FileRead(f, &file_len);

    printf("sending %u bytes\n", file_len);
    send(client,data, file_len, 0);
    free(data);

}
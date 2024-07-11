#include <winsock2.h>
#include <stdlib.h>       
#include <stdio.h>





#ifndef Router   
#define Router

//route is the http route and function is what to do when this route get called
void map(char* route, void* func);

// get the function that is assigned to the route
void* GetFunctionByRoute(char* route ); 


void SendFile(char* path, SOCKET client);
char* FileRead(FILE* f, UINT32* FileLenOut );

#endif
#ifndef FileLib   
#define FileLib   


char* getPath(char* request);
char* getMethod(char* request);

#endif

#ifndef HttpMethod

typedef enum{
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    PATCH,
    TRACE,
    OPTIONS

} HttpMethod ;

#endif
#ifndef HttpMethod

typedef enum{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    TRACE,
    OPTIONS,
    

} HttpMethod ;
#endif

#ifndef httpParser   
#define httpParser   


char* getPath(char* request);
HttpMethod getMethod(char* request);

#endif


#include <stdbool.h>
#include <string.h>
#include <stdio.h>


typedef enum{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    TRACE,
    OPTIONS,
    

} HttpMethod ;

char* getPath(char* request) {

}
HttpMethod getMethod(char* request) {

    
    char method[7];
    strncpy(method, request, 7);
    if(strncmp(method, "GET", 3)==0) {
        return GET;
    }
    if(strncmp(method, "POST", 4)==0) {
        return POST;
    }
    if(strncmp(method, "PUT", 3)==0) {
        return PUT;
    }
    


    return GET ;


}

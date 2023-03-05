#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char *protocol;
    char *host;
    char *pathname;
    char *search;
    char *hash;
    int port;
} Location;

Location *parse_url(char *url);

int main()
{
    char url[500] = "";
    fgets(url, 500, stdin); // Get url string
    Location *l = parse_url(url);
    printf("Location {\n  protocol: %s,\n  host: %s,\n", l->protocol, l->host);
    if (l->port)
        printf("  port: %d,\n", l->port);
    else
        printf("  port: (default),\n");
    printf("  pathname: /%s,\n  search: ?%s,\n  hash: #%s,\n}\n", l->pathname, l->search, l->hash);
    return 0;
}

Location *parse_url(char *url)
{
    static Location location;
    char pathname[100]="/";     //為什麼這三行刪了，就會有segamentation?
    char search[100]="?";
    char hash[100]="#";
    char *token, *token2;
    
    // protocol
    token = strtok(url, ":");
    location.protocol = token;

    // host, port
    token = strtok(NULL, ":");
    if( token != NULL ){    // port 存在    //這要怎麼判斷比較好？  
        token2 = strtok(NULL, "\n");
        if( token2 != NULL){
            token = token2;
        }
        location.host = token;
        printf( "host=%s (has port)\n", location.host );

        token = strtok(NULL, "/");
        // printf("this: token=%s\n", token);
        if(token != NULL){
            int len = strlen(token);    // 將char 轉成 int
            location.port = 0;
            for(int i=0, l=len-1; i<len; i++, l--){
                location.port += (token[i]-'0') * pow(10,l);
            }
        }
        else{
            location.port = 0;
        }
        // printf( "port=%d\n", location.port );
    }
    else{    // port 不存在
        if( strcmp(location.protocol, "http")==0 || strcmp(location.protocol, "https")==0 ){   
            location.port = 443;
        }
        else{
            location.port = 0;
        }
        token = strtok(NULL, "/");
        location.host = token;
        // printf( "host=%s (no port)\n", location.host );
    }

    token = strtok(NULL, "?");
    if(token != NULL){
        location.pathname = token;
    }
    else{
        location.pathname = "";
    }
    

    token = strtok(NULL, "#");
    if(token != NULL){
        location.search = token;
    }
    else{
        location.search = "";
    }

    token = strtok(NULL, "\n");
    if(token != NULL){
        location.hash = token;
    }
    else{
        location.hash = "";
    }

    for( int i=2; i<strlen(location.host); i++){
        location.host[i-2] = location.host[i];
    }
    return &location;
}
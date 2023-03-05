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

Location *parse_url(char *url){
    Location *l = (Location*)malloc(sizeof(Location));
    char *str;
    int i, url_i = -1;

    //---protocol
    str = (char*)malloc(10000 * sizeof(char));
    i = 0;
    while (url[++url_i] != ':' && url[url_i] != '\n')  str[i++] = url[url_i];
    str[i] = '\0';
    l->protocol = str;
    url_i += 2;

    //---host
    str = (char*)malloc(10000 * sizeof(char));
    i = 0;
    if(url[url_i] == '/')
        while (url[++url_i] != ':' && url[url_i] != '/' && url[url_i] != '?' && url[url_i] != '#' && url[url_i] != '\n')  str[i++] = url[url_i];
    str[i] = '\0';
    l->host = str;

    //---port
    int total = 0;
    if(url[url_i] == ':')
        while (url[++url_i] != '/' && url[url_i] != '?' && url[url_i] != '#' && url[url_i] != '\n')  total = total * 10 + url[url_i] - '0';
    l->port = total;
    
    //---pathname
    str = (char*)malloc(10000 * sizeof(char));
    i=0;
    if(url[url_i] == '/')
        while (url[++url_i] != '?' && url[url_i] != '#' && url[url_i] != '\n')  str[i++] = url[url_i];
    str[i] = '\0';
    l->pathname = str;

    //---search
    str = (char*)malloc(10000 * sizeof(char));
    i=0;
    if(url[url_i] == '?')
        while (url[++url_i] != '#' && url[url_i] != '\n')  str[i++] = url[url_i];
    str[i] = '\0';
    l->search = str;

    //---hash
    str = (char*)malloc(10000 * sizeof(char));
    i=0;
    if(url[url_i] == '#')
        while (url[++url_i] != '\n')  str[i++] = url[url_i];
    str[i] = '\0';
    l->hash = str;

    return l;
}
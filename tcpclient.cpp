#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

int main (){

    int sockfd, portno, n;
    portno = 5400;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if (server == NULL){
        cerr << "Failed to create socket";
        return -1;
    }

    server=gethostbyname("127.0.0.1");

    if (server == NULL){
        cerr << "Error no such host found";
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        cerr <<"ERROR connecting";
    
    bzero(buffer,256);
    
    string msg = "This is a message";
    strcpy(buffer, msg.c_str()); 
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0) 
         cerr << "ERROR writing to socket";
    
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);

    if (n < 0) 
         cerr << "ERROR reading to socket";
    
    printf("Client sent: %s\n", buffer);
    
    close(sockfd);
    return 0;
}
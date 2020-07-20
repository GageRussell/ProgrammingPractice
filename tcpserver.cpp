#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main(){
    int listening, newsockfd, portno;
    portno = 5400;
    char buffer[256];
    socklen_t clientlen;
    struct sockaddr_in serv_addr, client_addr;
    int n;
    //create a socket
    listening = socket(AF_INET,SOCK_STREAM, 0);
    
    if (listening == -1){
        cerr << "Failed to create socket";
        return -1;
    }
    //clear the address strcuture
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    //INADDR_ANY auto fills with current host IP
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    cout << serv_addr.sin_addr.s_addr << endl;
    //htons converts short int for port
    serv_addr.sin_port = htons(portno);

    //bind the scoket to IP and Port
    if(bind(listening, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        cerr << "Failed to bind socket";

    //Mark the socket for listening
    listen(listening,5);
    //Accept a call
    clientlen = sizeof(client_addr);
    newsockfd = accept(listening, (struct sockaddr *) &client_addr, &clientlen);
    if (newsockfd < 0)
        cerr << "Failed to accept";
    
    cout << "Server: recv connection from " << inet_ntoa(client_addr.sin_addr) << " " << "portno: " << ntohs(client_addr.sin_port) << endl;
    //send message to client
    send(newsockfd, "Hey there!\n",10,0);
    bzero(buffer, 256);
    //while recv display messages, echo messages
    
    n = read(newsockfd, buffer, 255);
    if (n<0) {
        cerr << "Failed to read from client";
        
    }
    cout << "Recv from client: " << buffer << endl;
    
    
    //close the socket
    close(newsockfd);
    close(listening);

    return 0;
}
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main() {

    // We need file descriptors for listening and connection.
    // The sockaddir_in is a struct holding information about
    // a server address.
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    // We require a buffer to hold information sent.
    char   sendBuff[256];
    time_t ticks; 

    // The call to socket() returns a file descriptor.
    // AF_INET means we are using IP, and SOCK_STREAM means
    // this is a streaming socket.
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    // We blank serv_addr and the buffer before setting/getting
    // their values.
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff,   '0', sizeof(sendBuff)); 

    // sin_family is whether to use IP
    // sin_addr is the address
    // sin_port is the port to use
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(5000); 

    // Once we create the socket and load the server address info,
    // we must call bind() to bind the socket to the address, then
    // listen() to listen for incoming data.
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    listen(listenfd, 10); 

    while(1) {

        // The call to accept() accepts a message from the socket
        // which is listening.
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 


        // ticks holds seconds; it's used for printing out current
        // time. This is what we send back to the client.
        ticks = time(NULL);

        // We write out the information to the client; the snprintf()
        // statement prints the time into sendBuff, then write sends
        // it out through the connection file descriptor.
        snprintf(sendBuff, sizeof(sendBuff), 
          "[%.24s] Hello!\r\n", 
          ctime(&ticks)
        );
        write(connfd, sendBuff, strlen(sendBuff)); 

        // We print a message to stdout to indicate we received a
        // request.
        printf(
          "[%.24s] Received request from client!\n",
          ctime(&ticks)
        );
        fflush(stdout);

        // Once finished accepting the message, we close the listen
        // file descriptor.
        close(connfd);

        sleep(1);

    }

}

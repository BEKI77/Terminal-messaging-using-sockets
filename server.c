#include "constants.h"

int main(int argc, char* argv[]){
    int port = 2000;
    char* ip = "";
    
    // File descriptor
    int serverFD = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in* serverAddress = createIpv4Address(ip, port);

    int result = bind(serverFD, (const struct sockaddr*)serverAddress, sizeof(*serverAddress));

    if(result){
        perror("Bind error");
        return -1;
    }

    printf("socket was bound successfully\n");

    int listenResult = listen(serverFD,10);

    if (listenResult){
        perror("Listen error");
        return -1;
    }

    struct sockaddr_in clientAddress;
    int clientAddresSize = sizeof(clientAddress);
    int clientFD = accept(serverFD, (struct sockaddr*)&clientAddress, &clientAddresSize);

    if(clientFD==-1){
        perror("Accept error");
        return -1;
    }

    char* line = NULL;
    size_t lineSize = 0;
    char buffer[1024];

    while(1){
        ssize_t receivedAmount = recv(clientFD, &buffer, 1024, 0);
        if(receivedAmount>0){
            printf("Message: %s \n", buffer);
        }else
            break;
    }
    close(clientFD);
    shutdown(serverFD, SHUT_RDWR);
     
    return 0;
}
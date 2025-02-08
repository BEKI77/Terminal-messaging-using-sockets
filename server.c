#include "constants.h"

struct AcceptedSocket{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};


void receiveAndPrintIncomingData(int socketFD){
    char buffer[1024];

    while(1){
        ssize_t receivedAmount = recv(socketFD, &buffer, 1024, 0);
        if(receivedAmount>0){
            printf("Message: %s \n", buffer);
        }else
            break;
    }

    close(socketFD);
}

void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* pSocket){
    pthread_t id;
    pthread_create(&id, NULL, (void *)receiveAndPrintIncomingData, (void *) pSocket->acceptedSocketFD);
}

struct AcceptedSocket* acceptIncomgingConnection(int serverSocketFD){

    struct sockaddr_in clientAddress;
    int clientAddresSize = sizeof(clientAddress);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr*)&clientAddress, &clientAddresSize);

    struct AcceptedSocket* acceptedSocket = malloc(sizeof(struct AcceptedSocket) );

    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD>0;

    if(!acceptedSocket->acceptedSuccessfully){
        acceptedSocket->error = clientSocketFD;
    }

    return acceptedSocket;
}

void startAcceptingIncomingConnections(int serverFD){
    while(1){
        struct AcceptedSocket* clientFD = acceptIncomgingConnection(serverFD);
        receiveAndPrintIncomingDataOnSeparateThread(clientFD);
    } 

}


int main(int argc, char* argv[]){
    if (argc<2){
        perror("Short argument: ./server port\n");
        return -1;
    }
    int port = atoi(argv[1]);
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

    startAcceptingIncomingConnections(serverFD);
    
    shutdown(serverFD, SHUT_RDWR);  
     
    return 0;
}
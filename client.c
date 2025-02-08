#include "constants.h"

void startListeningAndPrintMessagesOnNewThread(int socketFD);
void listenAndPrintMessages(int socketFD);

int main(int argc, char * argv[]) {
    // File descriptor
    if(argc<3){
        perror("Too short arguments: ./client ip-address port-number\n");
        return -1;
    }
    int clientFD = createTCPIpv4Socket();

    int port = atoi(argv[2]);
    char* ip = argv[1];
    // char str[10];
    // sprintf(str, "%d", port);
    printf("port: %d\n",port);
    printf("ip: %s\n", ip);
    if (clientFD<0){
        perror("socket error");
        return -1;
    }

    struct sockaddr_in* address = createIpv4Address(ip, port);

    int result =  connect(clientFD, (const struct sockaddr* )address, sizeof(*address));
    
    if(result){
        perror("Connect error");
        return -1;
    }

    printf("Connection was successfull \n");

    char* name =NULL;
    size_t nameSize = 0;
    printf("Enter your Name: \n");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount-1] = 0;

    char* line =NULL;
    size_t lineSize = 0;
    printf("Enter your message(type exit to end)\n");
        

    startListeningAndPrintMessagesOnNewThread(clientFD);

    char buffer[1024];


    while(1){
        
        ssize_t charCount = getline(&line, &lineSize, stdin);
        line[charCount-1] = 0;
        sprintf(buffer, "%s: %s", name, line);

        if(charCount>0){
            if(strcmp(line, "exit")==0)
                break;
            
            ssize_t amountSent = send(clientFD, buffer, strlen(buffer), 0);

        }
    }
    
    close(clientFD);

    return 0;
}

void startListeningAndPrintMessagesOnNewThread(int socketFD){

    pthread_t id;
    pthread_create(&id, NULL,(void *) listenAndPrintMessages, (void *) socketFD);
   
}

void listenAndPrintMessages(int socketFD){
    char buffer[1024];

    while(1){
        ssize_t receivedAmount = recv(socketFD, &buffer, 1024, 0);
        if(receivedAmount>0){
            buffer[receivedAmount] = 0;
            printf("Message: %s \n", buffer);

        }else
            break;
    }

    close(socketFD);
}
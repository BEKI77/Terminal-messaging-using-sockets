#include "constants.h"

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

    char* line =NULL;
    size_t lineSize = 0;
    printf("Enter your message(type exit to end)\n");

    while(1){
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if(charCount>0){
            if(strcmp(line, "exit\n")==0)
                break;
            
            ssize_t amountSent = send(clientFD, line, charCount, 0);

        }
    }
    
    close(clientFD);

    // char buffer[1024];

    // recv(s, buffer, 1024, 0 );
    
    // printf("Response: %s\n", buffer);

    return 0;
}
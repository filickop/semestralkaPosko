#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sockfdClient, nClient;
struct sockaddr_in serv_addrClient;
struct hostent* server;

char bufferC[256];

char *connection[];

int ticTacToeArrayC[3][3];

bool conEstClient(char *conn[]) {
    *connection = *conn;
    server = gethostbyname(conn[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        return false;
    }

    bzero((char*)&serv_addrClient, sizeof(serv_addrClient));
    serv_addrClient.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addrClient.sin_addr.s_addr,
            server->h_length
    );
    serv_addrClient.sin_port = htons(atoi(conn[0]));

    sockfdClient = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfdClient < 0)
    {
        perror("Error creating socket");
        return false;
    }

    if(connect(sockfdClient, (struct sockaddr*)&serv_addrClient, sizeof(serv_addrClient)) < 0)
    {
        perror("Error connecting to socket");
        return false;
    }
    return true;
}
void writeToArrayC(int symbol) {
    int x = bufferC[0] - '0';
    int y = bufferC[1] - '0';

    ticTacToeArrayC[x][y] = symbol;
}

int communicationClient() {

    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++) {
            ticTacToeArrayC[x][y] = 0;
        }
    }

    for (;;) {

        if(connection[2] == "C") {

            bzero(bufferC,256);
            nClient = read(sockfdClient, bufferC, 255);
            if (nClient < 0)
            {
                perror("Error reading from socket");
                return 6;
            }

            writeToArrayC(1);

            printf("%s\n",bufferC);
        }

        printf("Please enter a message: ");
        bzero(bufferC,256);
        fgets(bufferC, 255, stdin);

        //printf(bufferC);

        nClient = write(sockfdClient, bufferC, strlen(bufferC));
        if (nClient < 0)
        {
            perror("Error writing to socket");
            return 5;
        }

        if(connection[2] == "S") {

            bzero(bufferC, 256);
            nClient = read(sockfdClient, bufferC, 255);
            if (nClient < 0) {
                perror("Error reading from socket");
                return 6;
            }

            writeToArrayC(2);

            printf("%s\n", bufferC);
        }
        printf("POLE CLIENT\n");
        for(int x = 0; x < 3; x++){
            for(int y = 0; y < 3; y++) {
                printf("%d", ticTacToeArrayC[x][y]);
            }
            printf("\n");
        }
        printf("POLE CLIENT END\n");
        //close(sockfdClient);
    }
}


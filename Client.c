#include "Client.h"

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

void writeArrayToScreen() {
    printf("POLE CLIENT\n");
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++) {
            printf("%d", ticTacToeArrayC[x][y]);
        }
        printf("\n");
    }
    printf("POLE CLIENT END\n");
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

            if (bufferC[2] == '3') {
                writeArrayToScreen();
                printf("Nastala remiza\n");
                break;
            }
            else if(bufferC[2] != '0') {
                writeArrayToScreen();
                printf("Vyhrava %d\n", (bufferC[2] - '0'));
                break;
            }
            writeToArrayC(1);
            writeArrayToScreen();
            //printf("%s\n",bufferC);
        }
        int xTemp;
        int yTemp;
        do{
            printf("Please enter a message: ");
            bzero(bufferC,256);
            fgets(bufferC, 255, stdin);

            xTemp = bufferC[0] - '0';
            yTemp = bufferC[1] - '0';

        } while(ticTacToeArrayC[xTemp][yTemp] != 0);


        //printf(bufferC);

        nClient = write(sockfdClient, bufferC, strlen(bufferC));
        if (nClient < 0)
        {
            perror("Error writing to socket");
            return 5;
        }
        if(connection[2] == "S") {
            writeToArrayC(1);
        }
        else if(connection[2] == "C") {
            writeToArrayC(2);
        }
        writeArrayToScreen();

        if(connection[2] == "S") {

            bzero(bufferC, 256);
            nClient = read(sockfdClient, bufferC, 255);
            if (nClient < 0) {
                perror("Error reading from socket");
                return 6;
            }

            if (bufferC[2] == '3') {
                writeArrayToScreen();
                printf("Nastala remiza\n");
                break;
            }
            else if(bufferC[2] != '0') {
                writeArrayToScreen();
                printf("Vyhrava %d\n", (bufferC[2] - '0'));
                break;
            }
            writeToArrayC(2);
            writeArrayToScreen();
            //printf("%s\n", bufferC);
        }
    }
    close(sockfdClient);
}


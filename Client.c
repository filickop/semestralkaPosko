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
            if(ticTacToeArrayC[x][y] == 1) {
                printf("X");
            }
            else if(ticTacToeArrayC[x][y] == 2) {
                printf("O");
            }
            else {
                printf("-");
            }

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
                writeToArrayC(1);
                writeArrayToScreen();
                printf("Nastala remiza\n");

                break;
            }
            else if(bufferC[2] != '0') {
                writeToArrayC(bufferC[2] - '0');
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
        bool isCorrect = false;
        do{
            printf("Please enter a message: ");
            bzero(bufferC,256);
            fgets(bufferC, 255, stdin);

            xTemp = bufferC[0] - '0';
            yTemp = bufferC[1] - '0';

            if(xTemp < 0 || xTemp > 2 || yTemp < 0 || yTemp > 2) {
                isCorrect = false;
            }
            else {
                isCorrect = true;
            }

        } while(ticTacToeArrayC[xTemp][yTemp] != 0 && isCorrect);


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
                writeToArrayC(1);
                writeArrayToScreen();
                printf("Nastala remiza\n");

                break;
            }
            else if(bufferC[2] != '0') {
                writeToArrayC(bufferC[2] - '0');
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


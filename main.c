#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Server.c"
#include "Client.c"
#include <pthread.h>

char *connection[] = {"10907", "localhost", ""};
bool connectionSuccesfullC = false;

void * spustiServer(void * data) {

    char str[20];
    bool connectionSuccessfull = false;
    do{
        int port = (rand() % 20000) + 1025;

        sprintf(str,"%d", port );

        connection[0] = str;
        printf("cislo portu servera: %s\n", connection[0]);
        printf("\n");
        connectionSuccessfull = connEst(connection);
    } while(!connectionSuccessfull);

    comunication();

}

void * spustiClient(void * data) {
    for (int i = 0; i < 5; ++i) {
        connectionSuccesfullC = conEstClient(connection);
        if (connectionSuccesfullC) {
            printf("pripojenie uspesne\n");
            communicationClient();
            break;
        }
        sleep(1);
    }
}

int main(int argc, char *argv[]) {

    srand(time(NULL));


    char *bufff[10];
    do {
        printf("napis cislo pre zvolenie postupu:\n");
        printf("1 - pre zvolenie servera\n");
        printf("2 - pre zvolenie klienta\n");
        printf( "3 - pre okamzite ukoncenie programu\n");
        bzero(bufff,10);
        fgets( bufff,10, stdin);
        if (atoi(bufff) == 1 || atoi(bufff) == 2) {
            break;
        }
        else if (atoi(bufff) == 3) {
            return 0;
        }
        printf("zadali ste nespravne cislo pre zvolenie postupu alebo nespravny format\n");
    } while (true);

    if(atoi(bufff) == 1) {
        connection[2] = "S";

        pthread_t server;
        pthread_t client;

        pthread_create(&server,NULL, spustiServer, NULL);
        pthread_create(&client, NULL, spustiClient, NULL);

        pthread_join(server, NULL);
        pthread_join(client, NULL);
    }
    else if (atoi(bufff) == 2) {
        while (!connectionSuccesfullC) {
            do {
                printf("zadajte cislo portu servera:\n");
                bzero(bufff,10);
                fgets( bufff,10, stdin);
                if (atoi(bufff) > 1025 && atoi(bufff) < 21025) {
                    break;
                }
                printf("zadali ste nespravne cislo portu alebo nespravny format\n");
            } while (true);
            connection[0] = bufff;
            connection[2] = "C";
            pthread_t client;
            pthread_create(&client, NULL, spustiClient, NULL);
            pthread_join(client, NULL);
        }
    }


    return 0;
}

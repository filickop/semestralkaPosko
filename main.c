#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Server.c"
#include "Client.c"
#include <pthread.h>
char *connection[] = {"1030", "localhost", ""};

void * spustiServer(void * data) {

    char str[20];
    bool connectionSuccessfull = false;
    do{
        int port = (rand() % 20000) + 1025;

        sprintf(str,"%d", port );

        connection[0] = str;
        printf(connection[0]);
        printf("\n");
        connectionSuccessfull = connEst(connection);
    } while(!connectionSuccessfull);

    comunication();

}

void * spustiClient(void * data) {
    bool connectionSuccessfull = false;

    do{
        sleep(1);
        connectionSuccessfull = conEstClient(connection);
    } while(!connectionSuccessfull);

    printf("pripojenie uspesne\n");
    communicationClient();

}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    if(false) {
        connection[2] = "S";

        pthread_t server;
        pthread_t client;

        pthread_create(&server,NULL, spustiServer, NULL);
        pthread_create(&client, NULL, spustiClient, NULL);

        pthread_join(server, NULL);
        pthread_join(client, NULL);
    }
    else if (true) {
        connection[2] = "C";
        pthread_t client;
        pthread_create(&client, NULL, spustiClient, NULL);
        pthread_join(client, NULL);
    }


    return 0;
}

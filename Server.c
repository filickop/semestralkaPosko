#include "Server.h"

bool connEst(char *conn[]) {

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(conn[0]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return false;
    }

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return false;
    }

    listen(sockfd, 2);

    /*for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ticTacToeArrayS[i][j] = 0;
        }
    }*/
    return true;
}
int checker(int ticTacToeArrayS[3][3]) {
    for(int i = 0; i < 3; i++) {
        if(ticTacToeArrayS[0][i] == ticTacToeArrayS[1][i] && ticTacToeArrayS[0][i] == ticTacToeArrayS[2][i] && ticTacToeArrayS[0][i] != 0) {
            return ticTacToeArrayS[0][i];
        }
        if(ticTacToeArrayS[i][0] == ticTacToeArrayS[i][1] && ticTacToeArrayS[i][0] == ticTacToeArrayS[i][2] && ticTacToeArrayS[i][0] != 0) {
            return ticTacToeArrayS[i][0];
        }
    }
    if(ticTacToeArrayS[0][0] == ticTacToeArrayS[1][1] && ticTacToeArrayS[0][0] == ticTacToeArrayS[2][2] && ticTacToeArrayS[0][0] != 0) {
        return ticTacToeArrayS[0][0];
    }
    if(ticTacToeArrayS[0][2] == ticTacToeArrayS[1][1] && ticTacToeArrayS[0][2] == ticTacToeArrayS[2][0] && ticTacToeArrayS[0][2] != 0) {
        return ticTacToeArrayS[0][2];
    }
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ticTacToeArrayS[i][j] != 0) {
                count++;
            }
        }
    }
    if (count == 9) {
        return 3;
    }
    return 0;
}

void * fPlay1(void * data) {
    HPOLE * pole = data;

    while (true) {
        pthread_mutex_lock(pole->mutex);
        pthread_cond_wait(pole->play1, pole->mutex);

        n = read(player1, buffer, 255);

        int x = buffer[0]-'0';
        int y = buffer[1]-'0';
        pole->ticTacToeArrayS[x][y] = 1;
        //ticTacToeArrayS[x][y] = 1;
        //player1Play = false;

        buffer[2] = checker(pole->ticTacToeArrayS) + '0';
        n = write(player2, buffer, strlen(buffer)+1);

        if(checker(pole->ticTacToeArrayS) != 0) {
            n = write(player2, buffer, strlen(buffer)+1);
            n = write(player1, buffer, strlen(buffer)+1);
            break;
        }

        pthread_cond_signal(pole->play2);
        pthread_mutex_unlock(pole->mutex);
    }

}

void * fPlay2(void * data) {
    HPOLE * pole = data;
    while (true) {
        pthread_mutex_lock(pole->mutex);
        pthread_cond_wait(pole->play2, pole->mutex);

        n = read(player2, buffer, 255);

        int x = buffer[0]-'0';
        int y = buffer[1]-'0';
        pole->ticTacToeArrayS[x][y] = 2;
        //ticTacToeArrayS[x][y] = 2;
        //player1Play = true;

        buffer[2] = checker(pole->ticTacToeArrayS) + '0';
        n = write(player1, buffer, strlen(buffer)+1);

        if(checker(pole->ticTacToeArrayS) != 0) {
            n = write(player2, buffer, strlen(buffer)+1);
            n = write(player1, buffer, strlen(buffer)+1);
            break;
        }

        pthread_cond_signal(pole->play1);
        pthread_mutex_unlock(pole->mutex);
    }
}

void comunication() {
    cli_len = sizeof(cli_addr);
    player1 = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    player2 = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (player1 < 0 || player2 < 0)
    {
        perror("ERROR on accept");
        //return 3;
    }
    int tempTicTacToeArrayS[3][3];
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++) {
            tempTicTacToeArrayS[x][y] = 0;
        }
    }

    pthread_t player1T, player2T;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_t play1, play2;
    pthread_cond_init(&play1, NULL);
    pthread_cond_init(&play2, NULL);




    HPOLE ticTacToe  = {&mutex, &play1, &play2, &tempTicTacToeArrayS};
    pthread_create(&player1T, NULL, fPlay1, &ticTacToe);
    pthread_create(&player2T, NULL, fPlay2, &ticTacToe);
    pthread_join(player1T,NULL);
    pthread_join(player2T, NULL);


    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&play1);
    pthread_cond_destroy(&play2);


    close(player1);
    close(player2);
    close(sockfd);
}



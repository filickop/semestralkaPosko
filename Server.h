//
// Created by namer on 5. 1. 2022.
//

#ifndef SEMESTRALKATICTACTOE_SERVER_H
#define SEMESTRALKATICTACTOE_SERVER_H

bool connectionSuccesful = false;

int sockfd, player1, player2;
socklen_t cli_len;
struct sockaddr_in serv_addr, cli_addr;
int n;
char buffer[256];

int ticTacToeArrayS[3][3];

bool connEst(char *conn[]);
int checker();

void comunication();

#endif //SEMESTRALKATICTACTOE_SERVER_H

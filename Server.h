#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

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

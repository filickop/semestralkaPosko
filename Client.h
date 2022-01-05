//
// Created by namer on 5. 1. 2022.
//

#ifndef SEMESTRALKATICTACTOE_CLIENT_H
#define SEMESTRALKATICTACTOE_CLIENT_H


int sockfdClient, nClient;
struct sockaddr_in serv_addrClient;
struct hostent* server;

char bufferC[256];

char *connection[];

int ticTacToeArrayC[3][3];

bool conEstClient(char *conn[]);
void writeToArrayC(int symbol);

void writeArrayToScreen();

int communicationClient();

#endif //SEMESTRALKATICTACTOE_CLIENT_H

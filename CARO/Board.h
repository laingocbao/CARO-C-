#ifndef BOARD_H
#define BOARD_H
#include "Node.h"
#include <stdio.h>
#include <iostream>
#include <list>
#include <limits>

using namespace std;

class Board
{
	Node *root;
public:
	Board();
	Board(Node *root);
	~Board();

	void setRoot(Node *root);
	Node *getRoot();
	void displayBoard();
	void setCell(int i, int j, char cell);
	void getMovePlayer(char chessman);
	void getMoveComputer(char chessman);
	int max(int a, int b);
	int min(int a, int b);
	int abp_max(Node *state, char chessman, int depth, int alpha, int beta);
	int abp_min(Node *state, char chessman, int depth, int alpha, int beta);
	list<Node *> generateStateCaro(Node *root, char chessman);
	list<Node *> generateStateTicTacToe(Node *root, char chessman);
	bool checkWinCaro(char chessman);
	bool checkWinTicTacToe(char chessman);
};
#endif

#pragma once

class Node
{
	char **board;
	int numberRow;
public:
	Node();
	Node(char **board);
	~Node();

	void setBoard(char **board);
	void setCell(int i, int j, char cell);
	char **getBoard();
	int getRow();
	void display();
	bool checkWinCaro(char player);
	bool checkWinTicTacToe(char player);
	long heuristicCaro(char chessman);
	long heuristicCaroForChessman(char chessman);
	int heuristicTicTacToe(char chessman);
	bool checkBoardFull();
};


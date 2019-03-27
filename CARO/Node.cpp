#include "Node.h"
#define ROWS 15
#define NUMBER_WIN 5
#define PLAYER_1 88	// mã X
#define PLAYER_2 79	// mã O
#define COMPUTER 79	// mã O
using namespace std;


Node::Node()
{
	this->board = new char*[ROWS];

	for (int i = 0; i < ROWS; i++)
	{
		this->board[i] = new char[ROWS];
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			this->board[i][j] = '_';
		}
	}

	this->numberRow = ROWS;
}

Node::Node(char **board) {
	this->board = new char*[ROWS];

	for (int i = 0; i < ROWS; i++)
	{
		this->board[i] = new char[ROWS];
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			this->board[i][j] = board[i][j];
		}
	}

	this->numberRow = ROWS;
}

Node::~Node()
{
	if (this == NULL)
		return;
	for (int i = 0; i < ROWS; i++)
	{
		delete this->board[i];
	}

	delete this->board;
}

void Node::setBoard(char **board) {
	this->board = board;
}

void Node::setCell(int i, int j, char cell) {
	this->board[i][j] = cell;
}

char **Node::getBoard() {
	return this->board;
}

int Node::getRow() {
	return numberRow;
}

void Node::display() {
	if (ROWS == 3) {
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < ROWS; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << "\n";
		}
	}
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			cout <<i << " ";
		}
		cout << '\n';
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < ROWS; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << i << " ";
			cout << "\n";
		}
	}
}

bool Node::checkWinCaro(char player) {
	// Kiểm tra thắng thua được thực hiện sau mỗi nước đi, vì vậy chỉ kiểm tra người thực hiện nước đi có thắng hay không
	for (int i = 0; i < ROWS; i++)
	{
		for (int  j = 0; j < ROWS; j++)
		{
			if (board[i][j] == player) {
				// Khi người chơi có 5 quân cờ trên một dòng, cột, đường chéo
				// Kiểm tra dòng
				if (j + 4 < ROWS && board[i][j + 1] == player && board[i][j + 2] == player
					&& board[i][j + 3] == player && board[i][j + 4] == player) {
					return true;
				}

				// Kiểm tra cột
				if (i + 4 < ROWS && board[i + 1][j] == player && board[i + 2][j] == player
					&& board[i + 3][j] == player && board[i + 4][j] == player) {
					return true;
				}

				// Kiểm tra đường chéo chính
				if (i + 4 < ROWS && j + 4 < ROWS
					&& board[i + 1][j + 1] == player && board[i + 2][j + 2] == player
					&& board[i + 3][j + 3] == player && board[i + 4][j + 4] == player) {
					return true;
				}

				// Kiểm tra đường chéo phụ
				if (i + 4 > ROWS && j - 4 >= 0
					&& board[i + 1][j - 1] == player && board[i + 2][j - 3] == player
					&& board[i + 3][j - 3] == player && board[i + 4][j - 4] == player) {
					return true;
				}

				// Người chơi thắng khi có 4 quân cờ nằm trên một dòng, cột, đường chéo và một trong hai đầu đang rỗng
				// Kiểm tra dòng
				if (j - 1 >= 0 && j + 4 < ROWS && board[i][j + 1] == player && board[i][j + 2] == player
					&& board[i][j + 3] == player
					&& board[i][j - 1] == '_' && board[i][j + 4] == '_') {
					return true;
				}

				// Kiểm tra cột
				if (i - 1 >= 0 && i + 4 < ROWS && board[i + 1][j] == player && board[i + 2][j] == player
					&& board[i + 3][j] == player
					&& board[i - 1][j] == '_' && board[i + 4][j] == '_' ) {
					return true;
				}

				// Kiểm tra đường chéo chính
				if (i - 1 >= 0 && i + 4 < ROWS && j - 1 >= 0 && j + 4 < ROWS
					&& board[i + 1][j + 1] == player && board[i + 2][j + 2] == player
					&& board[i + 3][j + 3] == player 
					&& board[i - 1][j - 1] == '_' && board[i + 4][j + 4] == '_') {
					return true;
				}

				// Kiểm tra đường chéo phụ
				if (i - 1 >= 0 && j + 1 < ROWS && i + 4 > ROWS && j - 4 >= 0 
					&& board[i + 1][j - 1] == player && board[i + 2][j - 3] == player
					&& board[i + 3][j - 3] == player 
					&& board[i - 1][j + 1] == '_' && board[i + 4][j - 4] == '_') {
					return true;
				}

			}
		}
	}
	return false;
}

bool Node::checkWinTicTacToe(char player) {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (board[i][j] == player) {
				// Xét trên dòng
				if (i + 2 < ROWS && board[i + 1][j] == player && board[i + 2][j] == player) {
					return true;
				}

				// Xét trên cột
				if (j + 2 < ROWS && board[i][j + 1] == player && board[i][j + 2] == player) {
					return true;
				}

				// Xét trên đường chéo chính
				if (i + 2 < ROWS && j + 2 < ROWS
					&& board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) {
					return true;
				}

				// Xét trên đường chéo phụ
				if (i + 2 < ROWS && j - 2 >= 0
					&& board[i + 1][j - 1] == player && board[i + 2][j - 2] == player) {
					return true;
				}
			}
			
		}
	}
	return false;
}

long Node::heuristicCaro(char chessman) {
	long total = heuristicCaroForChessman(chessman) - heuristicCaroForChessman(chessman == 'O' ? 'X' : 'O');

	/*this->display();
	cout << total << '\n';*/
	return total;
}

long Node::heuristicCaroForChessman(char chessman) {
	long total = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (board[i][j] != chessman) {
				continue;
			}

			// XÉT TRÊN CỘT
			// Open Three 100000: _XXX_
			if (i > 0 && i + 3 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman
				&& board[i -1][j] == '_' && board[i + 3][j] == '_') {
				total += 100000;
				continue;
			}

			// Capped Three 10000: 
			if (i > 0 && i + 3 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman
				&& (board[i - 1][j] == '_' || board[i + 3][j] == '_')) {
				total += 10000;
				continue;
			}

			// Consecutive Five 10000000
			if (i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman 
				&& board[i + 3][j] == chessman && board[i + 4][j] == chessman){
				total += 10000000;
				continue;
			}

			// Open Four 1000000: _XXXX_
			if (i > 0 && i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman && board[i + 3][j] == chessman
				&& board[i - 1][j] == '_' && board[i + 4][j] == '_') {
				total += 1000000;
				continue;
			}

			// Capped Four 100050
			if (i > 0 && i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman && board[i + 3][j] == chessman
				&& (board[i - 1][j] == '_' || board[i + 4][j] == '_')) {
				total += 100050;
				continue;
			}

			// Gapped Three 100000
			// _XX_X_
			if (i > 0 && i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == '_' && board[i + 3][j] == chessman
				&& board[i - 1][j] == '_' && board[i + 4][j] == '_') {
				total += 100000;
				continue;
			}
			// _X_XX_
			if (i > 0 && i + 4 < ROWS
				&& board[i + 1][j] == '_' && board[i + 2][j] == chessman && board[i + 3][j] == chessman
				&& board[i - 1][j] == '_' && board[i + 4][j] == '_') {
				total += 100000;
				continue;
			}

			// Gapped Four 100050
			// X_XXX_
			if (i + 4 < ROWS
				&& board[i + 1][j] == '_' && board[i + 2][j] == chessman 
				&& board[i + 3][j] == chessman && board[i + 4][j] == chessman) {
				total += 100050;
				continue;
			}
			// XX_XX_
			if (i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == '_'
				&& board[i + 3][j] == chessman && board[i + 4][j] == chessman) {
				total += 100050;
				continue;
			}
			// XXX_X_
			if (i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman
				&& board[i + 3][j] == '_' && board[i + 4][j] == chessman) {
				total += 100050;
				continue;
			}

			// XÉT TRÊN DÒNG
			// Open Three 100000: _XXX_
			if (j > 0 && j + 3 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == chessman
				&& board[i][j - 1] == '_' && board[i][j + 3] == '_') {
				total += 100000;
				continue;
			}

			// Capped Three 10000: 
			if (j > 0 && j + 3 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == chessman
				&& (board[i][j - 1] == '_' || board[i][j + 3] == '_')) {
				total += 10000;
				continue;
			}

			// Consecutive Five 10000000
			if (j + 4 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == chessman
				&& board[i][j + 3] == chessman && board[i][j + 4] == chessman) {
				total += 10000000;
				continue;
			}

			// Open Four 1000000: _XXXX_
			if (j > 0 && j + 4 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == chessman && board[i][j + 3] == chessman
				&& board[i][j - 1] == '_' && board[i][j + 4] == '_') {
				total += 1000000;
				continue;
			}

			// Capped Four 100050
			if (j > 0 && j + 4 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == chessman && board[i][j + 3] == chessman
				&& (board[i][j - 1] == '_' || board[i][j + 4] == '_')) {
				total += 100050;
				continue;
			}

			// Gapped Three 100000
			// _XX_X_
			if (j > 0 && j + 4 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == '_' && board[i][j + 3] == chessman
				&& board[i][j - 1] == '_' && board[i][j + 4] == '_') {
				total += 100000;
				continue;
			}
			// _X_XX_
			if (j > 0 && j + 4 < ROWS
				&& board[i][j + 1] == '_' && board[i][j + 2] == chessman && board[i][j + 3] == chessman
				&& board[i][j - 1] == '_' && board[i][j + 4] == '_') {
				total += 100000;
				continue;
			}

			// Gapped Four 100050
			// X_XXX
			if (j + 4 < ROWS
				&& board[i][j + 1] == '_' && board[i][j + 2] == chessman
				&& board[i][j + 3] == chessman && board[i][j + 4] == chessman) {
				total += 100050;
				continue;
			}
			// XX_XX
			if (i + 4 < ROWS
				&& board[i][j + 1] == chessman && board[i][j + 2] == '_'
				&& board[i][j + 3] == chessman && board[i][j + 4] == chessman) {
				total += 100050;
				continue;
			}
			// XXX_X
			if (i + 4 < ROWS
				&& board[i + 1][j] == chessman && board[i + 2][j] == chessman
				&& board[i + 3][j] == '_' && board[i + 4][j] == chessman) {
				total += 100050;
				continue;
			}


			// XÉT TRÊN ĐƯỜNG CHÉO CHÍNH
			// Open Three 100000: _XXX_
			if (i > 0 && i + 3 < ROWS && j > 0 && j + 3 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman
				&& board[i - 1][j - 1] == '_' && board[i + 3][j + 3] == '_') {
				total += 100000;
				continue;
			}

			// Capped Three 10000: 
			if (i > 0 && i + 3 < ROWS && j > 0 && j + 3 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman
				&& (board[i - 1][j - 1] == '_' || board[i + 3][j + 3] == '_')) {
				total += 10000;
				continue;
			}

			// Consecutive Five 10000000
			if (i + 4 < ROWS && i + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman
				&& board[i + 3][j + 3] == chessman && board[i + 4][j + 4] == chessman) {
				total += 10000000;
				continue;
			}

			// Open Four 1000000: _XXXX_
			if (i > 0 && i + 4 < ROWS && j > 0 && j + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman && board[i + 3][j + 3] == chessman
				&& board[i - 1][j - 1] == '_' && board[i + 4][j + 4] == '_') {
				total += 1000000;
				continue;
			}

			// Capped Four 100050
			if (i > 0 && i + 4 < ROWS && j > 0 && j + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman && board[i + 3][j + 3] == chessman
				&& (board[i - 1][j - 1] == '_' || board[i + 4][j + 4] == '_')) {
				total += 100050;
				continue;
			}

			// Gapped Three 100000
			// _XX_X_
			if (i > 0 && i + 4 < ROWS && j > 0 && j + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == '_' && board[i + 3][j + 3] == chessman
				&& board[i - 1][j - 1] == '_' && board[i + 4][j + 4] == '_') {
				total += 100000;
				continue;
			}
			// _X_XX_
			if (i > 0 && i + 4 < ROWS && j > 0 && j + 4 < ROWS
				&& board[i + 1][j + 1] == '_' && board[i + 2][j + 2] == chessman && board[i + 3][j + 3] == chessman
				&& board[i - 1][j - 1] == '_' && board[i + 4][j + 4] == '_') {
				total += 100000;
				continue;
			}

			// Gapped Four 100050
			// X_XXX_
			if (i + 4 < ROWS && j + 4 < ROWS
				&& board[i + 1][j + 1] == '_' && board[i + 2][j + 2] == chessman
				&& board[i + 3][j + 3] == chessman && board[i + 4][j + 4] == chessman) {
				total += 100050;
				continue;
			}
			// XX_XX_
			if (i + 4 < ROWS && j + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == '_'
				&& board[i + 3][j + 3] == chessman && board[i + 4][j + 4] == chessman) {
				total += 100050;
				continue;
			}
			// XXX_X_
			if (i + 4 < ROWS && j + 4 < ROWS
				&& board[i + 1][j + 1] == chessman && board[i + 2][j + 2] == chessman
				&& board[i + 3][j + 3] == '_' && board[i + 4][j + 4] == chessman) {
				total += 100050;
				continue;
			}


			// XÉT TRÊN ĐƯỜNG CHÉO PHỤ
			// Open Three 100000: _XXX_
			if (i > 0 && i + 3 < ROWS && j - 3 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == chessman
				&& board[i - 1][j + 1] == '_' && board[i + 3][j - 3] == '_') {
				total += 100000;
				continue;
			}

			// Capped Three 10000: 
			if (i > 0 && i + 3 < ROWS && j - 3 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 1] == chessman
				&& (board[i - 1][j + 1] == '_' || board[i + 3][j - 3] == '_')) {
				total += 10000;
				continue;
			}

			// Consecutive Five 10000000
			if (i + 4 < ROWS && j - 4 >= 0
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == chessman
				&& board[i + 3][j - 3] == chessman && board[i + 4][j - 4] == chessman) {
				total += 10000000;
				continue;
			}

			// Open Four 1000000: _XXXX_
			if (i > 0 && i + 4 < ROWS && j - 4 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == chessman && board[i + 3][j - 3] == chessman
				&& board[i - 1][j + 1] == '_' && board[i + 4][j - 4] == '_') {
				total += 1000000;
				continue;
			}

			// Capped Four 100050
			if (i > 0 && i + 4 < ROWS && j - 4 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == chessman && board[i + 3][j - 3] == chessman
				&& (board[i - 1][j + 1] == '_' || board[i + 4][j - 4] == '_')) {
				total += 100050;
				continue;
			}

			// Gapped Three 100000
			// _XX_X_
			if (i > 0 && i + 4 < ROWS && j - 4 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == '_' && board[i + 3][j - 3] == chessman
				&& board[i - 1][j + 1] == '_' && board[i + 4][j - 4] == '_') {
				total += 100000;
				continue;
			}
			// _X_XX_
			if (i > 0 && i + 4 < ROWS && j - 4 >= 0 && j + 1 < ROWS
				&& board[i + 1][j - 1] == '_' && board[i + 2][j - 2] == chessman && board[i + 3][j - 3] == chessman
				&& board[i - 1][j + 1] == '_' && board[i + 4][j - 4] == '_') {
				total += 100000;
				continue;
			}

			// Gapped Four 100050
			// X_XXX_
			if (i + 4 < ROWS && j - 4 >= 0
				&& board[i + 1][j - 1] == '_' && board[i + 2][j - 2] == chessman
				&& board[i + 3][j - 3] == chessman && board[i + 4][j - 4] == chessman) {
				total += 100050;
				continue;
			}
			// XX_XX_
			if (i + 4 < ROWS && j - 4 >= 0
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == '_'
				&& board[i + 3][j - 3] == chessman && board[i + 4][j - 4] == chessman) {
				total += 100050;
				continue;
			}
			// XXX_X_
			if (i + 4 < ROWS && j - 4 >= 0
				&& board[i + 1][j - 1] == chessman && board[i + 2][j - 2] == chessman
				&& board[i + 3][j - 3] == '_' && board[i + 4][j - 4] == chessman) {
				total += 100050;
				continue;
			}

		}
	}
	
	return total;
}

int Node::heuristicTicTacToe(char chessman) {
	int total = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++) {

			if (board[i][j] == chessman) {
				// XÉT TRÊN DÒNG
				// +100 for each three - in-a - row for the AI
				if (j == 0 && board[i][j + 1] == board[i][j] && board[i][j + 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - row(and empty cell) for the AI
				if (j == 0 && board[i][j + 1] == board[i][j] && board[i][j + 2] == '_') {
					total += 10;
				}

				if (j == 1 && board[i][j + 1] == board[i][j] && board[i][j - 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - row(and two empty cells) for the AI
				if (j == 0 && board[i][j + 1] == '_' && board[i][j + 2] == '_') {
					total += 100;
				}

				if (j == 1 && board[i][j + 1] == '_' && board[i][j - 1] == '_') {
					total += 100;
				}

				// XÉT TRÊN CỘT
				// +100 for each three - in-a - column for the AI
				if (i == 0 && board[i + 1][j] == board[i][j] && board[i + 2][j] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - column(and empty cell) for the AI
				if (i == 0 && board[i + 1][j] == board[i][j] && board[i + 2][j] == '_') {
					total += 10;
				}

				if (i == 1 && board[i + 1][j] == board[i][j] && board[i - 1][j] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - column(and two empty cells) for the AI
				if (i == 0 && board[i + 1][j] == '_' && board[i + 2][j] == '_') {
					total += 10;
				}

				if (i == 1 && board[i + 1][j] == '_' && board[i - 1][j] == '_') {
					total += 10;
				}

				// XÉT TRÊN ĐƯỜNG CHÉO CHÍNH
				// +100 for each three - in-a - Main diagonal for the AI
				if (i == 0 && j == 0 && board[i + 1][j + 1] == board[i][j] && board[i + 2][j + 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - Main diagonal(and empty cell) for the AI
				if (i == 0 && j == 0 && board[i + 1][j + 1] == board[i][j] && board[i + 2][j + 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j + 1] == board[i][j] && board[i - 1][j - 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - Main diagonal(and two empty cells) for the AI
				if (i == 0 && j == 0 && board[i + 1][j + 1] == '_' && board[i + 2][j + 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j + 1] == '_' && board[i - 1][j - 1] == '_') {
					total += 10;
				}

				// XÉT TRÊN ĐƯỜNG CHÉO PHỤ
				// +100 for each three - in-a - Extra diagonal for the AI
				if (i == 0 && j == 2 && board[i + 1][j - 1] == board[i][j] && board[i + 2][j - 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - Extra diagonal(and empty cell) for the AI
				if (i == 0 && j == 2 && board[i + 1][j - 1] == board[i][j] && board[i + 2][j - 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j - 1] == board[i][j] && board[i - 1][j + 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - Extra diagonal(and two empty cells) for the AI
				if (i == 0 && j == 2 && board[i + 1][j - 1] == '_' && board[i + 2][j - 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j - 1] == '_' && board[i - 1][j + 1] == '_') {
					total += 10;
				}

			}
			else if(board[i][j] != chessman && board[i][j] != '_')
			{
				// XÉT TRÊN DÒNG
				// +100 for each three - in-a - row for the other player
				if (j == 0 && board[i][j + 1] == board[i][j] && board[i][j + 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - row(and empty cell) for the other player
				if (j == 0 && board[i][j + 1] == board[i][j] && board[i][j + 2] == '_') {
					total += 10;
				}

				if (j == 1 && board[i][j + 1] == board[i][j] && board[i][j - 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - row(and two empty cells) for the other player
				if (j == 0 && board[i][j + 1] == '_' && board[i][j + 2] == '_') {
					total += 100;
				}

				if (j == 1 && board[i][j + 1] == '_' && board[i][j - 1] == '_') {
					total += 100;
				}

				// XÉT TRÊN CỘT
				// +100 for each three - in-a - column for the other player
				if (i == 0 && board[i + 1][j] == board[i][j] && board[i + 2][j] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - column(and empty cell) for the other player
				if (i == 0 && board[i + 1][j] == board[i][j] && board[i + 2][j] == '_') {
					total += 10;
				}

				if (i == 1 && board[i + 1][j] == board[i][j] && board[i - 1][j] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - column(and two empty cells) for the other player
				if (i == 0 && board[i + 1][j] == '_' && board[i + 2][j] == '_') {
					total += 10;
				}

				if (i == 1 && board[i + 1][j] == '_' && board[i - 1][j] == '_') {
					total += 10;
				}

				// XÉT TRÊN ĐƯỜNG CHÉO CHÍNH
				// +100 for each three - in-a - Main diagonal for the other player
				if (i == 0 && j == 0 && board[i + 1][j + 1] == board[i][j] && board[i + 2][j + 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - Main diagonal(and empty cell) for the other player
				if (i == 0 && j == 0 && board[i + 1][j + 1] == board[i][j] && board[i + 2][j + 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j + 1] == board[i][j] && board[i - 1][j - 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - Main diagonal(and two empty cells) for the other player
				if (i == 0 && j == 0 && board[i + 1][j + 1] == '_' && board[i + 2][j + 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j + 1] == '_' && board[i - 1][j - 1] == '_') {
					total += 10;
				}

				// XÉT TRÊN ĐƯỜNG CHÉO PHỤ
				// +100 for each three - in-a - Extra diagonal for the other player
				if (i == 0 && j == 2 && board[i + 1][j - 1] == board[i][j] && board[i + 2][j - 2] == board[i][j]) {
					total += 100;
				}

				// + 10 for each two - in-a - Extra diagonal(and empty cell) for the other player
				if (i == 0 && j == 2 && board[i + 1][j - 1] == board[i][j] && board[i + 2][j - 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j - 1] == board[i][j] && board[i - 1][j + 1] == '_') {
					total += 10;
				}

				// + 1 for each one - in-a - Extra diagonal(and two empty cells) for the other player
				if (i == 0 && j == 2 && board[i + 1][j - 1] == '_' && board[i + 2][j - 2] == '_') {
					total += 10;
				}

				if (i == 1 && j == 1 && board[i + 1][j - 1] == '_' && board[i - 1][j + 1] == '_') {
					total += 10;
				}
			}
		}
	}

	return total;
}


bool Node::checkBoardFull() {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (board[i][j] == '_') {
				return true;
			}

		}
	}
	return false;
}
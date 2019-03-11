#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	this->root = new Node();
}

Board::Board(Node *root) {
	this->root = new Node(root->getBoard());
}

Board::~Board()
{
	if (this->root == NULL)
		return;
	delete this->root;
}

void Board::setRoot(Node *root) {
	this->root = root;
}

Node *Board::getRoot() {
	return this->root;
}

void Board::displayBoard() {
	this->root->display();
}

void Board::setCell(int i, int j, char cell) {
	this->root->setCell(i, j, cell);
}

void Board::getMovePlayer(char chessman) {
	int x, y;
	cout << "Ban nhap vao toa do:  ";
	cin >> x;
	cin >> y;
	this->root->setCell(x, y, chessman);
}

void Board::getMoveComputer() {
	int numberRow = this->root->getRow();
	int alpha_max = numeric_limits<int>::min();
	Node *bestState = root;

	if (numberRow == 3) {
		list<Node *> states = generateStateTicTacToe(root, 'O');

		//cout << "Cac trang thai duoc tao ra\n";
		for (std::list<Node *>::iterator s = states.begin(); s != states.end(); s++) {
			int result = abp_max((*s), 'X', 3, -numeric_limits<int>::max(), -numeric_limits<int>::min());
			/*(*s)->display();
			cout << result << '\n';*/
			if (alpha_max < result) {
				alpha_max = result;
				bestState = *s;
			}
		}

		this->root->setBoard(bestState->getBoard());
	}
	else
	{
		list<Node *> states = generateStateCaro(root, 'O');

		//cout << "Cac trang thai duoc tao ra\n";
		for (std::list<Node *>::iterator s = states.begin(); s != states.end(); s++) {
			int result = abp_max((*s), 'X', 2, -numeric_limits<int>::max(), -numeric_limits<int>::min());
			/*(*s)->display();
			cout << result << '\n';*/
			if (alpha_max < result) {
				alpha_max = result;
				bestState = *s;
			}
		}

		this->root->setBoard(bestState->getBoard());
	}
}

int Board::max(int a, int b) {
	return a > b ? a : b;
}

int Board::min(int a, int b) {
	return a > b ? b : a;
}

// Sử dụng trong trường hợp: máy tính sẽ là MAX, người chơi là MIN
int Board::abp_max(Node *state, char chessman, int depth, int alpha, int beta) {
	if (state->getRow() == 3) {
		// Nếu chiều sâu bằng 0
		if (depth == 0) {
			return state->heuristicTicTacToe(chessman);
		}

		// Tạo ra các con của state
		list<Node *> stateList = generateStateTicTacToe(state, chessman);

		// Nếu state không thể phát sinh thêm bất kỳ state nào nữa
		if (stateList.empty()) {
			return state->heuristicTicTacToe(chessman);
		}

		for (std::list<Node *>::iterator s = stateList.begin(); s != stateList.end(); s++) {
			int alpha1 = beta * -1;
			int beta1 = alpha * -1;
			alpha = max(alpha, -abp_max((*s), chessman == 'O' ? 'X' : 'O', depth - 1, alpha1, beta1));			
			if (alpha > beta) {
				return alpha;
			}
		}
		return alpha;
	}
	else
	{
		// Nếu chiều sâu bằng 0
		if (depth == 0) {
			return state->heuristicCaro(chessman);
		}

		// Tạo ra các con của state
		list<Node *> stateList = generateStateCaro(state, chessman);

		// Nếu state không thể phát sinh thêm bất kỳ state nào nữa
		if (stateList.empty()) {
			return state->heuristicCaro(chessman);
		}

		for (std::list<Node *>::iterator s = stateList.begin(); s != stateList.end(); s++) {
			int alpha1 = beta * -1;
			int beta1 = alpha * -1;
			alpha = max(alpha, -abp_max((*s), chessman == 'O' ? 'X' : 'O', depth - 1, alpha1, beta1));
			(*s)->display();
			cout << alpha << '\n';
			if (alpha > beta) {
				return alpha;
			}
		}
		return alpha;
	}
}

// Sử dụng trong trường hợp: máy tính sẽ là MIN, người chơi là MAX
int Board::abp_min(Node *state, char chessman, int depth, int alpha, int beta) {
	// Nếu chiều sâu bằng 0
	if (depth == 0) {
		return state->heuristicCaro(chessman);
	}

	// Tạo ra các con của state
	list<Node *> stateList = generateStateCaro(state, chessman);

	// Nếu state không thể phát sinh thêm bất kỳ state nào nữa
	if (stateList.empty()) {
		return state->heuristicCaro(chessman);
	}

	for (std::list<Node *>::iterator s = stateList.begin(); s != stateList.end(); s++) {
		int alpha1 = beta * -1;
		int beta1 = alpha * -1;
		beta = min(beta, -abp_min((*s), chessman == 'O' ? 'X' : 'O', depth - 1, alpha1, beta1));
		if (alpha > beta) {
			return beta;
		}
	}
	return beta;
}


list<Node *> Board::generateStateCaro(Node *root, char chessman) {
	int numberRow = root->getRow();
	bool flag = false;
	char **board = root->getBoard();
	list<int> listPoint;	// Danh sách các điểm
	for (int i = 0; i < numberRow; i++)
	{
		for (int j = 0; j < numberRow; j++)
		{
			if (board[i][j] != '_') {
				if (i + 1 < numberRow && board[i + 1][j] == '_') {
					flag = false;
					for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
						if ((*s) == ((i + 1) * numberRow + j)) {
							flag = true;
							break;
						}
					}

					if (flag == false) {
						listPoint.push_back((i + 1) * numberRow + j);
					}
				}
				if (i - 1 >= 0 && board[i - 1][j] == '_') {
					flag = false;
					for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
						if ((*s) == ((i - 1) * numberRow + j)) {
							flag = true;
							break;
						}
					}

					if (flag == false) {
						listPoint.push_back((i - 1) * numberRow + j);
					}
				}
				if (j + 1 < numberRow && board[i][j + 1] == '_') {
					flag = false;
					for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
						if ((*s) == (i * numberRow + j + 1)) {
							flag = true;
							break;
						}
					}

					if (flag == false) {
						listPoint.push_back(i * numberRow + j + 1);
					}
				}
				if (j - 1 >= 0 && board[i][j - 1] == '_') {
					flag = false;
					for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
						if ((*s) == (i * numberRow + j - 1)) {
							flag = true;
							break;
						}
					}

					if (flag == false) {
						listPoint.push_back(i * numberRow + j - 1);
					}
				}
			}
		}

	}

	/*cout << "Cac trang thai duoc sinh ra: \n";
	for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
		cout << (*s) / numberRow << " " << (*s) % numberRow << '\n';
	}*/

	list<Node *> listState;
	for (std::list<int>::iterator s = listPoint.begin(); s != listPoint.end(); s++) {
		Node *newState = new Node(root->getBoard());
		newState->setCell(*s / numberRow, *s % numberRow, chessman);
		listState.push_back(newState);
	}

	return listState;
}

list<Node *> Board::generateStateTicTacToe(Node *root, char chessman) {
	list<Node *> states;
	char **board = root->getBoard();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '_') {
				Node *state = new Node(board);
				state->setCell(i, j, chessman);
				states.push_back(state);
			}
		}
	}

	return states;
}

bool Board::checkWinCaro(char chessman) {
	return this->root->checkWinCaro(chessman);
}

bool Board::checkWinTicTacToe(char chessman){
	return this->root->checkWinTicTacToe(chessman);
}
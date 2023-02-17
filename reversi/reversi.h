#pragma once

#include<vector>
#include<list>
#include<memory>

using namespace std;

using RBOARD = vector<vector<uint8_t>>;

struct reversi
{
	RBOARD board;
	// 0 - white
	// 1 - black
	// 2 - free

	int scount = 0;
	int x = -1;
	int y = -1;

	reversi()
	{
		board = vector<vector<uint8_t>>(8, vector<uint8_t>(8,2));
		setStartPos();
	}

	reversi(const RBOARD& b, int c, int X, int Y) : board(b),scount(c),x(X),y(Y)
	{}

	void setStartPos()
	{
		board[3][3] = 0;
		board[3][4] = 1;
		board[4][3] = 1;
		board[4][4] = 0;
	}

	pair<int,int> countPoints()
	{
		int black = 0;
		int white = 0;

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (board[i][j] == 0)
					white++;
				else if (board[i][j] == 1)
					black++;

		return { white,black };
	}

	uint8_t getOpColor(uint8_t c)
	{
		if (c == 1)
			return 0;
		else return 1;
	}

	void setTurn(int i, int j, uint8_t color)
	{
		setMonet(i, j, color, getOpColor(color));
		x = i;
		y = j;
		scount++;
	}

	pair<int, int> checkHorRLine(int i, int j, uint8_t c)
	{
		for (; j < 8; j++)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return {-1, -1 };
	}

	pair<int, int> checkHorLLine(int i, int j, uint8_t c)
	{
		for (; j >= 0; j--)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkVerULine(int i, int j, uint8_t c)
	{
		for (; i >= 0; i--)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkVerDLine(int i, int j, uint8_t c)
	{
		for (; i < 8; i++)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkDiagLULine(int i, int j, uint8_t c)
	{
		for (; j >= 0 && i >= 0; i--, j--)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkDiagLDLine(int i, int j, uint8_t c)
	{
		for (; j >=0 && i < 8; i++, j--)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkDiagRULine(int i, int j, uint8_t c)
	{
		for (; j < 8 && i >= 0; i--, j++)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	pair<int, int> checkDiagRDLine(int i, int j, uint8_t c)
	{
		for (; j < 8 && i < 8; i++, j++)
		{
			if (board[i][j] == 2)
				break;
			if (board[i][j] != c && board[i][j] != 2)
				return { i,j };
		}

		return { -1, -1 };
	}

	list<pair<pair<int, int>, pair<int, int>>> possibleVars(int i, int j, uint8_t c)
	{
		list<pair<pair<int, int>, pair<int, int>>> vars = list<pair<pair<int, int>, pair<int, int>>>();

		if (i - 1 > 0 && board[i - 1][j] == c)
		{
			auto connector = checkVerULine(i-2, j, c);
			if(connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (i + 1 < 8 && board[i + 1][j] == c)
		{
			auto connector = checkVerDLine(i+2, j, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (j - 1 > 0 && board[i][j-1] == c)
		{
			auto connector = checkHorLLine(i, j-2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (j + 1 < 8 && board[i][j+1] == c)
		{
			auto connector = checkHorRLine(i, j+2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (i - 1 > 0 && j-1>0 && board[i - 1][j-1] == c)
		{
			auto connector = checkDiagLULine(i - 2, j - 2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (i - 1 > 0 && j+1<8 && board[i - 1][j+1] == c)
		{
			auto connector = checkDiagRULine(i - 2, j + 2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (i + 1 < 8 && j-1>0 &&  board[i + 1][j-1] == c)
		{
			auto connector = checkDiagLDLine(i + 2, j - 2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}
		if (i + 1 <8 && j+1<8 && board[i + 1][j+1] == c)
		{
			auto connector = checkDiagRDLine(i + 2, j + 2, c);
			if (connector.first != -1)
				vars.push_back({ {i,j}, connector });
		}

		return vars;
	}

	void paintHorRLine(RBOARD &board,int i, int j, uint8_t c)
	{
		for (; j < 8; j++)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintHorLLine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; j >= 0; j--)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintVerULine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; i >= 0; i--)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintVerDLine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; i < 8; i++)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintDiagLULine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; j >= 0 && i >= 0; i--, j--)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintDiagLDLine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; j >= 0 && i < 8; i++, j--)
		{
			if (board[i][j] != c )
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintDiagRULine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; j < 8 && i >= 0; i--, j++)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void paintDiagRDLine(RBOARD& board, int i, int j, uint8_t c)
	{
		for (; j < 8 && i < 8; i++, j++)
		{
			if (board[i][j] != c)
			{
				board[i][j] = c;
			}
			else break;
		}
	}

	void setMonet(int i, int j, uint8_t curColor, uint8_t opColor)
	{
		list<pair<pair<int, int>, pair<int, int>>> v = possibleVars(i, j, opColor);

		if (v.begin() != v.end())
		{
			for (auto& p : v)
			{
				RBOARD& b = this->board;
				b[i][j] = curColor;

				if (p.first.second < p.second.second)
				{
					if (p.first.first > p.second.first)
					{
						paintDiagRULine(b, i - 1, j + 1, curColor);
					}
					else if (p.first.first < p.second.first)
					{
						paintDiagRDLine(b, i + 1, j + 1, curColor);
					}
					else
					{
						paintHorRLine(b, i, j + 1, curColor);
					}
				}
				else if (p.first.second > p.second.second)
				{
					if (p.first.first > p.second.first)
					{
						paintDiagLULine(b, i - 1, j - 1, curColor);
					}
					else if (p.first.first < p.second.first)
					{
						paintDiagLDLine(b, i + 1, j - 1, curColor);
					}
					else
					{
						paintHorLLine(b, i, j - 1, curColor);
					}
				}
				else
				{
					if (p.first.first < p.second.first)
					{
						paintVerDLine(b, i + 1, j, curColor);
					}
					else if (p.first.first > p.second.first)
					{
						paintVerULine(b, i - 1, j, curColor);
					}
				}
			}
		}
	}

	list<shared_ptr<reversi>> getNextVariants(uint8_t curColor)
	{
		list < shared_ptr<reversi>> vars = list <shared_ptr<reversi>>();
		//uint8_t curColor = (scount+1) % 2;
		uint8_t opColor = getOpColor(curColor);

		if (this->scount == 60)
		{
			return vars;
		}

		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j] == 2)
				{
					list<pair<pair<int, int>, pair<int, int>>> v = possibleVars(i, j, opColor);

					if (v.begin() != v.end())
					{
						for (auto &p : v)
						{
							RBOARD b = this->board;
							b[i][j] = curColor;

							if (p.first.second < p.second.second)
							{
								if (p.first.first > p.second.first)
								{
									paintDiagRULine(b,i - 1, j + 1, curColor);
								}
								else if (p.first.first < p.second.first)
								{
									paintDiagRDLine(b,i + 1, j + 1, curColor);
								}
								else
								{
									paintHorRLine(b,i, j + 1, curColor);
								}
							}
							else if (p.first.second > p.second.second)
							{
								if (p.first.first > p.second.first)
								{
									paintDiagLULine(b,i - 1, j - 1, curColor);
								}
								else if (p.first.first < p.second.first)
								{
									paintDiagLDLine(b,i + 1, j - 1, curColor);
								}
								else
								{
									paintHorLLine(b,i, j - 1, curColor);
								}
							}
							else
							{
								if (p.first.first < p.second.first)
								{
									paintVerDLine(b,i + 1, j, curColor);
								}
								else if (p.first.first > p.second.first)
								{
									paintVerULine(b,i - 1, j, curColor);
								}
							}

							vars.push_back(make_shared<reversi>(b, this->scount + 1,i,j));
						}
					}

				}
			}
		}

		return vars;
	}

};

int validMoves(shared_ptr<reversi> s, uint8_t c) {
	int count = 0, i, j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			if (s->board[i][j] == 2)
			{
				auto r = s->possibleVars(i, j, c);
				if (r.begin() != r.end())
				{
					count++;
				}
			}
		}
	return count;
}

double heuristic(shared_ptr<reversi> s, uint8_t myColor) {
	RBOARD& grid = s->board;
	//uint8_t myColor = (s->scount + 1) % 2;
	uint8_t oppColor = s->getOpColor(myColor);
	int myTiles = 0, oppTiles = 0, i, j, k, myFrontTiles = 0, oppFrontTiles = 0, x, y;
	double p = 0, c = 0, l = 0, m = 0, f = 0, d = 0;

	const vector<int> X1 = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const vector<int> Y1 = { 0, 1, 1, 1, 0, -1, -1, -1 };
	vector<vector<int>> V = vector<vector<int>>(8);

	V[0] = vector<int>{ 20, -3, 11, 8, 8, 11, -3, 20 };
	V[1] = vector<int>{ -3, -7, -4, 1, 1, -4, -7, -3 };
	V[2] = vector<int>{ 11, -4, 2, 2, 2, 2, -4, 11 };
	V[3] = vector<int>{ 8, 1, 2, -3, -3, 2, 1, 8 };
	V[4] = vector<int>{ 8, 1, 2, -3, -3, 2, 1, 8 };
	V[5] = vector<int>{ 11, -4, 2, 2, 2, 2, -4, 11 };
	V[6] = vector<int>{ -3, -7, -4, 1, 1, -4, -7, -3 };
	V[7] = vector<int>{ 20, -3, 11, 8, 8, 11, -3, 20 };

	// Разность дисков
	// Подсчет граничных дисков
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++) {
			if (grid[i][j] == myColor) {
				d += V[i][j];
				myTiles++;
			}
			else if (grid[i][j] == oppColor) {
				d -= V[i][j];
				oppTiles++;
			}
			if (grid[i][j] != 2) {
				for (k = 0; k < 8; k++) {
					x = i + X1[k]; y = j + Y1[k];
					if (x >= 0 && x < 8 && y >= 0 && y < 8 && grid[x][y] == 2) {
						if (grid[i][j] == myColor)  myFrontTiles++;
						else oppFrontTiles++;
						break;
					}
				}
			}
		}
	if (myTiles > oppTiles)
		p = (100.0 * myTiles) / (myTiles + oppTiles);
	else if (myTiles < oppTiles)
		p = -(100.0 * oppTiles) / (myTiles + oppTiles);
	else p = 0;

	if (myFrontTiles > oppFrontTiles)
		f = -(100.0 * myFrontTiles) / (myFrontTiles + oppFrontTiles);
	else if (myFrontTiles < oppFrontTiles)
		f = (100.0 * oppFrontTiles) / (myFrontTiles + oppFrontTiles);
	else f = 0;

	// Захват углов
	myTiles = oppTiles = 0;
	if (grid[0][0] == myColor) myTiles++;
	else if (grid[0][0] == oppColor) oppTiles++;
	if (grid[0][7] == myColor) myTiles++;
	else if (grid[0][7] == oppColor) oppTiles++;
	if (grid[7][0] == myColor) myTiles++;
	else if (grid[7][0] == oppColor) oppTiles++;
	if (grid[7][7] == myColor) myTiles++;
	else if (grid[7][7] == oppColor) oppTiles++;
	c = 25 * (myTiles - oppTiles);

	// Блтизость к углам
	myTiles = oppTiles = 0;
	if (grid[0][0] == 2) {
		if (grid[0][1] == myColor) myTiles++;
		else if (grid[0][1] == oppColor) oppTiles++;
		if (grid[1][1] == myColor) myTiles++;
		else if (grid[1][1] == oppColor) oppTiles++;
		if (grid[1][0] == myColor) myTiles++;
		else if (grid[1][0] == oppColor) oppTiles++;
	}
	if (grid[0][7] == 2) {
		if (grid[0][6] == myColor) myTiles++;
		else if (grid[0][6] == oppColor) oppTiles++;
		if (grid[1][6] == myColor) myTiles++;
		else if (grid[1][6] == oppColor) oppTiles++;
		if (grid[1][7] == myColor) myTiles++;
		else if (grid[1][7] == oppColor) oppTiles++;
	}
	if (grid[7][0] == 2) {
		if (grid[7][1] == myColor) myTiles++;
		else if (grid[7][1] == oppColor) oppTiles++;
		if (grid[6][1] == myColor) myTiles++;
		else if (grid[6][1] == oppColor) oppTiles++;
		if (grid[6][0] == myColor) myTiles++;
		else if (grid[6][0] == oppColor) oppTiles++;
	}
	if (grid[7][7] == 2) {
		if (grid[6][7] == myColor) myTiles++;
		else if (grid[6][7] == oppColor) oppTiles++;
		if (grid[6][6] == myColor) myTiles++;
		else if (grid[6][6] == oppColor) oppTiles++;
		if (grid[7][6] == myColor) myTiles++;
		else if (grid[7][6] == oppColor) oppTiles++;
	}
	l = -12.5 * (myTiles - oppTiles);

	// Мобильность
	myTiles = validMoves(s, oppColor);
	oppTiles = validMoves(s, myColor);
	if (myTiles > oppTiles)
		m = (100.0 * myTiles) / (myTiles + oppTiles);
	else if (myTiles < oppTiles)
		m = -(100.0 * oppTiles) / (myTiles + oppTiles);
	else m = 0;

	// Результат
	double score = (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d);
	return score;
}

double alphaBeta(shared_ptr<reversi> s, int depth, double& alpha, double& beta, uint8_t curColor,bool maxColor)
{
	if (depth == 0 || s->scount == 60)
	{
		if (maxColor)
			return heuristic(s, s->getOpColor(curColor));
		else return heuristic(s, curColor);
		//return heuristic(s, curColor);
	}
	if (maxColor)
	{
		double val = INT_MIN;

		for (auto& child : s->getNextVariants(s->getOpColor(curColor)))
		{
			val = max(val, alphaBeta(child, depth - 1, alpha, beta, curColor,!maxColor));

			if (val >= beta)
				break;
			alpha = max(alpha, val);
		}
		return val;
	}
	else
	{
		double val = INT_MAX;

		for (auto& child : s->getNextVariants(curColor))
		{
			val = min(val, alphaBeta(child, depth - 1, alpha, beta, curColor,!maxColor));

			if (val <= alpha)
				break;
			beta = min(beta, val);
		}

		return val;
	}
}

bool chooseNewVariant(shared_ptr<reversi> s, uint8_t curColor,int depth)
{
	//int depth = 5;

	double alpha = INT_MIN;
	double beta = INT_MAX;
	bool hasVars = false;

	shared_ptr<reversi> nextVar = nullptr;
	double t = INT_MAX;

	for (auto& var : s->getNextVariants(curColor))
	{
		double res = alphaBeta(var, depth, alpha, beta, curColor,true);

		if (!nextVar)
			nextVar = var;
		if (t > res)
		{
			nextVar = var;
			t = res;
		}
	}

	if (nextVar)
	{
		s->setTurn(nextVar->x, nextVar->y, curColor);
		hasVars = true;
	}

	return hasVars;
}
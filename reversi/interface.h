#pragma once

#include<iostream>
#include"reversi.h"

using namespace std;

struct Interface {

	uint8_t pColor;
	shared_ptr<reversi> game;

	int depth = 5;

	std::ostream* stepThred= &cerr;
	std::ostream* logThred= &cout;

	Interface(int playerColor,int d=6, string outf="-") : depth(d)
	{
		if (outf == "-")
		{
			stepThred = &cerr;
			logThred = &cout;
		}
		else if (outf == "+")
		{
			stepThred = &cout;
			logThred = &cerr;
		}
		else
		{
			//todo file
		}

		if (playerColor == 0)
			pColor = 0;
		else pColor = 1;

		game = make_shared<reversi>();
	}

	void showBoard()
	{
		(*logThred) << endl;
		(*logThred) << "  ";
		for (int i = 0; i < 8; i++)
		{
			(*logThred) << (char)('a' + i) << " | ";
		}

		(*logThred) << endl;

		for (int i = 0; i < 8; i++)
		{
			(*logThred) << i + 1 << " ";
			for (int j = 0; j < 8; j++)
			{
				char sym = ' ';
				if (game -> board[i][j] == 0)
					sym = '0';
				if (game->board[i][j] == 1)
					sym = '1';

				(*logThred) << sym << " | ";
			}
			(*logThred) << endl;
			//(*logThred) << "-\t-\t-\t-\t-" << endl;
		}

		(*logThred) << endl;
	}

	string toStr(int i, int j)
	{
		string str = "a1";
		str[0] = j + 97;
		str[1] = i + '0' + 1;

		return str;
	}

	pair<int, int> toInt(string str)
	{
		return {  str[1] - 1 - '0',str[0] - 97};
	}

	int startGameLoop()
	{
		/*int c;
		cin >> c;

		if (c == 0)
			myColor = 0;
		else myColor = 1;*/

		bool endGame = false;
		bool playerHasVars = true;
		bool compHasVars = true;

		string input;
		showBoard();

		if (pColor == 0)
		{
			chooseNewVariant(game, game->getOpColor(pColor),depth);
			(*stepThred) << toStr(game->x, game->y) << endl;
			(*logThred) << toStr(game->x, game->y) << endl;
			showBoard();
		}

		while (!endGame)
		{			
			(*logThred) << "Step: " << game->scount+1 << endl;
			playerHasVars = validMoves(game, game->getOpColor(pColor));

			if (playerHasVars)
			{
				//cout << "Next turn" << endl;
				cin >> input;
				auto turn = toInt(input);
				game->setTurn(turn.first, turn.second, pColor);
				//(*stepThred) << toStr(game->x, game->y) << endl;
				//(*logThred) << toStr(game->x, game->y) << endl;
				showBoard();
			}
			else (*logThred) << "Player has no vars" << endl;
			compHasVars = chooseNewVariant(game, game->getOpColor(pColor),depth);
			if (compHasVars)
			{
				(*stepThred) << toStr(game->x, game->y) << endl;
				(*logThred) << toStr(game->x, game->y) << endl;
				showBoard();
			}
			else (*logThred) << "Comp has no vars" << endl;

			endGame = !playerHasVars && !compHasVars;
		}

		auto res = game->countPoints();
		if (res.first > res.second)
		{
			if (pColor == 0)
				return 3;
			else return 0;

		}
		else if (res.first < res.second)
		{
			if (pColor == 0)
				return 0;
			else return 3;
		}
		else return 4; // draw
	}

};
#pragma once
#include "GameManager.h"
#include <vector> 
#include <string>
#include <unordered_map>

class Enemy : public Character
{
public:
	Enemy();
	 void PlaceXOPublic(char XorO, Vector2 position, std::vector<char>& board,char otherXorO);
protected:
	std::pair<int,int> BestMove(std::vector<char>& board, char XorOEnemy, char XorOPlayer);
	int MinMax(std::vector<char>& board, int depth, bool isMaximising, char XorOEnemy, char XorOPlayer,  int alpha, int beta);
	void PlaceXO(char XorO, Vector2 position, std::vector<char>& board, char otherXorO);

private:
	int maxDepth = 4;
	int depth,winScore,looseScore,tieScore;
	std::unordered_map<char, int> memo;
	int evaluateBoard(const std::vector<char>& board, const char& XorOEnemy, const char& XorOPlayer);
	int evaluateLine(const std::vector<char>& board, int start, int step, const char& XorOEnemy, const char& XorOPlayer);
	Rectangle r;
};


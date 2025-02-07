#pragma once
#include "GameManager.h"
#include <vector> 
#include <string>
#include <unordered_map>

class Enemy : public Character
{
public:
	Enemy();
	 void PlaceXOPublic(std::string XorO, Vector2 position, std::vector<std::string>& board,std::string otherXorO);
protected:
	Vector2 BestMove(std::vector<std::string>& board, std::string XorOEnemy, std::string XorOPlayer);
	int MinMax(std::vector<std::string>& board, int depth, bool isMaximising, std::string XorOEnemy, std::string XorOPlayer,  int alpha, int beta);
	void PlaceXO(std::string XorO, Vector2 position, std::vector<std::string>& board, std::string otherXorO);

private:
	int maxDepth = 4;
	int depth,winScore,looseScore,tieScore;
	std::unordered_map<std::string, int> memo;
	int evaluateBoard(const std::vector<std::string>& board, const std::string& XorOEnemy, const std::string& XorOPlayer);
	int evaluateLine(const std::vector<std::string>& board, int start, int step, const std::string& XorOEnemy, const std::string& XorOPlayer);

};


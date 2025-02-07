#ifndef CHARACTER_H
#define CHARACTER_H

#include <array>
#include "raylib.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
class Character
{
public:
	
	Character();
	std::string GetXorO() const { return XorO; }
	std::vector<std::string> GetGraphXorO() const { return graphXO; }
	void DrawX(int x, int y, int cellWidth, int cellHeight, Texture2D playerX,Rectangle playerRect);
	void DrawO(int x, int y, int cellWidth, int cellHeight, Texture2D playerX, Rectangle playerRect);
	bool isFull(std::vector<std::string>& board);
	bool checkWin( std::vector<std::string>& board, std::string player,bool isPlayer);
	 static std::vector<std::pair<std::array<int, 4>, std::array<std::string, 4>>>count;
protected:
	int screenWidth, screenHeight;

	std::string XorO;
	std::vector<std::string> graphXO = std::vector<std::string>(16, "");

	
};

#endif
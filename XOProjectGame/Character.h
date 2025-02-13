#pragma once
#include <algorithm>
#include <array>
#include "raylib.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include "SoundPlayer.h"


class Character
{
public:
	
	Character();
	SoundPlayer& GetSound()  { return sound; };
	std::vector<char> GetGraphXorO() const { return graphXO; }
	void DrawX(int x, int y, int cellWidth, int cellHeight,int index ,Texture2D playerX,Rectangle playerRect);
	void DrawWinX(int x, int y, int cellWidth, int cellHeight, Texture2D playerX, Rectangle playerRect);
	void DrawO(int x, int y, int cellWidth, int cellHeight,int index, Texture2D playerX, Rectangle playerRect);
	bool isFull(std::vector<char>& board);
	bool checkWin( std::vector<char>& board, char player,bool isPlayer, Rectangle& playerRect);
	 static std::vector<std::pair<std::array<int, 4>, std::array<char, 4>>>count;
	  int score;
	  static int scoreGetter;
	  void ClearVectors();
	  void ClearCountVector();
protected:
	int screenWidth, screenHeight;
	std::string XorO;
	std::vector<char> graphXO = std::vector<char>(16, ' ');
	std::vector<std::pair<int, int>> boardInitial = std::vector<std::pair<int, int>>(16, { 0,0 });
	std::vector<std::pair<int, int>> boardO = std::vector<std::pair<int, int>>(16,{0,0});
private:
	SoundPlayer sound;
	float speed;

};


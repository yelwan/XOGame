#pragma once
#include <random>
#include <iostream>
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "raylib.h"
#include <vector>
#include <string>

class Enemy;

class GameManager 
{
public:
	GameManager();
	void BeginGameInit(int screenWidth, int screenHeight);
	void ReloadGame(std::vector<char>& board);
	void DrawGame(std::vector<char>& graphXO);
	void UpdateGame(std::vector<char>& graphXO);
	void CheckUp(std::vector<char>& graphXO);
	void CheckForPlace(std::vector<char>& graphXO);
	void CloseGame();
private:
	int cellWidth, cellHeight, screenWidth,screenHeight;
	Texture2D playerX, enemyX, playerXWin, enemyXWin;
	Rectangle playerRect;
	std::unique_ptr<Player> player;
	std::unique_ptr<Enemy> enemy;
	std::unique_ptr<Character> character;
	bool gameOver;
	bool playerHasPlayed;
	bool aiHasPlayed;
};


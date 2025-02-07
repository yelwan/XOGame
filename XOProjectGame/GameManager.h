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
	~GameManager();
	void BeginGame(int screenWidth, int screenHeight);
	
	
private:

	Vector2 GetClickPosition() const { return GetMousePosition(); }
	Player* player;
	Enemy* enemy;
	Character* character;
	bool gameOver;
	bool playerHasPlayed;
	bool aiHasPlayed;
};


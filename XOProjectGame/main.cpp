#include "GameManager.h"

int main() 
{
	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();

	 int screenWidth = 800;
	 int screenHeight = 600;


	 InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	 gameManager->BeginGameInit(screenWidth, screenHeight);


	 CloseWindow();
	 return 0;
}
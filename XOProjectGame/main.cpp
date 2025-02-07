#include "GameManager.h"

int main() 
{
	 GameManager* gameManager = new GameManager();

	 int screenWidth = 800;
	 int screenHeight = 600;


	 InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	 gameManager->BeginGame(screenWidth, screenHeight);


	 CloseWindow();
	 return 0;
}
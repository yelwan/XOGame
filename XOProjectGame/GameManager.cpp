    #include "GameManager.h"

    GameManager::GameManager() : gameOver(false), aiHasPlayed(false), playerHasPlayed(false)
    {
        player = new Player();
        enemy = new Enemy();
        character = new Character();
    }

    GameManager::~GameManager()
    {
        delete player;
        delete enemy;
        delete character;
    }

    void GameManager::BeginGame(int screenWidth, int screenHeight)
    {

        Texture2D playerX = LoadTexture("../XOProjectGame/X.png");
        Texture2D enemyX = LoadTexture("../XOProjectGame/O.png");
   
        std::vector<std::string> graphXO = character->GetGraphXorO();
        const int cellWidth = (int)screenWidth / 4;
        const int cellHeight = (int)screenHeight / 4;
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
            playerHasPlayed = aiHasPlayed = false;
            BeginDrawing();
            ClearBackground(RAYWHITE);
            

            for (int i = 1; i < 4; i++) {
                DrawLine(cellWidth * i, 0, cellWidth * i, screenHeight, BLACK);
                DrawLine(0, cellHeight * i, screenWidth, cellHeight * i, BLACK);
            }


            for (int i = 0; i < graphXO.size(); i++) {
                int row = i / 4;
                int col = i % 4;


                Rectangle playerRect = { 
                    static_cast<float>(col * cellWidth),
                    static_cast<float>(row * cellHeight),
                    static_cast<float>(cellWidth),
                    static_cast<float>(cellHeight)
                };
                 

                    if (graphXO[i] == "X") {
                        player->DrawX(col, row, cellWidth, cellHeight,playerX,playerRect);
                    }
                    if (graphXO[i] == "O") {
                        enemy->DrawO(col, row, cellWidth, cellHeight, enemyX,  playerRect);
                    }
            }

            if (!playerHasPlayed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 pos = GetMousePosition();
                    int col = pos.x / cellWidth;
                    int row = pos.y / cellHeight;
                    int index = row * 4 + col;

                    if (graphXO[index] == "") {
                        graphXO[index] = "X";
                        playerHasPlayed = true;
                    }
            }

            if (!aiHasPlayed && playerHasPlayed) {
                    enemy->PlaceXOPublic("O", { 0,0 }, graphXO, "X");
                    aiHasPlayed = true;
            }
            
           if (player->checkWin(graphXO, "X",false) || player->checkWin(graphXO, "O",false)) {
               player->checkWin(graphXO, "X", true);
               player->checkWin(graphXO, "O", true);
               int xWins = 0, oWins = 0;
               for (int i = 0; i < 4; i++) {
                   if (Character::count[i].second[i] == "X") {
                       xWins += Character::count[i].first[i]; 
                   }
                   else if (Character::count[i].second[i] == "O") {
                       oWins += Character::count[i].first[i]; 
                   }
               }

               if (xWins >= 3 || oWins >= 3) {
                   break;
               }
            }
           if (player->isFull(graphXO)) {
               for (int i = 0; i < graphXO.size(); i++) {
                   graphXO.at(i) = "";
               }
           }
            
                EndDrawing();
        }
       
    }
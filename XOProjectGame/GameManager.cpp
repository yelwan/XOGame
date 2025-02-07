    #include "GameManager.h"

    GameManager::GameManager() : gameOver(false), aiHasPlayed(false), playerHasPlayed(false), cellWidth(0), cellHeight(0),screenWidth(0),screenHeight(0)
    {
        playerRect = { 0.0f,0.0f,0.0f,0.0f };
        player = std::make_unique<Player>();
        enemy = std::make_unique<Enemy>();
        character = std::make_unique<Character>();
        
    }

  

    void GameManager::BeginGameInit(int screenWidth, int screenHeight)
    {       
        std::vector<char> graphXO = character->GetGraphXorO();
        playerX = LoadTexture("../XOProjectGame/X.png");
        enemyX = LoadTexture("../XOProjectGame/O.png");
        playerXWin = LoadTexture("../XOProjectGame/XWin.png");
        enemyXWin = LoadTexture("../XOProjectGame/OWin.png");
         this->screenWidth = screenWidth;
         this->screenHeight = screenHeight;
         cellWidth = screenWidth / 4;
         cellHeight = screenHeight / 4;
        SetTargetFPS(60);
        UpdateGame(graphXO);  
    }

    void GameManager::ReloadGame(std::vector<char>& board)
    {
        for (int i = 0; i < board.size(); i++) {
            board[i] = ' ';
        }
    }

    void GameManager::DrawGame(std::vector<char>& graphXO)
    {
      
       
        BeginDrawing();
        ClearBackground(RAYWHITE);


        for (int i = 1; i < 4; i++) {
            DrawLine(cellWidth * i, 0, cellWidth * i, screenHeight, BLACK);
            DrawLine(0, cellHeight * i, screenWidth, cellHeight * i, BLACK);
        }


        for (int i = 0; i < graphXO.size(); i++) {
            int row = i / 4;
            int col = i % 4;


            playerRect = {
               static_cast<float>(col * cellWidth),
               static_cast<float>(row * cellHeight),
               static_cast<float>(cellWidth),
               static_cast<float>(cellHeight)
            };


            if (graphXO[i] == 'X') {
                player->DrawX(col, row, cellWidth, cellHeight, playerX, playerRect);
            }
            if (graphXO[i] == 'O') {
                enemy->DrawO(col, row, cellWidth, cellHeight, enemyX, playerRect);
            }
        }

        CheckForPlace(graphXO);
        CheckUp(graphXO);
        EndDrawing();
    }

    void GameManager::UpdateGame(std::vector<char>& graphXO)
    {
        while (!WindowShouldClose())
        {
            playerHasPlayed = aiHasPlayed = false;
            DrawGame(graphXO);
                  
        }
    }

    void GameManager::CheckUp(std::vector<char>& graphXO)
    {
        if (player->checkWin(graphXO, 'X', false, playerRect) || player->checkWin(graphXO, 'O', false, playerRect)) {
            player->checkWin(graphXO, 'X', true, playerRect);
            player->checkWin(graphXO, 'O', true, playerRect);
            int xWins = 0, oWins = 0;
            for (int i = 0; i < graphXO.size(); i++) {
                if (graphXO[i] == 'X') {
                    player->DrawWinX(i % 4, i / 4, cellWidth, cellHeight, playerXWin, playerRect);
                }
                else if (graphXO[i] == 'O') {
                    player->DrawWinX(i % 4, i / 4, cellWidth, cellHeight, enemyXWin, playerRect);
                }
            }
            for (int i = 0; i < 4; i++) {
                if (Character::count[i].second[i] == 'X') {
                    xWins += Character::count[i].first[i];
                }
                else if (Character::count[i].second[i] == 'O') {
                    oWins += Character::count[i].first[i];
                }

            }

            if (xWins >= 3 || oWins >= 3) {
                CloseWindow();
            }
        }
        if (player->isFull(graphXO)) {
            ReloadGame(graphXO);
        }
    }

    void GameManager::CheckForPlace(std::vector<char>& graphXO)
    {
        if (!playerHasPlayed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            int col = pos.x / cellWidth;
            int row = pos.y / cellHeight;
            int index = row * 4 + col;

            if (graphXO[index] == ' ') {
                graphXO[index] = 'X';
                playerHasPlayed = true;
            }
        }

        if (!aiHasPlayed && playerHasPlayed) {
            enemy->PlaceXOPublic('O', {0,0}, graphXO, 'X');
            aiHasPlayed = true;
        }
    }

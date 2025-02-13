    #include "GameManager.h"
    #include "SoundPlayer.h"

    GameManager::GameManager() : gameOver(false), aiHasPlayed(false), playerHasPlayed(false), cellWidth(0), cellHeight(0),screenWidth(0),screenHeight(0)
    {
        player = std::make_unique<Player>();
        enemy = std::make_unique<Enemy>();
        
    }

  

    void GameManager::BeginGameInit(int screenWidth, int screenHeight)
    {       
        playerX = LoadTexture("../XOProjectGame/X.png");
        enemyX = LoadTexture("../XOProjectGame/O.png");
        playerXWin = LoadTexture("../XOProjectGame/XWin.png");
        enemyXWin = LoadTexture("../XOProjectGame/OWin.png");
         this->screenWidth = screenWidth;
         this->screenHeight = screenHeight;
         cellWidth = screenWidth / 4;
         cellHeight = screenHeight / 4;
        SetTargetFPS(45);
        InitAudioDevice();
        UpdateGame(graphXO);  
    }

    void GameManager::ReloadGame(std::vector<char>& board)
    {
        for (int i = 0; i < board.size(); i++) {
            board[i] = ' ';
        }
        player->ClearVectors();
        enemy->ClearVectors();
    }

    void GameManager::DrawGame(std::vector<char>& graphXO,GameState& state)
    {
        if (state != PLAYING) return;
        BeginDrawing();
        ClearBackground(RAYWHITE);


        for (int i = 1; i < 4; i++) {
            DrawLine(cellWidth * i, 0, cellWidth * i, screenHeight, BLACK);
            DrawLine(0, cellHeight * i, screenWidth, cellHeight * i, BLACK);
        }


        for (int i = 0; i < graphXO.size(); i++) {
            int row = i / 4;
            int col = i % 4;


            


            if (graphXO[i] == 'X') {
                player->DrawX(col * cellWidth, row * cellHeight, cellWidth, cellHeight,i, playerX, playerRect);
            }
            if (graphXO[i] == 'O') {
                enemy->DrawO(col * cellWidth, row * cellHeight, cellWidth, cellHeight,i, enemyX, playerRect);
            }
        }

        CheckForPlace(graphXO);
        CheckUp(graphXO);
        EndDrawing();
    }

    void GameManager::DrawIntro(GameState& state)
    {
      
        if (state != WAITING_FOR_INPUT) return;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Press: 1: to Play, esc: to exit",20,40,50,BLACK);
        if (IsKeyPressed(KEY_ONE)) state = PLAYING;
        EndDrawing();
    }

    void GameManager::DrawFinish(GameState& state)
    {
        if (state != GAME_OVER) return;
        ReloadGame(graphXO);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        int _score = Character::score;
        DrawText("Press: 1: to RePlay, esc: to exit", 20, 40, 45, BLACK);
        DrawText(TextFormat(_score < 3 ? "You Lost! Scoring:" : "You Won You scored: %d", _score), 40, 100, 50,RED);
      
        if (IsKeyPressed(KEY_ONE)) state = PLAYING;
        EndDrawing();
    }

    void GameManager::UpdateGame(std::vector<char>& graphXO)
    {
        state = WAITING_FOR_INPUT;
        while (!WindowShouldClose())
        {
            DrawIntro(state);
            playerHasPlayed = aiHasPlayed = false;
            DrawGame(graphXO,state);      
            DrawFinish(state);
        }
        CloseGame();
    }

    void GameManager::CheckUp(std::vector<char>& graphXO)
    {
        if (player->checkWin(graphXO, 'X', false, playerRect) || player->checkWin(graphXO, 'O', false, playerRect)) {
            player->checkWin(graphXO, 'X', true, playerRect);
            player->checkWin(graphXO, 'O', true, playerRect);
            int xWins = 0, oWins = 0;

            for (int i = 0; i < 4; i++) {
                if (Character::count[i].second[i] == 'X') {
                    xWins += Character::count[i].first[i];
                }
                else if (Character::count[i].second[i] == 'O') {
                    oWins += Character::count[i].first[i];
                }
            }

            if (xWins > 3 || oWins > 3) {
                player->checkWin(graphXO, 'X', true, playerRect);
                player->checkWin(graphXO, 'O', true, playerRect);
                state = GAME_OVER;
                xWins = oWins = 0;
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

    void GameManager::CloseGame()
    {
        CloseAudioDevice();
        UnloadTexture(playerX);
        UnloadTexture(enemyX);
        UnloadTexture(playerXWin);
        UnloadTexture(enemyXWin);
    }

#include "Character.h"
#include <iostream>

std::vector<std::pair<std::array<int, 4>, std::array<char, 4>>> Character::count(4);

Character::Character() : screenHeight(0), screenWidth(0) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            count[i].first[j] = 0;
            count[i].second[j] = ' ';
        }
    }
}

void Character::DrawX(int x, int y, int cellWidth, int cellHeight, Texture2D playerX, Rectangle playerRect)
{
    Rectangle sourceRect = { 0, 0, static_cast<float>(playerX.width), static_cast<float>(playerX.height) };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(playerX, sourceRect, playerRect, origin, 0.0f, WHITE);
}
void Character::DrawWinX(int x, int y, int cellWidth, int cellHeight, Texture2D playerX, Rectangle playerRect)
{
    Rectangle sourceRect = { 0, 0, static_cast<float>(playerX.width), static_cast<float>(playerX.height) };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(playerX, sourceRect, playerRect, origin, 0.0f, WHITE);
}
void Character::DrawO(int x, int y, int cellWidth, int cellHeight, Texture2D playerX, Rectangle playerRect)
{
 
    Rectangle sourceRect = { 0, 0, static_cast<float>(playerX.width), static_cast<float>(playerX.height) };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(playerX, sourceRect, playerRect, origin, 0.0f, WHITE);
}

bool Character::isFull(std::vector<char>& board)
{
    for (const char& cell : board) {
        if (cell == ' ') {
            return false;
        }
    }
    return true;
}


bool Character::checkWin(std::vector<char>& board, char player,bool isPlayer,Rectangle& playerRect)
{
    
    for (int row = 0; row < 4; row++) {
        if (board[row * 4] == player && board[row * 4 + 1] == player &&
            board[row * 4 + 2] == player && board[row * 4 + 3] == player) {
            if (isPlayer) {
                
                if (count[0].first[0] < 4) {
                    count[0].first[0]++;
                    count[0].second[0] = player;
                    board.at(row * 4) = ' ';
                    board.at(row * 4 + 1) = ' ';
                    board.at(row * 4 + 2) = ' ';
                    board.at(row * 4 + 3) = ' ';
                }
                else {
                    playerRect = {
                        0,
                        static_cast<float>(row),
                        1,
                        4
                    };
                }
                
            }
            return true;
        }
    }

    for (int col = 0; col < 4; col++) {
        if (board[col] == player && board[col + 4] == player &&
            board[col + 8] == player && board[col + 12] == player) {
            if ( isPlayer) {
                
                if (count[1].first[1] < 4) {
                    count[1].first[1]++;
                    count[1].second[1] = player;
                    board.at(col) = ' ';
                    board.at(col + 4) = ' ';
                    board.at(col + 8) = ' ';
                    board.at(col + 12) = ' ';
                }
                else {
                    playerRect = { static_cast<float>(col), 0, 1, 4 };
                }
            }
            return true;
        }
    }

    if (board[0] == player && board[5] == player && board[10] == player && board[15] == player) {
        if (isPlayer) {
            
            if (count[2].first[2] < 4) {
                count[2].first[2]++;
                count[2].second[2] = player;
                board.at(0) =' ';
                board.at(5) = ' ';
                board.at(10) = ' ';
                board.at(15) =' ';
            }
            else {
                playerRect = { 0, 0, 4, 4 };
            }
            
        }
        return true;
    }
    if (board[3] == player && board[6] == player && board[9] == player && board[12] == player) {
        if (isPlayer) {
           
            if (count[3].first[3] < 4) {
                count[3].first[3]++;
                count[3].second[3] = player;
                board.at(3) = ' ';
                board.at(6) = ' ';
                board.at(9) = ' ';
                board.at(12) = ' ';
            }
            else {
                playerRect = { 3, 0, -4, 4 };
            }
        }
        return true;
    }

    return false;
}




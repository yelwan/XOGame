#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : Character::Character(), depth(0), looseScore(-10), tieScore(0), winScore(10)
{
}

void Enemy::PlaceXOPublic(std::string XorO, Vector2 position, std::vector<std::string>& board, std::string otherXorO)
{
     PlaceXO(XorO, position, board,otherXorO);
}



Vector2 Enemy::BestMove(std::vector<std::string>& board, std::string XorO, std::string XorOPlayer)
{
    int bestScores = INT_MIN;
    Vector2 bestMove{ -2.0f,-2.0f };


    for (int i = 0; i < board.size(); i++) 
    {
        int row = i / 4; 
        int col = i % 4;


        if (board.at(i) == "") {
            board.at(i) = XorO;

            int _bestScores = MinMax(board, 0, false, XorO, XorOPlayer, INT_MIN, INT_MAX);
            board.at(i) = "";


            if (bestScores <= _bestScores) {
                bestScores = _bestScores;
                bestMove = Vector2{ static_cast<float>(col), static_cast<float>(row) };
            }
        }
    }
    return bestMove;
}

int Enemy::MinMax(std::vector<std::string>& board, int depth, bool isMaximising, std::string XorOEnemy, std::string XorOPlayer, int alpha, int beta)
{
    if (depth >= maxDepth) return evaluateBoard(board, XorOEnemy, XorOPlayer);

    std::string boardKey = (isMaximising ? "M" : "m");
    for (const auto& cell : board) {
        boardKey += (cell.empty() ? "_" : cell);
    }
    if (memo.find(boardKey) != memo.end())   return memo[boardKey];
    if (checkWin(board, XorOEnemy,false)) return winScore - depth;
    if (checkWin(board, XorOPlayer,false)) return looseScore + depth;
    if (isFull(board)) return tieScore;
    

    if (isMaximising) {
        int bestScore = INT_MIN;
        for (int i = 0; i < board.size(); i++)
        {
            if (board.at(i) == "")
            {
                board[i] =  XorOEnemy;

                int moveScore = MinMax(board, depth + 1, false, XorOEnemy, XorOPlayer, alpha, beta);

                board[i] = "";


                    bestScore = std::max(bestScore, moveScore);
                    alpha = std::max(alpha, bestScore);
                    memo[boardKey] = bestScore;
                if (beta <= alpha) {
                    break;
                }
                
            }
        }

        return bestScore;
    }
    else {
        int bestScore = INT_MAX;
        for (int i = 0; i < board.size(); i++)
        {
            if (board.at(i) == "")
            {
                board[i] = XorOPlayer;

                int moveScore = MinMax(board, depth + 1, true, XorOEnemy, XorOPlayer, alpha, beta);

                board[i] = "";


                    bestScore = std::min(bestScore, moveScore);
                    beta = std::min(beta, bestScore);
                    memo[boardKey] = bestScore;
                if (beta <= alpha) {
                    break;
                }
               
            }
        }

        return bestScore;
    }
    
}

void Enemy::PlaceXO(std::string XorO, Vector2 position, std::vector<std::string>& board, std::string otherXorO)
{
        Vector2 positionToPlace = BestMove(board, XorO, otherXorO);
        int row = static_cast<int>(positionToPlace.y);
        int col = static_cast<int>(positionToPlace.x);
        int index = row * 4 + col ;

        if (index >= 0 && index < graphXO.size() && board.at(index) == "")
        {
            board.at(index) = XorO;
        }

}



int Enemy::evaluateBoard(const std::vector<std::string>& board, const std::string& XorOEnemy, const std::string& XorOPlayer)
{
    int score = 0;

    for (int i = 0; i < 4; i++) {
        score += evaluateLine(board, i * 4, 1, XorOEnemy, XorOPlayer);
        score += evaluateLine(board, i, 4, XorOEnemy, XorOPlayer);
    }
    score += evaluateLine(board, 0, 5, XorOEnemy, XorOPlayer); 
    score += evaluateLine(board, 3, 3, XorOEnemy, XorOPlayer); 

    return score;
}

int Enemy::evaluateLine(const std::vector<std::string>& board, int start, int step, const std::string& XorOEnemy, const std::string& XorOPlayer) {
    int enemyCount = 0, playerCount = 0, emptyCount = 0;

    for (int i = 0; i < 4; i++) {
        int index = start + i * step;
        if (board[index] == XorOEnemy) enemyCount++;
        else if (board[index] == XorOPlayer) playerCount++;
        else emptyCount++;
    }

    if (enemyCount == 4) return INT_MAX; 
    if (playerCount == 4) return INT_MIN; 
    if (enemyCount == 3 && emptyCount == 1) return winScore; 
    if (playerCount == 3 && emptyCount == 1) return looseScore; 
    if (enemyCount == 2 && emptyCount == 2) return 5; 
    if (playerCount == 2 && emptyCount == 2) return -5; 
    return tieScore; 
}






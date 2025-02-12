#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : Character::Character(), depth(0), looseScore(-10), tieScore(0), winScore(10)
{
    r = { 0.0f,0.0f,0.0f,0.0f };
}

void Enemy::PlaceXOPublic(char XorO, Vector2 position, std::vector<char>& board, char otherXorO)
{
     PlaceXO(XorO, position, board,otherXorO);
}



std::pair<int,int> Enemy::BestMove(std::vector<char>& board, char XorO, char XorOPlayer)
{
    int bestScores = INT_MIN;
    std::pair<int,int> bestMove{ -2.0f,-2.0f };


    for (int i = 0; i < board.size(); i++) 
    {
        int row = i / 4; 
        int col = i % 4;


        if (board.at(i) == ' ') {
            board.at(i) = XorO;

            int _bestScores = MinMax(board, 0, false, XorO, XorOPlayer, INT_MIN, INT_MAX);
            board.at(i) = ' ';


            if (bestScores <= _bestScores) {
                bestScores = _bestScores;
                bestMove = {col,row};
            }
        }
    }
    return bestMove;
}

int Enemy::MinMax(std::vector<char>& board, int depth, bool isMaximising, char XorOEnemy, char XorOPlayer, int alpha, int beta)
{    
    if (depth >= maxDepth) return evaluateBoard(board, XorOEnemy, XorOPlayer);
    if (checkWin(board, 'O', false, r)) return winScore - depth;
    if (checkWin(board, 'X', false, r)) return looseScore + depth;
    if (isFull(board)) return tieScore;
    

    if (isMaximising) {
        int bestScore = INT_MIN;
        for (int i = 0; i < board.size(); i++)
        {
            if (board.at(i) == ' ')
            {
                board[i] =  XorOEnemy;

                int moveScore = MinMax(board, depth + 1, false, XorOEnemy, XorOPlayer, alpha, beta);

                board[i] = ' ';

                bestScore = std::max(bestScore, moveScore);
                alpha = std::max(alpha, bestScore);
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
            if (board.at(i) == ' ')
            {
                board[i] = XorOPlayer;

                int moveScore = MinMax(board, depth + 1, true, XorOEnemy, XorOPlayer, alpha, beta);

                board[i] = ' ';


                    bestScore = std::min(bestScore, moveScore);
                    beta = std::min(beta, bestScore);
                if (beta <= alpha) {
                    break;
                }
               
            }
        }

        return bestScore;
    }
    
}

void Enemy::PlaceXO(char XorO, Vector2 position, std::vector<char>& board, char otherXorO)
{
        int row = BestMove(board, XorO, otherXorO).second;
        int col = BestMove(board, XorO, otherXorO).first;
        int index = row * 4 + col ;

        if (index >= 0 && index < graphXO.size() && board.at(index) == ' ')
        {
            board.at(index) = XorO;
        }

}



int Enemy::evaluateBoard(const std::vector<char>& board, const char& XorOEnemy, const char& XorOPlayer)
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

int Enemy::evaluateLine(const std::vector<char>& board, int start, int step, const char& XorOEnemy, const char& XorOPlayer) {
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







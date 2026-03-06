#include "game.h"
#include <string>

Game::Game()
{
    Reset();
}

bool Game::Place(int x, int y)
{
    if (x < 0 || x > 2 || y < 0 || y > 2)
    {
        return false;
    }

    if (winner != 0)
    {
        return false;
    }

    if (board[y][x] != 0)
    {
        return false;
    }

    board[y][x] = currPlayer;

    CheckWinner();

    if (winner == 0)
    {
        if (currPlayer == 1)
        {
            currPlayer = 2;
        }
        else
        {
            currPlayer = 1;
        }
    }

    return true;
}

void Game::CheckWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            winner = board[i][0];
            return;
        }

        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            winner = board[0][i];
            return;
        }

       
    }

    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        winner = board[0][0];
        return;
    }

    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        winner = board[0][2];
        return;
    }

}

void Game::Reset()
{
    memset(board, 0, sizeof(board));
    currPlayer = 1;
    winner = 0;
}

int Game::GetCall(int x, int y)
{
    return board[y][x];
}

int Game::GetCurrentPlayer()
{
    return currPlayer;
}

int Game::GetWinner()
{
    return winner;
}

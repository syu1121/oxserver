#pragma once



class Game
{
private:
    int board[3][3];
    int currPlayer;
    int winner;

public:
    Game();
    bool Place(int x, int y);
    void CheckWinner();
    void Reset();

    int GetCall(int x, int y);
    int GetCurrentPlayer();
    int GetWinner();
    

};

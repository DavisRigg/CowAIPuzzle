#include <deque>
using namespace std;
class Gameboard { 
  public:
    int x = 1432; // x and y are the location of the new cow to be placed
    int y = 1432;
    int n; //variable for grid size
    int score = -1; //the score of the board
    deque<deque<char>> board; //2d deque containing the current board
    Gameboard() {}; //default constructor for Gameboard
    Gameboard(int c) //constructor for Gameboard
    {
      n = c;
      board.resize(n);
      for (int i = 0; i < n; i++) 
      {
        board.at(i).resize(n);
        for (int j = 0; j < n; j++) 
        { 
          board[i][j] = '.';
        }
    }
    };
    Gameboard(deque<deque<char>> copy, int c) //constructor for Gameboard
    {
      n = c;
      board.resize(n);
      for (int i = 0; i < n; i++) 
      {
        board.at(i).resize(n);
        for (int j = 0; j < n; j++) 
        { 
          board[i][j] = copy[i][j];
        }
    }
    };
    Gameboard operator=(Gameboard copy) //overloaded assignment operator for Gameboard
    {
      n = copy.n;
      score = copy.score;
      for (int i = 0; i < n; i++) 
      {
        for (int j = 0; j < n; j++) 
        { 
          board[i][j] = copy.board[i][j];
        }
      }
      return *this;
    };
    void calculatescore();
    void changeboard();
};
void Gameboard::changeboard() //changes board when not first iteration
{
  if(x != 1432 and y != 1432)
    board[x][y] = 'C';
}
void Gameboard::calculatescore() //score calculation
{
  int totalpoint = 0;
  int a = 0, b = 0;
  bool cowflag = false, hayflag = false, pondflag = false;
  while (a < n) 
  {
    while (b < n) 
    {
      if (board[a][b] == 'C') 
      {
        if (a != 0) 
        {
          if (board[a - 1][b] == '@')
            hayflag = true;
          if (board[a - 1][b] == '#')
            pondflag = true;
          if (board[a - 1][b] == 'C')
            cowflag = true;
        }
        if (a != n - 1) 
        {
          if (board[a + 1][b] == '@')
            hayflag = true;
          if (board[a + 1][b] == '#')
            pondflag = true;
          if (board[a + 1][b] == 'C')
            cowflag = true;
        }
        if (b != 0) 
        {
          if (board[a][b - 1] == '@')
            hayflag = true;
          if (board[a][b - 1] == '#')
            pondflag = true;
          if (board[a][b - 1] == 'C')
            cowflag = true;
        }
        if (b != n - 1) 
        {
          if (board[a][b + 1] == '@')
            hayflag = true;
          if (board[a][b + 1] == '#')
            pondflag = true;
          if (board[a][b + 1] == 'C')
            cowflag = true;
        }
        if (b != 0 && a != 0)
          if (board[a - 1][b - 1] == 'C')
            cowflag = true;
        if (b != n - 1 && a != 0)
          if (board[a - 1][b + 1] == 'C')
            cowflag = true;
        if (b != 0 && a != n - 1)
          if (board[a + 1][b - 1] == 'C')
            cowflag = true;
        if (b != n - 1 && a != n - 1)
          if (board[a + 1][b + 1] == 'C')
            cowflag = true;
        if (cowflag == true)
          totalpoint = totalpoint - 3;
        if (hayflag == true && pondflag == true)
          totalpoint = totalpoint + 3;
        else if (hayflag == true)
          totalpoint = totalpoint + 1;
        cowflag = false;
        hayflag = false;
        pondflag = false;
      }
      b++;
    }
    a++;
    b = 0;
  }
  score = totalpoint;
}
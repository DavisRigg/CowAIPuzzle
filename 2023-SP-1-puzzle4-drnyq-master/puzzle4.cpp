//Davis Rigg
#include <iostream>
#include <bits/stdc++.h>
#include <deque>
#include "gameboard.h"
using namespace std;
struct CompareScore { //orders entries into the priority
    bool operator()(Gameboard const& p1, Gameboard const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.score < p2.score;
    }
};
int main() 
{
  int n, x = 0, y = 0, cow = 0, cowcount = 0;
  // input grid size
  cin >> n;
  cout << n << endl;
  deque<deque<char>> field;
  field.resize(n);
  // create grid off of input
  while (y < n) 
  {
    field.at(y).resize(n);
    while (x < n) 
    {
      cin >> field[y][x];
      x++;
    }
    y++;
    x = 0;
  }
  y = 0;
   while (y < n) //loop to count haystacks/amount of cows to be placed
  {
    while (x < n) 
    {
      if (field[y][x] == '@')
        cow++;
      x++;
    }
    y++;
    x = 0;
  }
  y= 0;
  int oldscore = 0;
  bool up;
  Gameboard original(field, n);
  Gameboard copy = original;
  priority_queue<Gameboard, deque<Gameboard>, CompareScore> frontier; //priority queue that will hold all variations
  frontier.push(original);
  //Main best first search function
  while(!frontier.empty())
      {
        cowcount = 0;
      while (y < n) //loop to check if the proper amount of cows has been placed
      {
          while (x < n) 
          {
            if (frontier.top().board[y][x] == 'C')
              cowcount++;
            x++;
          }
        y++;
        x = 0;
      }
      y = 0;
      if(cowcount == cow)
        break;
      copy.board = frontier.top().board;
      while(x < n)
        {
          while(y < n)
            {
              if(copy.board[x][y] == '.')
              {
                up = true;
                original = copy; //copies all previous cows onto original
                original.x = x; //x and y variables to current cow
                original.y = y;
                original.changeboard(); //changes board variable to hold current cow
                original.calculatescore(); //update score to reflect new board
                if(frontier.top().score < original.score)
                { //these make sure each new cow is positive, no useless cows
                  frontier.push(original); //push new Gameboards to the frontier
                }
              }
              y++;
            }
          y = 0;
          x++;
        }
      y = 0;
      x = 0;
    }
  while (y < n)  //print solving board to file
  {
    while (x < n) 
    {
      cout << frontier.top().board[y][x];
      x++;
    }
    y++;
    x = 0;
    cout << endl;
  }
  cout << frontier.top().score;
}
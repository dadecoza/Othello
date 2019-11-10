/*
* MIT License
* 
* Copyright (c) 2019 Johannes le Roux (@dadecoza)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "othello.h"

void set_piece(int x, int y, piece p)
{
  switch (p)
  {
    case black:
      board[x] |= 1UL << y;
      break;

    case white:
      board[x] &= ~(1UL << y);
      break;
  }
  blank[x] |= (1UL << y);
}

piece check_piece(int x, int y)
{
  if ((x < 0)||( x > 8))
  {
    return none;
  }
  else if ((y < 0)||(y > 8))
  {
    return none;
  }
  else if (!((blank[x] >> y) & 1U))
  {
    return none;
  }
  else if ((board[x] >> y) & 1U) 
  {
    return black;
  }
  return white;
}

unsigned int flip(int x, int y, piece p, int flip)
{
  if ((blank[x] >> y) & 1U) 
  {
    return 0;
  }
  int i, xd, yd, xc, yc, tc;
  piece o = (p == white) ? black : white;
  int count = 0;
  for (xd = -1; xd < 2; xd++)
  {
    for (yd = -1; yd < 2; yd++)
    {
      xc = x + xd;
      yc = y + yd;
      tc = 0;
      piece pc = check_piece(xc, yc);
      while (pc == o)
      {
        xc = xc + xd;
        yc = yc + yd;
        tc++;
        pc = check_piece(xc, yc);
      }
      if (pc == p)
      {
        count += tc;
        if (flip)
        {
          xc = x + xd;
          yc = y + yd;
          piece pc = check_piece(xc, yc);
          while (pc == o)
          {
            set_piece(xc, yc, p);
            xc = xc + xd;
            yc = yc + yd;
            pc = check_piece(xc, yc);
          }
          set_piece(x, y, p);
        }
      }
    }
  }
  return count;
}

unsigned int computer_play(piece p)
{
  int x, y;
  int bestx = 0;
  int besty = 0;
  int best_flips = 0;
  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      int flips = flip(x, y, p, 0);
      if (flips > best_flips)
      {
        bestx = x;
        besty = y;
        best_flips = flips; 
      }
    }
  }
  return flip(bestx, besty, p, 1);
}

unsigned int human_play(int playx, int playy, piece p)
{  
  return flip(playx, playy, p, 1);
}

unsigned int moves_left()
{
  int i;
  for (i = 0; i < 8; i++)
  {
    if (blank[i] < 0xFF)
    {
      return 1;
    }
  }
  return 0;
}

unsigned int can_play(piece p)
{
  int x, y, flips;
  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      flips = flip(x, y, p, 0);
      if (flips > 0)
      {
        return 1;
      }
    }
  }
  return 0;
}

unsigned int count(piece p)
{
  int count = 0;
  int x,y;
  for (x = 0; x < 8; x++)
  {
    for (y = 0; y < 8; y++)
    {
      if (check_piece(x, y) == p)
      {
        count++;
      }
    }
  }
  return count;
}

void initialize_game()
{
  int i;
  for (i = 0; i < 8; i++)
  {
    blank[i] = 0;
    board[i] = 0;
  }
  set_piece(3, 3, black);
  set_piece(3, 4, white);
  set_piece(4, 3, white);
  set_piece(4, 4, black);
}

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

#ifndef OTHELLO_H_
#define OTHELLO_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  none,
  black,
  white    
}
piece;

extern unsigned char blank[8];
extern unsigned char board[8];

void set_piece(int, int, piece);
piece check_piece(int, int);
unsigned int flip(int, int, piece, int);
unsigned int computer_play(piece);
unsigned int human_play(int, int, piece);
unsigned int moves_left(void);
unsigned int can_play(piece);
unsigned int count(piece);
void initialize_game(void);

#ifdef __cplusplus
}
#endif

#endif // OTHELLO_H_

// Othello
#include "othello.h"

unsigned char blank[8];
unsigned char board[8];
boolean next_turn = false;

static char inchar()
{
  while (Serial.available() == 0)
  {
    delay(20);
  }
  return Serial.read();
}

int innum()
{
  int c = inchar();
  while ((c < 48)||(c > 71))
  {
    Serial.write(7);
    c = inchar();
  }
  return c - 48;
}

void draw_board()
{
  Serial.println("\r");
  Serial.println(" | 0| 1| 2| 3| 4| 5| 6| 7|\r");
  Serial.println("--------------------------\r");
  int x, y;
  for (x = 0; x < 8; x++)
  {
    Serial.print(x);
    Serial.print("|");
    for (y = 0; y < 8; y++)
    {
      switch (check_piece(x, y))
      {
        case black:
          Serial.print(" X|");
          break;
          
        case white:
          Serial.print(" O|");
          break;
          
        case none:
          Serial.print("  |");
          break;
      }
    }
    if (x == 3)
    {
      Serial.print(" Human X:");
      Serial.print(count(black));
    }
    else if (x == 4)
    {
      Serial.print(" Comp. O:");
      Serial.print(count(white));
    }
    Serial.println("\r");
    Serial.println("--------------------------\r");
  }
}

void setup()
{
  Serial.begin(2400);
  delay(500);
  Serial.write(20); //disable cursor
  Serial.write(12); // clear screen
  Serial.println("\r\n\r\n\r\n\r");
  Serial.println("          _   _          _ _\r");
  Serial.println("     ___ | |_| |__   ___| | | ___\r");
  Serial.println("    / _ \\| __| '_ \\ / _ \\ | |/ _ \\\r"); 
  Serial.println("   | (_) | |_| | | |  __/ | | (_) |\r");
  Serial.println("    \\___/ \\__|_| |_|\\___|_|_|\\___/ \r");
  Serial.println("\r");
  Serial.println("            2019 @dadecoza\r");
  Serial.println("\r");
  Serial.println("       Press any key to play ...\r");
  inchar();
  Serial.write(12);
}

void loop()
{
  initialize_game();
  draw_board();
  while(moves_left())
  {
    piece p = (next_turn) ? white : black;
    next_turn = !next_turn;
    if (can_play(p))
    {
      if ( p == white )
      {
        Serial.print("Thinking ...\r");
        delay(2000);
        Serial.println("            \r");
        computer_play(p);
      }
      else
      {
        int x, y;
        do
        {
          Serial.print("Move?");
          x = innum();
          y = innum();
          Serial.println("\r");
        } while (human_play(x,y,p) == 0);
      }
      draw_board();
    } else {
      Serial.println("Skip!\r");    
    }
  }
  Serial.println("Game Over!\r");
  Serial.println("Press any key to play again ...\r");
  inchar();
}

/*
  score.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/


#ifndef score_h
#define score_h

#include "Arduino.h"

class Score
{
  public:
  Score(bool);
  void set_debug(bool);
  
  int get_score();
  
  int update_score(int);

  int get_level();

  int get_lines();

  int get_game_speed();
  
  private:
  bool debug;
  
  int score;
  void reset_score();

  
  
  int level;
  int rows_to_level_up_fixed;
  void reset_level();
  void update_level();

  
  int lines;
  void reset_lines();
  void update_lines(int);
  
  
  int game_speed;
  void set_game_speed();
  
  
};
#endif

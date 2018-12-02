/*
  color.cpp - Library for generating colors for andom tetris pieces.
  Created by Skye Perry, Dec 1, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#include "color.h"

ColorScheme::ColorScheme(){
  for(int i = 0; i < 8; i++){
    //active_scheme[i] = classic[i];
    active_scheme[i] = warm_xmas[i];
  }
}

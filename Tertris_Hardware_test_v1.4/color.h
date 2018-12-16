/*
  color.h - Library for generating colors for andom tetris pieces.
  Created by Skye Perry, Dec 1, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#ifndef color_h
#define color_h
#include <FastLED.h>
#include "Arduino.h"

#define SEQUENCETOTAL 7

class ColorScheme
{
  public:
  
  ColorScheme();

  void set_color_scheme(String);

  CRGB active_scheme[8];
  
  void debug_print();
  
  
  
  
  
  private:

  CRGB classic[8] = {
                     CRGB(0,0,0), // Blank
                     CRGB(255, 123, 0),  //l_periscope
                     CRGB(112, 236, 239),  //stick
                     CRGB(255, 255, 0),  //square             
                     CRGB(0, 24, 230),  //r_periscope
                     CRGB(255, 0, 0),  //l_dog
                     CRGB(67, 255, 0),   //r_dog
                     CRGB(195, 0, 255)   //tee
                    };

  
  CRGB warm_xmas[8] = {
                     CRGB(3,3,3), // Blank
                     CRGB(155, 182, 88),  //l_periscope
                     CRGB(255,255,240),  //stick
                     CRGB(78,39,24),  //square             
                     CRGB(161,16,11),  //r_periscope
                     CRGB(31,64,10),  //l_dog
                     CRGB(161,16,11),   //r_dog
                     CRGB(31,64,10)   //tee
                      };
  
};
#endif

/*
  display.h - Library for handling LED matrix tetris display
  Created by Skye Perry, Dec 2, 2018.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/



#ifndef display_h
#define display_h
#include "Arduino.h"

#include "color.h"

/* Tetris LED Display
 * 
 */
#include <FastLED.h>
#define NUM_LEDS 200
#define FASTLED_DATA_PIN 2
// Define the array of leds



class Display
{
  public:
  CRGB leds[NUM_LEDS];
  Display();
  void initialize();
  ColorScheme color_scheme;

  void render(int gameboard[10][28]);

 void animate_erase_row(int);
  
  private:

  int get_led_index(int, int);
  
  
};
#endif

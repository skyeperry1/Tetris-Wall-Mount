/*
  Scoreboard.cpp - Library for running Tetris wall mount scoreboard.
  Created by Skye Perry, Dec 8, 2018.
  Released into the public domain.
*/


#ifndef scoreboard_h
#define scoreboard_h

#include "Arduino.h"

#include "DigitLedDisplay.h"

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN  18 // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    5  // or SS


class Scoreboard
{
  public:  
  Scoreboard();
  MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

  DigitLedDisplay ld = DigitLedDisplay(12,  13,14);
  
  void update_state();

  void print_score(int,int,int);
  void print_message(String);
  
  int state;
  void print_credits(int);
  void initialize();
  void debug_print();
  
  private:
  void update_segment_display(int , int);
  
  String format_int_string(String);
  String doubleToString(double input,int decimalPlaces);
};
#endif

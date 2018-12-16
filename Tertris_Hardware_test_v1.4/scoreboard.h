/*
  score.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/


#ifndef scoreboard_h
#define scoreboard_h

#include "Arduino.h"


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
  void update_state();

  void print_score(int,int);
  void print_message(String);
  
  
  void initialize();
  void debug_print();
  
  private:
  int state;
  String format_int_string(String);
  String doubleToString(double input,int decimalPlaces);
};
#endif
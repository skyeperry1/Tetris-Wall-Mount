/*
  Scoreboard.cpp - Library for running Tetris wall mount scoreboard.
  Created by Skye Perry, Dec 8, 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "scoreboard.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted


// Hardware SPI connection


uint8_t frameDelay = 25;  // default frame delay value
#define SPEED_TIME  25
#define PAUSE_TIME  2000

#define BUF_SIZE 2000 


char pd_message2[BUF_SIZE] = { "" };

// Global scorboard variables
uint8_t  curText;


char  *active_state[BUF_SIZE] =
{
  "Score",
  "0",
  "Level",
  "0"
};



char  *default_state[BUF_SIZE] =
{
  "Game",
  "Over",
  "Insert",
  "Coin"
};

char  *ready_state[BUF_SIZE] =
{
  "Game",
  "Over",
  "Insert",
  "Coin"
};

uint8_t  inFX, outFX;
textEffect_t  effect[] =
{
  PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_CLOSING,
  PA_RANDOM,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  //PA_DISSOLVE, //takes too long
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  //PA_SLICE, //takes too long
  PA_SCROLL_DOWN,
};

Scoreboard::Scoreboard(){
  state = 0;
}

void Scoreboard::initialize(){
  
  P.begin();
  P.setInvert(false);
  //P.displayText(active_state[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
  P.displayText("+scrbrd", PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate();
  delay(1000);



  ld.setBright(20);
  /* Set the digit count */
  ld.setDigitLimit(8);  
    for (int i = 0; i <= 8; i++) {
    /* Select Digit 5 and write B01100011 */
    ld.write(i, B01100011);
    delay(100);

    /* Select Digit 5 and write B00011101 */
    ld.write(i, B00011101);
    delay(100);
  }  
  ld.clear();
  
}


void Scoreboard::update_state(){
  if (P.displayAnimate()) // animates and returns true when an animation is completed
  {
    // Set the display for the next string.
    //curText = ++curText;
    curText >= 3? curText = 0: curText = curText + 1;
    P.setTextBuffer(active_state[curText]);

    // When we have gone back to the first string, set a new exit effect
    // and when we have done all those set a new entry effect.
    if (curText == 0)
    {
      outFX = (++outFX) % ARRAY_SIZE(effect);
      if (outFX == 0)
      {
        inFX = (++inFX) % ARRAY_SIZE(effect);
        if (inFX == 0)
          P.setInvert(!P.getInvert());
      }
      
      P.setTextEffect(effect[inFX], PA_SCROLL_LEFT);//effect[outFX]);

    }

    // Tell Parola we have a new animation
    P.displayReset();
  }  
  
  
}

void Scoreboard::debug_print(){
  
}


//Helper for converting coin value to string values for scoreboard
String Scoreboard::doubleToString(double input,int decimalPlaces){
  if(decimalPlaces!=0){
      String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1){
    if(input>0)
      string = "0"+string;
    else if(input<0)
      string = string.substring(0,1)+"0"+string.substring(1);
    }
      return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
    }
    else {
      return String((int)input);
  }
}


void Scoreboard::print_score(int score, int level,int rows){  
  String score_string = (String)score;//doubleToString(score,0);
  score_string = format_int_string(score_string);
  char str2[BUF_SIZE] = {""};
  score_string.toCharArray(str2, BUF_SIZE);
  format_int_string(score_string);
           
  active_state[1] = (char *)malloc(strlen(str2)+1);
  strcpy(active_state[1],str2);

  String level_string = (String)level;//doubleToString(score,0);
  char str3[BUF_SIZE] = {""};
  level_string.toCharArray(str3, BUF_SIZE);         
  active_state[3] = (char *)malloc(strlen(str3)+1);
  strcpy(active_state[3],str3);
  //curText = 1;

  update_segment_display(rows,level);
}

String Scoreboard::format_int_string(String arg_string){

  int arg_size = arg_string.length() - 1;
  char str[BUF_SIZE] = {""};
  arg_string.toCharArray(str, BUF_SIZE);  

  
  String formatted_string = "";
  int counter = 1;
  for(int i = arg_size; i >= 0 ; i --){
    formatted_string = (String)str[i] + formatted_string;
    counter % 3 == 0 && i!= 0 ? formatted_string = "," + formatted_string: "";
    ++counter;
  }
  //Serial.println(formatted_string);
  return formatted_string;
}

void Scoreboard::print_message(String message){
  char str2[BUF_SIZE] = {""};
  message.toCharArray(str2, BUF_SIZE);         
  active_state[1] = (char *)malloc(strlen(str2)+1);
  strcpy(active_state[1],str2);
  //curText = 0;
}



void Scoreboard::update_segment_display(int rows, int level){
    
  int first_segment_offset = 8 - (int)String(rows).length();
  ld.clear();
  ld.printDigit( rows, first_segment_offset);
  ld.printDigit( level,0);
}



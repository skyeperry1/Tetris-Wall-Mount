/*
  display.cpp - Library for handling LED matrix tetris display
  Created by Skye Perry, Dec 2, 2018.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#include "display.h"

Display::Display(){
}


void Display::render(int gameboard[10][28]){
  int led_index = 0;
 //for(int y = 20 - 1; y >= 0; y--){
 for(int y = 0 ; y < 20; y++){
            for(int x = 0; x < 10; x++){
              
                led_index = Display::get_led_index( x,  y);             

              if(gameboard[x][y]== 1){
                leds[led_index ] = color_scheme.active_scheme[1];      
              } else if(gameboard[x][y]== 2){
                leds[led_index ] = color_scheme.active_scheme[2];               
              } else if(gameboard[x][y]== 3){
                leds[led_index ] = color_scheme.active_scheme[3];               
              } else if(gameboard[x][y]== 4){
                leds[led_index ] = color_scheme.active_scheme[4];               
              }else if(gameboard[x][y]== 5){
                leds[led_index ] = color_scheme.active_scheme[5];               
              } else if(gameboard[x][y]== 6){
                leds[led_index ] = color_scheme.active_scheme[6];               
              } else if(gameboard[x][y]== 7){
                leds[led_index ] = color_scheme.active_scheme[7];               
              } else {
                leds[led_index ] = color_scheme.active_scheme[0];               
              }
              
            }
   }
   FastLED.show();
}





int Display::get_led_index(int x, int y){
 if(x % 2 == 0 ){
    return 20 * x + (19 -y);
  } else {  
    return 20 * x + y;  
  }  
}


void Display::initialize(){
  FastLED.addLeds<NEOPIXEL, FASTLED_DATA_PIN>(leds, NUM_LEDS);
  for(int x = 0; x < 200 ; x++){
              
                  leds[x ] = CRGB(random(0,50),random(0,50),random(0,50));//CRGB(100,27,20);
                  FastLED.show();
                  delay(1);
       }
         for(int x = 0; x < 200 ; x++){
              
                  leds[x ] = CRGB(0,0,0);//CRGB(100,27,20);
                  FastLED.show();
                  delay(1);
       }
  
}



void Display::animate_erase_row(int row){
      int high = 200;
      int med = 125;
      int low = 50;
      int finish = 0;
      int delay_val = 30;

      
      leds[get_led_index(4,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      leds[get_led_index(5,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(4,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(5,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(3,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      leds[get_led_index(6,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(4,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(5,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(3,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(6,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(2,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      leds[get_led_index(7,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      FastLED.show();
      delay(delay_val); 

      //leds[get_led_index(3,row)] = CRGB(finish,finish,finish);
      //leds[get_led_index(3,row)] = CRGB(low,low,low);
      
      leds[get_led_index(3,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(6,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(2,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(7,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(1,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      leds[get_led_index(8,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(2,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(7,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(1,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(8,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(0,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      leds[get_led_index(9,row)] = CRGB(random(high -50,high +50),random(high-50,high +50),random(high-50,high +50));
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(1,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(8,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(0,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      leds[get_led_index(9,row)] = CRGB(random(med -50, med +50),random(med-50,med +50),random(med-50,med +50));
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(0,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));
      leds[get_led_index(9,row)] = CRGB(random(low -50, low ),random(low-50,low ),random(low-50,low ));

      FastLED.show();
  
}


/*
void Display::animate_erase_row(int row){
      int high = 200;
      int med = 125;
      int low = 50;
      int finish = 0;
      int delay_val = 30;
  
      leds[get_led_index(4,row)] = CRGB(high,high,high);
      leds[get_led_index(5,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(4,row)] = CRGB(med,med,med);
      leds[get_led_index(5,row)] = CRGB(med,med,med);
      leds[get_led_index(3,row)] = CRGB(high,high,high);
      leds[get_led_index(6,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(4,row)] = CRGB(low,low,low);
      leds[get_led_index(5,row)] = CRGB(low,low,low);
      leds[get_led_index(3,row)] = CRGB(med,med,med);
      leds[get_led_index(6,row)] = CRGB(med,med,med);
      leds[get_led_index(2,row)] = CRGB(high,high,high);
      leds[get_led_index(7,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      //leds[get_led_index(3,row)] = CRGB(finish,finish,finish);
      //leds[get_led_index(3,row)] = CRGB(low,low,low);
      
      leds[get_led_index(3,row)] = CRGB(low,low,low);
      leds[get_led_index(6,row)] = CRGB(low,low,low);
      leds[get_led_index(2,row)] = CRGB(med,med,med);
      leds[get_led_index(7,row)] = CRGB(med,med,med);
      leds[get_led_index(1,row)] = CRGB(high,high,high);
      leds[get_led_index(8,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(2,row)] = CRGB(low,low,low);
      leds[get_led_index(7,row)] = CRGB(low,low,low);
      leds[get_led_index(1,row)] = CRGB(med,med,med);
      leds[get_led_index(8,row)] = CRGB(med,med,med);
      leds[get_led_index(0,row)] = CRGB(high,high,high);
      leds[get_led_index(9,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(1,row)] = CRGB(low,low,low);
      leds[get_led_index(8,row)] = CRGB(low,low,low);
      leds[get_led_index(0,row)] = CRGB(med,med,med);
      leds[get_led_index(9,row)] = CRGB(med,med,med);
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(0,row)] = CRGB(low,low,low);
      leds[get_led_index(9,row)] = CRGB(low,low,low);

      FastLED.show();
  
}*/

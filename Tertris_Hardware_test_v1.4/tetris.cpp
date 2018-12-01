/*
  Tetris.cpp - Library for flashing Tetros code.
  Created by Skye Perry, November 22, 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "tetris.h"

Score score(true);
Randomizer randomizer;

/* Tetris LED Display
 * 
 */
#include <FastLED.h>
#define NUM_LEDS 200
#define FASTLED_DATA_PIN 2
// Define the array of leds
CRGB leds[NUM_LEDS];

void Tetris::testDisplay(){
  int led_index = 0;
 //for(int y = 20 - 1; y >= 0; y--){
 for(int y = 0 ; y < 20; y++){
            for(int x = 0; x < 10; x++){

              if(x % 2 == 0 ){
                led_index = 20 * x + (19 -y);
              } else {  
                led_index = 20 * x + y;  
              }

              if(gameboard.active_state[x][y]== 1){
                leds[led_index ] = color_scheme.active_scheme[1];      
              } else if(gameboard.active_state[x][y]== 2){
                leds[led_index ] = color_scheme.active_scheme[2];               
              } else if(gameboard.active_state[x][y]== 3){
                leds[led_index ] = color_scheme.active_scheme[3];               
              } else if(gameboard.active_state[x][y]== 4){
                leds[led_index ] = color_scheme.active_scheme[4];               
              }else if(gameboard.active_state[x][y]== 5){
                leds[led_index ] = color_scheme.active_scheme[5];               
              } else if(gameboard.active_state[x][y]== 6){
                leds[led_index ] = color_scheme.active_scheme[6];               
              } else if(gameboard.active_state[x][y]== 7){
                leds[led_index ] = color_scheme.active_scheme[7];               
              } else {
                leds[led_index ] = color_scheme.active_scheme[0];               ;
              }
              
            }
   }
   FastLED.show();
}


int get_led_index(int x, int y){
 if(x % 2 == 0 ){
    return 20 * x + (19 -y);
  } else {  
    return 20 * x + y;  
  }  
}

void animate_erase_row(int row){
      int high = 100;
      int med = 50;
      int delay_val = 10;
  
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

      leds[get_led_index(4,row)] = CRGB(1,1,1);
      leds[get_led_index(5,row)] = CRGB(1,1,1);
      leds[get_led_index(3,row)] = CRGB(med,med,med);
      leds[get_led_index(6,row)] = CRGB(med,med,med);
      leds[get_led_index(2,row)] = CRGB(high,high,high);
      leds[get_led_index(7,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(3,row)] = CRGB(1,1,1);
      leds[get_led_index(6,row)] = CRGB(1,1,1);
      leds[get_led_index(2,row)] = CRGB(med,med,med);
      leds[get_led_index(7,row)] = CRGB(med,med,med);
      leds[get_led_index(1,row)] = CRGB(high,high,high);
      leds[get_led_index(8,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val); 

      leds[get_led_index(2,row)] = CRGB(1,1,1);
      leds[get_led_index(7,row)] = CRGB(1,1,1);
      leds[get_led_index(1,row)] = CRGB(med,med,med);
      leds[get_led_index(8,row)] = CRGB(med,med,med);
      leds[get_led_index(0,row)] = CRGB(high,high,high);
      leds[get_led_index(9,row)] = CRGB(high,high,high);
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(1,row)] = CRGB(1,1,1);
      leds[get_led_index(8,row)] = CRGB(1,1,1);
      leds[get_led_index(0,row)] = CRGB(med,med,med);
      leds[get_led_index(9,row)] = CRGB(med,med,med);
      FastLED.show();
      delay(delay_val);

      leds[get_led_index(0,row)] = CRGB(1,1,1);
      leds[get_led_index(9,row)] = CRGB(1,1,1);

      FastLED.show();
  
}



Tetris::Tetris()
{
  Serial.begin(115200);
  Serial.println("Starting Tetris...");
  score.set_debug(true);

  
  create_new_piece();
  
  lastUpdate = millis();
 
}


void Tetris::init_hardware(){
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

/* Public: update_game_state()
 * this function should be called every loop to run the game
 * 
 */
void Tetris::update_game_state(){
  int currentTime = millis();

  if(currentTime - lastUpdate > score.get_game_speed()){
    move_piece_down();
    //tetromino.debug_print();
    //gameboard.debug_print_active_state();
    lastUpdate = currentTime;
  }  
  //tetromino.debug_print();
  testDisplay();
}















/* Private: reset_player_location()
 * Reset the player x,y location to the top center of the board of the board
 * This is the starting x,y coordinate where the falling piece is rendered 
 */
 
void Tetris::reset_player_location(){  
  player_location_x = 3;
  player_location_y = 20;
  //Serial.println("resetPlayerLocation() resetting piece render index to the top of the board ("+(String)player_location_x+","+(String)player_location_y+")");
  return;  
}








/* Public: rotate_piece()
 * Rotates the active piece 90 degrees CCW, by incrementing the piece_rotation_index
 * This checks for collisions and will only make valid rotations when no collision occurs
 */

void Tetris::rotate_piece(){
  tetromino.rotate(1);
  gameboard.remove_tetromino(active_piece_tile_coordinates);
  set_active_piece_coordiantes();
 if(gameboard.check_for_collision(active_piece_tile_coordinates)){
    tetromino.rotate(-1);
    set_active_piece_coordiantes();
  }
  gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
  return;
}




/* Private move_player_location(int x, int y)
 * sets the player_location_x and player_location_y coordiantes to a new location
 * should also run collision detections here, maybe?
 */
 
void Tetris::move_player_location(int x, int y){ 
  

  player_location_x = player_location_x + x;
  player_location_y = player_location_y + y;  
  set_active_piece_coordiantes();

  
  return;
}



/* Public: move_piece_down()
 * moves the falling piece down 1 tile
 */
 
bool Tetris::move_piece_down(){  
  
  gameboard.remove_tetromino(active_piece_tile_coordinates);
  
  move_player_location(0, -1);
  
  if(gameboard.check_for_collision(active_piece_tile_coordinates)){
    move_player_location(0, 1);
    
    gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);

    process_complete_row();
    
    create_new_piece();
    //gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
    
    return true;
  } else {
  
  gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
  set_active_piece_coordiantes();
  
  return false;
  }
}



/* Public: move_piece_down()
 * moves the falling piece right 1 tile
 */
 
void Tetris::move_piece_left(){
  
  gameboard.remove_tetromino(active_piece_tile_coordinates);
  
  move_player_location(-1, 0);
  
  if(gameboard.check_for_collision(active_piece_tile_coordinates)){
     move_player_location(1, 0);  
  }  
  
  gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);

  return;
}



/* Public:move_piece_right()
 * moves the falling piece left 1 tile
 */
 
void Tetris::move_piece_right(){
 //This serves as a temp placeholder to revert back to if need be      

  
   gameboard.remove_tetromino(active_piece_tile_coordinates);


  //Move the player right
  move_player_location(1, 0);

  //Check for collision
  if(gameboard.check_for_collision(active_piece_tile_coordinates)){
    //Revert if collision is detected
     move_player_location(-1, 0);  
  }
  
   gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);

  return;  
}



/* Public: move_piece_to_floor()
 * moves the falling piece to the bottom of the gameboard
 */
 
void Tetris::move_piece_to_floor(){
  
    gameboard.remove_tetromino(active_piece_tile_coordinates);

   int closest_move = 28;
   for(int x = 0; x < 4; x++){
      //Serial.println("get drop height: " + (String)gameboard.get_drop_height(active_piece_tile_coordinates[x][0] ,active_piece_tile_coordinates[x][1]));
      if(gameboard.get_drop_height(active_piece_tile_coordinates[x][0] ,active_piece_tile_coordinates[x][1]) < closest_move){
        
        closest_move = gameboard.get_drop_height(active_piece_tile_coordinates[x][0] ,active_piece_tile_coordinates[x][1]);
        //Serial.println("closest_move:" + (String)closest_move);
      }
    } 

    
    //Serial.println("closest_move Move: " + (String)closest_move);
    move_player_location(0, -(closest_move));   
    gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
    testDisplay();
    process_complete_row();
    
        
    create_new_piece();
    
    return;

  
}



/* Private: move_piece_down()
 * translates the cuurent state active piece coordinetes with the current player location
 * into the active piece coordiantes array - the active_piece_tile_coordinates is what we can use for collision checking, 
 * rendering the game display output and placing pieces
 */
 
void Tetris::set_active_piece_coordiantes(){
  for(int x = 0; x < 4; x++){
      active_piece_tile_coordinates[x][0] = tetromino.active_tetromino[x][0] + player_location_x;
      active_piece_tile_coordinates[x][1] = tetromino.active_tetromino[x][1] + player_location_y;  
  } 
  
}



/* Private: render_new_piece()
 * This encapsulates and calls all the functions nessecary to render a random new piece at the
 * top of the gameboard. This resets the player location and piece_rotation_index to default.
 */
 
void Tetris::create_new_piece(){
  if(gameboard.check_for_top_out()){ Serial.println("**GAME OVER**");delay(10000);return;}
  reset_player_location();
  tetromino.init_new_tetromino();  
  set_active_piece_coordiantes();
  gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
  

  
  return;
}



void Tetris::process_complete_row(){  

  int offset = 0;
  int piece_tile_location_y;

    for(int x = 0;x < 4; x++ ){       
       piece_tile_location_y = active_piece_tile_coordinates[x][1]; // Get the y piece tile coordinates       
       if(gameboard.check_for_complete_row(piece_tile_location_y)){      
            animate_erase_row(piece_tile_location_y);
       }
    }
  

  
  for(int x = 0;x < 4; x++ ){  
     
     piece_tile_location_y = active_piece_tile_coordinates[x][1] - offset; // Get the y piece tile coordinates
     
     if(gameboard.check_for_complete_row(piece_tile_location_y)){ 
          gameboard.remove_row_from_gameboard(piece_tile_location_y);
          offset = offset  + 1;
     }
  }

  if(offset >= 1){
    score.update_score(offset);
  }

  return;
}









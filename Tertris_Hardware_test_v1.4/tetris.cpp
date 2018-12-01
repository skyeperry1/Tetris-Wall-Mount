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

              if(GameBoard[x][y]== 1){
                leds[led_index ] = CRGB(127,20,10);              
              } else if(GameBoard[x][y]== 2){
                leds[led_index ] = CRGB(17,88,62);              
              } else if(GameBoard[x][y]== 3){
                leds[led_index ] = CRGB(27,20,100);              
              } else if(GameBoard[x][y]== 4){
                leds[led_index ] = CRGB(150,150,10);              
              }else if(GameBoard[x][y]== 5){
                leds[led_index ] = CRGB(50,155,6);              
              } else {
                leds[led_index ] = CRGB(0,0,0);              ;
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

  
  initialize_gameboard();
  initialize_counters();
  create_new_piece();
  tetromino.debug_print();
  
  //serialPrintGameBoard();
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
    serialPrintGameBoard();
    lastUpdate = currentTime;
  }  
  tetromino.debug_print();
  testDisplay();
}



/* Public: serialPrintGameBoard()
 * Serial prints the gamboard state as integer values, formatted for arduino serial monitor
 * Prints the y axis of the array backwards so the xy coordiantes in the array are tranlated to the top right quadrent of a graph 
 */
 
void Tetris::serialPrintGameBoard(){
    Serial.println();
    Serial.println();
    Serial.println("**Current Score:**");
    Serial.println((String)score.get_score());
    Serial.println();
    Serial.println("**Current Gameboard State:**");
    for(int y = HEIGHT -1; y >= 0; y--){
      Serial.println();
      for(int x = 0; x < WIDTH; x++){
        Serial.print(GameBoard[x][y] );
      }      
    }
    Serial.println();
    Serial.println();
    return;    
}



/* Private: intialize_gameboard()                          
 * Sets each element of the Gamboard array to 0, effectivly resetting the gameboard                            
 * using the global WIDTH and HEIGHT defined in tetris.h                        
 */
 
void Tetris::initialize_gameboard(){
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){      
        GameBoard[x][y] = 0;
      }      
    }
    //Serial.println("intialize_gameboard() - Initialized new gameboard, all pixels set to 0");
    return;    
}



/* Private: initialize_counters()                      
 * Sets each element of the x_row_values adn y_column_values array to 0                           
 * using the global WIDTH and HEIGHT defined in tetris.h                        
 */
 
void Tetris::initialize_counters(){  
  for(int y = 0; y < HEIGHT; y++){
        x_row_values[y] = 0;
    }
    
    for(int x = 0; x < WIDTH; x++){      
            y_column_values[x] = 0;      
    } 
    //Serial.println("initialize_counters() - Initialized x_row_values and y_column_values, all elements set to 0");
    return;    
}



/* Private: update_counters()                      
 * updates the counters based on the new piece coordinates gameboard                           
 *                      
 */
 
void Tetris::update_counters(){  
    initialize_counters();
    remove_piece_from_gameboard();
    for(int x =0; x < WIDTH; x++){
     for(int y = 0; y < HEIGHT; y++){
       if(GameBoard[x][y] != 0){
          //x_row_values[y] = x_row_values[y] + 1;
          y_column_values[x] = y_column_values[x] + 1;
        }        
      }  
    }
    render_piece_to_gameboard();
}



/* Private: update_counters()                      
 * updates the counters based on the new piece coordinates gameboard                           
 *                      
 */
 
bool Tetris::check_for_loss(){  
   for(int x = 0; x < WIDTH; x++){  
           // Serial.println("** DEBUG: check_for_loss() - Column " + (String)x + " value: " + (String)GameBoard[x][24]);           
            if(GameBoard[x][24] != 0){
             // Serial.println("check_for_loss() - GAME OVER DETECTED");
              return true;
            }
    } 
    //Serial.println("check_for_loss() - no loss detected");
    return false;    
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
  //Check if iteration is at max and reset to zero, otherwise increment by 1
  //int prev_rotation = piece_rotation_index;
  //piece_rotation_index >=  3 ? piece_rotation_index = 0 : piece_rotation_index = piece_rotation_index + 1; 
  tetromino.rotate(1);
  remove_piece_from_gameboard();
  set_active_piece_coordiantes();
 if(check_for_collision()){
    tetromino.rotate(-1);
    set_active_piece_coordiantes();
    render_piece_to_gameboard();
    return;
  }
  render_piece_to_gameboard();
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

  //This serves as a temp placeholder to revert back to if need be      
  int prev_active_piece_tile_coordinates[4][2];
  
  remove_piece_from_gameboard();

  //store active state temporarily for if we need to revert
  for(int x = 0; x <4; x++){
    prev_active_piece_tile_coordinates[x][0] = active_piece_tile_coordinates[x][0];
    prev_active_piece_tile_coordinates[x][1] = active_piece_tile_coordinates[x][1];
  }
  
  move_player_location(0, -1);
  
  if(check_for_collision()){
    for(int x = 0; x <4; x++){
      active_piece_tile_coordinates[x][0] = prev_active_piece_tile_coordinates[x][0];
      active_piece_tile_coordinates[x][1] = prev_active_piece_tile_coordinates[x][1];
    } 
    render_piece_to_gameboard();
    //set_active_piece_coordiantes();
    process_complete_row();
    update_counters();
    
    create_new_piece();
    render_piece_to_gameboard();
    
    return true;
  } else {
  
  render_piece_to_gameboard();  
  process_complete_row();
  return false;
  }
}



/* Public: move_piece_down()
 * moves the falling piece right 1 tile
 */
 
void Tetris::move_piece_left(){
 

    //This serves as a temp placeholder to revert back to if need be      
  int prev_active_piece_tile_coordinates[4][2];
  
  remove_piece_from_gameboard();

  //store active state temporaroly for if we need to revert
  for(int x = 0; x <4; x++){
    prev_active_piece_tile_coordinates[x][0] = active_piece_tile_coordinates[x][0];
    prev_active_piece_tile_coordinates[x][1] = active_piece_tile_coordinates[x][1];
  }
  
  move_player_location(-1, 0);
  
  if(check_for_collision()){
    for(int x = 0; x <4; x++){
     
      active_piece_tile_coordinates[x][0] = prev_active_piece_tile_coordinates[x][0];
      active_piece_tile_coordinates[x][1] = prev_active_piece_tile_coordinates[x][1];
    }   
     move_player_location(1, 0);  
  }
  
  render_piece_to_gameboard();

  return;
}



/* Public: move_piece_down()
 * moves the falling piece left 1 tile
 */
 
void Tetris::move_piece_right(){
 //This serves as a temp placeholder to revert back to if need be      
  int prev_active_piece_tile_coordinates[4][2];
  
  remove_piece_from_gameboard();

  //store active state temporaroly for if we need to revert
  for(int x = 0; x <4; x++){
    prev_active_piece_tile_coordinates[x][0] = active_piece_tile_coordinates[x][0];
    prev_active_piece_tile_coordinates[x][1] = active_piece_tile_coordinates[x][1];
  }

  //Move the player right
  move_player_location(1, 0);


  //Check for collision
  if(check_for_collision()){
    for(int x = 0; x <4; x++){
     
      active_piece_tile_coordinates[x][0] = prev_active_piece_tile_coordinates[x][0];
      active_piece_tile_coordinates[x][1] = prev_active_piece_tile_coordinates[x][1];
    }   
    //Revert if collision is detected
     move_player_location(-1, 0);  
  }
  
  render_piece_to_gameboard();

  return;  
}



/* Public: move_piece_down()
 * moves the falling piece to the bottom of the gameboard
 */
 
void Tetris::move_piece_to_floor(){
  
   remove_piece_from_gameboard();

   int last_x;
   int closest_move = 28;
   for(int x = 0; x < 4; x++){
      if(active_piece_tile_coordinates[x][1] - y_column_values[active_piece_tile_coordinates[x][0]] < closest_move){
        
        closest_move = active_piece_tile_coordinates[x][1] - y_column_values[active_piece_tile_coordinates[x][0]];
        //Serial.println("closest_move:" + (String)closest_move);
      }
    } 

    move_player_location(0, -(closest_move));  
    set_active_piece_coordiantes();
    
    render_piece_to_gameboard();
    process_complete_row();
    update_counters();
    testDisplay();

    
    
    create_new_piece();
    render_piece_to_gameboard();
    
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
  tetromino.init_new_tetromino();
  reset_player_location();

  set_active_piece_coordiantes();

  if(check_for_loss()){ Serial.println("**GAME OVER**");delay(10000);return;}
  return;
}



/* Private: render_piece_in_gameboard()
 * erases the previous piece state from the gameboard and adds renders the updated position 
 * 
 * 
 */


void Tetris::render_piece_to_gameboard(){  
  
  int piece_tile_location_x, piece_tile_location_y;
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = active_piece_tile_coordinates[x][0]; // Get the x piece tile coordinates
     piece_tile_location_y = active_piece_tile_coordinates[x][1]; // Get the y piece tile coordinates
     GameBoard[piece_tile_location_x][piece_tile_location_y] = 2;//tetromino.active_color[0];
     //Serial.println("DEBUG: render_piece_to_gameboard() - placing active piece tile in gameboard at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")");
  }
  
  return;
}



void Tetris::process_complete_row(){  

  int offset = 0;
  int piece_tile_location_y;
  
  int row_animated[3];
    for(int x = 0;x < 4; x++ ){         
     piece_tile_location_y = active_piece_tile_coordinates[x][1]; // Get the y piece tile coordinates     
       /*if(check_for_complete_row(piece_tile_location_y) && piece_tile_location_y != row_animated[0] && piece_tile_location_y != row_animated[1] && piece_tile_location_y != row_animated[2]){
          animate_erase_row(piece_tile_location_y);
          row_animated[x] = piece_tile_location_y;

       }*/
       if(check_for_complete_row(piece_tile_location_y)){
          animate_erase_row(piece_tile_location_y);
       }
    }
  
  for(int x = 0;x < 4; x++ ){    
     
     piece_tile_location_y = active_piece_tile_coordinates[x][1] - offset; // Get the y piece tile coordinates
     
     if(check_for_complete_row(piece_tile_location_y)){      
       //remove row and shift down
       if(check_for_complete_row(piece_tile_location_y) && piece_tile_location_y != row_animated[0] && piece_tile_location_y != row_animated[1] && piece_tile_location_y != row_animated[2]){
          animate_erase_row(piece_tile_location_y);
          remove_row_from_gameboard(piece_tile_location_y);
          row_animated[x] = piece_tile_location_y;

       }
     
       offset = offset  + 1;
     }
  }

  if(offset >= 1){
    score.update_score(offset);
  }

  update_counters();
  return;
}




bool Tetris::check_for_complete_row(int row_y){  
     for(int x = 0; x < WIDTH; x++){
       if(GameBoard[x][row_y] == 0){
        return false;
       }
     }
     //Serial.println("DEBUG: Complete row found: " + (String)row_y);
     return true;
}


void Tetris::remove_row_from_gameboard(int row_y){  
  int tmp_gameBoard[10];
  bool empty_row;
  for(int y = row_y; y < 20; y++ ){    
     empty_row = true;
     for(int x = 0; x < WIDTH; x++){
      if(y == 19){
        GameBoard[x][y] = 0;
       } else {
        GameBoard[x][y] = GameBoard[x][y + 1];
       }
     }
  }
  
}





/* Private: remove_piece_from_gameboard()
 * removes the previous piece from the gamboard
 * 
 * 
 */
void Tetris::remove_piece_from_gameboard(){
  int piece_tile_location_x, piece_tile_location_y;
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = active_piece_tile_coordinates[x][0]; // Get the x piece tile coordinates 
     piece_tile_location_y = active_piece_tile_coordinates[x][1]; // Get the y piece tile coordinates
     GameBoard[piece_tile_location_x][piece_tile_location_y] = 0;
     //Serial.println("DEBUG: erase_prev_piece_from_gameboard() - placing active piece tile in gameboard at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")");
  }
  return;
}



/* Private: check_for_collision() -
 *  Checks if the current state of the gameboard has collisions
 *  
 * 
 */
 
bool Tetris::check_for_collision(){  
  int piece_tile_location_x, piece_tile_location_y = 0;  
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = active_piece_tile_coordinates[x][0];// + movement_x; // Get the x piece tile coordinates 
     piece_tile_location_y = active_piece_tile_coordinates[x][1];//+ movement_y; // Get the y piece tile coordinates
     
    if(piece_tile_location_x < 0 || piece_tile_location_x >= WIDTH){      
        //Serial.println("DEBUG: check_for_collision() -  Out of bounds collision detected on x axis at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")**");
        return true;
    } else if(piece_tile_location_y < 0 || piece_tile_location_y >= HEIGHT){
        //Serial.println("DEBUG: check_for_collision() -  Out of bounds collision detected on y axis at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")**");
        return true;     
    } else if (GameBoard[piece_tile_location_x][piece_tile_location_y] != 0){
        //Serial.println("DEBUG: check_for_collision() -  Gamboard piece collision detected at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")**");
        return true;
    }
  }
  //no colission detected
  return false;
}








/*
  gameboard.cpp- Library for keeping and updating tetris gameboard state
  Created by Skye Perry, Dec 1, 2018.
  Released into the public domain.
*/


#include "Arduino.h"
#include "gameboard.h"



/*  Constructor
 *  initialize new gameboard object
 * 
 */
Gameboard::Gameboard(){
  reset_state();

  
}



  int x_column_values[WIDTH];


    


int Gameboard::get_drop_height(int column_x, int start_height_y){
  for(int y = start_height_y; y >= 0; y--){
    if(active_state[column_x][y] != 0){
      Serial.println("Start height: " + (String)start_height_y   );
      return start_height_y - (y + 1); 
     }
  }
   return start_height_y;
}


/*  check_for_complete_row(int row_y) -
 *  Checks if the current state of the gameboard has collisions with the arg coordinates
 *  
 * 
 */
 
bool Gameboard::check_for_complete_row(int row_y){  
     for(int x = 0; x < WIDTH; x++){
       if(active_state[x][row_y] == 0){
        return false;
       }
     }
     //Serial.println("DEBUG: Complete row found: " + (String)row_y);
     return true;
}



/*
void Gameboard::remove_row_from_gameboard(int row_y){  
  bool empty_row = false;
  for(int y = row_y; y < HEIGHT -1 && !empty_row; y++ ){
     empty_row = true;    
     for(int x = 0; x < WIDTH; x++){
      if(y == 19){
        active_state[x][y] = 0;
        empty_row = false;
       } else {
        active_state[x][y] = active_state[x][y + 1];
       }
       if( active_state[x][y] != 0){empty_row = false;}
     }
  }
  
}
*/

void Gameboard::remove_row_from_gameboard(int row_y){  
 
  bool empty_row = false;
  for(int y = row_y; y < HEIGHT - 4 && !empty_row; y++ ){
     empty_row = true;    
     for(int x = 0; x < WIDTH; x++){
      if(y == HEIGHT - 4){
        active_state[x][y] = 0;
        empty_row = false;
       } else {
        active_state[x][y] = active_state[x][y + 1];
       }
       if( active_state[x][y] != 0){empty_row = false;}
     }
  }
  
}


/*  check_for_collision() -
 *  Checks if the current state of the gameboard has collisions with the arg coordinates
 *  
 * 
 */
 
bool Gameboard::check_for_collision(int arg_coordinates[4][2]){  
  int piece_tile_location_x, piece_tile_location_y;;  
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = arg_coordinates[x][0];
     piece_tile_location_y = arg_coordinates[x][1];     
    if(piece_tile_location_x < 0 || piece_tile_location_x >= WIDTH){  
        return true;
    } else if(piece_tile_location_y < 0 || piece_tile_location_y >= HEIGHT){ 
        return true;     
    } else if (active_state[piece_tile_location_x][piece_tile_location_y] != 0){
        //Serial.println("DEBUG: check_for_collision() -  Gamboard piece collision detected at (" + (String)piece_tile_location_x + "," + (String)piece_tile_location_y + ")**");
        return true;
    }
  }
  //no colission detected
  return false;
}




/* Public: check_for_top_out()                        
 * takes tetromino coordinates and renders to gameboard.active_state array as color_id                         
 *                     
 */
 
bool Gameboard::check_for_top_out(){
       for(int x = 0; x < WIDTH; x++){                   
            if(active_state[x][20] != 0){
              return true;
            }
    } 
    return false;  
}




/* Public: render_tetromino()                          
 * takes tetromino coordinates and renders to gameboard.active_state array as color_id                         
 *                     
 */
void Gameboard::render_tetromino(int tetromino_coordinates[4][2],int color_id){
  int piece_tile_location_x, piece_tile_location_y;
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = tetromino_coordinates[x][0]; // Get the x piece tile coordinates
     piece_tile_location_y = tetromino_coordinates[x][1]; // Get the y piece tile coordinates
     active_state[piece_tile_location_x][piece_tile_location_y] = color_id;
  }  
  return;  
}




/* Public: render_tetromino()                          
 * takes tetromino coordinates and removes (sets to 0) to gameboard.active_state array                
 *                     
 */
void Gameboard::remove_tetromino(int tetromino_coordinates[4][2]){
  int piece_tile_location_x, piece_tile_location_y;
  for(int x = 0;x < 4; x++ ){     
     piece_tile_location_x = tetromino_coordinates[x][0]; // Get the x piece tile coordinates
     piece_tile_location_y = tetromino_coordinates[x][1]; // Get the y piece tile coordinates
     active_state[piece_tile_location_x][piece_tile_location_y] = 0;
  }  
  return;  
}




/* Private: reset_state()                          
 * Sets each element of the active_state array to 0, effectivly resetting the gameboard                            
 * using the global WIDTH and HEIGHT defined in gameboard.h                        
 */
void Gameboard::reset_state(){
  for(int y = 0; y < HEIGHT; y++){
    for(int x = 0; x < WIDTH; x++){      
      Gameboard::active_state[x][y] = 0;
    }      
  }
  return;    
}




/* Public: debug_print_active_state()
 * Serial prints the gamboard state as integer values, formatted for arduino serial monitor
 * Prints the y axis of the array backwards so the xy coordiantes in the array are tranlated to the top right quadrent of a graph 
 */
 
void Gameboard::debug_print(){
    Serial.println("\n\n");
    Serial.println("check_for_top_out(): " + check_for_top_out() ? "true": "false");
    Serial.println("\n\n");
    return;    
}




/* Public: serialPrintgameboard.active_state()
 * Serial prints the gamboard state as integer values, formatted for arduino serial monitor
 * Prints the y axis of the array backwards so the xy coordiantes in the array are tranlated to the top right quadrent of a graph 
 */
 
void Gameboard::debug_print_active_state(){
    Serial.println("\n\n");
    Serial.println("**Current Gameboard State:**");
    for(int y = HEIGHT -1; y >= 0; y--){
      Serial.println();
      for(int x = 0; x < WIDTH; x++){
        Serial.print(active_state[x][y] == 0 ? " □ ": " ■ " );
      }
      if(y == HEIGHT - 4){
        Serial.print("\n----------------------------");
      }      
    }
    Serial.println("\n\n");
    return;    
}

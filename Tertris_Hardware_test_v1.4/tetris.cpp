/*
  Tetris.cpp - Library for flashing Tetros code.
  Created by Skye Perry, November 22, 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "tetris.h"

Score score(true);
Randomizer randomizer;



//Should be called in setup step of program
void Tetris::init_hardware(){
  audio.initialize();
  gameboard.initialize();
  scoreboard.initialize();  
  
}



Tetris::Tetris()
{
  Serial.begin(115200);
  Serial.println("Starting Tetris...");
  game_state = 0;
  score.set_debug(true);  
  Tetris::reset_game();
  lastUpdate = millis();
 
}



void Tetris::reset_game(){
  gameboard.reset_state();
  score.new_game();
  scoreboard.print_score(score.get_score(),score.get_level());
  Randomizer randomizer; 
  
}



bool Tetris::start_game(){
  if(game_state == 1){return false;} // can't start if we're already playing 
  Serial.println("Starting Tetris...");
  reset_game();
  audio.start_music(); // need to move this perhaps?
  create_new_piece();  
  lastUpdate = millis();  
  game_state = 1;
  return true;
}




/* Public: update_game_state()
 * this function should be called every loop to run the game
 * 
 */
void Tetris::update_game_state(){
  
  if(game_state == 1){
    int currentTime = millis();  
    if(currentTime - lastUpdate > score.get_game_speed()){
      move_piece_down();
      //tetromino.debug_print();
      //gameboard.debug_print_active_state();
      lastUpdate = currentTime;
      audio.update_state();
    } 
  }

  gameboard.render_display();
  scoreboard.update_state();
  
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

    int completed_rows = gameboard.process_complete_row(active_piece_tile_coordinates);
    score.update_score(completed_rows);
    scoreboard.print_score(score.get_score(),score.get_level());
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
    if(player_location_y > 19){return;} // make sure tile is in board
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
    gameboard.render_display();
    int completed_rows = gameboard.process_complete_row(active_piece_tile_coordinates);
    score.update_score(completed_rows);
    scoreboard.print_score(score.get_score(),score.get_level());
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
  if(gameboard.check_for_top_out()){ 
      Serial.println("**GAME OVER**");
      audio.sfx_game_over();
      game_state = 2;
      delay(3000);    
      return;
    }
  
  reset_player_location();
  tetromino.init_new_tetromino();  
  set_active_piece_coordiantes();
  gameboard.render_tetromino(active_piece_tile_coordinates,tetromino.color_id);
  
  return;
}

/*
  tetromino.cpp - 
  Created by Skye Perry, November 30, 2018.
  Library for used in tetris.cpp to hold the teromino defenitions and rotate the state, calls the randomizer which
  adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/



#include "tetromino.h"




/* Tetromino::Tetromino()
 * 
 * 
 */
Tetromino::Tetromino(){  
   init_new_tetromino();  
}




/* Tetromino::set_tetromino(bool active)
 * 
 * 
 */
void Tetromino::set_tetromino(bool active){
      int  piece_index;
      active ? piece_index = randomizer.get_current_piece() : piece_index = randomizer.get_next_piece();
      switch (piece_index) {
      case 1:
        // Serial.println("init_new_piece() - setting l_periscope as active piece");
        active ? color_id = 1: color_id = color_id;
        tetromino_name = "l_periscope";
        copy_tetromino_def(l_periscope,active);
        break;
      case 2:
        // Serial.println("init_new_piece() - setting stick as active piece");
         active ? color_id = 2: color_id = color_id;
        tetromino_name = "stick";
        copy_tetromino_def(stick,active);
        break;
      case 3:
        // Serial.println("init_new_piece() - setting square as active piece");
        tetromino_name = "square";
         active ? color_id = 3: color_id = color_id;
        copy_tetromino_def(square,active);
        break;
      case 4:
        // Serial.println("init_new_piece() - setting square as active piece");
         active ? color_id = 4: color_id = color_id;
        tetromino_name = "r_periscope";
        copy_tetromino_def(r_periscope,active);
        break;
      case 5:
        // Serial.println("init_new_piece() - setting square as active piece");
         active ? color_id = 5: color_id = color_id;
        tetromino_name = "l_dog";
        copy_tetromino_def(l_dog,active);
        break;
      case 6:
       // Serial.println("init_new_piece() - setting square as active piece");
        active ? color_id = 6: color_id = color_id;
        tetromino_name = "r_dog";
        copy_tetromino_def(r_dog,active);
        break;
      case 7:
        // Serial.println("init_new_piece() - setting square as active piece");
        active ? color_id = 7: color_id = color_id;
        tetromino_name = "tee";
        copy_tetromino_def(tee,active);
        break;
    }
}




/* Tetromino::copy_tetromino_def(int arg_tetromino[4][4][2],bool active)
 * 
 * 
 */
void Tetromino::copy_tetromino_def(int arg_tetromino[4][4][2],bool active){
 //Serial.println("intitialize_new_tetromino()");
    for(int x = 0; x < 4; x ++){
      for (int y = 0; y < 2; y++){
        if(active){
          active_tetromino[x][y] = arg_tetromino[rotation_index][x][y];
        } else {
          next_tetromino[x][y] = arg_tetromino[0][x][y];
        }
      }
    }

  return;  
}



/* Tetromino::change_rotation_index(int change)
 * 
 * 
 */
void Tetromino::change_rotation_index(int change){
    if(change == 1){
     rotation_index >=  3 ? rotation_index = 0 : rotation_index = rotation_index + 1;
   } else if (change == -1){
     rotation_index <=  0 ? rotation_index = 3 : rotation_index = rotation_index - 1;
   } 
}




/* Tetromino::rotate(int change)
 * 
 * 
 */
void Tetromino::rotate(int change){
    change_rotation_index(change);
    set_tetromino(true); // reset the active tetromino
}




/* Tetromino::init_new_tetromino()
 * 
 * 
 */
void Tetromino::init_new_tetromino(){
  
  rotation_index = 0;
  active_index = randomizer.get_new_piece();
  next_index = randomizer.get_next_piece();
  set_tetromino(true); // set acitve piece
  set_tetromino(false); // set next piece
  
}




/* Tetromino::debug_print()
 * 
 * 
 */
void Tetromino::debug_print(){
  Serial.println("**Active Piece**");
  // put your main code here, to run repeatedly:
      for(int i =0; i < 4; i++ ){
        Serial.print("[" + (String)active_tetromino[i][0] + "," + (String)active_tetromino[i][1] + "]");        
      }
      Serial.println();

     Serial.println("**Next Piece**");
  // put your main code here, to run repeatedly:
      for(int i =0; i < 4; i++ ){
        Serial.print("[" + (String)next_tetromino[i][0] + "," + (String)next_tetromino[i][1] + "]");        
      }
      Serial.println("\n\n");

      debug_print_piece(true);     

}




/* Tetromino::debug_print_piece(bool active)
 * 
 * 
 */
void Tetromino::debug_print_piece(bool active){
    Serial.println("**Active tetromino: " + tetromino_name + "**");
  // put your main code here, to run repeatedly:
    for(int y =3; y >= 0; y-- ){
      for(int x =0; x < 4; x++ ){
         bool active_tile = false;
         for(int i =0; i < 4; i++ ){
          if(active_tetromino[i][0] == x && active_tetromino[i][1] == y ){
             Serial.print(" ■ ");  
             active_tile = true;
          }              
        }
        if(!active_tile){Serial.print(" □ "); }
      }
        Serial.println();
      }
      Serial.println("\n\n");  
}

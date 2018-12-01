/*
  randomizer.cpp - Library for generating numbers (random tetris pieces).
  Created by Skye Perry, November 22, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#include "Arduino.h"
#include "randomizer.h"


/*  Constructor
 *  initialize new sequence
 * 
 */

Randomizer::Randomizer(){
    Serial.begin(115200);
    Randomizer::current_sequence_index = 0;
    Randomizer::active_sequence = 1;
    Randomizer::inactive_sequence = 0;
    Randomizer::generate_new_sequence(active_sequence);
    Randomizer::generate_new_sequence(inactive_sequence);
}




/*  generate_new_sequence()
 *  creates a new sequence of numbers 1-7
 * 
 */
 
void Randomizer::generate_new_sequence(int sequence){
  
  //Serial.println("generating new sequence...");  
  Randomizer::reset_sequence(sequence);
  
  int sequence_index = 0;
  
  while(sequence_index < SEQUENCETOTAL){
    
    int random_num = random(1,8);
    
    if(!is_already_picked(random_num, sequence)){
      
      Randomizer::sequence[sequence][sequence_index] = random_num;      
      sequence_index = sequence_index + 1; 
      //Serial.println("sequence[" + (String)sequence_index + "] is set to: " + (String)random_num  ); 
            
    }
  }
}




/*  is_already_picked()
 *  checks if a piece already exists in the sequence
 * 
 */
 
bool Randomizer::is_already_picked(int num, int sequence){
  
  for(int j = 0; j < SEQUENCETOTAL; j ++){
    
      if(num == Randomizer::sequence[sequence][j] ){
        return true;
      }
      
    }
    
    return false;
}




/*  reset_sequence()
 *  sets all the elements in a sequence to 0 (null)
 * 
 */

void Randomizer::reset_sequence(int sequence){
  
  for(int i =0; i< 7; i++){
    Randomizer::sequence[sequence][i] = 0;
  }  
  
}




/*  get_new_piece()
 *  returns the next piece in the sequence
 * 
 */

int Randomizer::get_new_piece(){
  
  Randomizer::increment_current_sequence_index();
  return Randomizer::sequence[Randomizer::active_sequence][current_sequence_index];
  
}


/*  get_current_piece()
 *  returns the current active piece 
 * 
 */
 
int Randomizer::get_current_piece(){
  
  return Randomizer::sequence[Randomizer::active_sequence][current_sequence_index];
  
}




/*  get_next_piece()
 *  returns the next piece and works across sequences
 * 
 */
int Randomizer::get_next_piece(){
  
  int next_piece = current_sequence_index + 1;
  
  if(next_piece > 6){    
    
    next_piece = next_piece - 7;
    return Randomizer::sequence[Randomizer::inactive_sequence][next_piece];    
    
  } else{    
    
    return Randomizer::sequence[Randomizer::active_sequence][next_piece];   
     
  }
  
}


/*  increment_current_sequence_index()
 *  increments the current_sequence_index 
 *  this handles the toggling of the active sequence and also 
 *  regenerates the stale sequence on switch
 */

void Randomizer::increment_current_sequence_index(){
  
  current_sequence_index = current_sequence_index + 1;
  
  if(current_sequence_index > 6){    
    
     current_sequence_index = 0;
     toggle_active_sequence();
     generate_new_sequence(inactive_sequence);  
        
  } 
     
}





/*  toggle_active_sequence()
 *  switches the active sequence
 * 
 */

void Randomizer::toggle_active_sequence(){
  
     if(Randomizer::active_sequence == 0){
      
        Randomizer::active_sequence = 1;
        Randomizer::inactive_sequence = 0;
        
     } else if (Randomizer::active_sequence == 1){
      
        Randomizer::active_sequence = 0;
        Randomizer::inactive_sequence = 1;
        
     } else {
      
      Serial.println("Error: increment_current_sequence_index() - Invalid active sequence: " + (String)Randomizer::active_sequence);
      
     }
}




/*  debug_print()
 *  just some good 'ol debuging to help out when things get wonky
 * 
 */
 
void Randomizer::debug_print(){
  
  Serial.println("      **Current active sequence**     ");
  Serial.print("            -");  
  for(int i = 0; i < SEQUENCETOTAL; i++){
    if(i == current_sequence_index){Serial.print("[");}
    Serial.print((String)Randomizer::sequence[active_sequence][i]);
    if(i == current_sequence_index){Serial.print("]");}
    Serial.print("-");
  }  
  Serial.println("");

  
  Serial.println("      **Current inactive sequence**     ");
  Serial.print("            -");   
  for(int i = 0; i < SEQUENCETOTAL; i++){
    Serial.print((String)Randomizer::sequence[inactive_sequence][i] + "-");
  }  
  Serial.println("");  


  Serial.println("      **Current Piece: " + (String)Randomizer::get_current_piece());
  Serial.println("");

  
  Serial.println("      **Next Piece: " + (String)Randomizer::get_next_piece() );
  Serial.println("");
  
}

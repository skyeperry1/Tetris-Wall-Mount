/*
  Tetris.cpp - Library for keeping Tetris score.
  Created by Skye Perry, November 22, 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "score.h"




Score::Score(bool debug = 0){
  Score::reset_score();
  Score::reset_level();
  Score::reset_lines();
  Score::rows_to_level_up_fixed = 10;
  Score::set_game_speed();
  //if(Score::debug){
    Serial.begin(115200);
    Serial.println("Starting Tetris Score Enginge -- Current score is: " + (String)Score::score);
  //}
  
}




void Score::set_debug(bool debuglevel){
  if(debuglevel){
   // Serial.println("get_score() -- returning current score of: " + (String)Score::score);
   Score::debug = true;
  } else {
    Score::debug = false;
  }
}




void Score::reset_score(){
  Score::score = 0;
  if(Score::debug){
    Serial.println("Starting Tetris Score Enginge -- Current score is: " + (String)Score::score);
  }
  return;
}




int Score::get_score(){
  if(Score::debug){
    Serial.println("get_score() -- returning current score of: " + (String)Score::score);
  }
  return Score::score;
}




void Score::reset_level(){
  Score::level = 1;
  if(Score::debug){
    Serial.println("Reseting level to:  " + (String)Score::level);
  }
  return;
}




int Score::get_level(){
  if(Score::debug){
    Serial.println("get_level() -- returning current level: " + (String)Score::level);
  }
  return Score::level;
}




void Score::update_level(){
  if(Score::debug){
    Serial.println("update_level() -- updating current level: " + (String)Score::level);
  }
  Score::level = floor(Score::lines / Score::rows_to_level_up_fixed) + 1;
  return;
}



void Score::reset_lines(){
  Score::lines = 0;
  if(Score::debug){
    Serial.println("Reseting lines to:  " + (String)Score::lines);
  }
  return;
}




int Score::get_lines(){
  if(Score::debug){
    Serial.println("get_lines() -- returning current rows: " + (String)Score::lines);
  }
  return Score::lines;
}




void Score::update_lines(int lines){
  Score::lines = Score::lines + lines;
  return;
}




void Score::set_game_speed(){      
      Score::game_speed = 800 - (Score::level * 60);
      Serial.println("set_game_speed() -- setting current game speed: " + (String)Score::game_speed);
      return; 
}




int Score::get_game_speed(){
  return Score::game_speed;
}


int Score::update_score(int rows_completed){  
  if(Score::debug){
    Serial.println("update_score() -- current score before update: " + (String)Score::score);
    Serial.println("               -- running with args completed rows:" + (String)rows_completed + " at level: " + (String)level );
  } 
  
  switch(rows_completed){
    case 1:  
      Score::score = 40 * (Score::level + 1) + Score::score;
      break;
    case 2: 
      Score::score = 100 * (Score::level + 1) + Score::score; 
      break;
    case 3:  
      Score::score = 300 * (Score::level + 1) + Score::score;
      break;
    case 4:
      Score::score = 1200 * (Score::level + 1) + Score::score;  
      break;
    default:
       if(debug){
          Serial.println("Warn - update_score(): Invalid rows completed amount");
        }
        break;
  }
  
  if(Score::debug){
    Serial.println("              -- after update: " + (String)Score::score);
  }
  update_lines(rows_completed);
  update_level();
  set_game_speed();
}

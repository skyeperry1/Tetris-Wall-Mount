/*
  color.h - Library for generating colors for andom tetris pieces.
  Created by Skye Perry, Dec 16, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/

#include "tetrisaudio.h"

//1
//2
//3
//4 antiga 
//5 coin
//6 pls wave back
//7 bgid
//8 boot
//9 game over sfx
//10 peace ppiece ?
//11 coin sfx


HardwareSerial mySoftwareSerial(1); //Setup Tx0 and Rx0

Audio::Audio(){
  stop_music();
  curr_song_index = 6;
}


void Audio::sfx_coin(){
  myDFPlayer.play(11);
}

void Audio::sfx_row_complete(){

}

void Audio::sfx_boot(){
  myDFPlayer.play(8);
}

void Audio::sfx_start(){

}

void Audio::sfx_pause(){

}

void Audio::sfx_game_over(){
  myDFPlayer.play(9);
}

void Audio::start_music(){
  play_music = true;
  play_song(curr_song_index);
}

void Audio::stop_music(){
  play_music = false;
}


void Audio::update_state(){  
  if(play_music){
    play_next_song_if_finished();
  }  
}


void Audio::play_next_song_if_finished(){
  if(curr_song_start + curr_song_length < millis()){
    play_song(get_next_song_index());
  }
}


void Audio::play_song(int song_index){  
  curr_song_length = song_lengths[song_index - 1];
  curr_song_start = millis();
  myDFPlayer.play(song_index);
}


int Audio::get_next_song_index(){
    curr_song_index >= total_songs ? curr_song_index = 1 : ++curr_song_index;
    return curr_song_index;  
}



void Audio::initialize(){
/*  Audio Setup
 * 
 */
  mySoftwareSerial.begin(9600, SERIAL_8N1, 1, 3);  // speed, type, RX0, TX0
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.    
    Serial.println(myDFPlayer.readType(),HEX);
    delay(1000);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }

  Serial.println(F("Audio is online."));
  delay(1000);

  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms  
  myDFPlayer.volume(13);  //Set volume value (0~30).
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // Set SD read
  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  sfx_boot();
  
}




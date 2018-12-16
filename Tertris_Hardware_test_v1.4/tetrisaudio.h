/*
  color.h - Library for generating colors for andom tetris pieces.
  Created by Skye Perry, Dec 1, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#ifndef terisaudio_h
#define terisaudio_h

#include "Arduino.h"


/*  Audio player
 * 
 * 
 */
#include "DFRobotDFPlayerMini.h"


class Audio
{
  public:
  Audio();
  void initialize();
  
  DFRobotDFPlayerMini myDFPlayer;
    
  void play_next_song_if_finished();
  
  int get_sound_file_index(String);
  
  void sfx_coin();
  void sfx_row_complete();
  
  void sfx_boot();
  void sfx_start();
  
  void sfx_pause();
  
  void sfx_game_over();
  
  void start_music();
  
  void stop_music();  
  
  void update_state();
    
  void play_song(int );  

  String cur_song_title;
  String cur_song_artist;
  
  private:
  
  bool play_music;
  int curr_song_length;
  int curr_song_index;
  int curr_song_start;
  int get_next_song_index();
  
  int total_songs = 7;
  //1
  //2
  //3
  //4 antiga 
  //5 piece peace
  //6 pls wave back
  //7 bgid
  //8 boot
  //9 game over sfx
  //10 peace ppiece ?
  //11 coin sfx
  int song_lengths[11] = {
    184000, // pink + white // 3:04 //1
    197000, // tetric classic 1 //2
    105000, //tetris og // 3
    203000, // Vida Antiga  // 3:23 // 4
    1,
    162000, // plswaveback  // 3:42   // 6
    296000, // bgid //4:56 // 7
    10,
    10,
    405000 // peace piece  // 6:45    // 11    
     
  };

  
  
};
#endif

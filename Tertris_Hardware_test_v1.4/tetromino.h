/*
  tetromino.cpp - 
  Created by Skye Perry, November 28, 2018.
  Library for used in tetris.cpp to hold the tetromino (piece) definitions
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#ifndef tetromino_h
#define tetromino_h
#include "randomizer.h"

#include "Arduino.h"

//this array represents the current active state 


class Tetromino
{
  public:
  
  Tetromino();  

  int active_tetromino[4][2];  
  int active_color[3];  
  String tetromino_name;

  int next_tetromino[4][2];
  int next_color[3];

  void init_new_tetromino();

  void rotate(int);  

  void debug_print();
  
  private:
    Randomizer randomizer;

    int rotation_index;

    void change_rotation_index(int);

    void copy_tetromino_def(int[4][4][2],bool);
    void set_tetromino(bool);

    int active_index;

    int next_index;

    void debug_print_piece(bool active);
   
    //Tetromino shape (reference pixel is in the bottom left of shape space, moving up and to the right)
    int  l_periscope[4][4][2] = {
                                  {{0,0}, {1,0}, {1,1}, {1,2}},
                                  {{0,1}, {1,1}, {2,0}, {2,1}},
                                  {{0,0}, {0,1}, {0,2}, {1,2}},
                                  {{0,0}, {0,1}, {1,0}, {2,0}}
                                };




   int  r_periscope[4][4][2] = {
                                  {{1,0}, {1,1}, {1,2}, {2,0}},
                                  {{0,1}, {1,1}, {2,1}, {2,2}},
                                  {{0,2}, {1,0}, {1,1}, {1,2}},
                                  {{0,0}, {0,1}, {1,1}, {2,1}}
                                };
                                
    
    
    
    int square[4][4][2] = {
                            {{1,1}, {1,2}, {2,1}, {2,2}},
                            {{1,1}, {1,2}, {2,1}, {2,2}},
                            {{1,1}, {1,2}, {2,1}, {2,2}},
                            {{1,1}, {1,2}, {2,1}, {2,2}}
                          };


    
    
    int stick[4][4][2] = {
                          {{1,0}, {1,1}, {1,2}, {1,3}},
                          {{0,2}, {1,2}, {2,2}, {3,2}},
                          {{2,0}, {2,1}, {2,2}, {2,3}},
                          {{0,1}, {1,1}, {2,1}, {3,1}}
                         };


                         
    
    int l_dog[4][4][2] = {
                          {{0,1}, {1,0}, {1,1}, {2,0}},
                          {{1,0}, {1,1}, {2,1}, {2,2}},
                          {{0,2}, {1,1}, {1,2}, {2,1}},
                          {{0,0}, {0,1}, {1,1}, {1,2}}
                         };


                         
                         
    int r_dog[4][4][2] = {
                          {{0,0}, {1,0}, {1,1}, {2,1}},
                          {{1,1}, {1,2}, {2,0}, {2,1}},
                          {{0,1}, {1,1}, {1,2}, {2,2}},
                          {{0,1}, {0,2}, {1,0}, {1,1}}
                         };



                         
    int tee[4][4][2] =   {
                          {{0,1}, {1,0}, {1,1}, {2,1}},
                          {{1,0}, {1,1}, {1,2}, {2,1}},
                          {{0,1}, {1,1}, {1,2}, {2,1}},
                          {{0,1}, {1,0}, {1,1}, {1,2}}
                         };

  
  
};
#endif

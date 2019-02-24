/*  Coin acceptor Interrupt
 * 
 * 
 */
uint8_t GPIO_Pin = 15;
//Attach coinInt to Interrupt Pin 17.
volatile double coinsValue = 1.00; // Has to be a double for the esp for some reason, initialize to 0
//Volatile as this variable changes any time the Interrupt is triggered
volatile int coinsChange = 0;     

static void IRAM_ATTR coinInserted()    
//The function that is called every time it recieves a pulse
{
 
//As we set the Pulse to represent 5p or 5c we add this to the coinsValue
  coinsChange = 1;                           
//Flag that there has been a coin inserted
//Serial.print("interrupt Fired");

}

int last_coin_insert = 0;

/* Tetris Game Code
 * 
 * 
 */
#include "tetris.h"
Tetris tetris;

/*  NES Controller
 *   
 *   
 */
#include <NintendoExtensionCtrl.h>
 NESMiniController nes;

bool state_Down,
     state_Up, 
     state_Left, 
     state_Right,
     state_A,
     state_B,
     state_Start,
     state_Select;
     
    bool lastState_Down,
     lastState_Up, 
     lastState_Left, 
     lastState_Right,
     lastState_A,
     lastState_B,
     lastState_Start,
     lastState_Select;


//Testing stuff
  

/*******************************************************************************************
 *  SETUP()
 ********************************************************************************************/
void setup() {
delay(2000); // if we're the first to get power, wait a sec for everything else to catch up

tetris.init_hardware();
tetris.game_credits = 4;
initController();
  
 
  /*  Coin acceptor interrupt setup
   * 
   */
  pinMode(digitalPinToInterrupt(GPIO_Pin), INPUT_PULLDOWN);   
  attachInterrupt(GPIO_Pin, &coinInserted, true);
  delay(1000);
  Serial.begin(115200);

  
}

  

/*******************************************************************************************
 *  LOOP()
 ********************************************************************************************/
void loop() {
    
  /* Handle coin change
   * 
   */
    if(coinsChange == 1)          
    //Check if a coin has been Inserted
      { 
        if( millis() - last_coin_insert > 250){ // debounce the coin acceptor
          last_coin_insert = millis();
          coinsValue = coinsValue + 0.25;
          ++tetris.game_credits;              
          Serial.println ("coins value: " + (String)coinsValue);
        }
        coinsChange = 0;//unflag that a coin has been inserted 
      }



 

  handle_controller_input();

  tetris.update_game_state();
    
}



void initController(){
  //init contorller
  Serial.println("Starting Controller...");
  nes.begin();
  if(!nes.connect()){
      Serial.print("NES Classic Controller not detected, trying to connect");
      for(int i = 0; i < 30; i++) {  
        Serial.print(".");
        delay(1000);
        nes.begin();
        if(nes.connect()) { 
            i =30; 
            Serial.println("+Controller Connected");
          }
        }
      } else {
      Serial.println("+Controller Connected");
    }
  if (nes.isKnockoff()) {  // Uh oh, looks like your controller isn't genuine?
    nes.setRequestSize(8);  // Requires 8 or more bytes for knockoff controllers
  }
    delay(1000);
}


void handle_controller_input(){
    boolean success = nes.update();  // Get new data from the controller
  
    if (!success) {  // Ruh roh
      Serial.println("Controller disconnected!");
      nes.begin();
      nes.connect(); 
      if (nes.isKnockoff()) {  // Uh oh, looks like your controller isn't genuine?
        nes.setRequestSize(8);  // Requires 8 or more bytes for knockoff controllers
      }     
    }  else {
     //Update all button states
     state_Down = nes.dpadDown();
     state_Up = nes.dpadUp();
     state_Left = nes.dpadLeft();
     state_Right = nes.dpadRight();
     state_A = nes.buttonA();
     state_B = nes.buttonB();
     state_Start = nes.buttonStart();
     state_Select = nes.buttonSelect();

     if (state_Select == 1 && state_Select != lastState_Select) {        
        //Select Button Press
        Serial.println(F("Select Button Pressed")); 

      //Start button press      
      } else if(state_Start && state_Start != lastState_Start) {       
        Serial.println(F("Start Button Pressed"));
        //if(coinsValue >= .25 && tetris.start_game()){'
        if(tetris.game_credits > 0 && tetris.start_game()){
          coinsValue = coinsValue - .25;
          --tetris.game_credits;          
        }
      //D-pad Down press  
      } else if(state_Down && state_Down != lastState_Down) {      
        Serial.println(F("D Pad Down"));
        tetris.move_piece_down();

      //D-pad Up press  
      } else if(state_Up && state_Up != lastState_Up) {       
        Serial.println(F("D Pad Up"));

      //D-pad Left press
      } else if(state_Left && state_Left != lastState_Left) {       
        Serial.println(F("D Pad Left"));
        tetris.move_piece_left();
        
      //D-pad Right press  
      } else if(state_Right && state_Right != lastState_Right) {      
        Serial.println(F("D Pad Right"));
        tetris.move_piece_right();

        
      //A button press  
      } else if(state_A && state_A != lastState_A) {        
        Serial.println(F("A Button Pressed"));
        tetris.rotate_piece();

      //B button press
      } else if(state_B && state_B != lastState_B) { 
        Serial.println(F("B Button Pressed"));    
        tetris.move_piece_to_floor();    
      } else{
        //No buttons currently pressed  
      }
     
     //Update last button state
     lastState_Down = state_Down;
     lastState_Up = state_Up; 
     lastState_Left = state_Left; 
     lastState_Right = state_Right;
     lastState_A = state_A;
     lastState_B = state_B;
     lastState_Start = state_Start;
     lastState_Select = state_Select;
     
  } // End Controller Handling  
}

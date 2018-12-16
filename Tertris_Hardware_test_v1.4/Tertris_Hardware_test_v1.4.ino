

/*  Coin acceptor Interrupt
 * 
 * 
 */
uint8_t GPIO_Pin = 15;
//Attach coinInt to Interrupt Pin 17.
volatile double coinsValue = 0.00; // Has to be a double for the esp for some reason, initialize to 0
//Volatile as this variable changes any time the Interrupt is triggered
volatile int coinsChange = 0;     

static void IRAM_ATTR coinInserted()    
//The function that is called every time it recieves a pulse
{
  coinsValue = coinsValue + 0.25;  
//As we set the Pulse to represent 5p or 5c we add this to the coinsValue
  coinsChange = 1;                           
//Flag that there has been a coin inserted
//Serial.print("interrupt Fired");

}







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

    tetris.init_hardware();

/*  Controller Setup
 * 
 */
initController();
  


 
/*  Coin acceptor interrupt setup
 * 
 */
  pinMode(digitalPinToInterrupt(GPIO_Pin), INPUT_PULLDOWN); 
  
  attachInterrupt(GPIO_Pin, &coinInserted, true);
  //P.displayText("+coin", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  //P.displayAnimate();
  delay(1000);


  Serial.begin(115200);

  //P.displayText(pc[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
  
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
        coinsChange = 0;//unflag that a coin has been inserted     

      
          // When we have gone back to the first string, set a new exit effect
          // and when we have done all those set a new entry effect.
       }
    //End coin drop


 
  
  handle_controller_input();
  tetris.update_game_state();
    
}



void initController(){
  //init contorller
  Serial.println("Starting Controller...");
  nes.begin();
  if(!nes.connect()){
      Serial.print("NES Classic Controller not detected, trying to connect");
      //P.displayText("!cntrl", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
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
      //P.displayText("+cntrl", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
      Serial.println("+Controller Connected");
    }
    //P.displayAnimate();
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
        coinsChange = 1;
        coinsValue = coinsValue + .25;  

      //Start button press      
      } else if(state_Start && state_Start != lastState_Start) {       
        Serial.println(F("Start Button Pressed"));

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

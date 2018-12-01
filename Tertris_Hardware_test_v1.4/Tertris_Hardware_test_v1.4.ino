


/*  Audio player
 * 
 * 
 */
#include "DFRobotDFPlayerMini.h"

HardwareSerial mySoftwareSerial(1); //Setup Tx0 and Rx0
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);




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




/*  Scorboard Display
 * 
 * 
 */
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN  18 // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    5  // or SS

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint8_t frameDelay = 25;  // default frame delay value
#define SPEED_TIME  25
#define PAUSE_TIME  2000

#define BUF_SIZE 300 
char pd_message2[BUF_SIZE] = { "" };

// Global scorboard variables
uint8_t  curText;
char  *pc[] =
{
  "Insert",
  "Coin",
};

uint8_t  inFX, outFX;
textEffect_t  effect[] =
{
  PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_CLOSING,
  PA_RANDOM,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  PA_DISSOLVE,
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_SLICE,
  PA_SCROLL_DOWN,
};

//Helper for converting coin value to string values for scoreboard
String doubleToString(double input,int decimalPlaces){
  if(decimalPlaces!=0){
    String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1){
    if(input>0)
    string = "0"+string;
    else if(input<0)
    string = string.substring(0,1)+"0"+string.substring(1);
    }
    return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
    }
    else {
    return String((int)input);
  }
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
/*  Scoreboard Setup
 * 
 */

  P.begin();
  P.setInvert(false);
  //P.displayText(pc[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
  P.displayText("boot...", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate();
  delay(2000);

/*  Controller Setup
 * 
 */
initController();
  
/*  Audio Setup
 * 
 */
  mySoftwareSerial.begin(9600, SERIAL_8N1, 1, 3);  // speed, type, RX0, TX0
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.    
    Serial.println(myDFPlayer.readType(),HEX);
    P.displayText("!audio", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
    P.displayAnimate();
    delay(1000);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }

  Serial.println(F("Audio is online."));
  P.displayText("+audio", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate();
  delay(1000);

  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms  
  myDFPlayer.volume(15);  //Set volume value (0~30).
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // Set SD read
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); //Set EQ
  myDFPlayer.play(4);  //Play the initializing mp3



 
/*  Coin acceptor interrupt setup
 * 
 */
  pinMode(digitalPinToInterrupt(GPIO_Pin), INPUT_PULLDOWN); 
  
  attachInterrupt(GPIO_Pin, &coinInserted, true);
  P.displayText("+coin", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate();
  delay(1000);




/*  Controller Setup
 * 
 */
  Serial.begin(115200);





/*  Tetris LED display setup
 * 
 */
 /* FastLED.addLeds<NEOPIXEL, FASTLED_DATA_PIN>(leds, NUM_LEDS);
  P.displayText("+led", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate();  
  for(int x = 0; x < 200 ; x++){
              
                  leds[x ] = CRGB(random(0,50),random(0,50),random(0,50));//CRGB(100,27,20);
                  FastLED.show();
                  delay(10);
       }
         for(int x = 0; x < 200 ; x++){
              
                  leds[x ] = CRGB(0,0,0);//CRGB(100,27,20);
                  FastLED.show();
                  delay(10);
       }
*/


/*  End boot sequence 
 * 
 * 
 */
  P.displayText("init", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate(); 
  delay(1000);
  P.displayText("okay", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
  P.displayAnimate(); 
  delay(1000);
     
  P.displayText(pc[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
  
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
        myDFPlayer.play(5);//Play coin inseted sound          
    
        String message1 = "Credit";       
   
         //Set and copy first string 
         char str[] = "Credit:";
         pc[0] = (char *)malloc(strlen(str)+1);
         strcpy(pc[0],str);

         //Copy second String         
         char str2[BUF_SIZE] = {""};
         String message2 = "$" + doubleToString(coinsValue, 2);
         message2.toCharArray(str2, BUF_SIZE);         
         pc[1] = (char *)malloc(strlen(str2)+1);
         strcpy(pc[1],str2);

         Serial.print(message1);
         Serial.println(message2);
        
         // Set the display for the first string.
          curText = 0;//(++curText) % ARRAY_SIZE(pc);
          P.setTextBuffer(pc[curText]);
      
          // When we have gone back to the first string, set a new exit effect
          // and when we have done all those set a new entry effect.
          if (curText == 0)
          {
            outFX = (++outFX) % ARRAY_SIZE(effect);
            if (outFX == 0)
            {
              inFX = (++inFX) % ARRAY_SIZE(effect);
              if (inFX == 0)
                P.setInvert(!P.getInvert());
            }
            P.setSpeed(25);
            P.setPause(900);
            frameDelay = 30;
            P.setTextEffect(PA_SCROLL_UP, PA_SCROLL_UP);
          }
      
          // Tell Parola we have a new animation
          P.displayReset();
    }
    //End coin drop


//Scoreboard Updates


  if (P.displayAnimate()) // animates and returns true when an animation is completed
  {
    // Set the display for the next string.
    curText = (++curText) % ARRAY_SIZE(pc);
    P.setTextBuffer(pc[curText]);

    // When we have gone back to the first string, set a new exit effect
    // and when we have done all those set a new entry effect.
    if (curText == 0)
    {
      outFX = (++outFX) % ARRAY_SIZE(effect);
      if (outFX == 0)
      {
        inFX = (++inFX) % ARRAY_SIZE(effect);
        if (inFX == 0)
          P.setInvert(!P.getInvert());
      }
      
      P.setTextEffect(effect[inFX], effect[outFX]);

    }

    // Tell Parola we have a new animation
    P.displayReset();
  }
  
  handle_controller_input();
  tetris.update_game_state();
  //testDisplay();
  
}








void initController(){
  //init contorller
  Serial.println("Starting Controller...");
  nes.begin();
  if(!nes.connect()){
      Serial.print("NES Classic Controller not detected, trying to connect");
      P.displayText("!cntrl", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
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
      P.displayText("+cntrl", PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT);
      Serial.println("+Controller Connected");
    }
    P.displayAnimate();
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

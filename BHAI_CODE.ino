#include<SPI.h>
#include <LCD5110_Basic.h>
#include <SoftwareSerial.h>
int spk = 9;

LCD5110 myGLCD(7,6,5,3,4);
SoftwareSerial BT(0, 1);          //RX||TX
String voice;
void print_lcd();
void play_tone();
void display_face();
void dance();
void hi();
void finger();

unsigned long time = 0;


extern uint8_t SmallFont[];
extern uint8_t FACE_AN_1[];
extern uint8_t FACE_AN_2[];
extern uint8_t FACE_AN_3[];
extern uint8_t BHAI[];
extern uint8_t DANCE_1[];
extern uint8_t DANCE_2[];
extern uint8_t FING[];
extern uint8_t HI[];
extern uint8_t HI_2[];
extern uint8_t HI_3[];
extern uint8_t HI_4[];
extern uint8_t HI_5[];

#define LIGHT A0
#define TV A1
#define DOOR_OPEN A2
#define DOOR_CLOSED A3
#define FAN1 A4
#define FAN2 A5

void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD();
  BT.begin(38400);
  Serial.begin(38400);

  pinMode(LIGHT, OUTPUT);
  pinMode(TV, OUTPUT);
  pinMode(DOOR_OPEN, OUTPUT);
  pinMode(DOOR_CLOSED, OUTPUT);
  pinMode(FAN1, OUTPUT);
  pinMode(FAN2, OUTPUT);

  //boot first
  
  print_lcd("Booting...", "");
  print_lcd("", "Booting...");  
  play_tone(); 
  print_lcd("Hello!", "");
  print_lcd("I am ", "B.H.A.I");
  play_tone();
  for(int i=0; i<10; i++){
  display_face();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = BT.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 0) {    //condition checks if there is some string on the serial sent by the android device.
    Serial.println(voice);



  if(voice=="TV on")         //tv on
  {
  digitalWrite(TV, HIGH);     //turns the TV pin on.
  print_lcd("TV is on.", ""); //prints "TV is on" on the display
  play_tone();                //plays the beep
  display_face();             //resets the display to show the face.
  }

  
  else if(voice=="TV off")  //tv off
  {
  digitalWrite(TV, LOW);
  print_lcd("TV is off.", "");
  play_tone();                            //the same comments as above.
  display_face();
  }

  
  else if(voice=="light on")   //light on
  {
  digitalWrite(LIGHT, HIGH);
  print_lcd("Light is on.", "");
  play_tone();
  display_face();
  }
  
  
  else if(voice=="light off")   //light off
  {
  digitalWrite(LIGHT, LOW);
  print_lcd("Light is off.", "");
  play_tone();
  display_face();
  }
  
  
  else if(voice=="open door")  //door open
  {
  digitalWrite(DOOR_OPEN, HIGH);        //turns on the pin for opening rotating the motor in one direction
  digitalWrite(DOOR_CLOSED, LOW);       //keeps this pin off
  print_lcd("Door is open.", "");       
  play_tone();
  delay(3000);                          //keeps the motor on for three seconds
  digitalWrite(DOOR_OPEN, LOW);         //stops the motor after three seconds
  display_face();
  }

  
  else if(voice=="close door")   //door close
  {
  digitalWrite(DOOR_OPEN, LOW);
  digitalWrite(DOOR_CLOSED, HIGH);      //turns this pin high to rotate the motor for door in the opposite direction
  print_lcd("Door is closed.", "");
  play_tone();
  delay(3000);                          //motor rotates for 3 seconds
  digitalWrite(DOOR_CLOSED, LOW);        //stops the motor after 3 seconds.
  display_face();
  }

  
  else if(voice=="fan on")   //fan on 
  {
  digitalWrite(FAN1, HIGH);                       //turns on the fan motor
  digitalWrite(FAN2, LOW);
  print_lcd("Fan is on.", "");
  play_tone();
  display_face();
  }
  
  
  else if(voice=="fan of")   //fan off
  {
  digitalWrite(FAN1, LOW);                      //turns off the motor connected to the fan
  digitalWrite(FAN2, LOW);
  print_lcd("Fan is off.", "");
  play_tone();
  display_face();
  }

  //*** from here the responsive conditions start. here you can talk to the arduino.***
  
  else if(voice=="hello"  || voice=="hi"){       //for normal greetings like hello or hi.
  print_lcd("Oh, Hi there!.", "");              //prints the response on the LCD
  hi();
  play_tone();
  display_face();
  }

  
 else if(voice=="how are you"){
  print_lcd("I am Fine.", "How are you??");         //prints the response in two different lines because of the lenght of the response.
  play_tone();
  display_face();
  }

  
  else if(voice=="what is your name"){
   print_lcd("People call me", "B.H.A.I");          //printed in two lines to make the response seem more dramatic
   play_tone();
  display_face();
  }

  else if(voice=="what does bhai mean"  || voice=="what does bye mean"){      //used "bhai" and "bye" because the android application sometimes reads "bhai" as "bye"
   myGLCD.print("Basic", LEFT, 0);                    //         
   myGLCD.print("Home", LEFT, 12);                   //
   myGLCD.print("Artificial", LEFT, 24);            //did not use the function here because the function i made takes only two trings as the parameters. 
   myGLCD.print("Intelligence", LEFT, 36);         //
   delay(3000);
   myGLCD.clrScr();
   display_face();   
  }

  //JOKE CODE
  
  
  else if(voice=="who are you" || voice=="who're you"){
   print_lcd("B.H.A.I", "");        // prints the acronym
   play_tone();
   display_face();
  }

  //BHai Code ends

  else if(voice=="bye"){
    pinMode(A0,LOW);
    pinMode(A1, LOW);
    pinMode(A2, LOW);                   //all devices off
    pinMode(A3, LOW);
    pinMode(A4, LOW);
    pinMode(A5, LOW);
   print_lcd("Okay!", "Take care");     //prints response/
   hi_bye();                               //plays the waving hand animation again
   play_tone();
   display_face();
  }

  else if(voice=="bhai dance"){
    dance();                              //displays the dancing animation
    play_tone();
    display_face();
  }


  else{                                  //used as exception handler if the user or the application sends in a string which the arduino does not recognize. 
   print_lcd("Pardon??","");              
   play_tone();
   play_tone();
   display_face();
  }
  voice="";                              //reset the string voice to empty for the next string.
  }
  }

  // function to print on lcd

void print_lcd(String text, String text_2){
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);          //set the font as small text
  myGLCD.print(text, CENTER, 16);     //print string 1 in the center 
  myGLCD.print(text_2, CENTER, 25);   //print the string 2 in the center below string 1
  delay(2000);
  myGLCD.clrScr();
}

//this function is used to play the beep for 500ms 

void play_tone(){
  tone(spk, 1000);
  delay(500);
  noTone(spk);        //stops the beeping
}

//this function displays the face of BHAI and is called after every else if condition

void display_face(){
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, FACE_AN_1, 84, 48);
  delay(100);
  myGLCD.drawBitmap(0, 0, FACE_AN_2, 84, 48);
  delay(100);
  myGLCD.drawBitmap(0, 0, FACE_AN_3, 84, 48);
  delay(100);
  myGLCD.drawBitmap(0, 0, FACE_AN_2, 84, 48);
  delay(100);
  myGLCD.drawBitmap(0, 0, FACE_AN_1, 84, 48);
}

//this function plays the animation for the hi and bye gesture to be displayed on th screen.
//calls the HI, HI_2, HI_3, HI_4, HI_5 on the display 5 times after a 30 ms delay.

void hi(){
  myGLCD.clrScr();
  for(int i=0; i<5; i++){
  myGLCD.drawBitmap(0, 0, HI, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_2, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_3, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_4, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_5, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_4, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_3, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI_2, 84, 48);
  delay(30);
  myGLCD.drawBitmap(0, 0, HI, 84, 48);
  delay(30);
}
}

// this function plays the stick guy dancing animation on the display.
//calls the DANCE_1 and DANCE_2 bitmaps on the screen after a delay of 100 ms for r20 times.

void dance(){
  myGLCD.clrScr();
  for(int i=0; i<20; i++){
  myGLCD.drawBitmap(0, 0, DANCE_1, 84, 48);
  delay(100);
  myGLCD.drawBitmap(0, 0, DANCE_2, 84, 48);
  delay(100);
  }

  //this function displays the finger on the display. 
  //just in case, BHAI finds something offensive.
  
  }
  void finger(){
    myGLCD.clrScr();
    myGLCD.drawBitmap(0,0, FING, 84, 48);
    delay(3000);
  }


    

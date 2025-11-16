/*
The Wizard of Oz - Enclosure Project
by 'No Place Like Ohm' 
- Vivian Coleman, Oz Dieckmann, Lauren Cogbill -

Enclosure Project for AET 314 - CODE AND FABRICATION.
*/



#include <Servo.h>

//Instantiates Servos and their respective pin no.'s
Servo tornadoSrv;
const int toSrvPin = A0;
Servo cowSrv;
const int coSrvPin = A1;
Servo brotherSrv;
const int brSrvPin = A2;
Servo wagonSrv;
const int waSrvPin = A3;
Servo shelterSrv;
const int shSrvPin = A4;
Servo slipperSrv;
const int slSrvPin = A5;

//LED NUMBERS
const int HappyLightPin = 13;
const int SadLightPin = 11;

//SWITCH NUMBERS
const int firstButtonPin = 8;
const int tornadoButtonPin = 7;
const int cowButtonPin = 6;
const int brotherButtonPin = 5;
const int wagonButtonPin = 4;
const int curtainButtonPin = 3;
const int shelterButtonPin = 2;

//STORY FLAG STATE
int story;
/*
0 - Beginning 
1 - Dorothy by Professor Marvel's Cart (first)
2 - Dorothy by the Storm Shelter (first)
3 - Dorothy by the Cow
4 - Dorothy by the Brothers
5 - Dorothy by Professor Marvel's Cart (second)
6 - Wizard's Cord Pulled
7 - Dorothy by the Storm Shelter (second)
*/


void setup() {
  Serial.begin(9600);

  //RESETS STORY PROGRESS
  story = 0;

  //ATTACHES AND INITIALIZES SERVOs
  tornadoSrv.attach(toSrvPin);
  tornadoSrv.write(90); //EDIT TO MATCH EXACT STOPPING POINT
  cowSrv.attach(coSrvPin);
  cowSrv.write(0);
  brotherSrv.attach(brSrvPin);
  brotherSrv.write(0);
  wagonSrv.attach(waSrvPin);
  wagonSrv.write(0);
  shelterSrv.attach(shSrvPin);
  shelterSrv.write(90); //EDIT TO MATCH EXACT STOPPING POINT
  slipperSrv.attach(slSrvPin);
  slipperSrv.write(90); //EDIT TO MATCH EXACT STOPPING POINT

  //INSTANTIATES LEDs
  pinMode(HappyLightPin, OUTPUT);
  pinMode(SadLightPin, OUTPUT);

  //INSTANTIATES SWITCHes
  pinMode(firstButtonPin, INPUT);
  pinMode(tornadoButtonPin, INPUT);
  pinMode(cowButtonPin, INPUT);
  pinMode(brotherButtonPin, INPUT);
  pinMode(wagonButtonPin, INPUT);
  pinMode(curtainButtonPin, INPUT);
  pinMode(shelterButtonPin, INPUT);

}

//INDIVIDUAL STORY BEATS
void storyOne() {
  if(digitalRead(firstButtonPin)){
    digitalWrite(SadLightPin, HIGH); // Illuminates the sad face
    story = 1;
  }
}

void storyTwo() {
  if(digitalRead(tornadoButtonPin)){
    digitalWrite(SadLightPin, LOW); //turns off sad face
    tornadoSrv.write(120); // Starts the tornado spinning
    story = 2;
  }
}

void storyThree() {
  if(digitalRead(cowButtonPin)){
    tornadoSrv.write(90); // Stops the tornado spinning (WARNING: EDIT TO MATCH STOPPING POINT OF SERVO)
    cowSrv.write(180); // Flips the Cow to the Munchkin
    story = 3;
  }
}

void storyFour() {
  if(digitalRead(brotherButtonPin)){
    brotherSrv.write(180); //Flips the Brothers to the Oz Trio
    story = 4;
  }
}

void storyFive() {
  if(digitalRead(wagonButtonPin)){
    wagonSrv.write(180); //Flips the Wagon to the Wizard
    story = 5;
  }
}

void storySix() {
  if(digitalRead(curtainButtonPin)){
    digitalWrite(SadLightPin, HIGH); // Illuminates the sad face
    story = 6;
  }
}

void storySeven() {
  if(digitalRead(shelterButtonPin)){
    digitalWrite(SadLightPin, LOW); // Turns off the sad face
    shelterSrv.write(100); // Figure out timer so it only lasts a short period of time
    slipperSrv.write(100); //Figure out exact speed to make the mechanism work
    story = 7;
  }
}

void storyEight() {
  //timer set for the shelter
  //timer set for the slippers
}


//ARRAY OF FUNCTION POINTERS
void (*storyManager[])(void) { 
  storyOne(),
  storyTwo(),
  storyThree(),
  storyFour(),
  storyFive(),
  storySix(),
  storySeven(),
  storyEight()

};

void loop() {

  storyManager[story](); //Only runs the current story progress function.
  /* This is done to conserve on processing power. 
   * Instead of checking every single possible boardstate, it only cares what the next board state is.
   */
  

}

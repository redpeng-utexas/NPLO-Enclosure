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

// TIMERS
int timer;
int timergoal;

void setup() {
  Serial.begin(9600);

  //RESETS STORY PROGRESS
  story = 0;

  //TIMER AND TIMERGOAL
  timer = 0;
  timergoal = 192;

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
    story = 1;
    Serial.println("First Switch.");
  }
}

void storyTwo() {
  digitalWrite(SadLightPin, HIGH); // Illuminates the sad face
  if(digitalRead(tornadoButtonPin)){
    digitalWrite(SadLightPin, LOW); //turns off sad face
    story = 2;
    Serial.println("Second Switch.");
  }
}

void storyThree() {
  tornadoSrv.write(120); // Starts the tornado spinning
  if(digitalRead(cowButtonPin)){
    tornadoSrv.write(90); // Stops the tornado spinning (WARNING: EDIT TO MATCH STOPPING POINT OF SERVO)
    cowSrv.write(180); // Flips the Cow to the Munchkin
    story = 3;
    Serial.println("Third Switch.");
  }
}

void storyFour() {
  if(digitalRead(brotherButtonPin)){
    brotherSrv.write(180); //Flips the Brothers to the Oz Trio
    story = 4;
    Serial.println("Fourth Switch.");
  }
}

void storyFive() {
  if(digitalRead(wagonButtonPin)){
    wagonSrv.write(180); //Flips the Wagon to the Wizard
    story = 5;
    Serial.println("Fifth Switch.");
  }
}

void storySix() {
  if(/*digitalRead(curtainButtonPin)*/ true){
    story = 6;
    Serial.println("Sixth Switch.");
  }
}

void storySeven() {
  digitalWrite(SadLightPin, HIGH); // Illuminates the sad face
  if(digitalRead(shelterButtonPin)){
    digitalWrite(SadLightPin, LOW); // Turns off the sad face
    story = 7;
    Serial.println("Seventh Switch.");
    timer = millis();
    timergoal = timer + 1600;
  }
}

void storyEight() {
  shelterSrv.write(100); //Starts the shelter and slipper spinning.
  slipperSrv.write(100); 
  if(timer > timergoal){
    story = 8;
    Serial.println(String(timer) + " " + String(timergoal));
    timergoal = timer + 2800;
  } 
  timer = millis();
}

void storyNine(){
  shelterSrv.write(90); //Stops the shelter and slipper spinning.
  slipperSrv.write(90);
  timer = millis();
  Serial.println(String(timer) + " " + String(timergoal));
  if(timer > timergoal){
    story = 9;
  }
}

void storyTen(){ //starts reset
  cowSrv.write(0);
  brotherSrv.write(0);
  wagonSrv.write(0);
  shelterSrv.write(100); 
  slipperSrv.write(100); 
  timer = millis();
  timergoal = timer + 1600;
  story = 10;
}

void storyEleven(){ //finishes reset
  timer = millis();
  if( timer > timergoal){
    shelterSrv.write(90); //Stops the shelter and slipper spinning.
    slipperSrv.write(90);
    story = 0;
  }
}



//ARRAY OF FUNCTION POINTERS <DEFUNCT>
/*void (*storyManager[])(void) { 
  storyOne(),
  storyTwo(),
  storyThree(),
  storyFour(),
  storyFive(),
  storySix(),
  storySeven(),
  storyEight(),
  storyNine()
};*/

void loop() {

  //storyManager[story](); <DEFUNCT>
  
  switch (story){ //Only runs the current story progress function.
    case 0:
      storyOne();
      break;
    case 1:
      storyTwo();
      break;
    case 2:
      storyThree();
      break;
    case 3:
      storyFour();
      break;
    case 4:
      storyFive();
      break;
    case 5:
      storySix();
      break;
    case 6:
      storySeven();
      break;
    case 7:
      storyEight();
      break;
    case 8:
      storyNine();
      break;
    case 9:
      storyTen();
      break;
    case 10:
      storyEleven();
      break;
    default:
      Serial.println("Story progress is wrong.");
      break;
  } /* This is done to conserve on processing power. 
   * Instead of checking every single possible boardstate, it only cares what the next board state is.
   */
  

}

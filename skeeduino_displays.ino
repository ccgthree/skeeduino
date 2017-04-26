#include <SoftwareSerial.h>
#include <Servo.h>

// Name (or label) servo.
Servo ballReturn;

// Declare serial displays.
SoftwareSerial scoreDisp(A0,12);
SoftwareSerial ballDisp(A1,13);

// Pin declarations
int sensors[8] = {9,8,7,6,5,4,3,2};     // create an array of sensors
int resetButton = 10;
int servPin = 11;


// General declarations
int score = 0;
int balls = 9;
int n = 0;
int result;
int s;

// Buffer Declarations
char ballTemp[10];
char scoreTemp[10];

// Debounce delays
int sensDelay = 500; 
int resetDelay = 500;

// Servo Declarations
int open = 90;
int close = 180;

void setup() {
  // Decided to try using a for loop to designate each input pin as an INPUT. Works.
  for (int eachSensor = 0; eachSensor <= 7; eachSensor++) {
    pinMode(sensors[eachSensor], INPUT); 
  }
  pinMode(resetButton, INPUT);
  ballReturn.attach(servPin);
  Serial.begin(9600);
  ballDisp.begin(9600);
  scoreDisp.begin(9600);
  resetDisplays();
  updateDisplays();
}

void loop() {

  while (balls > 0) {
    
    // returnControl(close);

    for(s = 0; s <= 7; s++){    // Check sensor array.
    result = digitalRead(sensors[s]);           
      
      if (result == LOW) {
        if (s == 0) {
          n = 100;
          addpoints(n);
        }
        if (s == 1) {
          n = 100;
          addpoints(n);
        }
        if (s == 2) {
          n = 50;
          addpoints(n);
        }
        if (s == 3) {
          n = 40;
          addpoints(n);
        }
        if (s == 4) {
          n = 30;
          addpoints(n);
        }
        if (s == 5) {
          n = 20;
          addpoints(n);
        }
         if (s == 6) {
          n = 10;
          addpoints(n);
        }
        
        if (s == 7) {
          n = 0;
          addpoints(n);
        }
        else {
          //donothing
        }
      }
    }

// add line: a break attached to button to reset inc, without resetting arduino.       
    
    startOver();
    
  }//end of while loop
  
  startOver();

} //end of primary loop

void addpoints(int n){
  score = score + n;
  balls = balls - 1;
  updateDisplays();
  Serial.print("Your score is: ");
  Serial.println(score);
  Serial.print("Balls Remaining: ");
  Serial.println(balls);
  delay(sensDelay);
}

void reset(){
  returnControl(open);
  score = 0;
  balls = 9;
  updateDisplays();
  Serial.print("Balls Remaining: ");
  Serial.println(balls);
  delay(1500);
  returnControl(close);
}

void startOver(){
  int resetState = digitalRead(resetButton);
  if (resetState == HIGH){
    reset();
    delay(resetDelay);
  }
}

void returnControl(int x){
  ballReturn.write(x);
}

void updateDisplays(){
  resetDisplays();
  sprintf(ballTemp, "%4d", balls);
  sprintf(scoreTemp, "%04d", score);
  ballDisp.print(ballTemp);
  scoreDisp.print(score);
}

void resetDisplays(){
  ballDisp.write('v');
  scoreDisp.write('v');
}


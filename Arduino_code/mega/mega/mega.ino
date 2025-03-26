#include <Arduino.h>

// Include Arduino Wire library for I2C
#include <Wire.h>
#include "detect_value.h"

// Lcd library
#include <LiquidCrystal_I2C.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define pins
# define Start_Button 5
# define Up_button 4
# define Left_Button 3
# define Right_Button 2
# define Down_Button 6
# define Move_Button 7

// Define LCD
LiquidCrystal_I2C lcd (0x27,16,2);

// Globals
String message = "";
String reply = "NULL";
String AI_move = "";
char Request_Type;
bool Have_Message = false, On_Request = false, Have_AI = false;

int* temp;
const int pinP[8] = {22,24,26,28,30,32,34,36};
const int pinN[8] = {23,25,27,29,31,33,35,37};
char board[8][8] = {{'R','N','B','Q','K','B','N','R'},
                    {'P','P','P','P','P','P','P','P'},
                    {'0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0'},
                    {'0','0','0','0','0','0','0','0'},
                    {'p','p','p','p','p','p','p','p'},
                    {'r','n','b','q','k','b','n','q'}};
// Stanley's part here:

int* boardToYX (String input) {
  int textLen = input.length();
  int splitPos = input.indexOf(" ");
  static int Pos[4] = {}; // {startY, startX, endY, endX}
  String startPos = input.substring(0, splitPos);
  String endPos = input.substring(splitPos+1, textLen);
  char arr[8] = {'a','b','c','d','e','f','g','h'};
  for (int i = 0; i < 8; i++) {
    if (arr[i] == startPos[0]) Pos[1] = i; Pos[0] = startPos[1] - '0' - 1;
  }
  for (int i = 0; i < 8; i++) {
    if (arr[i] == endPos[0]) Pos[3] = i; Pos[2] = endPos[1] - '0' - 1;
  }
  return Pos;
}

struct led {
  void init() {
    for (int i = 0; i < 8; i++) {
      pinMode(pinP[i], OUTPUT);
      pinMode(pinN[i], OUTPUT);
    }
  }

  void on (int y, int x) {
    digitalWrite(pinP[y], HIGH);
    digitalWrite(pinN[x], LOW);
  }

  void offAll () {
    for(int i = 0; i < 8; i++) {
      digitalWrite(pinP[i], LOW);
      digitalWrite(pinN[i], HIGH);
    }
  }
}led;


//Dectector
const int matrix_input_pin[12] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
const String cheat_moves[3] = {"d2 d4", "c2 c4", "e2 e3"};
int cheater = 0;

void requestEvent() { // Function to run when master requests data
  //-----------Ｃ　Ａ　Ｕ　Ｔ　Ｉ　Ｏ　Ｎ-----------
  // This area treats if statments weridly (I don't know why)
  
  if(reply != "NULL") {
    Serial.println("requestEvent replied with:"); // Debug printing
    Serial.println(reply);
    int n = reply.length(); // Duplicating a char array of the reply string
    char re[n];             // (Since the Wire.write() function only takes char array)
    for (int i=0;i<n;i++) {
      re[i] = reply.charAt(i);
    }
    Wire.write(re,sizeof(re)); // Send it
  }
  reply = "NULL";
}

void receiveEvent() { // Function to run when things are send(800 words at most)
  if (Wire.available() || On_Request == false) { // indeed have a message(and it not currently on quest)
    
    message = ""; // Initialize
    message = "";

    // Locals
    byte input[50]; // a byte array to hold the ASCII code of chars trnsfered
    byte cur = 0; // the pos of the current end of the input message
    char temp;

    // Read while data received
    while (Wire.available()) {
      input[cur] = Wire.read(); // Read in the stuff in wire
      char temp = input[cur]; // Transfer ASCII to char
      message += temp; // appennd it to the message
      cur++; // push the pos forward 
    }

    // Check if it is a special message for request
    if(message[0] == 'R' && message[1] == 'E' && message[2] == 'Q') {

      // Serial.println("It did gone in the request zone");
      On_Request = true; 
      Request_Type = message.charAt(4); // Extract the request code
      
      switch (Request_Type) {
        case 'A': // If the request is "start game"
          Serial.println("Request: Start Game");
          break;
        
        case 'B': // If the request is "player make move"
          Serial.println("Request: Player Make Move");   
          break;
        
        default:
          break;
      }
    }
    else if(message[0] == 'P' && message[1] == 'C' && message[2] == ':') { // Check if it is a message from computer
      Have_Message = true;
      Serial.print("------");
      Serial.print("PC message is :");
      Serial.println("------");
      Serial.println(message);
      Serial.println("------------------------");
      if(message[4] == 'M'&& message[5] == '_') {
        Have_AI = true;
        AI_move = "";
        if(message[6] == 'M'){
          AI_move += message[11];
          AI_move += message[12];
          AI_move += ' ';
          AI_move += message[13];
          AI_move += message[14];
        }
        else if(message[6] == 'P'){
          AI_move += message[20];
          AI_move += message[21];
          AI_move += ' ';
          AI_move += message[22];
          AI_move += message[23];
          AI_move += message[24];
        }
      }
    }
    else if(message[0] == 'L' && message[1] == 'E' && message[2] == 'O') { // Check if it is a message from leo
    Have_Message = true;
      Serial.print("------");
      Serial.print("LEO message is :");
      Serial.println("------");
      Serial.println(message);
      Serial.println("------------------------");

    }
  }
}

void CaseA() { // Function to start game()
  if(digitalRead(Start_Button) == HIGH) {
    // BoardSetup();
    reply = "A"; 
    cheater = 0;
  }
  else {
    reply = "NULL";
  }
  // Y(yes) or A(yes with AI on)
}

void CaseB() { // Function to player make move
  if(digitalRead(Move_Button) == HIGH) {
    reply = cheat_moves[cheater];
    cheater += 1;
    led.offAll();
  }
  else {
    reply = "NULL";
  }
  // letter + number + letter + number(perhaps + letter(promotion))
}

void setup() {

  // ------------------I2C coummunicate part------------------
  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR); 
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  // Function to run when master requests data
  Wire.onRequest(requestEvent);
  // ------------------I2C coummunicate part------------------

  // Start serial for debugging 
  Serial.begin(115200);
  
  //  ------------------------Pin mode------------------------
  pinMode(Start_Button, INPUT);
  pinMode(Move_Button, INPUT);
  //  ------------------------Pin mode------------------------

  //  --------------------------LCD---------------------------
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("waiting...      ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  //  --------------------------LCD---------------------------

  led.init();
  led.offAll();

}

void loop() {
  if(Have_Message == true) { // If there is a message in hand
    // Print it...
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message);
    delay(10);
    Have_Message = false; // set Have_message to false
  }
  if(On_Request == true) { // if is on request
    switch (Request_Type) {
      case 'A': // start game
        CaseA();
        break;
      
      case 'B': // player make move
        CaseB();
        break;
      
      default:
        break;
    }
    On_Request = false;
  }
  if(Have_AI == true){
    led.offAll();
    temp = boardToYX(AI_move);
    led.on(temp[0],temp[1]);
    delay(3000);
    led.offAll();
    led.on(temp[2],temp[3]);
    delay(3000);
    Have_AI = false; 
    led.offAll();
  }
  
}

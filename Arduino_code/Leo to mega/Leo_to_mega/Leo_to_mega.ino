// Keyboards library
#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_sv_SE.h>

// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Pin defines
#define DEBUG_PIN 7

// Other defines 
#define PMV_mainT 60

// Global variables
bool game = false;
bool requestingP = false;
bool requestingPro = false;
String answer = ""; // String to hold answer
String Re_reply = "The reply LEO got: "; // The string to reply to mega[debug use]
String RQmessage = "      "; // Making the request message
String reply = ""; // The reply string for PlayerMakeMove and PlayerMakePRO
String Serial_text = ""; // The serial from computer

void setup() {
  // Initialize I2C communications as Master(no parameter)
  Wire.begin();

  // Pins
  pinMode(DEBUG_PIN, INPUT);
}

String serialRead() { // Function to read data from Serial
  String input = "";
  while (Serial.available()) {
    input = Serial.readString();
  }
  return input;
}

void Transfer(String input) { // Function to send normal message to Slave
  Wire.beginTransmission(SLAVE_ADDR); // Start transmission
  
  // Setup a char array that is a copy of the message string
  int input_size = input.length();
  char message[input_size];
  for (int i=0;i<input_size;i++) {
    message[i] = input.charAt(i);
  }

  // send it
  Wire.write(message,sizeof(message));
  Wire.endTransmission();
}

String Give_Quest(char code) { // Function to assign quest
  answer = ""; 
  Re_reply = "LEO: The reply LEO got: ";
  Wire.beginTransmission(SLAVE_ADDR); // Start transmission
  RQmessage = "      "; // Making the request message
  RQmessage[0] = 'R';
  RQmessage[1] = 'E';
  RQmessage[2] = 'Q';
  RQmessage[3] = ' ';
  RQmessage[4] = code;
  RQmessage[5] = '\n';
  Transfer(RQmessage);
  delay(1000);
  // request different amount of information from slave determined by request code
  switch (code) {
    case 'A': // start game
      Wire.requestFrom(SLAVE_ADDR, 1); // Y or A
      break;
    
    case 'B': // player make move
      Wire.requestFrom(SLAVE_ADDR, 5);    
      break;
    
    case 'C': // player make move promote
      Wire.requestFrom(SLAVE_ADDR, 1);    
      break;

    default:
      break;
  }
  delay(200);
  if (Wire.available()) { // getting the data returned
    while (Wire.available()){
      answer += (char) Wire.read();
    }
  }
  if(answer != ""){
    Re_reply += answer;
    Transfer(Re_reply); // debug message
  }
  Wire.endTransmission(); // end transmission
  return answer; // return answer
}

void GameStarter() {
  String reply = Give_Quest('A');
  if(reply.charAt(0) == 'Y' || reply.charAt(0) == 'A') { // Let's start the game
    // Press the Win key
    Keyboard.press(KEY_LEFT_GUI);
    delay(50);
    // Press "r"
    Keyboard.press('r');
    delay(50);
    // Release both keys
    Keyboard.release(KEY_LEFT_GUI);
    delay(50);
    Keyboard.release('r');
    // Release all keys (double check)
    Keyboard.releaseAll();
    delay(600);


    // Type the file path you want to open
    String filePath = "D:\\coding\\me-trying-to-make-games-of-my-own\\chess-console-local\\build\\chess.exe";

    // Type the file path
    Keyboard.print(filePath);
    delay(50);
    // Press Enter to execute the file
    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    delay(1000);

    //Shift to english
    Keyboard.press(KEY_LEFT_SHIFT);
    delay(50);
    Keyboard.release(KEY_LEFT_SHIFT);

    // Start arduino mode
    Keyboard.press('d');
    delay(50);
    Keyboard.release('d');
    delay(50);
    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    delay(200);
    // Turn on AI mode depending on the reply
    if(reply == "A") {
      Keyboard.press('a');
      delay(50);
      Keyboard.release('a');
      delay(50);
      Keyboard.press(KEY_RETURN);
      delay(50);
      Keyboard.release(KEY_RETURN);
      delay(200);
      delay(200);
    }

    // Create new game
    Keyboard.press('n');
    delay(50);
    Keyboard.release('n');
    delay(50);
    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    delay(200);
    
    game = true;
  }
  else return;
}

void PlayerMakeMove() {
  reply = Give_Quest('B');
  int n = reply.length();
  int checker = 0;
  int check0 = (int)reply[0] - 'a';
  if(check0 > 0 && check0 < 9)  checker ++;

  int check1 = (int)reply[1] - '0';
  if(check0 > 0 && check0 < 9)  checker ++;

  int check2 = (int)reply[3] - 'a';
  if(check0 > 0 && check0 < 9)  checker ++;

  int check3 = (int)reply[4] - '0';
  if(check0 > 0 && check0 < 9)  checker ++;

  if(checker == 4 ) { // normal case
    Transfer("LEO: Normal case --- from leo process");
    Keyboard.releaseAll();
    Keyboard.print('m');
    delay(PMV_mainT);

    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    delay(PMV_mainT);
    
    delay(100);

    delay(50);
    Keyboard.print(reply[0]);
    delay(PMV_mainT);

    Keyboard.print(reply[1]);
    delay(PMV_mainT);

    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    Keyboard.releaseAll();
    delay(PMV_mainT);

    delay(400);

    Keyboard.print(reply[3]);
    delay(PMV_mainT);
    Keyboard.print(reply[4]);
    delay(PMV_mainT);

    Keyboard.press(KEY_RETURN);
    delay(50);
    Keyboard.release(KEY_RETURN);
    Keyboard.releaseAll();
    delay(PMV_mainT);
    delay(500);
    requestingP = false;
  }
  else return;
}

void PlayerMakePRO() {
  reply = Give_Quest('C');
  Keyboard.print(reply);
  delay(PMV_mainT);

  Keyboard.press(KEY_RETURN);
  delay(50);
  Keyboard.release(KEY_RETURN);
  Keyboard.releaseAll();

  delay(500);

  requestingP = false;
}

void loop() {
  while(game == false) { // Wait till the game started
    GameStarter();
    delay(500);
    requestingP = true;
  }
  if(requestingP == true){
    while(requestingP == true) {
      if(digitalRead(DEBUG_PIN) == HIGH){
        game = false;
        break;
      }
      Transfer("LEO: leo asking for move");
      PlayerMakeMove();
    }
  }
  if(requestingPro == true){
    while(requestingPro == true) {
      if(digitalRead(DEBUG_PIN) == HIGH){
        game = false;
        break;
      }
      Transfer("LEO: leo asking for PROmove");
      PlayerMakePRO();
    }
  }
  if(digitalRead(DEBUG_PIN) == HIGH){
    game = false;
  }
  if(Serial.available()) {
    Serial_text = serialRead();
    if(Serial_text == "PC: ROUND finished\n"){ // We need the player to make move
      requestingP = true;
    }
    if(Serial_text == "PC: PROMOTE\n"){
      requestingPro = true;
    }
    else{
      Serial_text += "---from computer ";
      Transfer(Serial_text);
    }
  }
  delay(10);
}

/* Request code chart

A - StartGame
B - PlayerMakesMove
C - PlayerMakePRO

*/

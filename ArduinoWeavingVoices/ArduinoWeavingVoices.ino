/* 
Weaving Voices keyboard read sketch
*/


#include <Keypad.h>

const byte ROWS = 6; //four rows
const byte COLS = 4; //three columns
char hexaKeys[ROWS][COLS] = {
{'1','2','3','q'},
{'4','5','6','w'},
{'7','8','9','e'},
{'*','0','#','r'},
{'a','s','d','t'},
{'f','g','h','y'}
};


byte rowPins[ROWS] = {8, 7, 6, 5, 4, 3}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {12, 11, 10, 9}; //connect to the column pinouts of the kpd

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}

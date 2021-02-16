#include <OLED_I2C.h>

extern uint8_t BigFont[];
OLED  myOLED(SDA, SCL, 8); //green - 4, yellow - 5


int discOne = 3;
int discTwo = 5;
int switchPin = 11; //green
int selectPin = 12; //red

int arrIndex = 0;
String breathingTechnique[] = {"4-7-8", "4-4-4", "5-5-5"};
String selectedTechnique = breathingTechnique[0];
int arrSize = (sizeof(breathingTechnique) / sizeof(breathingTechnique[0]));

void setup() {
  Serial.begin(9600);
  myOLED.begin();
  myOLED.setFont(BigFont);
  myOLED.update();
  pinMode(discOne, OUTPUT);
  pinMode(discTwo, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(selectPin, INPUT_PULLUP); 
  arrIndex = 0;
  myOLED.print("Hello!", CENTER, 24);
  myOLED.update();
  myOLED.clrScr();
}

void loop() {
  Serial.println("RUNNING");
  if (digitalRead(switchPin) == LOW) {
    Serial.println("SWITCH TECHNIQUE BTN PRESSED");
    if (arrIndex >= arrSize) {
      arrIndex = 0;
    } 
    myOLED.clrScr();
    myOLED.print(breathingTechnique[arrIndex++], CENTER, 24);
    myOLED.update();
  } else if (digitalRead(selectPin) == LOW) {
    Serial.println("SELECT TECHNIQUE BTN PRESSED: " + arrIndex);
    switch (arrIndex) {
      case 1:
        getBreathingTechnique(4, 7, 8);
        break;
      case 2:
        getBreathingTechnique(4, 4, 4);
        break;
      case 3:
        getBreathingTechnique(5, 5, 5);
        break;
    }
  }
  delay(200);
}

void count(int n) {
  for(int i = n; i > 0; i--) {
    myOLED.printNumI(i, CENTER, 24);
    myOLED.update();
    delay(1000);
  }
}

void getBreathingTechnique(int inhale, int hold, int exhale) {
  myOLED.print("INHALE", CENTER, 24);
  myOLED.update();
  analogWrite(discOne, 255);
  analogWrite(discTwo, 255);
  delay(500);
  myOLED.clrScr();
  analogWrite(discOne, 0);
  analogWrite(discTwo, 0);
  count(inhale);

  myOLED.print("HOLD", CENTER, 24);
  myOLED.update();
  analogWrite(discOne, 255);
  analogWrite(discTwo, 255);
  delay(500);
  myOLED.clrScr();
  analogWrite(discOne, 0);
  analogWrite(discTwo, 0);
  count(hold);

  myOLED.print("EXHALE", CENTER, 24);
  myOLED.update();
  analogWrite(discOne, 255);
  analogWrite(discTwo, 255);
  delay(500);
  myOLED.clrScr();
  analogWrite(discOne, 0);
  analogWrite(discTwo, 0);
  count(exhale);
}

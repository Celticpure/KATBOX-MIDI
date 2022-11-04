#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

// Control Surface:
#include <Control_Surface.h>
#include <AH/Hardware/MultiPurposeButton.hpp> //FOR USING MULTIPURPOSE BUTTON FUNCTION

BluetoothMIDI_Interface midi;                 //TYPE OF INTERFACE USED TO COMMUNICATE

// DISPLAY:
Adafruit_SSD1306 display(-1);

// this constant won't change:
const int button1  = 15;            //GPIO 15, BUTTON 1
const int button2  = 19;            //GPIO 19, BUTTON 2
const int button3  = 4;             //GPIO 4, BUTTON 3
const int button4  = 5;             //GPIO 5, BUTTON 4

MultiPurposeButton btn1{15};      //BTN No.1
MultiPurposeButton btn2{19};      //BTN No.2
MultiPurposeButton btn3{4};       //BTN No.3
MultiPurposeButton btn4{5};       //BTN No.4

// variables will change:
int buttonState = 1;
byte buttonstate = 0;

void setup() {

  Serial.begin (9600);                        // initialize serial communication:

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C

  display.clearDisplay();                     // Clear the buffer.

  display.setFont(&FreeSans9pt7b);            // Set Font

  Control_Surface.begin();                    // Set Control Surface
  btn1, btn2, btn3, btn4.setLongPressDelay(1000);
  btn1, btn2, btn3, btn4.setMultiPressDelay(400);
  btn1, btn2, btn3, btn4.begin();

  // delay(2000);
  //display.clearDisplay();

  // initialize the button pin as a input:
  {
    pinMode(button1, INPUT_PULLUP);     //"INPUT_PULLUP" OR "INPUT"????????
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(button4, INPUT_PULLUP);
    digitalWrite(button1, HIGH);
    digitalWrite(button2, HIGH);
    digitalWrite(button3, HIGH);
    digitalWrite(button4, HIGH);
  }
}

void loop() {
  //display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 15);
  display.println("KATBOX MIDI");
  display.display();
  //delay(2000);

  multibtn();
  btn_disp();
  Control_Surface.loop();
}

void multibtn()
{
  switch (btn1.update()) {      //BTN No.1
    case btn1.None: break;
    case btn1.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}, 0); break;
    case btn1.ShortPressRelease: break;
    case btn1.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_2, CHANNEL_1}, 0);
      break;
    case btn1.LongPressRelease:
      break;
    case btn1.MultiPress: break;
    case btn1.MultiPressDone: break;
  }
  switch (btn2.update()) {      //BTN No.2
    case btn2.None: break;
    case btn2.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_3, CHANNEL_2}, 0);
      break;
    case btn2.ShortPressRelease: break;
    case btn2.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, 0);
      break;
    case btn2.LongPressRelease:
      break;
    case btn2.MultiPress: break;
    case btn2.MultiPressDone: break;
  }
  switch (btn3.update()) {      //BTN No.3
    case btn3.None: break;
    case btn3.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_5, CHANNEL_3}, 0);
      break;
    case btn3.ShortPressRelease:
      break;
    case btn3.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_6, CHANNEL_3}, 0);
      break;
    case btn3.LongPressRelease:
      break;
    case btn3.MultiPress: break;
    case btn3.MultiPressDone: break;
  }
  switch (btn4.update()) {      //BTN No.4
    case btn4.None: break;
    case btn4.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_7, CHANNEL_4}, 0);
      break;
    case btn4.ShortPressRelease:
      break;
    case btn4.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_8, CHANNEL_4}, 0);
      break;
    case btn4.LongPressRelease:
      break;
    case btn4.MultiPress: break;
    case btn4.MultiPressDone: break;
  }
}

void btn_disp(){
  if (digitalRead(button1) == LOW)        //BUTTON 1 DISPLAY
  { display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    //display.setTextSize(1);
    display.print("PATCH 1");
  }
  else if (digitalRead(button2) == LOW)   //BUTTON 2 DISPLAY
  { display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    //display.setTextSize(1);
    display.print("PATCH 2");
  }
  else if (digitalRead(button3) == LOW)   //BUTTON 3 DISPLAY
  { display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    //display.setTextSize(1);
    display.print("PATCH 3");
  }
  else if (digitalRead(button4) == LOW)   //BUTTON 4 DISPLAY
  { display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    //display.setTextSize(1);
    display.print("PATCH 4");
  }
  display.display();
}

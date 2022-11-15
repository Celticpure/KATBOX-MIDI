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

MultiPurposeButton btn1{15};      //BTN No.1
MultiPurposeButton btn2{19};      //BTN No.2
MultiPurposeButton btn3{4};       //BTN No.3
MultiPurposeButton btn4{5};       //BTN No.4

int new_button, old_button;
char str_buf[30];

void btn_disp() {
  if (new_button != old_button) {
    old_button = new_button;
    display.fillRect(0, 20, 100, 40, BLACK);
    sprintf(str_buf, "PATCH %d", new_button);
    display.setCursor(0, 40);
    display.print(str_buf);
    display.display();
  }
}

void multibtn()
{
  switch (btn1.update()) {      //BTN No.1
    case btn1.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}, 0);
      new_button = 1;
      break;
    case btn1.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_2, CHANNEL_1}, 0);
      new_button = 1;
      break;
  }
  switch (btn2.update()) {      //BTN No.2
    case btn2.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_3, CHANNEL_2}, 0);
      new_button = 2;
      break;
    case btn2.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, 0);
      new_button = 2;
      break;
  }
  switch (btn3.update()) {      //BTN No.3
    case btn3.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_5, CHANNEL_3}, 0);
      new_button = 3;
      break;
    case btn3.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_6, CHANNEL_3}, 0);
      new_button = 3;
      break;
  }
  switch (btn4.update()) {      //BTN No.4
    case btn4.PressStart:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_7, CHANNEL_4}, 0);
      new_button = 4;
      break;
    case btn4.LongPress:
      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_8, CHANNEL_4}, 0);
      new_button = 4;
      break;
  }
}


void setup() {
  Serial.begin (9600);                        // initialize serial communication:

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C
  display.clearDisplay();                     // Clear the buffer.
  display.setFont(&FreeSans9pt7b);            // Set Font

  Control_Surface.begin();                    // Set Control Surface
  btn1.setLongPressDelay(1000);
  btn2.setLongPressDelay(1000);
  btn3.setLongPressDelay(1000);
  btn4.setLongPressDelay(1000);
  btn1.setMultiPressDelay(400);
  btn2.setMultiPressDelay(400);
  btn3.setMultiPressDelay(400);
  btn4.setMultiPressDelay(400);
  btn1.begin();
  btn2.begin();
  btn3.begin();
  btn4.begin();

  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 15);
  display.println("KATBOX MIDI");
  display.display();

  old_button = 0;
  new_button = 0;
}

void loop() {
  Control_Surface.loop();
  multibtn();
  btn_disp();
}

#include <U8g2lib.h>
#include "wordlist.h"

// Display-Setup (SH1106 I2C)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Button-Pin
#define sw_pin 2
int lastButtonState = HIGH;
bool running = false;

const int wordCount = sizeof(wordList) / sizeof(wordList[0]);

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_courB10_tf);
  pinMode(sw_pin, INPUT_PULLUP);

  u8g2.clearBuffer();
  u8g2.setCursor(45,35);
  u8g2.print("Ready.");
  u8g2.sendBuffer();
}

void loop() {
  int buttonState = digitalRead(sw_pin);

  if (!running && buttonState == LOW && lastButtonState == HIGH) {
    delay(50); // debounce
    running = true;

    for (int i = 0; i < wordCount; i++) {
      u8g2.clearBuffer();
      u8g2.setCursor(0,20);
      u8g2.print(wordList[i]);
      u8g2.sendBuffer();

      Keyboard.print(wordList[i]);
      Keyboard.press(KEY_ENTER);
      delay(20);
      Keyboard.release(KEY_ENTER);

      delay(5000);
    }

    u8g2.clearBuffer();
    u8g2.setCursor(0,20);
    u8g2.print("Done!");
    u8g2.sendBuffer();

    delay(2000); 

    u8g2.clearBuffer();
    u8g2.setCursor(0,20);
    u8g2.print("Ready.");
    u8g2.sendBuffer();

    running = false;
  }

  lastButtonState = buttonState;
}

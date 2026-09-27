// While the button (P1.4) is held down, the NeoPixel (D1, P1.5) cycles
// through rainbow colors. Each press also types a URL over USB HID.
//
// Board settings (Tools menu):
//   Board:       CH552 Board
//   Clock:       16 MHz (internal)
//   USB Settings: USER CODE w/ 148B USB ram
//
// This sketch also needs the "userUsbHidKeyboard" helper files sitting
// next to it (see setup notes below) - they come from the ch55xduino
// examples folder: File > Examples > CH55xduino > 05.USB > HidKeyboard.
// Copy that example's "src" folder into this sketch's folder so you end up
// with:
//   firmware/
//     firmware.ino
//     src/userUsbHidKeyboard/USBHIDKeyboard.c
//     src/userUsbHidKeyboard/USBHIDKeyboard.h
//     src/userUsbHidKeyboard/USBconstant.c
//     src/userUsbHidKeyboard/USBconstant.h
//     src/userUsbHidKeyboard/USBhandler.c
//     src/userUsbHidKeyboard/USBhandler.h

#ifndef USER_USB_RAM
#error "This sketch needs to be compiled with a USER USB setting"
#endif

#include <WS2812.h>
#include "src/userUsbHidKeyboard/USBHIDKeyboard.h"

#define BUTTON_PIN 14 // P1.4 (SW1)
#define LED_PIN 15    // P1.5 (NeoPixel data, via R4)

__xdata uint8_t ledData[3];

bool buttonPressedPrev = false;
uint8_t hue = 0;

void setPixelOff() {
  set_pixel_for_GRB_LED(ledData, 0, 0, 0, 0);
  neopixel_show_P1_5(ledData, 3);
}

// Classic color wheel: pos 0-255 sweeps through the rainbow.
// Scaled down (>>3) to keep it comfortably dim.
void wheel(uint8_t pos, uint8_t *r, uint8_t *g, uint8_t *b) {
  pos = 255 - pos;
  if (pos < 85) {
    *r = 255 - pos * 3;
    *g = 0;
    *b = pos * 3;
  } else if (pos < 170) {
    pos -= 85;
    *r = 0;
    *g = pos * 3;
    *b = 255 - pos * 3;
  } else {
    pos -= 170;
    *r = pos * 3;
    *g = 255 - pos * 3;
    *b = 0;
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  USBInit();
  setPixelOff();
}

void loop() {
  bool buttonPressed = !digitalRead(BUTTON_PIN);

  if (buttonPressed != buttonPressedPrev) {
    buttonPressedPrev = buttonPressed;
    if (buttonPressed) {
      Keyboard_print("https://github.com/acornitum/snowflake");
    } else {
      setPixelOff();
    }
    delay(20); // naive debounce
  }

  if (buttonPressed) {
    uint8_t r, g, b;
    wheel(hue, &r, &g, &b);
    set_pixel_for_GRB_LED(ledData, 0, r >> 3, g >> 3, b >> 3);
    neopixel_show_P1_5(ledData, 3);
    hue += 3;
    delay(20); // rotation speed
  }
}

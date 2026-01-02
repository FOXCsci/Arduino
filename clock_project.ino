#include <Wire.h>
#include <DS3231.h>
#include <FastLED.h>


/*
TODO: 
-make functions for repetitive actions
-make a 2d const bool array to map to bool arrays to avoid redundancy
-use millis() function to control rainbow effect
- CLEAR SEGMENT ARRAYS BEFORE WRITING -> memset(bool_arr, 0, sizeof(bool_arr))
*/

#define DATA_PIN 4
#define NUM_LEDS 112
#define SECOND_DIGIT 28
#define THIRD_DIGIT 56
#define FOURTH_DIGIT 84
#define DEBUG 0

bool tens_hours[7];
bool ones_hours[7];
bool tens_minutes[7];
bool ones_minutes[7];

DS3231 clock;
RTCDateTime dt;


CRGB leds[NUM_LEDS];

void setDigit(bool logic_arr[], int num) {
  switch (num) {
    case 0:
      logic_arr[0] = 1;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 1;
      logic_arr[5] = 1;
      logic_arr[6] = 0;
      break;

    case 1:
      logic_arr[0] = 0;
      logic_arr[1] = 0;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 0;
      logic_arr[5] = 0;
      logic_arr[6] = 0;
      break;

    case 2:
      logic_arr[0] = 0;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 0;
      logic_arr[4] = 1;
      logic_arr[5] = 1;
      logic_arr[6] = 1;
      break;

    case 3:
      logic_arr[0] = 0;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 1;
      logic_arr[5] = 0;
      logic_arr[6] = 1;
      break;

    case 4:
      logic_arr[0] = 1;
      logic_arr[1] = 0;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 0;
      logic_arr[5] = 0;
      logic_arr[6] = 1;
      break;

    case 5:
      logic_arr[0] = 1;
      logic_arr[1] = 1;
      logic_arr[2] = 0;
      logic_arr[3] = 1;
      logic_arr[4] = 1;
      logic_arr[5] = 0;
      logic_arr[6] = 1;
      break;

    case 6:
      logic_arr[0] = 1;
      logic_arr[1] = 1;
      logic_arr[2] = 0;
      logic_arr[3] = 1;
      logic_arr[4] = 1;
      logic_arr[5] = 1;
      logic_arr[6] = 1;
      break;

    case 7:
      logic_arr[0] = 0;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 0;
      logic_arr[5] = 0;
      logic_arr[6] = 0;
      break;

    case 8:
      logic_arr[0] = 1;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 1;
      logic_arr[5] = 1;
      logic_arr[6] = 1;
      break;

    case 9:
      logic_arr[0] = 1;
      logic_arr[1] = 1;
      logic_arr[2] = 1;
      logic_arr[3] = 1;
      logic_arr[4] = 0;
      logic_arr[5] = 0;
      logic_arr[6] = 1;
      break;

    default:
      break;
  }
}

  void setup() {
  Serial.begin(9600);
  clock.begin();

  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);

  //clock.setDateTime(2026, 1 ,1, 15, 34, 20);
}

void loop() {
  dt = clock.getDateTime();

#if DEBUG
  Serial.print(dt.hour);
  Serial.print(":");
  Serial.print(dt.minute);
  Serial.print(":");
  Serial.println(dt.second);
  delay(1000);
#endif

  //clear arrays
  memset(tens_hours, 0, sizeof(tens_hours));
  memset(ones_hours, 0, sizeof(tens_hours));
  memset(tens_minutes, 0, sizeof(tens_hours));
  memset(ones_minutes, 0, sizeof(tens_hours));


  // get boolean data
  setDigit(tens_hours, dt.hour/10);
  setDigit(ones_hours, dt.hour%10);
  setDigit(tens_minutes, dt.minute/10);
  setDigit(ones_minutes, dt.minute%10);
  //read boolean data into leds array

  for (int i = 0; i < 7; i++) {
    if (tens_hours[i]) {
      leds[(i * 4)] = ColorFromPalette(RainbowColors_p, i * 255 / NUM_LEDS);
      leds[(i * 4) + 1] = ColorFromPalette(RainbowColors_p, (i + 1) * 255 / NUM_LEDS);
      leds[(i * 4) + 2] = ColorFromPalette(RainbowColors_p, (i + 2) * 255 / NUM_LEDS);
      leds[(i * 4) + 3] = ColorFromPalette(RainbowColors_p, (i + 3) * 255 / NUM_LEDS);
    }

    else {
      leds[(i * 4)] = CRGB::Black;
      leds[(i * 4) + 1] = CRGB::Black;
      leds[(i * 4) + 2] = CRGB::Black;
      leds[(i * 4) + 3] = CRGB::Black;
    }
  }

  for (int i = 0; i < 7; i++) {
    if (ones_hours[i]) {
      leds[(i * 4) + SECOND_DIGIT] = ColorFromPalette(RainbowColors_p, i * 255 / NUM_LEDS);
      leds[(i * 4) + 1 + SECOND_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 1 + SECOND_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 2 + SECOND_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 2 + SECOND_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 3 + SECOND_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 3 + SECOND_DIGIT) * 255 / NUM_LEDS);
    }

    else {
      leds[(i * 4) + SECOND_DIGIT] = CRGB::Black;
      leds[(i * 4) + 1 + SECOND_DIGIT] = CRGB::Black;
      leds[(i * 4) + 2 + SECOND_DIGIT] = CRGB::Black;
      leds[(i * 4) + 3 + SECOND_DIGIT] = CRGB::Black;
    }
  }

  for (int i = 0; i < 7; i++) {
    if (tens_minutes[i]) {
      leds[(i * 4) + THIRD_DIGIT] = ColorFromPalette(RainbowColors_p, i * 255 / NUM_LEDS);
      leds[(i * 4) + 1 + THIRD_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 1 + THIRD_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 2 + THIRD_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 2 + THIRD_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 3 + THIRD_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 3 + THIRD_DIGIT) * 255 / NUM_LEDS);
    }

    else {
      leds[(i * 4) + THIRD_DIGIT] = CRGB::Black;
      leds[(i * 4) + 1 + THIRD_DIGIT] = CRGB::Black;
      leds[(i * 4) + 2 + THIRD_DIGIT] = CRGB::Black;
      leds[(i * 4) + 3 + THIRD_DIGIT] = CRGB::Black;
    }
  }

  for (int i = 0; i < 7; i++) {
    if (ones_minutes[i]) {
      leds[(i * 4) + FOURTH_DIGIT] = ColorFromPalette(RainbowColors_p, i * 255 / NUM_LEDS);
      leds[(i * 4) + 1 + FOURTH_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 1 + FOURTH_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 2 + FOURTH_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 2 + FOURTH_DIGIT) * 255 / NUM_LEDS);
      leds[(i * 4) + 3 + FOURTH_DIGIT] = ColorFromPalette(RainbowColors_p, (i + 3 + FOURTH_DIGIT) * 255 / NUM_LEDS);
    }

    else {
      leds[(i * 4) + FOURTH_DIGIT] = CRGB::Black;
      leds[(i * 4) + 1 + FOURTH_DIGIT] = CRGB::Black;
      leds[(i * 4) + 2 + FOURTH_DIGIT] = CRGB::Black;
      leds[(i * 4) + 3 + FOURTH_DIGIT] = CRGB::Black;
    }
  }


  FastLED.show();
}

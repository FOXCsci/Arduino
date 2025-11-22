#include <Wire.h>
#include <DS3231.h>
#include <FastLED.h>

#define SET_TIME 0

#define STRIP_LENGTH 4 /* Used for accessing certain strips of leds in the leds array*/
#define NUM_LEDS 112

/***** RTC VARIABLES *****/
DS3231 clock;
RTCDateTime dt;
/*************************/

/***** LED VARIABLES *****/
CRGB leds[NUM_LEDS];
/*************************/

/***** PROGRAM VARIABLES *****/
int year;
int month; 
int day;
int hours;
int minutes;
int seconds;
bool first_digit_hours[7];
bool second_digit_hours[7];

bool first_digit_minutes[7];
bool second_digit_minutes[7];

bool first_digit_seconds[7];
bool second_digit_seconds[7];
/*****************************/

/***** FUNCTION PROTOTYPES *****/
  /*Transform: Makes an array have certain segments activated depending on the number passed to it. For example if one is passed, segments 2 and 3 will be activated
    which corresponds to elements 1 and 2 being set to 1*/
int transform(int number, int digit[], int size); 
/*******************************/

void setup() {
  Serial.begin(9600);
  clock.begin();

  if(SET_TIME) {
    while(Serial.available() == 0);
    
      int init_year = Serial.parseInt();
      int init_month = Serial.parseInt();
      int init_day = Serial.parseInt();
      int init_hour = Serial.parseInt();
      int init_minute = Serial.parseInt();
      int init_second = Serial.parseInt();
      //Set time 
      clock.setDateTime(init_year, init_month, init_day, init_hour, init_minute, init_second);
  }
}

void loop() {
  dt = clock.getDateTime();
  year = dt.year; 
  month = dt.month;
  day = dt.month;
  hours = dt.hour;
  minutes = dt.minute;
  seconds = dt.second;

  transform(seconds/10, first_digit_seconds, sizeof(first_digit_seconds));
  transform(seconds%10, second_digit_seconds, sizeof(second_digit_seconds));

  transform(minutes/10, first_digit_minutes, sizeof(first_digit_minutes));
  transform(minutes%10, second_digit_minutes, sizeof(second_digit_minutes));

  transform(minutes/10, first_digit_hours, sizeof(first_digit_hours));
  transform(minutes%10, second_digit_hours, sizeof(second_digit_hours));
}




/***** FUNCTIONS *****/

int transform(int number, int digit[], int size) {
  if (size > 7) {
    return -1;
  }

  switch (number) {
    case 0:
      digit[0] = 1;
      digit[1] = 1;
      digit[2] = 1;
      digit[3] = 1;
      digit[4] = 1;
      digit[5] = 0;
      digit[6] = 1;
      break;

    case 1:
      digit[0] = 0;
      digit[1] = 1;
      digit[2] = 1;
      digit[3] = 0;
      digit[4] = 0;
      digit[5] = 0;
      digit[6] = 0;
      break;

    case 2:
      digit[0] = 1;
      digit[1] = 1;
      digit[2] = 0;
      digit[3] = 1;
      digit[4] = 0;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 3:
      digit[0] = 1;
      digit[1] = 0;
      digit[2] = 0;
      digit[3] = 1;
      digit[4] = 1;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 4:
      digit[0] = 0;
      digit[1] = 0;
      digit[2] = 1;
      digit[3] = 0;
      digit[4] = 1;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 5:
      digit[0] = 1;
      digit[1] = 0;
      digit[2] = 1;
      digit[3] = 1;
      digit[4] = 0;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 6:
      digit[0] = 1;
      digit[1] = 1;
      digit[2] = 1;
      digit[3] = 1;
      digit[4] = 0;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 7:
      digit[0] = 0;
      digit[1] = 0;
      digit[2] = 0;
      digit[3] = 1;
      digit[4] = 1;
      digit[5] = 0;
      digit[6] = 1;   
      break;

    case 8:
      digit[0] = 1;
      digit[1] = 1;
      digit[2] = 1;
      digit[3] = 1;
      digit[4] = 1;
      digit[5] = 1;
      digit[6] = 1;
      break;

    case 9:
      digit[0] = 1;
      digit[1] = 0;
      digit[2] = 1;
      digit[3] = 1;
      digit[4] = 1;
      digit[5] = 1;
      digit[6] = 1;
      break;

    default:
      break;
  }
  return 0;
}

/*********************/


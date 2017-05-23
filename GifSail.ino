/*
   Animated GIFs Display Code for Copa Clambana Dance Floor

   This file contains code to parse animated GIF files

   Written by: Robin Newhouse

   Copyright (c) 2016 Robin Newhouse

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// #include <GIFDecoder.h>
// #include <IRremote.h>
// #include <OctoWS2811.h>
#include <SD.h>
#include "GIFDecoder.h"

// #include "LEDMap.h"

//======================================================
//============ Constants and Fields ====================
//======================================================
// #define NUM_LEDS_PER_STRIP 288
// #define NUM_STRIPS 4
// const int NUM_LEDS = NUM_LEDS_PER_STRIP * NUM_STRIPS;
// #define LED_PER_PIX 8
// #define LED_TYPE OCTOWS2811
// #define DISPLAY_TIME_SECONDS 30
// SD confuiguration
#define USE_SDIO 1
const uint8_t SD_CS = SS;

#define WHITE  0xFFFFFF
#define BLACK  0x000000

#define GIF_DIRECTORY "/gifs/"
#define TERMINATE_ANIMATION -1
#define CONTINUE_ANIMATION 0

// fields
int num_files;
int fileIndex;

unsigned long renderTime;
unsigned long futureTime;
int controlFlag = 0;

char directory[30];

// initialize LED array with the proper LED type
// OctoWS2811 leds(NUM_LEDS_PER_STRIP, displayMemory, drawingMemory, config);


//======================================================
//============ Gif Rendering Callbacks   ===============
//======================================================
void screenClearCallback(void) {
  // Wipe all black
  // for (int i = 0; i <= NUM_LEDS; i++) {
  //   leds.setPixel(i, BLACK);
  // }
  LEDS.clear();
}

void updateScreenCallback(void) {
  // Render current LED array
  if( Show() == false)
    controlFlag = TERMINATE_ANIMATION;
  screenClearCallback();
}

int checkControlCallback(void) {
  if (controlFlag != CONTINUE_ANIMATION)
    return TERMINATE_ANIMATION; // stop the animation

  return CONTINUE_ANIMATION;
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  // Fill each LED that belongs to this pixel
  bool out_of_bounds = false;
  // bool out_of_bounds = x >= 12 || y >= 12;
  if ( out_of_bounds ) {
    Serial.println("Index out of bounds");
    controlFlag = TERMINATE_ANIMATION;
    return;
  }

  leds[Sail[x][y]] = CRGB( red, green, blue);

  // for (int i = 0; i < LED_PER_PIX; i++) {
  //   int led_index = myPixelMap [x][y][i];
  //   // converts rgb to hex
  //   leds.setPixel(led_index, ((red << 16) | (green << 8) | blue));
  // }
}

int increment_file(){
  // increment file
  if (fileIndex >= num_files - 1)
    fileIndex = 0;
  if (fileIndex < 0)
    fileIndex = num_files - 1;
  else fileIndex++;
  return fileIndex;
}

void playGIF(){
  controlFlag = 0; // reset flag
  char pathname[30];
  char directory[30];
  strcpy(directory, GIF_DIRECTORY);
  
  // Strangely this number must be continully updated
  // num_files = enumerateGIFFiles(directory, false);

  increment_file();

  //             Uncomment for random
  // fileIndex = random(num_files);  // select a file index (keep track)


  getGIFFilenameByIndex(directory, fileIndex, pathname);


// Repeat Gif until finished or until NEXT button is pushed
while (cont) {
  Serial.print("#");
  // The gif processing sequence starts here
  int result = processGIFFile(pathname);
      if (result < 0 || controlFlag < 0) { // Error, skip this one.
        Serial.println("Error processing GIF file.");
        increment_file();
        getGIFFilenameByIndex(directory, fileIndex, pathname);
        controlFlag = 0; // reset flag
    }
  }
}

void setupGIFs(){
  strcpy(directory, GIF_DIRECTORY);

  if (!SD.exists(directory)) {
    SD.begin(SD_CS);
    delay(400);
    Serial.println("initialization failed!");
    return;
  }

  num_files = enumerateGIFFiles(directory, false);
  Serial.println("SD Setup Complete");
  Serial.println("========================");
  Serial.print(num_files);
  Serial.println(" animations present.");

// start on a random file
  fileIndex = random(num_files);
// or start on the first file
  fileIndex = 0;


// set callbacks for gif decoder
  setScreenClearCallback(screenClearCallback);
  setUpdateScreenCallback(updateScreenCallback);
  setDrawPixelCallback(drawPixelCallback);
  setCheckControlCallback(checkControlCallback);
}

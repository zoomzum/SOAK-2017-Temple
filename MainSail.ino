

/* Required Connections
  --------------------
   pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
   pin 14: LED strip #2    All 8 are the same length.
   pin 7:  LED strip #3
   pin 8:  LED strip #4    A 100 ohm resistor should used
   pin 6:  LED strip #5    between each Teensy pin and the
   pin 20: LED strip #6    wire to the LED strip, to minimize
   pin 21: LED strip #7    high frequency ringining & noise.
   pin 5:  LED strip #8
   pin 15 & 16 - Connect together, but do not use
   pin 4 - Do not use
   pin 3 - Do not use as PWM.  Normal use is ok.
   pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
           logic analyzer or even an LED (brighter = CPU busier)

   ....   ....   ....   ....   ....   ....   ....   ....   ....   ....
  y72|    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  5 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  4 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  3 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  2 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
  1 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |

  x 1    2 3    4 5    6 7    8 9   10 11  12 13  14 15  16 17  18 19   20
*/



#define USE_OCTOWS2811
#include <OctoWS2811.h>
#include <FastLED.h>


//===============
#define NUM_LEDS_PER_STRIP 300
#define NUM_STRIPS 5
const int PIN_D17 = 17;
//added for fastLED
//const CRGBArray<1500> ledArray;
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
const int numOfBytes = NUM_LEDS_PER_STRIP * NUM_STRIPS * 3;
const int numLeds = NUM_STRIPS * NUM_LEDS_PER_STRIP;

char inputBuffer[numOfBytes];

int  Sail[21][80];
int  SailTop[11][7] = {73, 74, 75, 76, 77, 78};
elapsedMillis sStart;
unsigned long sEnd = 10000;
boolean cont;
boolean panelActive;

void setup() {
  pinMode(PIN_D17, INPUT_PULLUP);
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(100);
  delay(500);
  Serial1.begin(19200);

  // initialize random generator
  randomSeed(analogRead(3)); 

  //  Serial.begin(115200);
  //  Serial.setTimeout(500);
  LEDS.show();

  makeArray();

  setupGIFs();
}

void loop() {

  //  if(Serial.available()>0){
  //  Serial.readBytes(inputBuffer, numOfBytes);

  fill_solid( &(leds[0]), 1500, CRGB(0, 0, 0) );
  LEDS.setBrightness(255);

  sStart = 0;
  sEnd = 30000;
  cont = true;
  //while (cont == true) {
  //   if (sStart < sEnd) {

  //PLACE THE NAME OF YOUR ROUTINE HERE.  It will run for 30 seconds.  If you need to adjust this, change sEnd above to the number of milliseconds you want it to run.
  //  Panel();
  SequenceB();

  //^^^^^^^^^^^^^^^^^^^^^^^^
  //delay(100);
  // } else {
  // cont = false;
  //


  /*
    sStart = 0;
    sEnd=10000;
    cont = true;
    while (cont == true) {
      if (sStart < sEnd) {
        CoolGradient();
      } else {
        cont = false;
      }
    }


    sStart = 0;
    sEnd=30000;
    cont = true;
    while (cont == true) {
    if (sStart < sEnd) {
     Corner();//CascadeUp
    } else {
      cont = false;
    }}

    sStart = 0;
    cont = true;
    sEnd=30000;
    while (cont == true) {
      if (sStart < sEnd) {
        Rain();
      } else {
        cont = false;
      }
    }

    sStart = 0;
    cont = true;
    sEnd=20000;
    while (cont == true) {
      if (sStart < sEnd) {
        Rainbow();
      } else {
        cont = false;
      }
    }

    sStart = 0;
    cont = true;
    sEnd=20000;
    while (cont == true) {
      if (sStart < sEnd) {
        SequenceB();
      } else {
        cont = false;
      }
    }

    sStart = 0;
    cont = true;
    sEnd=20000;
    while (cont == true) {
      if (sStart < sEnd) {
    CosmicRainbow();
     } else {
        cont = false;
      }
    }

    sStart = 0;
    cont = true;
    sEnd=20000;
    while (cont == true) {
      if (sStart < sEnd) {
        RedShift();
      } else {
        cont = false;
      }
    }

    sStart = 0;
    cont = true;
    sEnd=20000;
    while (cont == true) {
      if (sStart < sEnd) {
        Edges();
      } else {
        cont = false;
      }
    }
  */
}//end of loop


void makeArray() {
  int y, s;
  s = 0;

  for (int x = 1; x < 20; x += 2) {
    int l =  (150 * s);
    int  l2 = l + 149;
    for (y = 1; y <= 75; y++) {
      Sail[x][y] = l++;
      Sail[x + 1][y] = l2--;
    }
    s++;

  }

  SailTop[1][1] = 72;
  SailTop[1][2] = 73;
  SailTop[1][3] = 74;
  SailTop[1][4] = 75;
  SailTop[1][5] = 76;
  SailTop[1][6] = 77;

  for (int numsail = 2; numsail <= 10; numsail++) {
    for (int pos = 1; pos <= 6; pos++) {
      SailTop[numsail][pos] = SailTop[numsail - 1][pos] + 150;
    }
  }
}



boolean Show() {
  if (sStart > sEnd || digitalRead(PIN_D17) == LOW) {
    delay(10);
    cont = false;
    return cont;
  }
  //test pin here
  Panel();
  if (panelActive == true) {
    while (panelActive == true) {
      Serial.print("Hit");
      Panel();
    }
  }
  LEDS.show();
  cont = true;
  return cont;
}

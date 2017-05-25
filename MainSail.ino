

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
#define LONG_PRESS 1000
#define HOUR 3600*1000
#define DAY 3600*1000*24
#define RUNTIME 30*1000
const int buttonPin = 17;
const int ledPin = 13; 

//added for fastLED
//const CRGBArray<1500> ledArray;
CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
CRGB leds_backup[NUM_STRIPS * NUM_LEDS_PER_STRIP];
CHSV IR_leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
const int numOfBytes = NUM_LEDS_PER_STRIP * NUM_STRIPS * 3;
const int numLeds = NUM_STRIPS * NUM_LEDS_PER_STRIP;

char inputBuffer[numOfBytes];

int  Sail[21][80];
int  SailTop[11][7] = {73, 74, 75, 76, 77, 78};
elapsedMillis millis_elapsed;
elapsedMillis frame_millis_elapsed;
unsigned long millis_to_run;
unsigned long last_frame_millis;

// button stuff
int buttonPressedTime;

boolean cont;
boolean panelActive;

void setup() {
  Serial.begin(115200);
  delay(20);
  Serial.println("Initializing");


  pinMode(buttonPin, INPUT_PULLUP);
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(100);
  delay(400);
  Serial1.begin(19200);

  // initialize random generator
  randomSeed(millis()); 

  LEDS.show();

  makeArray();

  // setupGIFs();

  // initializePanel();
  Serial.println("Initialization complete");

}

// call this before every sequence
void reset_for_next_pattern(){
  fill_solid( &(leds[0]), 1500, CRGB::Black );
  LEDS.setBrightness(255);

  millis_elapsed = 0;
  millis_to_run = RUNTIME;
  cont = true;
}

void loop() {

  //  if(Serial.available()>0){
  //  Serial.readBytes(inputBuffer, numOfBytes);

  // reset_for_next_pattern();
  // loopPanel();

  //PLACE THE NAME OF YOUR ROUTINE HERE.  It will run for 30 seconds.  If you need to adjust this, change millis_to_run above to the number of milliseconds you want it to run.
  //  Panel();
  // SequenceB();

  // reset_for_next_pattern();
  // millis_to_run = 35*1000; // default is 30 seconds
  // playGIF();


  reset_for_next_pattern();
  CoolGradient();

  reset_for_next_pattern();
  WolfPinwheel_2();

  // reset_for_next_pattern();
  // WolfPinwheel_2();
  /*
    millis_elapsed = 0;
    millis_to_run=10000;
    cont = true;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
      } else {
        cont = false;
      }
    }


    millis_elapsed = 0;
    millis_to_run=30000;
    cont = true;
    while (cont == true) {
    if (millis_elapsed < millis_to_run) {
     Corner();//CascadeUp
    } else {
      cont = false;
    }}

    millis_elapsed = 0;
    cont = true;
    millis_to_run=30000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
        Rain();
      } else {
        cont = false;
      }
    }

    millis_elapsed = 0;
    cont = true;
    millis_to_run=20000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
        Rainbow();
      } else {
        cont = false;
      }
    }

    millis_elapsed = 0;
    cont = true;
    millis_to_run=20000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
        SequenceB();
      } else {
        cont = false;
      }
    }

    millis_elapsed = 0;
    cont = true;
    millis_to_run=20000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
    CosmicRainbow();
     } else {
        cont = false;
      }
    }

    millis_elapsed = 0;
    cont = true;
    millis_to_run=20000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
        RedShift();
      } else {
        cont = false;
      }
    }

    millis_elapsed = 0;
    cont = true;
    millis_to_run=20000;
    while (cont == true) {
      if (millis_elapsed < millis_to_run) {
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

CRGB hsv2rgb(CHSV hsv){
  CRGB rgb;
  hsv2rgb_rainbow(hsv, rgb);
  return rgb;
}

bool Show() {
  // time's up
  if (millis_elapsed > millis_to_run){
    cont = false;
    return cont; 
  }

  // test if button press, short or long
  if (digitalRead(buttonPin) == LOW) {
    buttonPressedTime = millis();
    delay(20); // debounce
    while (digitalRead(buttonPin) == LOW)
        delay(10); 
    if(millis() - buttonPressedTime >= LONG_PRESS) {
        millis_to_run = HOUR;
      } else {
      millis_to_run = RUNTIME;
      cont = false;
      return cont;
    }
  }


  /* This block deals with the reading and adding of IR board infromation*/
  // test
  if(Serial.read() == 'a'){
    IR_leds[Sail[1][1]] = CHSV(100, 255, 255);
    Serial.println("setting leds[Sail[1][1]] = CHSV(100, 255, 255);");
  }

  // Read from IR Panel
  receive();
  for (int i = 0; i < NUM_STRIPS*NUM_LEDS_PER_STRIP; ++i)
  { 
    IR_leds[i].v = max(IR_leds[i].v - (int) frame_millis_elapsed, 0);

    // store original LED colors
    memcpy( leds_backup, leds, NUM_STRIPS * NUM_LEDS_PER_STRIP * sizeof(CRGB)  );
    // add layer to LEDs
    leds[i] += hsv2rgb(IR_leds[i]);
    // print out debug information
    // if (IR_leds[i].v > 0)
    // {
    //   Serial.print("IR_leds[i].v = ");
    //   Serial.println(leds[i].g);
    //   Serial.print("frame_millis_elapsed = ");
    //   Serial.println(frame_millis_elapsed);
    // }
  }
  LEDS.show();
  //restore original colors
  memcpy( leds, leds_backup, NUM_STRIPS * NUM_LEDS_PER_STRIP * sizeof(CRGB) );
  /* End IR block*/

  frame_millis_elapsed = 0;
  cont = true;
  return cont;
}


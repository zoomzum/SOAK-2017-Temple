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
y69|    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
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

#include <OctoWS2811.h>

const int ledsPerStrip = 300;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB| WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int  Sail[21][72];
int  SailBottom[10][7] = {2,1,0,149,148,147};
int  SailTop[10][7] ={72,73,74,75,76,77};

void setup() {
makeArray();
}

void loop() {
leds.begin();


for (int n=0;n<200;n++){
SequenceA();
}

for (int n=0;n<200;n++){
SequenceB();
}
}


void makeArray(){
int y,s;
s=0;
// int Sail[20][72];
for (int x=1; x<20; x+=2){ 
 int l = 3 + (150 * s);
    int  l2 = l+143;
  for (y=1; y<70; y++){  
 Sail[x][y] = l++;
 Sail[x+1][y] = l2--;
  }
   s++;
 
}  
//Serial.begin(9600);
//Serial.print(SailBottom[0][1]);
SailBottom[1][1] = 2;
SailBottom[1][2] = 1;
SailBottom[1][3] = 0;
SailBottom[1][4] = 149;
SailBottom[1][5] = 148;
SailBottom[1][6] = 147;

SailTop[1][1]= 72;
SailTop[1][2]= 73;
SailTop[1][3]= 74;
SailTop[1][4]= 75;
SailTop[1][5]= 76;
SailTop[1][6]= 77;

for (int numsail = 2;numsail<=10; numsail++){
 for (int pos=1; pos<7; pos++){SailBottom[numsail][pos]= SailBottom[numsail-1][pos]+150;
SailTop[numsail][pos]= SailTop[numsail-1][pos]+150;
}
}
}


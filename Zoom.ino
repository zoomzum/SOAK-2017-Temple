//Sparkles
void Sparkles() {
  while(cont){
  //
  int l, lnum, n,  x, y, z , i=0;

  //  leds.begin();
  lnum = random(50);
  for (l = 0; l < lnum; l++) {
    n = random(1500);
    x = random(255);
    y = random(255);
    z = random(255);
   //    leds.setPixel(n, x, y, z);
    leds[n] = CRGB( x, y, z);
 }
 
 
    if(!Show()) return; 
// Show();
  delay(100);
  fill_solid( &(leds[i]), 1500, CRGB(0,0, 0) );
 // LEDS.clear()1
}} 

//Slow Fade
void SequenceB() { while (cont){
  LEDS.setBrightness(100);
  int lnum = 75;
  int green = 0;
//int i;
  for (int red = 255; red >= -255; red -= 50) {
    for (int blue = -255; blue <= 255; blue += 50) {
      for (int ld = 1; ld <= lnum; ld++) {
        for (int x = 1; x <= 20; x++) {
          leds[Sail[x][ld]] = CRGB( abs(red),abs(green), abs(blue));
         } cont =Show();
           if(!cont) {return;} 
     delay(1);
    //    fill_solid( &(leds[i]), 1500, CRGB(0,0, 00) );
      }
   }
 
  }
}}

void Rain() {while (cont){
  int i = 0, brt = 30;
  fill_solid( &(leds[i]), 1500, CRGB(0, 0, 10) );
    if(!Show()) return; 
  int s;
  int  st ;
  for ( s = 1; s <= 20; s++) {
    st =  ((s + 1) / 2 + .5) ;
    for (brt = 30; brt <= 50; brt ++) {
      fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, brt));//}
   
      if(!Show()) return; 
 
      delay (1);
    }

    fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, 30));
 
     if(!Show()) return; 

    for (int y1 = 72; y1 > 1; y1--) {
      leds[Sail[s][y1]] = CRGB(0, 0, 255);
      leds[Sail[s][y1 + 1]] = CRGB(0, 0, 215);
      leds[Sail[s][y1 + 2]] = CRGB(0, 0, 175);
      leds[Sail[s][y1 + 3]] = CRGB(0, 0, 135);
      leds[Sail[s][y1 + 4]] = CRGB(0, 0, 95);
      leds[Sail[s][y1 + 5]] = CRGB(0, 0, 55);
      leds[Sail[s][y1 + 6]] = CRGB(0, 0, 30);

      LEDS.delay (1);
    //cont =  Show();
    if(!Show()) return; 
    //if(!cont) {return;} 
    }
  }
}}
//Raindrops
void Rain2() {

int  y1[21];
 if(!Show()) return; 
int s=0;//, st[10] ;
 for ( s = 1; s <= 20; s++) {
 y1[s]=(69);
// leds[Sail[s][y1[s]]] = 0x0000FF;//CRGB(0, 0, 255);

 }
while(1){  
s=random(21);
 
  //  st[s] =  ((s + 1) / 2 + .5) ;
   //  for (brt = 30; brt <= 50; brt ++) {
  //    fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, brt));//}
   //   if(!Show()) return; 
   //   delay (1);
  // }
  //fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, 30));
 //   if(!Show()) return; 
  //for (int y1 = 72; y1 > 1; y1--) {
         
      leds[Sail[s][y1[s]]] = CRGB(0, 0, 215);
    leds[Sail[s][y1[s] + 1]] = CRGB(0, 0, 175);
     leds[Sail[s][y1[s] + 2]] = CRGB(0, 0, 175);
     leds[Sail[s][y1[s] + 3]] = CRGB(0, 0, 135);
      leds[Sail[s][y1[s] + 4]] = CRGB(0, 0, 95);
      leds[Sail[s][y1[s] + 5]] =  CRGB(0, 0, 55);
      leds[Sail[s][y1[s] + 6]] = CRGB(0, 0, 30);
     
y1[s]-=1;
if (y1[s]==2) y1[s]=69;
delay(1);
 if(!Show()) return; 
   
    } 
}


void Rainbow() {while (cont){
  LEDS.setBrightness(50);
  static uint8_t hue = 0;
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
      leds[(i*NUM_LEDS_PER_STRIP) + j] = CHSV((32*i) + hue+j,192,255);
    }
  }

  // Set the first n leds on each strip to show which strip it is
  for(int i = 0; i < NUM_STRIPS; i++) {
    for(int j = 0; j <= i; j++) {
      leds[(i*NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
    }
  }

  hue++;

  if(!Show()) return; 
  LEDS.delay(10);
}}

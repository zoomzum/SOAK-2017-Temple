//Sparkles
void Sparkles() {
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
    leds[n] = CHSV( x, y, z);
 }
  Show();
  delay(100);
  fill_solid( &(leds[i]), 1500, CRGB(0,0, 0) );
 // LEDS.clear()1
} 

//Slow Fade
void SequenceB() { 
  LEDS.setBrightness(100);
  int lnum = 75;
  int green = 0;
//int i;
  for (int red = 255; red >= -255; red -= 50) {
    for (int blue = -255; blue <= 255; blue += 50) {
      for (int ld = 1; ld <= lnum; ld++) {
        for (int x = 1; x <= 20; x++) {
          leds[Sail[x][ld]] = CRGB( abs(red),abs(green), abs(blue));
          }
         
        Show();
      
    delay(1);
    //    fill_solid( &(leds[i]), 1500, CRGB(0,0, 00) );
      }
    }

  }
}

//Raindrops
void Rain() {
  int i = 0, brt = 30;
  fill_solid( &(leds[i]), 1500, CRGB(0, 0, 10) );
  Show();
  int s;
  int  st ;
  for ( s = 1; s <= 20; s++) {
    st =  ((s + 1) / 2 + .5) ;
    for (brt = 30; brt <= 50; brt ++) {
      fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, brt));//}
      LEDS.show();

      delay (1);
    }

    fill_solid( &leds[SailTop[st][1]], 6, CRGB(0, 0, 30));
    Show();

    for (int y1 = 72; y1 > 1; y1--) {
      leds[Sail[s][y1]] = CRGB(0, 0, 255);
      leds[Sail[s][y1 + 1]] = CRGB(0, 0, 215);
      leds[Sail[s][y1 + 2]] = CRGB(0, 0, 175);
      leds[Sail[s][y1 + 3]] = CRGB(0, 0, 135);
      leds[Sail[s][y1 + 4]] = CRGB(0, 0, 95);
      leds[Sail[s][y1 + 5]] = CRGB(0, 0, 55);
      leds[Sail[s][y1 + 6]] = CRGB(0, 0, 30);

      LEDS.delay (1);
      Show();
    }
  }
}

void Rainbow() {
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

 Show();
  LEDS.delay(10);
}

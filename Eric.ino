
void CosmicRainbow() {
  while (cont){
    LEDS.setBrightness(100);
    int lnum = 75;
  //  int red = 0;
    for (int red = 255; red >= -255; red -=32) {
      for (int blue = 255; blue >= -255; blue -=16) {
        for (int green = 255; green >= 255; green -= 8) {
    
          // Populate sales
          for (int sail = 1; sail < 20; sail+=2) {
            for (int ld = 1; ld <= lnum; ld++) {
              for (int x = 0; x <= 1; x++) {
                leds[Sail[x+sail][ld]] = CRGB( abs(sail*ld*4 + red),abs(sail*ld*2 + blue), abs(sail*ld + green));
              }
            }

           if(!Show()) return; 
            delay(5);
          }
        }
      }
    }
  }
}

void RedShift() {
  while (cont){
    LEDS.setBrightness(100);
    int lnum = 75;
 //   int red = 0;
    for (int red = 255; red >= -255; red -=32) {
      for (int blue = 255; blue >= -255; blue -=16) {
        for (int green = 255; green >= 255; green -= 8) {
    
          // Populate sales
          for (int sail = 1; sail < 20; sail+=2) {
            for (int ld = 1; ld <= lnum; ld++) {
              for (int x = 0; x <= 1; x++) {
                leds[Sail[x+sail][ld]] =CRGB( abs(red*x),abs(blue + sail*5), abs(green + ld*x));
              }
            }

           if(!Show()) return; 
            delay(5);
          }
        }
      }
    }
  }
}

void Edges() {
  while (cont){
    LEDS.setBrightness(100);
    int lnum = 75;
//    int red = 0;
    for (int red = 255; red >= -255; red -=32) {
      for (int blue = 255; blue >= -255; blue -=16) {
        for (int green = 255; green >= 255; green -= 8) {
    
          // Populate sales
          for (int sail = 1; sail < 20; sail+=2) {
            for (int ld = 1; ld <= lnum; ld++) {
              for (int x = 0; x <= 1; x++) {
                leds[Sail[x+sail][ld]] =CRGB( abs(red * lnum),abs(blue + (lnum *x)), abs((lnum + green) * x));
              }
            }

           if(!Show()) return; 
            delay(5);
          }
        }
      }
    }
  }
}


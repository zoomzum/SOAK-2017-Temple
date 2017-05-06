//Please use the comand Show() instead of LEDS.show().  This will allow for code interruption after a set period in the case of an endless loop.
//Also, please try to avoid endless loops.  The calling function is set to repeat your sequence for 30 seconds, and it's the only sequence running, it will continue to repeat.

void CoolGradient() {while (cont){
  LEDS.setBrightness(100);
  int lnum = 75;
  int red = 0;
  for (int blue = 255; blue >= -255; blue -= 25) {
    for (int green = -255; green <= 255; green += 50) {
      for (int sail = 1; sail < 20; sail+=2) {
        for (int ld = 1; ld <= lnum; ld++) {
          for (int x = 0; x <= 1; x++) {
            leds[Sail[x+sail][ld]] = CRGB( abs(red),abs(green), abs(blue));
          }
        }
       if(!Show()) return; 
        delay(5);
      }
    }
  } 
} }
void Corner() {while (cont){
  LEDS.setBrightness(50);
  int red = 1;
  int blue = 0;
  int green = 1;
  for (int b = 2; b < 76; b++) {
    for (int x = 1; x <= 21; x++) {
       if (red >= 255) {
         red = random(255);
       } else {
         red ++;
       }
       if (green >= 255) {
         green = random(255);
       } else {
         green ++;
       }
       for (int w = 0; w < 20; w++) {
         leds[Sail[x][(-(4*x)+b)-w]] = CRGB(red, blue, green);
       }
    }
     if(!Show()) return; 
    delay(1);
    fill_solid( &(leds[0]), 1500, CRGB(0, 0, 0) );
  }
} }


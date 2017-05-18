//Please use the comand Show() instead of LEDS.show().  This will allow for code interruption after a set period in the case of an endless loop.
//Also, please try to avoid endless loops.  The calling function is set to repeat your sequence for 30 seconds, and it's the only sequence running, it will continue to repeat.

void testOne() {
   int i = 0;
   int pick = random(255);
     while (cont){
        LEDS.setBrightness(50);
        int r = random(255);
        int g = random(255);
        int b = random(255);
        int start_x = random(1, 21);
        int start_y = random(3, 72);
        if (start_x % 2 == 0){
          leds[Sail[start_x][start_y]] = CRGB(r,g,b);
          leds[Sail[start_x][start_y - 3]] = CRGB(r,g,b);
          leds[Sail[start_x - 1][start_y]] = CRGB(r,g,b);
          leds[Sail[start_x - 1][start_y - 3]] = CRGB(r,g,b);
          if (!Show()) return;
          //Show();
          delay(100);
          fadeToBlackBy(leds,1499, 10);  
          //fill_solid( &(leds[i]), 1500, CRGB(0,0, 0) );
          //pick = random(255);
          }
          else{
            start_x = random(255);
          }
         }
   }

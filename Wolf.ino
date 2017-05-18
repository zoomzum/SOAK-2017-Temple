// Wolf's Code Space
//(c)2017 R.A.Griffin.

#define  COMET_COUNT 4
#define SAIL_COUNT  10
uint8_t   cometDirection[SAIL_COUNT][COMET_COUNT];
float   cometLoc[SAIL_COUNT][COMET_COUNT];
uint32_t  cometColor[SAIL_COUNT][COMET_COUNT];
float   cometSpeed[SAIL_COUNT][COMET_COUNT];
int rainbowColors[180];
uint32_t  Phase;
boolean    ClearingFlag;

// ==========================================   Wolf ColorWheel  ==========================================
// (C)2017 R.A. Griffin


void WolfColorWheel()
{
  float centerX = 20/2, centerY = 72/2;
  float wanderX = 0.15, wanderY = 0.5;
  float offset = 1.0;

  do {
    setupRainbow();
    for(uint8_t x=0; x<20; x++) {
      for(uint8_t y=0; y<72; y++) {
        float Angle = atan2(y-centerY, x-centerX) * 180.0 / 3.14159 + 360;
        int16_t aa = Angle + offset;
        uint32_t color = rainbowColors[aa % 180];
        setGridPixel(x, y, color>>16, (color>>8) &0xff, color & 0xff);
        }
      }
    offset += 5;

    centerX += wanderX;
    if(centerX < 0) {
      centerX = 0;
      wanderX = random(6) / 10.0 + 0.2;
      }
    if(centerX > 19) {
      centerX = 19;
      wanderX = random(6) / -10.0 - 0.2;
      }
      
    centerY += wanderY;
    if(centerY < 0) {
      centerY = 0;
      wanderY = random(10) / 10.0 + 0.5;
      }
    if(centerY > 71) {
      centerY = 71;
      wanderY = random(10) / -10.0 - 0.5;
      }
    delay(10);
    } while(Show());
  }




// ==========================================   Wolf AtariPong  ==========================================
// (C)2017 R.A. Griffin

void WolfAtariPong(boolean colorBall)
{
  float ballX = 8, ballY=40;
  float deltaY = 2.0;
  uint8_t dirX=1;

  //Set up the playing field
  for(uint x=0; x<20; x++) {
    setGridPixel(x, 71, 255, 255, 0);
    setGridPixel(x, 0, 255, 255, 0);
    }
  Phase = 0;

  setupRainbow();

  do {
    for(uint y=1; y<71; y+=4)
      setGridPixel(10, y, 32, 32, 32);

    setGridPixel(ballX, ballY, 0,0,0);
    setGridPixel(ballX-1, ballY, 0,0,0);
    setGridPixel(ballX+1, ballY, 0,0,0);

    for(int16_t i=1; i<78; i++) {
      if(i < ballY-4 || i > ballY+4) {
        setGridPixel(0, i, 0,0,0);
        setGridPixel(19, i, 0,0,0);
        }
      else {
        setGridPixel(0, i, 64,255,64);
        setGridPixel(19, i, 255,64,64);
        }
      }

    if(dirX) {
      if(++ballX > 18) dirX=0;
      }
    else {
      if(--ballX < 2) dirX=1;
      }

    ballY += deltaY;
    if(ballY < 3) {
      ballY = 2;
      deltaY = 2.0;
      }
    if(ballY > 69) {
      ballY = 69;
      deltaY = -2.0;
      }

    if(colorBall) {
      Phase += 3;
      uint32_t rgb = rainbowColors[Phase%180];
      setGridPixel(ballX, ballY, rgb>>16, rgb>>8, rgb);
      setGridPixel(ballX-1, ballY, rgb>>16, rgb>>8, rgb);
      setGridPixel(ballX+1, ballY, rgb>>16, rgb>>8, rgb);
      }
    else {
      setGridPixel(ballX, ballY, 255,255,255);
      setGridPixel(ballX-1, ballY, 255,255,255);
      setGridPixel(ballX+1, ballY, 255,255,255);
      }
    if(!Show()) return;
    delay(40);
    }while(1);
  }


// ==========================================   Wolf ColorTunnel  ==========================================
// (C)2017 R.A. Griffin


void WolfColorTunnel(void)
{
  float phase = 0;
  float centerX=20/2, centerY = 72/2;

  float wanderX = 0.025;
  float wanderY = 0.1;

  setupRainbow();

  do {
    //Set up every pixel on the grid based on distance from center
    for(uint16_t y=0; y<72; y++)
      for(uint16_t x=0; x<20; x++) {
        float xx = x-centerX;
        float yy = y-centerY;
        float dist = sqrt(xx*xx + yy*yy);
        uint32_t cidx = int(dist+phase);
        uint32_t rado = (cidx % 5 < 3) ? rainbowColors[cidx%180] : 0;
        setGridPixel(x, y, rado >> 16, (rado>>8) & 0xff, rado & 0xff);
//        setGridPixel(x, y, rado >> 16, 0xff, rado & 0xff);
        }
    delay(3);
    phase -= 0.1;

    //Wander the centerpoint (optional)
    centerX += wanderX;
    if(centerX > 19 || centerX < 0) wanderX = -wanderX;
    centerY += wanderY;
    if(centerY > 71 || centerY < 0) wanderY = -wanderY;

    } while(Show());
  }



void setGridPixel(uint16_t x, uint16_t y, uint8_t red, uint8_t green, uint8_t blue)
{
  if(x > 19 || y > 71) return;
  uint8_t z = x&0xfe;

  uint16_t idx = (x & 1) ? z*75 + 150-y : z*75 + y;
#ifdef OCTOLIB
  LEDS.setPixel(idx, red, green, blue);
#else
  leds[idx] = CRGB(red, green, blue);
#endif
  }







//
// setupRainbow - pre-compute the 180 rainbow colors   => rainbowColors[]
//

void setupRainbow(void)
{
  for (int i=0; i<180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 50;
    rainbowColors[i] = makeColor(hue, saturation, lightness);
    }
  }



// ==========================================   Wolf Comets  ==========================================
// (C)2017 R.A. Griffin


void WolfComets(boolean enableClearing) {
  Phase = 0;
  ClearingFlag = 0;
  for(uint8_t i=0; i<COMET_COUNT; i++)
    for(uint8_t j=0; j<SAIL_COUNT; j++)
      setupComet(j, i);

  do {
    for(uint8_t s=0; s<SAIL_COUNT; s++)
      for(uint8_t i=0; i<COMET_COUNT; i++)
        runComet(s,i, enableClearing);
    delay(10);
    if(enableClearing) {
      Phase ++;
      ClearingFlag = (Phase > 200 && Phase < 500);
      if(Phase == 1000) Phase = 0;
      }
    } while(Show());
  }


void setupComet(uint8_t sail, uint8_t idx)
{
  if(sail >= SAIL_COUNT) return;

  //Blackout clearing, use "phase" at certain times during a cycle
  if(ClearingFlag) return;

  //Comet random color
  uint8_t red, green, blue;
  do {
    red = random(256);
    green = random(256);
    blue = random(256);
    } while(red < 128 && green < 128 && blue < 128);

  cometColor[sail][idx] = red << 16 | green << 8 | blue;
  cometSpeed[sail][idx] = random(8) / 10.0 + 0.2;

  uint8_t temp = random(128);
  if((temp & 1) == 0) {
    cometLoc[sail][idx] = 72;
    cometDirection[sail][idx] = 0;
    }
  else {
    cometLoc[sail][idx] = 0;
    cometDirection[sail][idx] = 1;
    }
  }


void runComet(uint8_t sail, uint8_t idx, boolean CFlag)
{
  int16_t ploc = cometLoc[sail][idx];
  //Check if comet went off edge
  if(ploc < -10 || ploc > 72+10) {
    setupComet(sail, idx);
    return;
    }

  float red = cometColor[sail][idx] >> 16;
  float green = (cometColor[sail][idx] >> 8) & 0xff;
  float blue = cometColor[sail][idx] & 0xff;

  uint8_t rr, gg, bb;
  uint8_t len = CFlag ? 11 : 10;

  for(uint16_t i=0; i<len; i++) {
    if(ploc >= 0 && ploc < 72) {
//      if(ClearingFlag && i == 9) {
//        rr = gg = bb = 0;
//        }
//      else {
      float ratio = (10-i) / 10.0;
      rr = red * ratio;
      gg = green * ratio;
      bb = blue * ratio;

#ifdef OCTOLIB
      LEDS.setPixel(ploc+sail*150, rr<<16 | gg<<8 | bb);
      LEDS.setPixel(150-ploc+sail*150, rr<<16 | gg<<8 | bb);
//      LEDS.setPixel(78+ploc+sail*150, rr<<16 | gg<<8 | bb);
#else
      leds[ploc+sail*150] = CRGB(rr, gg, bb);
//same way
      leds[150-ploc+sail*150] = CRGB(rr, gg, bb);
//opposite way    leds[75+ploc+sail*150] = CRGB(rr, gg, bb);
#endif
      }
    if(cometDirection[sail][idx])
      ploc --;
    else
      ploc ++;
    }


  // Advance position of comet
  if(cometDirection[sail][idx])
    cometLoc[sail][idx] += cometSpeed[sail][idx];
  else
    cometLoc[sail][idx] -= cometSpeed[sail][idx];
  }


// ==========================================   Wolf Boxes  ==========================================
// (C)2017 R.A. Griffin


void WolfBoxes(void)
{
  uint8_t red, green, blue;
  do {
    uint16_t x = random(10);
    uint16_t y = random(10);


    if(random(10) > 3) {
      red = random(256);
      green = random(256);
      blue = random(256);
      }
    else
      red = green = blue = 0;

    for(uint16_t i=0; i<7; i++) {
#ifdef OCTOLIB
      LEDS.setPixel(x*150+y*7+i, red<<16 | green<<8 | blue);
      LEDS.setPixel(x*150+149-y*7+i, red<<16 | green<<8 | blue);
#else
      leds[x*150+y*7+i] = CRGB(red, green, blue);
      leds[x*150+149-y*7-i] = CRGB(red, green, blue);
#endif
      }
    delay(50);
    } while(Show());
  }

// ==========================================   Wolf FuzzScreen  ==========================================
// (C)2017 R.A. Griffin

void WolfFuzzScreen(void)
{
  int8_t percentage = 1;
  uint8_t direction = 1;
  boolean continuePattern;
  uint8_t rr=0, gg=255, bb=0, last_mask = 2;

  do {
    for(uint16_t i=0; i<150*10; i++) {
      if(percentage > random(100))
#ifdef OCTOLIB
        LEDS.setPixel(i, rr<<16 | gg<<8 | bb);
#else
        leds[i] = CRGB(rr,gg,bb);
#endif
    else
#ifdef OCTOLIB
        LEDS.setPixel(i, 0);
#else
        leds[i] = 0;
#endif
      }
    continuePattern = Show();
    delay(10);
    if(direction) {
      percentage += 2;
      if(percentage >= 100)
        direction = 0;
      }
    else {
      percentage -= 2;
      if(percentage <= 0) {
        direction = 1;
        uint8_t mask;
        do {
          mask = random(7) + 1;
          } while(mask == last_mask);
        last_mask = mask;
        rr = (mask & 1) ? 255 : 0;
        gg = (mask & 2) ? 255 : 0;
        bb = (mask & 4) ? 255 : 0;
        }
      percentage = 0;
      }
    } while(continuePattern);
  }




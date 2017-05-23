// ====================================================================================
//
//    Wolf's Coding for Temple to Valhalla (2017)
//
//  (C)2017 R.A. Griffin. All Rights Reserved. Use is granted to Zoom Newhouse
//  for the Temple to Valhalla project only. All other uses prohibited without
//  express written permission from R.A. Griffin. Please respect copyright!
//
//  Contact: realder@gmail.com   FB: http://facebook.com/alexander.griffin.777
// ====================================================================================
//
// Completed Patterns (alphabetical order):
//  WolfAlienSpaceship();
//  WolfAtariPong(boolean);   //true=color ball, false=white only
//  WolfBoxes();
//  WolfColorTunnel();
//  WolfColorWheel(boolean);  //true=black sector, false=all color
//  WolfComets(boolean);    //true=fade-to-black and reset; false=persistent color trails (very different looks!)
//  WolfEyeball();
//  WolfFractals();     //UNFINISHED: Use only if you are desperate for more patterns!
//  WolfFuzzScreen();
//  WolfMoire();
//  WolfPinwheel_1();
//  WolfPinwheel_2();
//  WolfSeaStorm();
//  WolfStarfield(boolean);   //true=color stars, false=white only
//  WolfSpiralStarfield(boolean color,boolean tails); //true=color stars, false=white only (pattern looks best using(true,true))



#define COMET_COUNT 4
#define SAIL_COUNT  10
#define  STARZ   50

uint8_t   cometDirection[SAIL_COUNT][COMET_COUNT];
float   cometLoc[SAIL_COUNT][COMET_COUNT];
uint32_t  cometColor[SAIL_COUNT][COMET_COUNT];
float   cometSpeed[SAIL_COUNT][COMET_COUNT];
uint32_t  Phase;
boolean   ClearingFlag;
int   rainbowColors[180];


// ==========================================   Wolf WarpTunnel  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

void WolfWarpTunnel(void)
{
  Phase=0;
  setupRainbow();
  do {
    clearGrid();
    for(uint16_t ring=0; ring<10; ring++) {
      uint32_t rgb = 0;
      if(Phase+ring>100 && Phase+ring<280) { rgb=rainbowColors[(Phase-ring*20)%180]; }
//      rgb=rainbowColors[(i+ring)%180];
      WolfCircle(10,36, (float)ring, ring*3.6, rgb>>16,rgb>>8,rgb);
      }
    if(++Phase>300) Phase=0;
    delay(40);
    } while(Show());
  }




// ==========================================   Wolf Starfield  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

void WolfStarfield(boolean inColor)
{
  float px[STARZ], py[STARZ], vx[STARZ], vy[STARZ];
  uint32_t cc[STARZ];
  setupRainbow();
  for(uint8_t i=0; i<STARZ; i++) px[i]=py[i]=-5;
  do {
    clearGrid();
    for(uint8_t i=0; i<STARZ; i++) {
      if(px[i]<0||px[i]>19||py[i]<0||py[i]>71) {
        px[i]=10;py[i]=36;
        vx[i]=velo(10);vy[i]=velo(36);
        cc[i]=inColor?rainbowColors[random(180)]:0xffffff;
        }
      setGridPixel(px[i],py[i],cc[i]>>16,cc[i]>>8,cc[i]);
      px[i]+=vx[i]; py[i]+=vy[i];
      }
    delay(10);
    }while(Show());
  }



// ==========================================   Wolf SpiralStarfield  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

  
void WolfSpiralStarfield(boolean inColor, boolean fadeEffect)
{
  float pr[STARZ], vel[STARZ];
  int32_t cc[STARZ], pa[STARZ];
  setupRainbow();
  for(uint8_t i=0; i<STARZ; i++) pr[i] = 100.0;
  do {
    if(fadeEffect) WolfFadeToBlack(16); else clearGrid();
    for(uint8_t i=0; i<STARZ; i++) {
      if(pr[i]>50) {
        pr[i]=0; pa[i]=random(360);
        cc[i]=inColor?rainbowColors[random(180)]:0xffffff;
        vel[i]=random(20)/40.0;
        }
      int16_t x=10+sin(pa[i]*2*3.14159/360)*pr[i]/3.6;
      if(x>=0) setGridPixel(x,
        36+cos(pa[i]*2*3.14159/360)*pr[i],
        cc[i]>>16,cc[i]>>8,cc[i]);
      pr[i] += vel[i];
      if(Phase%2000<1000) pa[i]+=2; else pa[i]-=2;
      }
    Phase++;
    delay(10);
    } while(Show());
  }






float velo(uint8_t max) {
  float temp = (random(45)+5)*max/7000.0;
  return random(2)==1 ? temp : -temp;
  }

// ==========================================   Wolf SeaStorm  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

void WolfSeaStorm(void)
{
  uint8_t ff=0, forg=0;
  uint16_t dd=5;
  clearGrid();
  do {
    for(uint8_t x=0; x<20; x++) {
      for(uint8_t y=0; y<40; y++) setGridPixel(x,y,0,0,y<(28+10*sin(x/2.0+Phase/10.0)*cos(Phase/15.0))?64:0);
      }
    Phase++;
    if(ff) {
      WolfDrawLine(forg,71,random(20),0,255,255,255);
      if(--ff==0) { dd=random(150)+50; clearGrid(); }
      }
    if(dd) { if(--dd == 0) { ff=random(8)+1; forg=random(20); } }
    delay(10);
    } while(Show());
  }





// ==========================================   Wolf Eyeball  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.


void WolfEyeball(void)
{
  uint16_t seq = 0, pattern = 0;
  setupRainbow();
  do {
    clearGrid();
    if(pattern==0) { seq = 0; pattern = random(5)+1; }
    for(uint16_t i=1; i<16; i++) WolfCircle(10,36, i/1.6,i, 40,40,0);
    if(pattern==1) {
      if(++seq > 100) pattern=0;
      }
    uint16_t icc = 10;
    if(pattern==2) {
      if(seq<25) {icc = (50-seq)/5;}
      else if(seq < 50) {icc=5;}
      else if(seq < 75) { icc = (seq-25)/5;}
      if(++seq > 100) pattern=0;
      }
    if(pattern==3) {
      if(seq<25) {icc = seq/5+10;}
      else if(seq < 50) {icc=15;}
      else if(seq < 75) { icc = (75-seq)/5+10;}
      if(++seq > 100) pattern=0;
      }
    WolfRadialDraw(icc,36,(uint32_t*)rainbowColors,180,++Phase,32.0);
    for(uint16_t i=1; i<7; i++) WolfCircle(icc,36,i/3.6,i, 0,0,0);
 //   setGridPixel(10,35,0,0,0);  //grrr

    if(pattern==4||pattern==5) {
      float gg = (seq < 25) ? (25-seq)/1.8 : (seq-24)/1.8;
      for(uint16_t i=15; i>gg; i--) WolfCircle(10,36,15.0/1.6,i,0,0,40);
      if(++seq > 75) pattern=0;
      }
    delay(3);
    }while(Show());
  }



void WolfCircle(int16_t centerX, int16_t centerY, float radiusX, float radiusY, uint8_t r, uint8_t g, uint8_t b)
{
  uint16_t points = (radiusX+radiusY) * 3.14159 *1.5;
  int16_t lx=-1,ly=-1;
  for(uint16_t i=0; i<points; i++) {
    float angle = i*2.0*3.14159/points;
    float x = centerX+cos(angle)*radiusX;
    float y = centerY+sin(angle)*radiusY;
    if(lx!=int(x)||ly!=int(y)) setGridPixel(x,y,r,g,b);
    lx=x;ly=y;
    }
  }



// ==========================================   Wolf Moire   ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

void WolfMoire(boolean randomly)
{
  float x1, y1, x2, y2, dx1, dy1, dx2, dy2;

  x1=random(20); dx1=newDelta(x1,20);
  y1=random(72); dy1=newDelta(y1,72);
  x2=random(20); dx2=newDelta(x2,20);
  y2=random(72); dy2=newDelta(y2,72);
  setupRainbow();

  do {
    WolfFadeToBlack(10);
    uint32_t rgb = randomly ? rainbowColors[random(180)] : rainbowColors[Phase % 180];
    Phase+=5;
    WolfDrawLine(x1, y1, x2, y2, rgb>>16,rgb>>8,rgb);
    x1 += dx1; y1 += dy1; x2 += dx2; y2 += dy2;
    if(x1 < 1 || x1 > 18) dx1 = newDelta(x1,20);
    if(x2 < 1 || x2 > 18) dx2 = newDelta(x2,20);
    if(y1 < 1 || y1 > 70) dy1 = newDelta(y1,72);
    if(y2 < 1 || y2 > 70) dy2 = newDelta(y2,72);
    delay(30);
    } while(Show());
  }



float newDelta(float loc, uint8_t vec)
{
  float temp = 0;
  while(fabs(temp) < 0.3) {
    temp = random(vec) / 20.0;
    }
  return loc<10? temp : -temp;
  }


void WolfFadeToBlack(uint8_t amount)
{
#ifdef OCTOLIB
  LEDS.fadeToBlack(amount);
#else
  for(uint16_t i=0; i<1500; i++)
    leds[i].fadeToBlackBy(amount);
#endif
  }




// ==========================================   Wolf Pinwheels   ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.


void WolfPinwheel_1(void)
{
  clearGrid();
  setupRainbow();
  uint16_t pp = 0;
  do {
    int16_t RSpeed = random(21)-10;
    if(RSpeed == 0) RSpeed = 5;

    for(int16_t y=10; y<62; y++) {
      WolfRadialDraw(4, y, (uint32_t*) rainbowColors, 180, pp+=RSpeed, 50.0);
      delay(10);
      if(!Show()) return;
      }
    for(float x=4; x<15; x+=0.125) {
      WolfRadialDraw((uint16_t) x, 62, (uint32_t*) rainbowColors, 180, pp+=RSpeed, 50.0);
      delay(10);
      if(!Show()) return;
      }
    for(int16_t y=62; y>10; y--) {
      WolfRadialDraw(15, y, (uint32_t*) rainbowColors, 180, pp+=RSpeed, 50.0);
      delay(10);
      if(!Show()) return;
      }
    for(float x=15; x>4; x-=0.125) {
      WolfRadialDraw((uint16_t) x, 10, (uint32_t*) rainbowColors, 180, pp+=RSpeed, 50.0);
      delay(10);
      if(!Show()) return;
      }
    } while(Show());
  }

void WolfPinwheel_2(void)
{
  int16_t dd = 100;
  uint8_t direction = 0;
  clearGrid();
  setupRainbow();
  do {
    WolfFadeToBlack(8);
    WolfRadialDraw(10, 36, (uint32_t*) rainbowColors, 180, Phase, (float)dd);
    if(direction) { if(++dd>120) direction = 0; }
    else { if(--dd<1) direction = 1; }
    delay(10);
    if(++Phase>=180) Phase = 0;
    } while(Show());
  }

//note: diameter is between 0-100
void WolfRadialDraw(int16_t xcenter, int16_t ycenter, uint32_t *pattern, uint8_t patternSize, uint16_t offset, float diameter)
{
  for(uint16_t i=0; i<360; i++) {
    float angle = i*2*3.14159/360;
    int16_t x2 = xcenter + cos(angle)*diameter/10.0;  //was 5
    int16_t y2 = ycenter + sin(angle)*diameter/2.78;  //was 18
    uint32_t rgb = pattern[offset%patternSize];
    ++offset;
    WolfDrawLine(xcenter, ycenter, x2, y2, rgb>>16, rgb>>8, rgb);
    }
  }



// ==========================================   Wolf Fractals   ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.
// UNFINISHED - DON'T USE unless you are in desperate need of patterns!!!!


void WolfFractals(void) {
  clearGrid();
  setupRainbow();
  uint8_t rondo=0;
  
  for(uint16_t y=0; y<72; y++) {
    rondo+=5;
    if(rondo>=180) rondo=0;
    uint32_t rgb = rainbowColors[rondo];
    WolfDrawLine(0,0,19,y,rgb>>16, rgb>>8, rgb);
//    WolfDrawLine(19,71,0,71-y,rgb>>16, rgb>>8, rgb);
    if(!Show()) return;
    delay(30);
    }
  delay(1000);

  for(uint16_t y=71; y>0; y--) {
    rondo+=5;
    if(rondo>=180) rondo=0;
    uint32_t rgb = rainbowColors[rondo];
    WolfDrawLine(0,71,19,y,rgb>>16, rgb>>8, rgb);
    if(!Show()) return;
    delay(20);
    }
  delay(1000);

  for(uint16_t y=0; y<72; y++) {
    rondo+=5;
    if(rondo>=180) rondo=0;
    uint32_t rgb = rainbowColors[rondo];
    WolfDrawLine(19,71,0,y,rgb>>16, rgb>>8, rgb);
    if(!Show()) return;
    delay(20);
    }
  delay(1000);

  for(uint16_t y=0; y<72; y++) {
    rondo+=5;
    if(rondo>=180) rondo=0;
    uint32_t rgb = rainbowColors[rondo];
    WolfDrawLine(19,0,0,y,rgb>>16, rgb>>8, rgb);
    if(!Show()) return;
    delay(20);
    }
  delay(1000);
  }


void WolfDrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int8_t r, int8_t g, int8_t b)
{
  if(x1 == x2) {
    if(y1>y2) { int16_t temp=y2; y2=y1; y1=temp; }
    for(;y1<=y2; y1++) setGridPixel(x1, y1, r, g, b);
    return;
    }
  if(y1 == y2) {
    if(x1>x2) { int16_t temp=x2; x2=x1; x1=temp; }
    for(;x1<=x2; x1++) setGridPixel(x1, y1, r, g, b);
    return;
    }
  if(x1 > x2) {
    int8_t temp = x2; x2=x1; x1=temp;
    temp=y2; y2=y1; y1=temp;
    }

  float xx = x1, yy=y1;
  float xStep = x2-x1;
  float yStep = y2-y1;
  if(fabs(xStep) > fabs(yStep)) {
    yStep /= xStep;
    xStep = 1.0;
    }
  else {
    xStep /= fabs(yStep);
    yStep /= fabs(yStep);
    }
  while(xx<x2) {
    setGridPixel((uint16_t) xx, (uint16_t) yy, r, g, b);
    xx += xStep; yy += yStep;
    }
  setGridPixel(x2, y2, r, g, b);
  }


// ==========================================   Wolf AlienSpaceship  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.

void WolfAlienSpaceship(void) {
  uint8_t shellHeight[20] = { 2,3,4,5,6, 6,6,7,7,7,
    7,7,7,6,6, 6,5,4,3,2 };
  uint8_t rr, gg, bb;

  float ypos = 30;

  do {
    ypos = sin(Phase / 250.0) * 20.0 + 45.0;
    clearGrid();

    //Draw disc
    uint8_t yy = ypos;
    for(uint8_t x=0; x<20; x++) {
      for(uint8_t y=0; y<8; y++) {
        if(y < shellHeight[x]) {
          setGridPixel(x, yy-y, 255,0,0);
          setGridPixel(x, yy+y+1, 255,0,0);
          }
        }
      }
    //Draw eye
    uint8_t eye = (++Phase / 15) % 16;
    setGridPixel(eye+1, yy, 0,0,0);
    setGridPixel(eye+1, yy+1, 0,0,0);
    setGridPixel(eye+2, yy, 255,255,255);
    setGridPixel(eye+2, yy+1, 255,255,255);
    setGridPixel(eye+3, yy, 0,0,0);
    setGridPixel(eye+3, yy+1, 0,0,0);


    //Thrusters
    for(uint8_t x=5; x<15; x++) {
      int16_t YLIM = ypos-shellHeight[x];
      if(YLIM < 0) YLIM=0;
      for(uint8_t y=YLIM; y>ypos-20; y--) {
        uint8_t p = random(20);
        if(p > 9) {
          rr = gg = bb = 0;
          }
        else if(p > 5) {
          rr = 128;
          gg = 128;
          bb = 0;
          }
        else if(p > 1) {
          rr = 0x0e;
          gg = 0x48;
          bb = 0;
          }
        else {
          rr = gg = bb = 255;
          }

        setGridPixel(x,y, rr, gg, bb);
        }
      }


    delay(10);
    } while(Show());
  }


void clearGrid(void) 
{
#ifdef OCTOLIB
  clearAllLEDs();
#else
//  LEDS.clear(); // only clears channel 0!!
  fill_solid(&leds[0], 1500, CRGB(0,0, 0) );
#endif
  }

// ==========================================   Wolf ColorWheel  ==========================================
// (C)2017 R.A. Griffin. All Rights Reserved.


void WolfColorWheel(boolean fanBlade)
{
  float centerX = 20/2, centerY = 72/2;
  float wanderX = 0.15, wanderY = 0.5;
  float offset = 1.0;

  float fanOffset = 15;
  Phase = 0;
  setupRainbow();

  do {
    for(uint8_t x=0; x<20; x++) {
      for(uint8_t y=0; y<72; y++) {
        float Angle = atan2(y-centerY, x-centerX) * 180.0 / 3.14159 + 180;
        int16_t aa = int(Angle + offset) % 180;
        uint32_t color = fabs(Angle - fanOffset) < 35 && fanBlade ? 0 : rainbowColors[aa];
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

    fanOffset += 4;
    if(fanOffset > 360) fanOffset = 0;
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

  uint16_t idx = (x & 1) ? z*75 + 149-y : z*75 + y;
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
      if(percentage > (int8_t) random(100))
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


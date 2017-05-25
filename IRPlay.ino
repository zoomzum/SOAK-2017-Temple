void IRPlay(int irX, int irY, int irDist, int irSize, int irMass){
//if(irMass>20){
int X = min(((irX+1)/4.3)+1,20);
int Y = min(75,((95-irY)*.8));
int Dist = irDist;
int Mass = irMass;
// CRGB
// int red=min(Dist*Mass*1.1,255);
// int green= min(Dist*1,255);
// int blue= min(Dist*1.6,255);
// CHSV
int hue=min(Dist*Mass*1.1,255);
int sat= min(Dist*1,255);
int val= min(Dist*1.6,255);

IR_leds[Sail[X][Y]] = CHSV(hue, sat, val);
// LEDS.show();
// addSquare(X,Y,irMass);
//}  
// fadeToBlackBy(leds,1499, 40);
}

void addSquare(int x, int y, int mass){

  for (int xx = x-2; xx < x+2; ++xx)
  {
    if ((xx < 1) || (xx > 20)) continue;
    for (int yy = y-mass/3; yy < y+mass/3; ++yy)
    {
      if ((yy < 1) || (yy > 72)) continue;
      IR_leds[Sail[xx][yy]] = CHSV(100,255,mass);
    }
  }

}
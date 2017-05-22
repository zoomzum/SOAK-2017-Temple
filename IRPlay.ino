void IRPlay(int irX, int irY, int irDist, int irSize, int irMass){
//if(irMass>20){
int X = min(((irX+1)/4.3)+1,20);
int Y = min(75,((95-irY)*.8));
int Dist = irDist;
int Mass = irMass;
int red=min(Dist*Mass*1.1,255);
int green= min(Dist*1,255);
int blue= min(Dist*1.6,255);
 
  leds[Sail[X][Y]] = CRGB( red  , green, blue);
  LEDS.show();
//}  
//fadeToBlackBy(leds,1499, 40);
}




void SequenceA() {
  //
 int l, lnum, n,  x, y, z ;

leds.begin();
lnum=random(20);
for (l=0;l<lnum;l++){
n = random(150);
x = random(255);
y = random(255);
z = random(255);
leds.setPixel(n,x,y,z);

//leds.setPixel(ledsPerStrip+50,x,y,z);
}
leds.show();
delay(100);
}



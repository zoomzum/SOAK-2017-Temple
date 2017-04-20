void SequenceB() {
 Serial.begin(9600);
  Serial.print(1);
int lnum=70;

 int green = 0;
for (int red = 150; red>=-150; red-=30){ 

  for (int blue = -150; blue<=150; blue+=30){
    for (int ld=1;ld<=lnum;ld++){
  leds.setPixel(Sail[1][ld],abs(red),abs(green),abs(blue));
  leds.setPixel(Sail[2][ld],abs(red),abs(green),abs(blue));
 
 for (int b=1;b<=6;b++){
 leds.setPixel(SailBottom[1][b],abs(red),abs(green),abs(blue));
  leds.setPixel(SailTop[1][b],abs(red),abs(green),abs(blue));
 }
 
 leds.show();
  }
}
} 
delay(1);
}





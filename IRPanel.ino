void Panel()
{
//  Serial1.begin(19200);
  loopPanel();

}


void loopPanel() {
  //while (cont) {

 Serial.println("DEBUG 1");

  receive();
  delay(10);
  fadeToBlackBy(leds, 1499, 10);
  LEDS.show();
}
//}

void receive()
{
  Serial.println("DEBUG 2");

  static int count = 0;
  static uint8_t buf[48];

  while (Serial1.available()) {
    uint8_t n = Serial1.read();
    Serial.println("DEBUG 3");

    if (n > 250) {
      Serial.println("DEBUG 4");

      count = 0;

    } else {
      buf[count++] = n;
      if (count >= 48) {

        parse(buf);
        count = 0;


      }
    }
  }
}

void pbuf(const uint8_t *p)
{
  for (int i = 0; i < 48; i++) {
    Serial.printf(" %3d", p[i]);
  }
}

int ncmp(const void *a, const void *b)
{
  return (int)(*(const uint8_t *)a) - (int)(*(const uint8_t *)b);
}

bool find_object(uint8_t *buf, uint8_t *object, int x, int y)
{
  int i = x + y * 6;

  if (x >= 6) return false;
  if (y >= 8) return false;
  if (buf[i] == 0) return false;
  object[i] = buf[i]; // make a copy of only this object
  buf[i] = 0;  // delete the object as we find it
  find_object(buf, object, x + 1, y); // find all horz connected
  find_object(buf, object, x, y + 1); // find all vert connected
  return true;
}

void position(const uint8_t *object, int *xpos, int *ypos, int *dist, int *size, int *mass)
{
  int i, x, y, sum = 0, xsum = 0, ysum = 0, max = 0, min, count;

  for (x = 0; x < 6; x++) {
    for (y = 0; y < 8; y++) {
      int n = object[x + y * 6];
      sum += n;
      xsum += x * n;
      ysum += y * n;
      if (n > max) max = n; // max is closest point
    }
  }
  *dist = max;
  //Serial.printf("xy = %.2f, %.2f\n", (float)xsum / (float)sum, (float)ysum / (float)sum);
  *xpos = (xsum * 4266 / sum) >> 8; // X Position: scale is 0 to 99
  *ypos = (ysum * 3200 / sum) >> 8; // Y Position: scale is 0 to 99
  min = max / 6; // don't consider fringe points in size & mass
  count = 0;
  sum = 0;
  for (i = 0; i < 48; i++) {
    if (object[i] > min) {
      count++; // size is number of substantial points
      sum += object[i];
    }
  }
  *mass = sum / count;
  *size = count;
  //Serial.printf("xy=%d,%d  dist=%d  size=%d  mass=%d\n", *xpos, *ypos, *dist, *size, *mass);
}

void parse(uint8_t *buf)
{
  uint8_t sorted[48], object[48];
  int median, threshold = 3;
  int i, x, y;
  static int runcount = 0;

  // first compute a detection threshold
  memcpy(sorted, buf, 48);
  qsort(sorted, 48, 1, ncmp);
  median = (buf[15] + buf[16]) / 2; // actually 33rd percentile
  if (median > threshold) threshold = median;
  // discard all readings less than threshold
  for (i = 0; i < 48; i++) {
    if (buf[i] < threshold) buf[i] = 0;
  }
  // discover all the "objects"
  memset(object, 0, 48);
  for (x = 0; x < 6; x++) {
    for (y = 0; y < 8; y++) {
      if (find_object(buf, object, x, y)) {
        // TODO: something...
        int xpos, ypos, dist, size, mass;
        position(object, &xpos, &ypos, &dist, &size, &mass);
        if (size > 1 || mass > 5) {
          // found a meaningful object
          Serial.print("HIT");
          //for Show() to catch activity
          panelActive = true;
          //
          Serial.printf("%d: ", runcount);
          Serial.printf("xy=%d,%d  dist=%d  size=%d  mass=%d\n", xpos, ypos, dist, size, mass);
          //
          //if (mass>10){
          IRPlay( xpos, ypos, dist, size, mass);
          // }
          //
          //Serial.print("obj: ");
          //pbuf(object);
          //Serial.println();
          memset(object, 0, 48);
        }
      }else{
        panelActive = false;
        }
      /////////
      //   

    }

  }
  runcount++;

  //pbuf(buf);


  //Serial.printf("data %d %d\n", buf[42], buf[43]);
}





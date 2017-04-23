# SOAK-2017-Temple
This is for crowdsourced contributions to the lighting display for the temple for SOAK 2017: Superstition.

Temple this year is a Viking ship with an 8'x12' sail consisting of 10 illuminated panels, each being 8' tall and 10" wide, separated by a 4" gap with a string of mirrors in each gap.  Each panel is lit with a strip of WS2811 LEDs (30/meter) 69 on each side and 6 along the top and bottom. LED 3 is at the bottom left of the first sail element, LED 146 is at the bottom right of the first sail element, 153 is at the bottom left of the second element, etc. 
Here is the led layout for the first element:
<pre>
  7 7 7 7 7 7
  2 3 4 5 6 7 
71           78
.            .
.            .
.            .
.            .
.            .
.            .
.            .
.            .
.            .
.            .
2            147
1            148
0            149
 
 </pre>
I have created a two dimensional array to help you if you want to use it. Sail(1,1) refers to LED 4, Sail(1,72refers to LED 71 (top left).  Sail(2,1) refers to LED 149 (bottom right of the first element).  This way you can refer to each LED by its x/y coordinate.  The top row of each strip can be addressed using Sai1Top[1][1] through SailTop[1][6] (left to right) for the first element Sai1Top[2][1] through SailTop[2][6] for the second element, etc.

See SequenceA and SequenceB for examples. Have fun!!

Or you can use led(x) if you want to provide your own instructions. See above diagram and add 150 for each sail element, from left to right.

Temple Sail Layout:
<pre>
      ....   ....   ....   ....   ....   ....   ....   ....   ....   ....  
 y72 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   . |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   5 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   4 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   3 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   2 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
   1 |    | |    | |    | |    | |    | |    | |    | |    | |    | |    |  
      ....   ....   ....   ....   ....   ....   ....   ....   ....   ....
   x 1    2 3    4 5    6 7    8 9   10 11  12 13  14 15  16 17  18 19   20'
</pre>

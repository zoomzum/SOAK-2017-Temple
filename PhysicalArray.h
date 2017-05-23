/*
  Animated GIFs Display Code for SOAK 2017 Temple Sails

   This file contains code to parse animated GIF files

   Written by: Robin Newhouse

   Copyright (c) 2017 Robin Newhouse

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef PHYSICALARRAY_H_INCLUDED
#define PHYSICALARRAY_H_INCLUDED

#define N_SAILS 10
#define SPACING 11

const int x_body_map[N_SAILS * SPACING] = {
//0   1   2    3   4   5   6  7    8   9   10 // gif x coordinate
  1, -1, -1,  -1, -1, -1, -1, 2,  -1, -1, -1, // sail 'x' coordinate
  3, -1, -1,  -1, -1, -1, -1, 4,  -1, -1, -1, //sail 2
  5, -1, -1,  -1, -1, -1, -1, 6,  -1, -1, -1, // sail 3
  7, -1, -1,  -1, -1, -1, -1, 8,  -1, -1, -1, 
  9, -1, -1,  -1, -1, -1, -1, 10, -1, -1, -1,  
  11, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1,  
  13, -1, -1, -1, -1, -1, -1, 14, -1, -1, -1,  
  15, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1,  
  17, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1,  
  19, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1   // sail 10
};

const int x_top_map[N_SAILS * SPACING] = {
//0   1   2   3   4   5   6   7   8   9   10 // gif x coordinate
  1,  2,  3,  4,  5,  6,  7,  8, -1, -1, -1, // sail 'x' coordinate
  9, 10, 11, 12, 13, 14, 15, 16, -1, -1, -1, //sail 2
 17, 18, 19, 20, 21, 22, 23, 24, -1, -1, -1, // sail 3
 25, 26, 27, 28, 29, 30, 31, 32, -1, -1, -1,
 33, 34, 35, 36, 37, 38, 39, 40, -1, -1, -1, 
 41, 42, 43, 44, 45, 46, 47, 48, -1, -1, -1, 
 49, 50, 51, 52, 53, 54, 55, 56, -1, -1, -1, 
 57, 58, 59, 60, 61, 62, 63, 64, -1, -1, -1, 
 65, 66, 67, 68, 69, 70, 71, 72, -1, -1, -1, 
 73, 74, 75, 76, 77, 78, 79, 80, -1, -1, -1  // sail 10
};

#endif

/*
   Copyright (C) 2016 Ignacio Vina (@igvina)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

// ArdBitmaplib: version 1.0.0

#ifndef _ARDBITMAPLIB_H_
#define _ARDBITMAPLIB_H_

//Uncomment ARDUBOY_2 if you want to use this library 
//#define ARDUBOY_2

//Comment SPEED_HACK if speed is not important (reduce ~100 bytes)
#define SPEED_HACK

//Uncomment RESIZE_HACK for fast drawResized with resize >= 1.0
//#define RESIZE_HACK

#ifdef ARDUBOY_2
#include <Arduboy2.h>
#else
#include <Arduboy.h>
#endif

#define ALIGN_H_LEFT    0b00000000
#define ALIGN_H_RIGHT   0b00000001
#define ALIGN_H_CENTER  0b00000010
#define ALIGN_V_TOP     0b00000000
#define ALIGN_V_BOTTOM  0b00000100
#define ALIGN_V_CENTER  0b00001000
#define ALIGN_CENTER    0b00001010
#define ALIGN_NONE      0b00000000

#define MIRROR_NONE       0b00000000
#define MIRROR_HORIZONTAL 0b00000001
#define MIRROR_VERTICAL   0b00000010
#define MIRROR_HOR_VER    0b00000011

static const uint8_t BIT_SHIFT[8] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
};

/*
static const uint8_t REVERSE_16[16] = { 0, 8,  4, 12, 
                          2, 10, 6, 14 , 
                          1, 9,  5, 13,
                          3, 11, 7, 15 };

static const uint8_t REVERSE_256[256] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
    };
*/
    
class ArdBitmaplib
{
  public:
#ifdef ARDUBOY_2
    ArdBitmaplib(Arduboy2 &arduboy);
#else
    ArdBitmaplib(Arduboy &arduboy);
#endif

    void drawCompressed(int16_t sx, int16_t sy, const uint8_t *compBitmap, uint8_t color, uint8_t align, uint8_t mirror);   
    void drawCompressedResized(int16_t sx, int16_t sy, const uint8_t *compBitmap, uint8_t color,uint8_t align, uint8_t mirror, float resize);

    void drawBitmap(int16_t sx, int16_t sy, const uint8_t *bitmap,uint8_t w, uint8_t h, uint8_t color, uint8_t align, uint8_t mirror);
    void drawBitmapResized(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t w,uint8_t h, uint8_t color,uint8_t align, uint8_t mirror, float resize);
  
  private:

#ifdef ARDUBOY_2
    Arduboy2 *arduboy;
#else
    Arduboy *arduboy;
#endif
 // Slower
 //unsigned char *sBuffer;
};

#endif

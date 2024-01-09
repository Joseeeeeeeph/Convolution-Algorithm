#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //specifies height in pixels
    WORD biPlanes;  //specifies the number of color planes, must be 1
    WORD biBitCount;  //specifies the number of bits per pixel
    DWORD biCompression;  //specifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by the bitmap
    DWORD biClrImportant;  //number of colors that are important
} BITMAPINFOHEADER;
#pragma pack(pop)

extern int image_width;
extern int image_height;
extern int num_of_colours;

uint8_t* read_image();
void test_write();
float*** create_matrix();
void write_image();

#endif //_IMAGE_H
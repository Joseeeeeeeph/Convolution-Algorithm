#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  // Specifies the file type.
    DWORD bfSize;  // Specifies the size in bytes of the bitmap file.
    WORD bfReserved1;  // Reserved; must be 0.
    WORD bfReserved2;  // Reserved; must be 0.
    DWORD bfOffBits;  // Specifies the offset in bytes from the bitmapfileheader to the bitmap bits.
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  // Specifies the number of bytes required by the struct.
    LONG biWidth;  // Specifies width in pixels.
    LONG biHeight;  // Specifies height in pixels.
    WORD biPlanes;  // Specifies the number of color planes, must be 1.
    WORD biBitCount;  // Specifies the number of bits per pixel.
    DWORD biCompression;  // Specifies the type of compression.
    DWORD biSizeImage;  // Size of image in bytes.
    LONG biXPelsPerMeter;  // Number of pixels per meter in x axis.
    LONG biYPelsPerMeter;  // Number of pixels per meter in y axis.
    DWORD biClrUsed;  // Number of colors used by the bitmap.
    DWORD biClrImportant;  // Number of colors that are important.
} BITMAPINFOHEADER;
#pragma pack(pop)

extern int image_width;
extern int image_height;
extern const int NUM_OF_COLOURS;

float*** read_image();
void write_image(float*** matrix);
float* greyscale(float* pixel);
void free_image_memory();

#endif //_IMAGE_H
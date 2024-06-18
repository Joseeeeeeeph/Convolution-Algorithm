#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H

typedef struct {
    int i;
    int j;
    int x;
    int y;
} extern_px;

float*** convolve(float*** matrix);
void free_convolution_memory(void);

extern int convolution_type;

#endif //_CONVOLUTION_H
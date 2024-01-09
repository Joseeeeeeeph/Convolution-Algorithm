#include <stdio.h>
#include <stdlib.h>
#include "include/convolution.h"
#include "include/image.h"

void main() {
    uint8_t* pixel_data = read_image();
    float*** image = create_matrix(pixel_data);
    float*** convolved_image = convolve(image);
    write_image(convolved_image);
    
    free_convolution_memory();
    free(pixel_data);
    free(image);
}
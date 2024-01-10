#include <stdio.h>
#include <stdlib.h>
#include "include/convolution.h"
#include "include/image.h"

int main() {
    uint8_t* pixel_data = read_image();
    float*** image = create_matrix(pixel_data);
    free(pixel_data);

    printf("Please select an option below:\n\n 1. Box blur\n\n 2. Gaussian blur\n\n>> ");
    scanf("%d", &convolution_type);

    float*** convolved_image = convolve(image);

    free_convolution_memory();
    free(image);

    write_image(convolved_image);
    return 0;
}

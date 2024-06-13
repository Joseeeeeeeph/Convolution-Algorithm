#include <stdio.h>
#include <stdlib.h>
#include "include/convolution.h"
#include "include/image.h"

int main() {
    float*** image = read_image();

    // Operation Selection:
    convolution_type = 0;
    printf("Please select an option below:\n\n 1. Box blur\n\n 2. Gaussian blur\n\n 3. Laplacian edge-detection\n\n>> ");
    while (convolution_type < 1 || convolution_type > 3) {
        scanf("%d", &convolution_type);
        if (convolution_type < 1 || convolution_type > 3) printf("\nPlease type a number shown above.\n\n>> ");
    }

    float*** convolved_image = convolve(image);

    free_convolution_memory();
    free(image);

    write_image(convolved_image);

    free_image_memory();

    return 0;
}

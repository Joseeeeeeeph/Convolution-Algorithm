#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/constants.h"
#include "include/convolution.h"
#include "include/image.h"

int convolution_type;
int kernel_length;
int kernel_size;
int kernel_radius;
extern_px* special_pixels;
float* multiplied_vector;
float* sum_vector;

void initialise_algorithm() {
    kernel_length = 9;                                              // must be odd for now.
    kernel_size = kernel_length * kernel_length;
    kernel_radius = floor(kernel_length / 2);
    special_pixels = malloc(kernel_size * sizeof(extern_px));
}

long double gaussian(long double x, long double y) {
    long double var = pow(0.5, 2);
    return (1 / (2 * pi * var)) * powl(e, -(((x * x) + (y * y))/2 * var));
}

float* scalar_multiplication(const float* vector, const float scalar, int length) {
    multiplied_vector = calloc(length, sizeof(float));
    for (int i = 0; i < length; i++) {
        multiplied_vector[i] = vector[i] * scalar;
    }
    return multiplied_vector;
}

float** create_kernel() {
    long double gauss_sum = 0;
    float** kernel = malloc(sizeof(float*) * kernel_length);

    for (int i = 0; i < kernel_length; i++) {
        kernel[i] = malloc(sizeof(float) * kernel_length);
        for (int j = 0; j < kernel_length; j++) {
            switch (convolution_type) {
                case 1:
                    kernel[i][j] = 1.0 / kernel_size;
                    break;
                case 2:
                    long double x = i - (kernel_length - 1) / 2.0;
                    long double y = j - (kernel_length - 1) / 2.0;
                    kernel[i][j] = gaussian(x, y);
                    gauss_sum += kernel[i][j];
                    break;
            }
        }
    }

    if (convolution_type == 2) {
        for (int i = 0; i < kernel_length; i++) {
            for (int j = 0; j < kernel_length; j++) {
                kernel[i][j] /= gauss_sum;
            }
        }
    }

    return kernel;
}

float* convolve_pixel(float*** matrix, float** kernel, int x, int y) {
    int sum_vector_length = num_of_colours;
    int special_pixels_index = 0;
    sum_vector = calloc(sum_vector_length, sizeof(float));

    for (int k = 0; k < kernel_size; k++) {
        special_pixels[k].i = INT16_MAX;
        special_pixels[k].j = INT16_MAX;
    }

    for (int i = -(kernel_radius); i <= kernel_radius; i++) {
        for (int j = -(kernel_radius); j <= kernel_radius; j++) {
            if (x + i < 0 || y + j < 0 || x + i >= image_height || y + j >= image_width) {
                special_pixels[special_pixels_index].i = i;
                special_pixels[special_pixels_index].j = j;
                special_pixels[special_pixels_index].x = x;
                special_pixels[special_pixels_index].y = y;
            }
            special_pixels_index++;
        }
    }

    if (special_pixels_index != kernel_size) {
        printf("PIXEL FAILED\n");
        float* green = malloc(sizeof(float) * 3);
        green[0] = 0.0;
        green[1] = 255.0;
        green[2] = 0.0;
        return green;
    }

    special_pixels_index = 0;

    for (int i = -(kernel_radius); i <= kernel_radius; i++) {
        for (int j = -(kernel_radius); j <= kernel_radius; j++) {
            if (i != special_pixels[special_pixels_index].i && j != special_pixels[special_pixels_index].j) {
                for (int n = 0; n < sum_vector_length; n++) {
                    sum_vector[n] += scalar_multiplication(matrix[x+i][y+j], kernel[i+kernel_radius][j+kernel_radius], sum_vector_length)[n];
                }
            } else {
                for (int n = 0; n < sum_vector_length; n++) {
                    sum_vector[n] += scalar_multiplication(matrix[x][y], kernel[i+kernel_radius][j+kernel_radius], sum_vector_length)[n];
                }
            }
            special_pixels_index++;
        }
    }

    return sum_vector;
}

float*** convolve(float*** matrix) {
    initialise_algorithm();

    float** kernel = create_kernel();

    float*** convolved_matrix = malloc(sizeof(float*) * image_height);
    for (int i = 0; i < image_height; i++) {
        convolved_matrix[i] = malloc(sizeof(float*) * image_width);
        for (int j = 0; j < image_width; j++) {
            convolved_matrix[i][j] = convolve_pixel(matrix, kernel, i, j);
        }
    }
    
    free(kernel);
    return convolved_matrix;
}

void free_convolution_memory() {
    free(multiplied_vector);
    free(sum_vector);
    free(special_pixels);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "include/image.h"

FILE* file_p;
BITMAPFILEHEADER file_header;
BITMAPINFOHEADER info_header;

int image_width;
int image_height;
int num_of_colours;
int pixels_size;

uint8_t* read_image() {
    uint8_t* pixels;
    file_p = fopen("../input/input.bmp", "rb");

    if (file_p != NULL) {
        fread(&file_header, sizeof(file_header), 1, file_p);
        fread(&info_header, sizeof(info_header), 1, file_p);
        image_width = info_header.biWidth;
        image_height = info_header.biHeight;

        pixels_size = file_header.bfSize-54;
        pixels = malloc(pixels_size);

        fseek(file_p, file_header.bfOffBits, SEEK_SET);
        fread(pixels, sizeof(uint8_t), pixels_size, file_p);

        fclose(file_p);
    } else {
        printf("Error opening file.");
    }
    return pixels;
}

float*** create_matrix(uint8_t* pixels) {
    num_of_colours = 3;
    float*** matrix = malloc(sizeof(float*) * image_height);

    for (int i = 0; i < image_height; i++) {
        matrix[i] = malloc(sizeof(float*) * image_width);
        for (int j = 0; j < image_width; j++) {
            matrix[i][j] = malloc(num_of_colours * sizeof(float));
        }
    }

    int pixel_index = -1;
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            for (int n = 0; n < num_of_colours; n++) {
                pixel_index++;
                matrix[i][j][n] = pixels[pixel_index];
            }
            pixel_index++;
        }
    }

    return matrix;
}

uint8_t* create_pixels(float*** matrix) {
    uint8_t* pixels = malloc(pixels_size);

    int pixel_index = -1;
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            for (int n = 0; n < num_of_colours; n++) {
                pixel_index++;
                pixels[pixel_index] = round(matrix[i][j][n]);
            }
            pixel_index++;
            pixels[pixel_index] = 255;
        }
    }

    return pixels;
}

void write_image(float*** matrix) {
    uint8_t* output = create_pixels(matrix);

    file_p = fopen("../output/output.bmp", "wb");

    if (file_p != NULL) {
        fwrite(&file_header, sizeof(file_header), 1, file_p);
        fwrite(&info_header, sizeof(info_header), 1, file_p);
        fwrite(output, sizeof(uint8_t), pixels_size, file_p);
        fclose(file_p);

        printf("Image Convolved.");
    } else {
        printf("Error creating file.");
    }

    free(output);
}
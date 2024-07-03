#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "include/image.h"

FILE* file_p;
BITMAPFILEHEADER file_header;
BITMAPINFOHEADER info_header;

const int COLOUR_CHANNELS = 3;

int image_width;
int image_height;
int pixels_size;
int offset;
uint8_t* offset_array;
uint8_t offset_byte_value;

// Checks if data has a byte offset (either every 4 bytes, or at the end of each line):
int offset_check(uint8_t* data) {
    int offset_bytes = 4;
    int locked = 0;

    for (int i = offset_bytes - 1; i < pixels_size; i += offset_bytes) {
        if (data[i] != 255 && data[i] != 0) {
            offset_bytes = image_width;
            break;
        } else if (data[i] == 255 && !locked) {
            offset_byte_value = 255;
            locked = 1;
        } else if (data[i] == 0 && !locked) {
            offset_byte_value = 0;
            locked = 1;
        } else if (data[i] != offset_byte_value && locked) {
            offset_bytes = image_width;
            break;
        }
    }

    int n = 0;
    if (offset_bytes == image_width) {
        for (int i = (image_width * COLOUR_CHANNELS); i < pixels_size; i += ((image_width * COLOUR_CHANNELS) + 1)) {
            if (i + 3 < pixels_size) {
                if (((data[i] == data[i - 3] || data[i] == data[i - 2] || data[i] == data[i - 1]) || (data[i] == data[i + 1] || data[i] == data[i + 2] || data[i] == data[i + 3]))
                && ((data[i - 3] != 0 || data[i - 2] != 0 || data[i - 1] != 0) && (data[i + 1] != 0 || data[i + 2] != 0 || data[i + 3] != 0))) {
                    return 0;
                }
            }
            n++;
        }

        offset_array = malloc(n * sizeof(uint8_t));

        return 2;

    } else return 1;
}

// Reads the input.bmp data and creates an array of pixels:
uint8_t* read_data(void) {
    uint8_t* pixels;
    file_p = fopen("input/input.bmp", "rb");

    if (file_p != NULL) {
        fread(&file_header, sizeof(file_header), 1, file_p);
        fread(&info_header, sizeof(info_header), 1, file_p);
        image_width = info_header.biWidth;
        image_height = info_header.biHeight;

        pixels_size = file_header.bfSize-file_header.bfOffBits;
        pixels = malloc(pixels_size);

        fseek(file_p, file_header.bfOffBits, SEEK_SET);
        fread(pixels, sizeof(uint8_t), pixels_size, file_p);

        fclose(file_p);

        offset = offset_check(pixels);
    } else {
        printf("Error opening file.");
    }

    return pixels;
}

// Creates a matrix of each pixel (a third order tensor of each colour channel) from the pixel data:
float*** read_image(void) {
    //COLOUR_CHANNELS = 3;
    uint8_t* pixels = read_data();

    float*** matrix = malloc(sizeof(float*) * image_height);

    for (int i = 0; i < image_height; i++) {
        matrix[i] = malloc(sizeof(float*) * image_width);
        for (int j = 0; j < image_width; j++) {
            matrix[i][j] = malloc(COLOUR_CHANNELS * sizeof(float));
        }
    }

    int pixel_index = -1;
    int byte_index = -1;
    int increment = 0;
    int locked = 0;

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            for (int n = 0; n < COLOUR_CHANNELS; n++) {
                pixel_index++;
                if (offset == 2 && (pixel_index % (image_width * COLOUR_CHANNELS) == increment && pixel_index != 0) && !locked) {
                    byte_index++;
                    offset_array[byte_index] = (uint8_t)pixels[pixel_index];
                    n--;
                    increment++;
                    locked = 1;
                } else {
                    matrix[i][j][n] = pixels[pixel_index];
                    locked = 0;
                }
            }
            if (offset == 1) {
                pixel_index++;
            }
        }
    }

    return matrix;
}

// Converts the matrix back into pixel data:
uint8_t* create_pixels(float*** matrix) {
    uint8_t* pixels = malloc(pixels_size);

    int pixel_index = -1;
    int byte_index = -1;
    int increment = 0;
    int locked = 0;

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            for (int n = 0; n < COLOUR_CHANNELS; n++) {
                pixel_index++;
                if (offset == 2 && (pixel_index % (image_width * COLOUR_CHANNELS) == increment && pixel_index != 0) && !locked) {
                    byte_index++;
                    pixels[pixel_index] = offset_array[byte_index];
                    n--;
                    increment++;
                    locked = 1;
                } else {
                    pixels[pixel_index] = (uint8_t)round(matrix[i][j][n]);
                    locked = 0;
                }
            }
            if (offset == 1) {
                pixel_index++;
                pixels[pixel_index] = offset_byte_value;
            }
        }
    }

    return pixels;
}

// Writes the pixel data as output.bmp:
void write_image(float*** matrix) {
    uint8_t* output = create_pixels(matrix);

    file_p = fopen("output/output.bmp", "wb");

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

float* greyscale(float* pixel) {
    for (int n = 0; n < COLOUR_CHANNELS; n++) {
        pixel[n] = pixel[0] * 0.114 + pixel[1] * 0.587 + pixel[2] * 0.299;
    }

    return pixel;
}

void free_image_memory(void) {
    free(offset_array);
}
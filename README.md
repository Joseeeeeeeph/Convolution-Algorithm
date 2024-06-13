# Joseeeeeeeph's Convolution Algorithm #

## This is a simple bitmap image processor and convolution algorithm written in C, that currently applies either box blur, Gaussian blur or Laplacian edge-detection to an image ###

### Run: ./convolve ###

The input image must be named _"input.bmp"_ and placed in the _input_ directory. There are also example images for you.

The output will be generated as _"output.bmp"_ in the _output_ directory.

The algorithm uses edge-extension as its edge handling.

The size of the kernel, and the size of the variance for Gaussian blur, can be edited in _src/convolution.c_. The kernel width/height must be an odd number (though this will probably change in the future). Larger kernel sizes return weird results for edge-detection.

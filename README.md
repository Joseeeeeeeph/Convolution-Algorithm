# Joseeeeeeeph's Convolution Algorithm #

_NOTE: This is a WIP that so far only works with small .bmp, with a byte offset to align each 3 colour values (RGB) to 4 bytes. Large .bmp without this offset are not supported yet._

### This is a simple image processor and convolution algorithm written in C, that currently applies either box blur, Gaussian blur or edge-detection to an image. The algorithm uses edge-extension as its edge handling. ###

### Run: /src/convolve ###

The input image must be in bitmap (.bmp) format and named _"input.bmp"_. The input image must also be placed in the _input_ directory. There already exists an example image in the directory.

The output will be generated as _"output.bmp"_ in the _output_ directory.

The source code is in the _src_ directory.

More features such as unsharp masking will be implemented in the future. Support for larger bitmap images with different offset structures will also be implemented.

The size of the kernel, and the size of the variance for Gaussian blur, can be edited in _convolution.c_. The kernel width/height must be an odd number (though this will probably change in the future). Larger kernel sizes are only recommended for blurring.

This is a small amateur project and a WIP.
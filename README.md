# Joseeeeeeeph's Convolution Algorithm 

### This is a simple image processor and convolution algorithm written in C, that currently applies 'box blur' to an image. The algorithm uses edge extension as its edge handling.

### Run: /src/box_blur

The input image must be in bitmap (.bmp) format and named _"input.bmp"_. The input image must also be placed in the _input_ directory.

The output will be generated as _"output.bmp"_ in the _output_ directory.

The source code is in the _src_ directory.

More features such as Gaussian blur, sharpening and edge detection will be implemented in the future.

The size of the kernel can be edited in _convolution.c_, but must be an odd number. This will probably change in the future.

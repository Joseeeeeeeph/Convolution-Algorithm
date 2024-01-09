# Joseeeeeeeph's Convolution Algorithm 

**_NOTE: THIS IS A WIP THAT SO FAR ONLY WORKS WITH SMALL .bmp, WITH A BYTE OFFSET TO ALIGN EACH 3 COLOUR VALUES (RGB) TO 4 BYTES. LARGE .bmp WITHOUT THIS OFFSET ARE NOT SUPPORTED YET._**

### This is a simple image processor and convolution algorithm written in C, that currently applies 'box blur' to an image. The algorithm uses edge extension as its edge handling.

### Run: /src/box_blur

The input image must be in bitmap (.bmp) format and named _"input.bmp"_. The input image must also be placed in the _input_ directory.

The output will be generated as _"output.bmp"_ in the _output_ directory.

The source code is in the _src_ directory.

More features such as Gaussian blur, sharpening and edge detection will be implemented in the future. Support for larger bitmap images with different offset structures will also be implemented.

The size of the kernel can be edited in _convolution.c_, but must be an odd number. This will probably change in the future.

This is a small amateur project and a WIP.

OpticalFlow
===========

In those file there are some classes useful to evaluate dense optical flow with OpenCV libraries. The library is at beta stage.

OpticalFlowPC
-------------

This class is part of another project in my repo [[1]], that will publied in the next days.

Classes are developed with variable precision. To have double precision you have to compile with definition `PRECISION_DOUBLE`. If you want single precision, define the variable `PRECISION_FLOAT`.

`OpticalFlowPC` uses phase correlation to evaluate the optical flow [[2]]. The class is provided as an "engine class", that should be initialized and then used with `eval` method:

This is an example:

```C++
#include "libOpticalFlow.hpp"

[...]

Mat oldFrame, newFrame, opticalFlow;

VideoCapture cap("video.avi");

cap >> oldFrame;
cap >> newFrame;

OpticalFlowPC engine(window_dimension, window_gaussian_filter, sigma_of_filter);
engine.eval(oldFrame, newFrame, opticalFlow);
```

The resulting optical flow has two components.

OpticalFlowF
------------

This class is used to evaluate the optical flow using Farneback method.

IF YOU LIKE OR WANT TO USE THIS PROJECT, PLEASE STAR IT!

---

1: Project Repo

2: Optical Flow Estimation using Fourier Mellin Transform.

 [1]: https://github.com/MatteoRagni
 [2]: http://www.umiacs.umd.edu/~huytho/papers/HoGoecke_CVPR2008.pdf

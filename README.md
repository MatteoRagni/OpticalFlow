OpticalFlow
===========

In those file there are some classes useful to evaluate dense optical flow with OpenCV libraries.
THE CLASSES ARE IN BETA VERSION!
This class is part of another project in my repo, that will publied in the next days.

Classes are developed with variable precision. To have double precision 

`OpticalFlowPC` uses phase correlation to evaluate the optical flow. The class is provided as an "engine class", that should be initialized and then used with `eval` method:

```
OpticalFlowPC engine(window_dimension, window_gaussian_filter, sigma_of_filter);
engine.eval(oldFrame, newFrame, opticalFlow);

```

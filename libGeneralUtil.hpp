/*
 * libGeneralUtil.hpp
 *
 *  Created on: Jan 3, 2014
 *      Author: Matteo Ragni
 *
 *  This file contains a series of general utilities that I'll use across my projects.
 *
 */

#ifndef LIBGENERALUTIL_HPP_
#define LIBGENERALUTIL_HPP_

#include <math.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <opencv2/opencv.hpp>

// WARNING! PRECISION_DOUBLE is defined as preprocessor directive on command line.

/* Definition for Map class */
#if defined(PRECISION_DOUBLE)
	#define MAPTYPE		double
	#define MAPDEPTHX 	CV_64F
	#define MAPVEC(x)	Vec ## x ## d
	#define MAPDEPTH(x) CV_64F ## C ## x
#endif
#if defined(PRECISION_FLOAT) && !defined(PRECISION_DOUBLE)
	#define MAPTYPE		float
	#define MAPDEPTHX 	CV_32F
	#define MAPVEC(x)	Vec ## x ## f
	#define MAPDEPTH(x) CV_32F ## C ## x
#endif

/* Definition for timeMap class */

using namespace cv;
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long int ulong;
typedef long int ilong;

// Export a mat to a file for MATLAB. Automatically split the mat-
// To access a channel dot notation should be used:
// mat - 2 channel
// 	-> mat.channel1
// 	-> mat.channel2
void Mat2file(Mat&, const char*);

// Convert image in gray
void bgr2gray(Mat&);
// Convert an image to float precision
void cvt2prec(Mat&);

// Generate a linear matrix along X on channel 1 and along Y on channel 2
Mat linearMat(ulong, ulong);


#endif /* LIBGENERALUTIL_HPP_ */

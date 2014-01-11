/*
 * libOpticalFlow.hpp
 *
 *  Created on: Jan 5, 2014
 *      Author: Matteo Ragni
 */

#ifndef LIBOPTICALFLOW_HPP_
#define LIBOPTICALFLOW_HPP_

#include "libGeneralUtil.hpp"

#if defined(PRECISION_DOUBLE)
	#define OFTYPE		double
	#define OFDEPTHX 	CV_64F
	#define OFVEC(x)	Vec ## x ## d
	#define OFDEPTH(x) 	CV_64F ## C ## x
#endif
#if defined(PRECISION_FLOAT) && !defined(PRECISION_DOUBLE)
	#define OFTYPE		float
	#define OFDEPTHX 	CV_32F
	#define OFVEC(x)	Vec ## x ## f
	#define OFDEPTH(x)	CV_32F ## C ## x
#endif

class OpticalFlowPC {
private:
	ilong winSize, winCenter, rows, cols, gaussWin;
	Mat HanWin, f1, f2, res, w1, w2;
	double sigma;

	inline void emptyCnstr();
	// Prepares the two frames (to gray scale, floating point)
	void prepareFrame(Mat*, Mat*);
	void extractRoi(ilong, ilong);

public:
	OpticalFlowPC();
	// Parameter in construction of the engine:
	// ilong -> window dimensions
	// ilong -> gaussian blur window dimension
	// double -> gaussian sigm (X = Y)
	OpticalFlowPC(ilong, ilong, double);

	// Run the optical flow with parameters defined in construction
	void eval(Mat*, Mat*, Mat&);

};

class OpticalFlowF {
private:
	double pyrscale, sigma_n;
	int rows, cols, pyrlevel, winSize, iteration, poly_n;
	Mat f1, f2, res;
	void emptyCnstr();
	void prepareFrame(Mat*, Mat*);

public:
	OpticalFlowF();
	// Parameters to construct the engine
	// int rows
	// int cols
	// double pyramid scale (0.5 half the previous)
	// int level of pyramid
	// int dimension of the window
	// int number of iteration
	// int number of poly
	// double sigma to the poly
	OpticalFlowF(int, int, double, int, int, int, int, double);

	void eval(Mat*, Mat*, Mat&);


};


#endif /* LIBOPTICALFLOW_HPP_ */

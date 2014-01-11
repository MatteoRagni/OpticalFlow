/*
 * libOpticalFlow.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: Matteo Ragni
 */

#include "libOpticalFlow.hpp"

/* CONSTRUCTORS */

inline void OpticalFlowPC::emptyCnstr() {
	this->winSize = 0;
	this->winCenter = 0;
	this->rows = 0;
	this->cols = 0;
	this->gaussWin = 0;
	this->sigma = 0;
	this->f1 = Mat();
	this->f2 = Mat();
	this->w1 = Mat();
	this->w2 = Mat();
	this->res = Mat();
}

OpticalFlowPC::OpticalFlowPC() {
	this->emptyCnstr();
}

OpticalFlowPC::OpticalFlowPC(ilong par1, ilong par2, double par3) {
	this->emptyCnstr();
	this->winSize = ((par1 % 2 == 0) ? par1 + 1: par1);
	this->gaussWin = ((par2 % 2 == 0) ? par2 + 1: par2);
	this->winCenter = (this->winSize - 1)/2;
	this->sigma = abs(par3);
	createHanningWindow(this->HanWin, Size(this->winSize, this->winSize), OFDEPTHX);
}

/* METHODS */

void OpticalFlowPC::prepareFrame(Mat* inf1, Mat* inf2) {
	this->f1 = Mat();
	this->f2 = Mat();
	this->f1 = inf1->clone();
	this->f2 = inf2->clone();
	bgr2gray(this->f1);
	bgr2gray(this->f2);

	cvt2prec(this->f1);
	cvt2prec(this->f2);

	this->rows = (ilong)this->f1.rows;
	this->cols = (ilong)this->f1.cols;
}

void OpticalFlowPC::extractRoi(ilong row, ilong col) {
	this->w1 = Mat(this->winSize, this->winSize, OFDEPTHX);
	this->w2 = Mat(this->winSize, this->winSize, OFDEPTHX);
	ilong x1, x2, y1, y2;
	int dx, dy;
	x1 = col;
	y1 = row;
	x2 = x1 + this->winSize;
	y2 = y1 + this->winSize;

	dx = x2 - x1;
	dy = y2 - y1;

	// X
	if (x1 < 0) {
		dx = x2;
		x1 = 0;
	}
	if (x2 >= this->cols) {
		dx = this->winSize - (x2 - this->cols);
		// x1 = x1;
	}
	// Y
	if (y1 < 0) {
		dy = y2;
		y1 = 0;
	}
	if (y2 >= this->rows) {
		dy = this->winSize - (y2 - this->rows);
	}

	Rect ROI = Rect(x1, y1, dx, dy);
	this->w1 = this->f1(ROI);
	this->w2 = this->f2(ROI);

	if ((this->w1.rows != this->HanWin.rows) | (this->w1.cols != this->HanWin.cols)) {
		this->HanWin = Mat(Size(this->w1.cols, this->w1.rows), OFDEPTHX);
		createHanningWindow(this->HanWin, Size(this->w1.cols, this->w1.rows), OFDEPTHX);
	}

}

/* Evaluation algorithm */

void OpticalFlowPC::eval(Mat* frame1, Mat* frame2, Mat& result) {
	prepareFrame(frame1, frame2);

	result = Mat::zeros(Size(this->cols, this->rows), OFDEPTH(2));
	this->res = Mat::zeros(Size(this->cols, this->rows), CV_64FC2);

	Point2d d;
	Vec2d v;

	// Elaborating solutions inside the image
	for (ilong r = -this->winCenter; r < (this->rows - this->winCenter); r++) {
		for (ilong c = -this->winCenter; c < (this->cols - this->winCenter); c++) {
			d = Point2d(0.0,0.0);
			this->extractRoi(r, c);

			d = phaseCorrelate(this->w1, this->w2, this->HanWin);
			v = Vec2d(d.x,d.y);

			this->res.at<Vec2d>(r + this->winCenter,c + this->winCenter) = v;
		}
	}

	// Gaussian filtering along the edges. It is the same to make the weighted sum
	GaussianBlur(this->res, this->res, Size(this->gaussWin, this->gaussWin), this->sigma);

	this->res.convertTo(result, OFDEPTHX);
}

/**************************************************************/

/* CONSTRUCTORS */

void OpticalFlowF::emptyCnstr() {
	this->f1 = Mat();
	this->f2 = Mat();
	this->res = Mat();
	this->rows = 0;
	this->cols = 0;
	this->pyrlevel = 0;
	this->winSize = 0;
	this->iteration = 0;
	this->poly_n = 0;
	this->pyrscale = 0;
	this->sigma_n = 0;
}

OpticalFlowF::OpticalFlowF() {
	this->emptyCnstr();
}

OpticalFlowF::OpticalFlowF(int _rows, int _cols, double _pyrscale, int _pyrlevel, int _winSize, int _iteration, int _poly_n, double _sigma_n){
	this->emptyCnstr();
	this->rows = _rows;
	this->cols = _cols;
	this->pyrlevel = _pyrlevel;
	this->winSize = _winSize;
	this->iteration = _iteration;
	this->poly_n = _poly_n;
	this->pyrscale = _pyrscale;
	this->sigma_n = _sigma_n;

	this->f1 = Mat(this->rows, this->cols, CV_8UC3);
	this->f2 = Mat(this->rows, this->cols, CV_8UC3);
	this->res = Mat::zeros(this->rows, this->cols, CV_32FC2);
}

void OpticalFlowF::eval(Mat* in1, Mat* in2, Mat& out) {

	this->f1 = in1->clone();
	this->f2 = in2->clone();
	out = Mat(this->rows, this->cols, OFDEPTH(2));

	bgr2gray(this->f1);
	bgr2gray(this->f2);

	calcOpticalFlowFarneback(this->f1, this->f2, this->res,										\
							 this->pyrscale, this->pyrlevel, this->winSize, this->iteration,	\
							 this->poly_n, this->sigma_n, OPTFLOW_USE_INITIAL_FLOW);

	this->res.convertTo(out, OFDEPTHX);
}

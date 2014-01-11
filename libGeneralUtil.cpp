/*
 * libGeneralUtili.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: Matteo Ragni
 *
 *      This file contains a series of general utilities that I'll use across my projects.
 */

#include "libGeneralUtil.hpp"

void Mat2file(Mat& input, const char* varname) {

	char filename[50];

    sprintf(filename, "script-%s.m", varname);
	ofstream fout(filename);
    if(!fout) {
    	cout << "File Not Opened" << endl;
    	return;
    }

    if (input.channels() != 1) {

    	char savevarname[50];
    	vector<Mat> comps;
		split(input, comps);

		for (uint k = 0; k < comps.size(); k++) {
			sprintf(savevarname, "%s.channel%i", varname, k+1);
			fout << savevarname << " = [";
			for(int i = 0; i < comps[k].rows; i++) {
				for(int j = 0; j<comps[k].cols; j++) {
					fout << comps[k].at<MAPTYPE>(i,j) << "\t";
				}
				if (i != comps[k].rows - 1) fout << ";";
			}
			fout << "];" << endl;
			comps[k].release();
		}
		comps.clear();
    } else {
        fout << varname << " = [";
		for(int i = 0; i < input.rows; i++) {
			for(int j = 0; j < input.cols; j++) {
				fout << input.at<MAPTYPE>(i,j)<<"\t";
			}
			if (i != input.rows - 1) fout << ";";
		}
		fout << "];" << endl;
    }
    fout.close();
}

Mat linearMat(ulong rows, ulong cols) {
	Mat ret = Mat(rows, cols, MAPDEPTH(2));
	for (ulong k = 0; k < rows; k++ ) {
		for (ulong j = 0; j < rows; j++ ) {
			ret.at<MAPVEC(2)>(k,j) = MAPVEC(2)((MAPTYPE)j,(MAPTYPE)k);
		}
	}
	return ret;
}

void bgr2gray(Mat& in) {
	Mat m = in.clone();
	cvtColor(m, in, CV_BGR2GRAY);
	m.release();
}

void cvt2prec(Mat& in) {
	Mat m = in.clone();
	int d;
	switch (m.channels()) {
		case 1: d = MAPDEPTHX; break;
		case 2: d = MAPDEPTH(2); break;
		case 3: d = MAPDEPTH(3); break;
		case 4: d = MAPDEPTH(4); break;
	}
	in = Mat(m.rows, m.cols, d);
	m.convertTo(in, MAPDEPTHX, 1.0/255);
	m.release();
}


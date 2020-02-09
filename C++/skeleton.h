#pragma once
#ifndef SKELETON_H
#define SKELETON_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
//#include <fstream>


namespace pgcv {
	int skeleton(cv::Mat input, cv::Mat& output, int iteration);
	//returns the number of iterations have been done in the process
}

#endif

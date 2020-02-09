/*
This function is able to generate the morphological skeleton of a binary image using the hit-miss operation of the specific kernel which is designed for this purpose. For a morphological skeleton, it is necessary to rotate the kernel 8 times with 45 degrees angle and then apply the hit-miss operation on the image using each of the kernels.

Every step of applying the eight kernels to the image removes one layer from the binary image. Therefore, if we want to reach the main skeleton of the binary objects, we should do this operation as many as possible until the image doesn't change anymore (it means, the step that we can't remove any other layer from the image; the main skeleton of the image).

Since we don't have infinity on the computer, we can use thousands of iterations to reach the skeleton. Don't worry about the time! This function checks the result in every iteration, and if it doesn't change anymore (the definition of the main skeleton), it terminates the program (Otherwise, it continues until it reaches the maximum allowed iteration).

Don't forget that you need the OpenCV library to run the function.

This function is the exact equivalent to the MATLAB's morphological skeleton: skel = bwmorph(bw, 'skel', max_iter);

You can study the theoretical foundations of this operator in the reference below:

Haralick, Robert M., and Linda G. Shapiro. Computer and robot vision. Vol. 1. Reading: Addison-wesley, 1992, pages 170-171.

Implementation by: Peyman Ghasemi - p.ghasemi94 {AT} gmail

Example:

cv::Mat im = cv::imread("example.jpg", cv::LOAD_IMAGE_GRAYSCALE);
cv::Mat input, output;
cv::threshold(im, input, 127, 255, cv::THRESH_BINARY);

int max_allowed_iters = 1000;
int number_of_iters = pgcv::skeleton(input, output, max_allowed_iters);

std::cout << "Number of iterations which were needed for the skeleton (didn't change anymore after that) = "<<number_of_iters<<std::endl;
cv::namedWindow("input");

cv::imshow("input", input);

cv::namedWindow("Output");

cv::imshow("Output", output);

cv::waitKey(0);

*/

#include "skeleton.h"
//#include <time.h>

void one_skel_operation(cv::Mat in, cv::Mat& out) {
	
	//define the hit-or-miss kernels
	std::vector<cv::Mat> kernels(8);

	kernels[0] = (cv::Mat_<int>(3, 3) <<
		1, 1, 1,
		0, 1, 0,
	   -1,-1,-1);
	kernels[1] = (cv::Mat_<int>(3, 3) <<
		 0, 1, 0,
		-1, 1, 1,
		-1,-1, 0);
	kernels[2] = (cv::Mat_<int>(3, 3) <<
		1, 0,-1,
		1, 1,-1,
		1, 0,-1);
	kernels[3] = (cv::Mat_<int>(3, 3) <<
		0, 1, 0,
		1, 1,-1,
		0,-1,-1);
	kernels[4] = (cv::Mat_<int>(3, 3) <<
		-1, 0, 1,
		-1, 1, 1,
		-1, 0, 1);
	kernels[5] = (cv::Mat_<int>(3, 3) <<
		0,-1,-1,
		1, 1,-1,
		0, 1, 0);
	kernels[6] = (cv::Mat_<int>(3, 3) <<
		-1,-1,-1,
		 0, 1, 0,
		 1, 1, 1);
	kernels[7] = (cv::Mat_<int>(3, 3) <<
		-1,-1, 0,
		-1, 1, 1,
		 0, 1, 0);

	//Do the operation
	out = in.clone(); //set output pixels like input
	cv::Mat hitmissOut;

	

	for (int i = 0; i < 8; i++) {
		morphologyEx(out, hitmissOut, cv::MORPH_HITMISS, kernels[i]); //hit or miss operation
		cv::subtract(out, hitmissOut, out);
		//out = out - hitmissOut;
	}
	/// 


}


// use this function to get the result of skeleton
namespace pgcv {
	int skeleton(cv::Mat input, cv::Mat& output, int iteration) {

		cv::Mat Previous;
		output = input.clone();
		int STOPFLAG = 0;
		int step = 0;

		while (!STOPFLAG) {
			step++;

			Previous = output.clone();

			one_skel_operation(Previous, output); //Do the operator of skeleton one time

			//if image does't change in next iteration or it is the end of the maximum iteration, stop!
			cv::Mat isequal;
			cv::bitwise_xor(Previous, output, isequal); //XOR of two images as the index of similarity
			int nnz = cv::countNonZero(isequal); //if fully similar, then XOR is compeletly zero

			if (nnz == 0 || step == iteration) { //if image doesn't change anymore or it is the end of the iteration
				STOPFLAG = 1;
			}

			//cv::namedWindow("Draft");
			//cv::imshow("Draft",  output);
			//cv::waitKey(0);
		}
		return step; //return the number of steps
	}
}


//void main()
//{
//
//	cv::Mat im = cv::imread("img.png", CV_LOAD_IMAGE_GRAYSCALE);
//	cv::Mat input, output;
//	cv::threshold(im, input, 127, 255, CV_THRESH_BINARY);
//
//	clock_t start0 = clock();
//	pgcv::skeleton(input, output, 30);
//	clock_t stop0 = clock();
//	double time = (double)(stop0 - start0) / CLOCKS_PER_SEC;
//	std::cout << "global " << globTime<<std::endl<< time << std::endl;
//	
//	cv::namedWindow("input");
//	cv::imshow("input", input);
//	cv::namedWindow("Output");
//	cv::imshow("Output", (output*255));
//	cv::waitKey(0);
//}

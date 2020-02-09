# skeleton


This function is able to generate the morphological skeleton of a binary image using the hit-miss operation of the specific kernel which is designed for this purpose. For a morphological skeleton, it is necessary to rotate the kernel 8 times with 45 degrees angle and then apply the hit-miss operation on the image using each of the kernels.

Every step of applying the eight kernels to the image removes one layer from the binary image. Therefore, if we want to reach the main skeleton of the binary objects, we should do this operation as many as possible until the image doesn't change anymore (it means, the step that we can't remove any other layer from the image; the main skeleton of the image).

Since we don't have infinity on the computer, we can use thousands of iterations to reach the skeleton. Don't worry about the time! This function checks the result in every iteration, and if it doesn't change anymore (the definition of the main skeleton), it terminates the program (Otherwise, it continues until it reaches the maximum allowed iteration).

Don't forget that you need the OpenCV library to run the function.

This function is the exact equivalent to the MATLAB's morphological skeleton: skel = bwmorph(bw, 'skel', max_iter);

You can study the theoretical foundations of this operator in the reference below:

**Haralick, Robert M., and Linda G. Shapiro. Computer and robot vision. Vol. 1. Reading: Addison-wesley, 1992, pages 170-171.**


Implementation by: **Peyman Ghasemi** - _p.ghasemi94 {AT} gmail_


------------------------

Example:

**C++:**

```c++

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

```

-------------------------

**Python:**

```python
input = cv.imread("example.jpg',cv.IMREAD_GRAYSCALE)

input = cv.threshold(input, 128, 255, cv.THRESH_BINARY)


max_allowed_iters = 1000

number_of_iters, output = skeleton.skeleton(input, max_allowed_iters)

print("Number of iterations which were needed for the skeleton (didn't change anymore after that) = " + str(number_of_iters))



cv.imshow("input", input)
cv.imshow("output", output)
cv.waitKey()

```

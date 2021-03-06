"""
This function is able to generate the morphological skeleton of a binary image using the hit-miss operation of the specific kernel which is designed for this purpose. For a morphological skeleton, it is necessary to rotate the kernel 8 times with 45 degrees angle and then apply the hit-miss operation on the image using each of the kernels.

Every step of applying the eight kernels to the image removes one layer from the binary image. Therefore, if we want to reach the main skeleton of the binary objects, we should do this operation as many as possible until the image doesn't change anymore (it means, the step that we can't remove any other layer from the image; the main skeleton of the image).

Since we don't have infinity on the computer, we can use thousands of iterations to reach the skeleton. Don't worry about the time! This function checks the result in every iteration, and if it doesn't change anymore (the definition of the main skeleton), it terminates the program (Otherwise, it continues until it reaches the maximum allowed iteration).

Don't forget that you need the OpenCV library to run the function.

This function is the exact equivalent to the MATLAB's morphological skeleton: skel = bwmorph(bw, 'skel', max_iter);

You can study the theoretical foundations of this operator in the reference below:

Haralick, Robert M., and Linda G. Shapiro. Computer and robot vision. Vol. 1. Reading: Addison-wesley, 1992, pages 170-171.

Implementation by: Peyman Ghasemi - p.ghasemi94 {AT} gmail

Example:
input = cv.imread("example.jpg',cv.IMREAD_GRAYSCALE)
input = cv.threshold(input, 128, 255, cv.THRESH_BINARY)

max_allowed_iters = 1000
number_of_iters, output = skeleton.skeleton(input, max_allowed_iters)

print("Number of iterations which were needed for the skeleton (didn't change anymore after that) = " + str(number_of_iters))
cv.imshow("input", input)
cv.imshow("output", output)
cv.waitKey()
"""



import numpy as np
import cv2 as cv

# eight kernels to be used for skeleton operation on binary images
skeleton_kernel = {
    0: np.array(([1, 1, 1],
                 [0, 1, 0],
                 [-1, -1, -1]), dtype="int"),
    1: np.array(([0, 1, 0],
                 [-1, 1, 1],
                 [-1, -1, 0]), dtype="int"),
    2: np.array(([1, 0, -1],
                 [1, 1, -1],
                 [1, 0, -1]), dtype="int"),
    3: np.array(([0, 1, 0],
                 [1, 1, -1],
                 [0, -1, -1]), dtype="int"),
    4: np.array(([-1, 0, 1],
                 [-1, 1, 1],
                 [-1, 0, 1]), dtype="int"),
    5: np.array(([0, -1, -1],
                 [1, 1, -1],
                 [0, 1, 0]), dtype="int"),
    6: np.array(([-1, -1, -1],
                 [0, 1, 0],
                 [1, 1, 1]), dtype="int"),
    7: np.array(([-1, -1, 0],
                 [-1, 1, 1],
                 [0, 1, 0]), dtype="int")
}


# one iteration of 8 series of hit-miss operations of skeleton morphological filter
def one_skel_operation(input_img):
    out = np.copy(input_img)  # set output pixels like input

    # apply eight hit-miss kernels
    for i in range(8):
        hitmissout = cv.morphologyEx(out, cv.MORPH_HITMISS, skeleton_kernel[i])  # hit or miss operation
        out = cv.subtract(out, hitmissout)  # subtraction from answer

    return out


# main skeleton function
# returns: number of iterations has been done for the result AND the skeleton image
def skeleton(input_img, num_itr):
    output = np.copy(input_img)
    step = 0

    while True:
        step += 1  # one step ahead to count iterations
        previous = np.copy(output)

        output = one_skel_operation(previous)  # Do the operator of skeleton one time

        # if image does't change in next iteration or it is the end of the maximum iteration, stop!
        is_equal = cv.bitwise_xor(previous, output)  # XOR of two images as the index of similarity
        nnz = cv.countNonZero(is_equal)  # if fully similar, then XOR is completely zero

        # if image doesn't change anymore or it is the end of the iteration
        if nnz == 0 or step == num_itr:
            break

    return step, output




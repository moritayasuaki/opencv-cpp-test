#ifndef __MY_UTIL_H__
#define __MY_UTIL_H__

#define VERTICAL 0
#define HORIZONTAL 1

Point getMirrorAxis(const Mat& image, int axis);
Point getMatchPoint(const Mat& image, const Mat& temp);
Point getCenter(const Mat& image);
Point getAlign(const Mat& image, const Mat& temp, int axis);
void setGaussianWindow(Mat& image);
void setHanningWindow(Mat& image);

#endif

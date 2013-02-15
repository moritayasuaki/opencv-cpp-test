#ifndef __MY_UTIL_H__
#define __MY_UTIL_H__

#define VERTICAL 0
#define HORIZONTAL 1

#include <cv.h>

int mirrorPosition(const cv::Mat& image, int axis);
cv::Point matchPoint(const cv::Mat& image, const cv::Mat& temp);
cv::Point center(const cv::Mat& image);
cv::Point align(const cv::Mat& image, int axis);

void setWindow(cv::Mat& image, double (*func)(double,double,double));
void setGaussianWindow(cv::Mat& image);
void setHanningWindow(cv::Mat& image);

double gaussian(double x, double y, double sigma);
double hanning(double x, double y, double scale);

#endif

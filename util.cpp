#include <cv.h>
#include <math.h>
#include "util.hpp"

using namespace cv;
using namespace std;

int mirrorPosition(const Mat& image, int axis){
  Mat flipped;
  int w = image.size().width;
  int h = image.size().height;
  Rect r;
  flip(image, flipped, axis);
  if (axis == HORIZONTAL) {
    r = Rect(w/4,0,w/2,h);
  }
  else {
    r = Rect(0,h/4,w,h/2);
  }
  flipped = flipped(r);
  Point max = matchPoint(image,flipped);
  if (axis == HORIZONTAL){
    return (max.x/2+w/4+w/8); // return x position for HORIZONTAL
  }
  else{
    return (max.y/2+h/4+h/8); // return y position for VERTICAL
  }
}

Point matchPoint(const Mat& image, const Mat& temp){
  Mat match;
  Point max;
  matchTemplate(image,temp,match,CV_TM_CCOEFF_NORMED);
  minMaxLoc(match,NULL,NULL,NULL,&max);
  return max;
}

Point center(const Mat& image){
  Moments m = moments(image);
  return Point(m.m10/m.m00,m.m01/m.m00);
}

Point align(const Mat& image, int axis){
  int w = image.size().width;
  int h = image.size().height;
  int dx,dy;
  dx = mirrorPosition(image, axis);
  Point p = center(image(Rect(dx-200,h/4,400,h/2)));
  dy = p.y+h/4;
  return Point(dx,dy);
}


void setWindow(Mat& image, double (*func)(double,double,double), double scale){
  int t = image.type();
  int w = image.cols;
  int h = image.rows;
  CV_Assert(t == CV_32FC1 );
  for (int y = 0; y < h; y++){
    float* fptr = image.ptr<float>(y);
    for (int x = 0; x < w; x++){
      fptr[x] *= (float)(func((double)x/w,(double)y/h,scale));
    }
  }
}
void setGaussianWindow(Mat& image){
  setWindow(image, gaussian, 0.5);
}
void setHanningWindow(Mat& image){
  setWindow(image, hanning, 1);
}

double gaussian(double x, double y,double sigma){
  double x2 = (x-0.5)*(x-0.5);
  double y2 = (y-0.5)*(y-0.5);
  double sigma2 = sigma*sigma;
  return exp(-(x2+y2)/sigma2);
}
double hanning(double x, double y,double scale){
  return cos(M_PI*(x-0.5))*cos(M_PI*(y-0.5));
}

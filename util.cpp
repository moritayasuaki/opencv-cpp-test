#include <cv.h>
#include <math.h>
#include "util.hpp"
using namespace cv;
using namespace std;

Point getCenter(const Mat& image){
  int
}

void setWindow(Mat& mat);

void setHanningWindow(Mat& mat){
  int t = mat.type();
  CV_Assert(t == CV_32FC1 || t == CV_64FC1);
  if(t == CV_32FC1){
    for (int r = 0; r < mat.rows; r++){
      float* fptr = mat.ptr<float>(r);
      for (int c = 0; c < mat.cols; c++){
        
      }
    }
  }
  else if(t == CV_64FC1){
    for (int r = 0; r < 
  }
} 
Point getAlign(const Mat& image, const Mat& temp, int axis){
  int w = image.size().width;
  int h = image.size().height;
  int dx,dy;
  Mat m1 = image.clone();
  int cx = w/2;
  int cy = h/2;
  float cdpi = M_PI/(m1.cols-1);
  float rdpi = M_PI/(m1.cols-1);
  m1.convertTo(m1,CV_32FC1);
 Point p = getMirrorAxis(m1, axis);
  Mat temp2 = temp(Rect(w/4,h/4,w/2,h/2));
  if (axis == HORIZONTAL){
    dx = p.x;
    Mat image2 = image(Rect(dx-w/4,0,w/2,h));
    Point p2 = getMatchPoint(image2,temp2);
    dy = p2.y/2 + h/4 + h/8;
  }
  else {
    dy = p.y;
    Mat image2 = image(Rect(0,dy-h/4,w,h/2));
    Point p2 = getMatchPoint(image2,temp2);
    dx = p2.x/2 + w/4 + w/8;
  }
  return Point(dx,dy);
}

Point getMatchPoint(const Mat& image, const Mat& temp){
  Mat match;
  Point max;
  matchTemplate(image,temp,match,CV_TM_CCOEFF);
  minMaxLoc(match,NULL,NULL,NULL,&max);
  return max;
}

Point getMirrorAxis(const Mat& image, int axis) {
  Mat flipped;
  flip(image, flipped, axis); // flip around Y axis
  int w = flipped.size().width;
  int h = flipped.size().height;
  Rect r;
  if (axis == HORIZONTAL){
    r = Rect(w/4,0,w/2,h);
  }
  else {
    r = Rect(0,h/4,w,h/2);
  }
  flipped = flipped(r);
  Point max = getMatchPoint(image,flipped);
  if (axis == HORIZONTAL){
    return (Point(max.x/2+w/4+w/8,0));
  }
  else{
    return (Point(0,max.y/2+h/4+h/8));
  }
}

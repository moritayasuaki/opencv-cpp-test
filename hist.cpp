#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include "extractor.hpp"
using namespace cv;
using namespace std;
using namespace de32f;
#define VERTICAL 0
#define HORIZONTAL 1

void distributedKeyPoints(const Mat& image,int size,vector<KeyPoint> &keypoints);
Point getAlign(const Mat& image, const Mat& temp, int axis);
Point getMatchPoint(const Mat& image, const Mat& temp);
Point getMirrorAxis(const Mat& image, int axis); 

int main(int argc, char** argv) {
  if(argc != 5){
    cout << "argc=" << argc << endl;
    return (-1);
  }
  Mat img1 = imread(argv[1],0); // color image
  Mat img2 = imread(argv[2],0); // color image
  FileStorage fs(argv[3],FileStorage::READ);
  Mat vocab;
  fs["vocab"] >> vocab;
  vocab.convertTo(vocab,CV_32F);
  Point p = getAlign(img1, img2, HORIZONTAL);
  Mat img3 = img1(Rect(p.x-300,p.y-150,600,600));

  DescriptorExtractor *extractor = (new DE32F(new FREAK(false,false)));
  DescriptorMatcher  *matcher = (new BFMatcher(NORM_L2));

  vector<KeyPoint> keys(0);
  distributedKeyPoints(img3,30,keys);
  BOWImgDescriptorExtractor bowextractor(extractor,matcher);
  bowextractor.setVocabulary(vocab);
  Mat desc;
  bowextractor.compute(img3, keys, desc);
  FileStorage fs2(argv[4],FileStorage::WRITE);
  fs2 << "hist" << desc;
  return (0);
}

void distributedKeyPoints(const Mat& image,int size,vector<KeyPoint> &keypoints){
  int w = image.size().width;
  int h = image.size().height;
  int divw = w/size;
  int divh = h/size;
  keypoints.resize((w/size)*(h/size));
  for (int i = 0; i < divw; i++){
    for (int j = 0; j < divh; j++){
      keypoints[i+j*divw] = KeyPoint(Point(i*size,j*size),size);
    }
  }
}

Point getAlign(const Mat& image, const Mat& temp, int axis){
  int w = image.size().width;
  int h = image.size().height;
  int dx,dy;
  Point p = getMirrorAxis(image, axis);
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

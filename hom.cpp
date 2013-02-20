#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <sstream>
#include <string>
#include "util.hpp"


static const int n_params = 1;

using namespace cv;
using namespace std;

#define DEBUG_WAIT 250
#define DEBUG_SHOW(x) imshow("test",(x));waitKey(DEBUG_WAIT)

void getFilename(const string &path,string &filename){
  int slapos = path.find_last_of("/");
  filename = path.substr(slapos+1, path.size()-slapos);
}

int main(int argc,char ** argv){
  if (argc < n_params+1){
    cout << "prease input parameter." << endl;
    return (-1);
  }
  string prefix(argv[1]);
  namedWindow("test");
  for (int i = 2; i < argc; i++){
    Mat img = imread(argv[i],1);
    Mat img2;
    string filename;
    getFilename(string(argv[i]),filename);
    cvtColor(img,img2, CV_RGB2GRAY);
    img2.convertTo(img2,CV_32FC1);
    GaussianBlur(img2,img2,Size(9,9),9.0/4.0);
    setGaussianWindow(img2);
    Point p = align(img2,HORIZONTAL);
    Rect r(p.x-360,p.y-240,720,720);
    ostringstream os;
    os << prefix << filename;
    string o = os.str();
    imwrite(o,img(r));
    cout << filename << " -> " << o << endl;
  }
  return(0);
}



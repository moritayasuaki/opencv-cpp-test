#include <cv.h>
#include <highgui.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <string.h>


using namespace cv;
using namespace std;

#define VERTICAL 0
#define HORIZONTAL 1

void loadFeatureFromDir(vector<Mat> &vec, char* dirname);

int main(int argc, char** argv) {
  if(argc != 3){
    cout << "argc=" << argc << endl;
    return (-1);
  }
  vector<Mat> vec;
  loadFeatureFromDir(vec,argv[1]);
  BOWKMeansTrainer bowtrainer(30);
  for (int i = 0; i < vec.size(); i++){
    bowtrainer.add(vec[i]);
  }
  cout << bowtrainer.descripotorsCount() << endl;
  Mat vocab = bowtrainer.cluster();
  FileStorage fp(argv[2],FileStorage::WRITE);
  // for (int i = 0; i < vec.size(); i++){
  // }
  fp << "vocab" << vocab;
  return (0);
}

void loadFeatureFromDir(vector<Mat> &vec, char* dirname){
  DIR* dp=opendir(dirname);
  struct dirent* dent;
  do{
    dent = readdir(dp);
    if (dent!=NULL) {
      char *ex = strstr(dent->d_name,".");
      if (strcmp(ex,".yml")==0){
        char tx[256];
        strcpy(tx,dirname);
        strcat(tx,dent->d_name);
        FileStorage fp(tx,FileStorage::READ);
        Mat m;
        fp["brief"] >> m;
        m.convertTo(m,CV_32F);
        vec.push_back(m);
      }
    }
  } while (dent != NULL); 
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



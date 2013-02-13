#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>
#include <fstream>
#include <map>
#include <ml.h>
using namespace cv;
using namespace std;


void loadTrainData(char *dirname,vector<string>& ids,vector<Mat> traino){
  ids.clear();
  vector<Mat> train;
  DIR* dp=opendir(dirname);
  struct dirent* dent;
  do{
    dent = readdir(dp);
    if (dent!=NULL) {
      char *ex = strstr(dent->d_name,"R.yml");
      if (ex!= NULL && strcmp(ex,"R.yml")==0){
        string str(dent->d_name);
        str.erase(str.find_first_of("R.yml"));

        char tx[256];
        strcpy(tx,dirname);
        strcat(tx,dent->d_name);
        FileStorage fp(tx,FileStorage::READ);
        Mat m;
        fp["hist"] >> m;
        m.convertTo(m,CV_32FC1);
        train.push_back(m);
        ids.push_back(str);
      }
    }
  } while (dent != NULL);
  // for (int i = 0; i < ids.size(); i ++ ){
    // cout << ids[i] << endl;
  // }
  traino = train;
  // cout << traino <<endl;
}


int main(int argc, char** argv) {
  if(argc != 2){
    cout << "argc=" << argc << endl;
    return (-1);
  }
  vector<Mat> train;
  vector<string> ids;
  loadTrainData(argv[1],ids,train);
  int i;
  for (i = 0; i< ids.size(); i++){
    cout << "(\"" << ids[i] << "\"" << "," << "\"" << train[i] << "\")" << endl;
  }
  return (0);
}


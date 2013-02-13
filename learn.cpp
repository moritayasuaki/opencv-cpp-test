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


void loadTrainData(char *dirname,vector<string>& ids,Mat& traino){
  ids.clear();
  Mat train;
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


void loadResponsData(char *filepath,map<string,string>& mp){
  mp.clear();
  ifstream ifs(filepath);
  string str;
  string key;
  string val;
  while(getline(ifs,str)){
    string t("");
    istringstream iss(str);
    iss >> key >> t;
    if(key != ""){
      val = t;
      mp.insert(map<string,string>::value_type(key,val));
    }
  }
  map<string,string>::iterator it = mp.begin();
  // while( it != mp.end() ){
    // cout << it->first << ":" << it->second << endl;
    // ++it;
  // }
}

float str2value(const string& str){
  if (str.find("grain") != -1){
    return 1;
  }
  else {
    return -1;
  }
}

int main(int argc, char** argv) {
  if(argc != 4){
    cout << "argc=" << argc << endl;
    return (-1);
  }
  vector<string> ids;
  map<string,string> mp;
  Mat train;
  vector<float> v;
  
  loadTrainData(argv[1],ids,train);
  loadResponsData(argv[2],mp);
  int i;
  for (i = 0; i < ids.size(); i++){
    if(mp.find(ids[i])!=mp.end()){
      v.push_back(str2value(mp[ids[i]]));
    }
    else{
      cout << "error: " << ids.size() << " " << i << " " << ids[i] << endl;
    }
  }
  Mat respons(v);
  CvSVM svm;
  train.convertTo(train,CV_32FC1);
  respons.convertTo(respons,CV_32FC1);
  // cout << train << endl;
  // cout << respons << endl;
  CvTermCriteria criteria;
  CvSVMParams params;
  CvParamGrid cgrid(20,30,1.1);
  CvParamGrid ggrid(2.0,10.0,1.1);
  criteria = cvTermCriteria(CV_TERMCRIT_EPS, 10000, 1e-8);
  params = CvSVMParams (CvSVM::C_SVC, CvSVM::RBF, /*degree*/ 0.0, /*gamma*/1.5,/*coef0*/ 0.0,/*C*/1000.0,/*nu*/0.0,/*p*/0.0,NULL,criteria);
  svm.train_auto(train,respons,Mat(),Mat(),params,5,cgrid,ggrid,CvParamGrid(),CvParamGrid());
  double positives = 0;
  double negatives = 0;
  double pmatch = 0;
  double nmatch = 0;
  for (i = 0; i< ids.size(); i++){
    if(respons.at<float>(0,i) > 0){
      positives += 1.0;
      if(respons.at<float>(0,i) * svm.predict(train.row(i)) > 0){
        pmatch += 1.0;
      }
    }
    else{
      negatives += 1.0;
      if(respons.at<float>(0,i) * svm.predict(train.row(i)) > 0){
        nmatch += 1.0;
      }
    }
  }
  svm.save(argv[3],"try1");
  cout << "p=" << pmatch/positives << ",n=" << nmatch/negatives << ",all=" << (pmatch+nmatch)/ids.size() << " " << positives/ids.size() << endl;
  return (0);
}


#ifndef __DE32F__
#define __DE32F__
#include <cv.h>

#ifdef __cplusplus
#include <limits>
namespace de32f
{
using namespace cv;
CV_EXPORTS bool initModule_feature2d();
class CV_EXPORTS DE32F : public DescriptorExtractor
{
public:
  DE32F(const Ptr<DescriptorExtractor>& descriptorExtractor);
  virtual void read(const FileNode&);
  virtual void write(FileStorage&) const;
  virtual int descriptorSize() const;
  virtual int descriptorType() const;
  virtual bool empty() const;
protected:
  virtual void computeImpl(const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors) const;
  Ptr<DescriptorExtractor> descriptorExtractor;
};
}
#endif
#endif

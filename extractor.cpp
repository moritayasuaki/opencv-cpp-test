#include <cv.h>
#include "extractor.hpp"
namespace de32f{
using namespace cv;
DE32F::DE32F(const Ptr<DescriptorExtractor>& _descriptorExtractor) :
  descriptorExtractor(_descriptorExtractor)
{
  CV_Assert( !descriptorExtractor.empty() );
}

void DE32F::computeImpl( const Mat& image, vector<KeyPoint>& keypoint, Mat& descriptors) const
{
  descriptorExtractor->compute(image, keypoint, descriptors);
  descriptors.convertTo(descriptors,CV_32F);
}

void DE32F::read( const FileNode& fn)
{
  descriptorExtractor->read(fn);
}

void DE32F::write(FileStorage& fs) const
{
  descriptorExtractor->write(fs);
}

int DE32F::descriptorSize() const
{
  return descriptorExtractor->descriptorSize();
}

int DE32F::descriptorType() const
{
  return (CV_32F);
}

bool DE32F::empty() const
{
  return descriptorExtractor.empty() || (DescriptorExtractor*)(descriptorExtractor->empty());
}
}

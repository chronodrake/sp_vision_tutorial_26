#include<opencv2/opencv.hpp>
using namespace cv;

Mat resizeandcenter(const Mat& src, int targetSize, double& scale, Point& offset);
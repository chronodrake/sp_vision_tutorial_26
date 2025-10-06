#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>
using cv::Mat;
class myCamera{
    public:
    myCamera(int & ret);
    Mat read(int & ret);
    ~myCamera();
    private:
    void * handle_;
    int ret_;

};
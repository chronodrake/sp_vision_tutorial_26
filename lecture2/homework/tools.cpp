#include<tools.hpp>
#include<opencv2/opencv.hpp>
    Mat resizeandcenter(const Mat& src, int targetSize, double& scale, Point& offset) {

    double scaleW = static_cast<double>(targetSize) / src.cols;
    double scaleH = static_cast<double>(targetSize) / src.rows;  //find Scaling ratio
    scale = std::min(scaleW, scaleH); 


    int newWidth = static_cast<int>(src.cols * scale);
    int newHeight = static_cast<int>(src.rows * scale);

    offset.x = (targetSize - newWidth) / 2;
    offset.y = (targetSize - newHeight) / 2;//find offset
    

    Mat resized;
    resize(src, resized, Size(newWidth, newHeight), 0, 0, INTER_LINEAR);

    Mat result = Mat::zeros(targetSize, targetSize, src.type());
    resized.copyTo(result(Rect(offset.x, offset.y, newWidth, newHeight)));
    
    return result;
}
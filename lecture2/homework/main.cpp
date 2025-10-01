#include<tools.hpp>
#include<fmt/core.h>
#include<fmt/format.h>

int main(){
    Mat src = imread("img.jpg");
    if (src.empty()) {
        fmt::print("Counld not read the image!");
        return -1;
    }
    
    int targetSize = 640;
    double scale;
    Point offset;
    

    Mat result = resizeandcenter(src, targetSize, scale, offset);
    

    fmt::print("Scaling ratio: {:.2f}\n", scale);
    fmt::print("Xoffset: {} pixels\nYoffset: {} pixels\n", offset.x, offset.y);
    

    imshow("original image", src);
    imshow("resize and center", result);
    waitKey(0);
    
    
    return 0;


}
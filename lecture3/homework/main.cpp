#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"
using auto_aim::YOLO;
using cv::Mat;
using auto_aim::Armor;
int main()
{
    int retvalue=0;
    // 初始化相机、yolo类
    myCamera camera(retvalue);
    YOLO yolo_detector("./configs/yolo.yaml");
    int frame_count = 0;
      if(retvalue!=0){
        std::cout<<"error!"<<std::endl;
        return -1;
        
      }
    while (1) {
        // 调用相机读取图像
    Mat img=camera.read(retvalue);
    if(retvalue!=0){
        break;
        
      }
        // 调用yolo识别装甲板
    std::list<Armor> detected_armors = yolo_detector.detect(img, frame_count);
    
        for (const auto& armor : detected_armors) {
        if (armor.points.size() == 4) {
            tools::draw_points(img,armor.points);  // 绘制红色矩形
        }
    }
        // 显示图像
     cv::resize(img, img , cv::Size(640, 480));
     cv::imshow("img", img);
     if (cv::waitKey(0) == 'q') {
            break;
         }
     }
    if(retvalue==0){

        return 0;
    }
    else{
        std::cout<<"error!"<<std::endl;
        return -1;
    }

}
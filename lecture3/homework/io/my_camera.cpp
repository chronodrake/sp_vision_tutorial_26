#include<io/my_camera.hpp>
#include<opencv2/opencv.hpp>
using cv::Mat;
cv::Mat transfer(MV_FRAME_OUT& raw)
{
    MV_CC_PIXEL_CONVERT_PARAM cvt_param;
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    cvt_param.nWidth = raw.stFrameInfo.nWidth;
    cvt_param.nHeight = raw.stFrameInfo.nHeight;

    cvt_param.pSrcData = raw.pBufAddr;
    cvt_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    cvt_param.enSrcPixelType = raw.stFrameInfo.enPixelType;

    cvt_param.pDstBuffer = img.data;
    cvt_param.nDstBufferSize = img.total() * img.elemSize();
    cvt_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    auto pixel_type = raw.stFrameInfo.enPixelType;
    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
      {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
      {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
      {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
      {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}};
    cv::cvtColor(img, img, type_map.at(pixel_type));
    
    return img;
}
myCamera::myCamera(int &ret){      

    MV_CC_DEVICE_INFO_LIST device_list;
    ret_ = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
    if (ret_ != MV_OK) {
      ret=-1;
    }
  
    if (device_list.nDeviceNum == 0) {
      ret=-1;
    }
  
    ret_ = MV_CC_CreateHandle(&handle_, device_list.pDeviceInfo[0]);
    if (ret_ != MV_OK) {
      ret=-1;
    }
  
    ret_ = MV_CC_OpenDevice(handle_);
    if (ret_ != MV_OK) {
      ret=-1;
    }
  
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", 10000);
    MV_CC_SetFloatValue(handle_, "Gain", 20);
    MV_CC_SetFrameRate(handle_, 60);
}
   
// 读取一帧图像
Mat myCamera::read(int &ret)
{ ret_ = MV_CC_StartGrabbing(handle_);
    Mat wrongimg;
    if (ret_ != MV_OK) {
      
      return wrongimg;
      ret =-1;
    }
  
    MV_FRAME_OUT raw;
    unsigned int nMsec = 100;

    ret_ = MV_CC_GetImageBuffer(handle_, &raw, nMsec);
    if (ret_ != MV_OK) {
      return wrongimg;
      ret=-1;
    }

    cv::Mat img = transfer(raw);


    ret_ = MV_CC_FreeImageBuffer(handle_, &raw);

    if (ret_ != MV_OK) {
      return wrongimg;}
      ret=-1;
    return img;
    }
   
    
                      

  myCamera::~myCamera() {
   ret_ = MV_CC_StopGrabbing(handle_);
   ret_ = MV_CC_CloseDevice(handle_);
   ret_ = MV_CC_DestroyHandle(handle_);
   handle_ =nullptr;




  }

    


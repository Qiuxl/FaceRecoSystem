//ImageNormalize类
//图像识别人脸并提供裁剪的接口
//HAAR特征检测
//暂时只检测正脸并截图
#ifndef IMAGE_NORMALIZE_H
#define IMAGE_NORMALIZE_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/contrib/contrib.hpp" 
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <exception>

//检测方式HAAR or LBP
#define HAAR_DETECT_MODE 0
#define LBP_DETECT_MODE 1

class ImageNormalize
{
private:
	//四种检测模式
	cv::CascadeClassifier face_cascade[4];
	int minNeighbor;
	double scaleFactor;
public:
	//load xml 异常
	class LoadXMLException :public std::exception
	{
	public:
		LoadXMLException() : std::exception("Init Error: xmls don't exist! ")
		{}
	};
	//默认480*640的大小
	ImageNormalize();
	//设置重复检测次数
	void SetMinNeighbor(int);
	//设置图片尺度参数
	void SetScaleFactor(double);
	//获得重复检测参数
	int GetMinNeighbor() const;
	//获得图片尺度参数
	double GetScaleFactor() const;
	//cut image based on Rect
	void CutImage(const cv::Mat &src, const cv::Rect &Rect, cv::Mat &dst);
	//detect the faces and display
	bool DetectAndDisplay(const cv::Mat &src, const int MODE = LBP_DETECT_MODE);
	//detect the faces and return as fixed size Rected-Image
	bool DetectAndExtractFace(const cv::Mat &src, std::vector<cv::Mat> &ds, const int MODE = LBP_DETECT_MODE);
	~ImageNormalize();
};
#endif
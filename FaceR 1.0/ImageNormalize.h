//ImageNormalize��
//ͼ��ʶ���������ṩ�ü��Ľӿ�
//HAAR�������
//��ʱֻ�����������ͼ
#ifndef IMAGE_NORMALIZE_H
#define IMAGE_NORMALIZE_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/contrib/contrib.hpp" 
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <exception>

//��ⷽʽHAAR or LBP
#define HAAR_DETECT_MODE 0
#define LBP_DETECT_MODE 1

class ImageNormalize
{
private:
	//���ּ��ģʽ
	cv::CascadeClassifier face_cascade[4];
	int minNeighbor;
	double scaleFactor;
public:
	//load xml �쳣
	class LoadXMLException :public std::exception
	{
	public:
		LoadXMLException() : std::exception("Init Error: xmls don't exist! ")
		{}
	};
	//Ĭ��480*640�Ĵ�С
	ImageNormalize();
	//�����ظ�������
	void SetMinNeighbor(int);
	//����ͼƬ�߶Ȳ���
	void SetScaleFactor(double);
	//����ظ�������
	int GetMinNeighbor() const;
	//���ͼƬ�߶Ȳ���
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
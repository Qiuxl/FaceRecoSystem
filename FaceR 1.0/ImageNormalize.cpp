#include"stdafx.h"
#include "ImageNormalize.h"
#include <string>
using namespace cv;
using namespace std;

ImageNormalize::ImageNormalize() :scaleFactor(1.1), minNeighbor(3)
{
	//HAAR 检测
	const string haar_cascade_name = "haarcascade_frontalface_default.xml";
	//HAAR 侧脸
	const string profile_haar_cascade_name = "haarcascade_profileface.xml";	
	//LBP 正脸
	const string lbp_cascade_name = "lbpcascade_frontalface.xml";
	//lbp 侧脸
	const string profile_lbp_cascade_name = "lbpcascade_profileface.xml";
	//load initialization
	if (!face_cascade[0].load(haar_cascade_name));
	else if (!face_cascade[1].load(profile_haar_cascade_name));
	else if (!face_cascade[2].load(lbp_cascade_name));
	else if (!face_cascade[3].load(profile_lbp_cascade_name));
	else
		return;
	throw LoadXMLException();
}

void ImageNormalize::SetMinNeighbor(int n)
{
	minNeighbor = n;
}

void ImageNormalize::SetScaleFactor(double factor)
{
	scaleFactor = factor;
}

int ImageNormalize::GetMinNeighbor() const
{
	return minNeighbor;
}

double ImageNormalize::GetScaleFactor() const
{
	return scaleFactor;
}

//根据矩形区域截图
void ImageNormalize::CutImage(const Mat &src, const Rect &Rect, Mat &dst)
{
	Mat Image_Cutted(src, Rect);
	dst = Image_Cutted.clone();
}

//检测人脸并显示
bool ImageNormalize::DetectAndDisplay(const Mat &src, const int MODE)
{
	vector<Rect> faces, profiles;
	Mat src_gray, src_copy;
	int FaceCascadeIndex, ProfileCascadeIndex;
	//根据MODE设置不同的级联检测器
	switch (MODE)
	{
	case(HAAR_DETECT_MODE):
	{
		FaceCascadeIndex = 0;
		ProfileCascadeIndex = 1;
		break;
	}
	case(LBP_DETECT_MODE) :
	{
		FaceCascadeIndex = 2;
		ProfileCascadeIndex = 3;
		break;
	}
	default:
		break;
	}
	//转化为灰度图
	if (src.empty())
		return false;
	else if (src.channels() > 1)
		cvtColor(src, src_gray, CV_BGR2GRAY);
	else
		src_gray = src;	
	//灰度图归一化
	equalizeHist(src_gray, src_gray);
	src_copy = src;
	//正脸检测并绘图
	face_cascade[FaceCascadeIndex].detectMultiScale(src_gray, faces, scaleFactor, minNeighbor, 0, Size(30, 30));
	for (vector<Rect>::iterator it = faces.begin(); it != faces.end(); it++)
		rectangle(src_copy, *it, Scalar(255, 0, 0), 2, 8, 0);
	//侧脸检测并绘图
	face_cascade[ProfileCascadeIndex].detectMultiScale(src_gray, profiles, scaleFactor, minNeighbor, 0, Size(30, 30));
	for (vector<Rect>::iterator it = profiles.begin(); it != profiles.end(); it++)
		rectangle(src_copy, *it, Scalar(255, 0, 0), 2, 8, 0);
	//新窗口显示
	imshow("FACE", src_copy);
	return true;
}

bool ImageNormalize::DetectAndExtractFace(const Mat &src, vector<Mat> &dst, const int MODE)
{
	vector<Rect> faces, profiles;
	Mat src_gray, src_copy;
	int FaceCascadeIndex, ProfileCascadeIndex;
	//根据MODE设置不同的检测器
	switch (MODE)
	{
	case(HAAR_DETECT_MODE) :
	{
		FaceCascadeIndex = 0;
		ProfileCascadeIndex = 1;
		break;
	}
	case(LBP_DETECT_MODE) :
	{
		FaceCascadeIndex = 2;
		ProfileCascadeIndex = 3;
		break;
	}
	default:
		break;
	}
	//转化为灰度图
	if (src.empty())
		return false;
	else if (src.channels() > 1)
		cvtColor(src, src_gray, CV_BGR2GRAY);
	else
		src_gray = src;
	//灰度图归一化
	equalizeHist(src_gray, src_gray);
	//接口：void CascadeClassifier::detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())
	//检测
	face_cascade[FaceCascadeIndex].detectMultiScale(src_gray, faces, scaleFactor, minNeighbor, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
	face_cascade[ProfileCascadeIndex].detectMultiScale(src_gray, profiles, scaleFactor, minNeighbor, 0 | CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
	//根据得到的rect截图
	for (vector<Rect>::iterator it = faces.begin(); it != faces.end(); it++)
	{
		Mat SingleFace;
		CutImage(src_gray, *it, SingleFace);
		dst.push_back(SingleFace);
	}
	//侧脸截图
	for (vector<Rect>::iterator it = profiles.begin(); it != profiles.end(); it++)
	{
		Mat SingleFace;
		CutImage(src_gray, *it, SingleFace);
		dst.push_back(SingleFace);
	}
	return true;
}

ImageNormalize::~ImageNormalize()
{
}
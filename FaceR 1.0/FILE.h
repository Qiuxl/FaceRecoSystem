#ifndef _FILE_h_
#define _FILE_h_
#include <string>
#include <memory>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
struct personalInfo
{
	std::string name;
	std::string sid;
	int num_spic;
	int num_epic;
	std::string perDir;
};
class FileManager
{
private:
	std::vector <std::string> pids;
	char* imageBuffer;
	bool makeDir(std::string Dir);												//判断文件目录的存在情况，不存在则创建新的目录
	bool generateSourceCSV(personalInfo &stuInfo, std::vector<std::string> filetypes);//根据学生信息生成源文件的 CSV 文件
	bool generateEgiFaceCSV(personalInfo &stuInfo, std::string filetype);		//根据学生信息生成处理后的 CSV 文件
public:
	FileManager();
	~FileManager();
	bool initial(void);																//FileManager 的初始化程序
	bool close(void);																//FileManager 的关闭程序
	bool writeInfo(personalInfo &stuInfo);											//将相关的信息写入对应的文件中
	bool transferImage(std::string &sourceFile, std::string &targetFile);			//根据路径复制文件
	bool getStuinfo(personalInfo &stuInfo, std::string &sid);						//根据学号将相关的信息读取到 stuInfo 中
	bool loadImages(personalInfo &stuInfo, std::vector<std::string> fileRoutes);	//支持多文件传输，需要传入路径以及学生信息
	void getSourcesCsvRoute(std::string &sourceCSVRoute, personalInfo &stuInfo);	//根据学生信息读取 CSV 路径
	void getEgiFaceCsvRoute(std::string &egifacesCSVRoute, personalInfo &stuInfo);	//根据学生信息读取 CSV 路劲
	bool getPersonIndex(std::vector<std::string> &personIDs);						//将现有的学生学号返回
	bool writeMATtoSource(personalInfo &stuInfo, cv::Mat &source);					//根据学生信息存储用摄像头拍下来的照片
	bool writeMATtoEgiFace(personalInfo &stuInfo, cv::Mat &egiface);				//根据学生信息存储处理后的图片
	//bool loadImages_test(std::vector<std::string> fileRoutes);
};
#endif

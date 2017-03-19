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
	bool makeDir(std::string Dir);												//�ж��ļ�Ŀ¼�Ĵ���������������򴴽��µ�Ŀ¼
	bool generateSourceCSV(personalInfo &stuInfo, std::vector<std::string> filetypes);//����ѧ����Ϣ����Դ�ļ��� CSV �ļ�
	bool generateEgiFaceCSV(personalInfo &stuInfo, std::string filetype);		//����ѧ����Ϣ���ɴ����� CSV �ļ�
public:
	FileManager();
	~FileManager();
	bool initial(void);																//FileManager �ĳ�ʼ������
	bool close(void);																//FileManager �Ĺرճ���
	bool writeInfo(personalInfo &stuInfo);											//����ص���Ϣд���Ӧ���ļ���
	bool transferImage(std::string &sourceFile, std::string &targetFile);			//����·�������ļ�
	bool getStuinfo(personalInfo &stuInfo, std::string &sid);						//����ѧ�Ž���ص���Ϣ��ȡ�� stuInfo ��
	bool loadImages(personalInfo &stuInfo, std::vector<std::string> fileRoutes);	//֧�ֶ��ļ����䣬��Ҫ����·���Լ�ѧ����Ϣ
	void getSourcesCsvRoute(std::string &sourceCSVRoute, personalInfo &stuInfo);	//����ѧ����Ϣ��ȡ CSV ·��
	void getEgiFaceCsvRoute(std::string &egifacesCSVRoute, personalInfo &stuInfo);	//����ѧ����Ϣ��ȡ CSV ·��
	bool getPersonIndex(std::vector<std::string> &personIDs);						//�����е�ѧ��ѧ�ŷ���
	bool writeMATtoSource(personalInfo &stuInfo, cv::Mat &source);					//����ѧ����Ϣ�洢������ͷ����������Ƭ
	bool writeMATtoEgiFace(personalInfo &stuInfo, cv::Mat &egiface);				//����ѧ����Ϣ�洢������ͼƬ
	//bool loadImages_test(std::vector<std::string> fileRoutes);
};
#endif

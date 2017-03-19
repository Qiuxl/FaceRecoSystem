#ifndef _MODELE_H_
#define _MODELE_H_


#pragma once

#include<string>
#include<vector>
#include<memory>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include"../../ImageNormalize.h"
#include"../common/commandparameter.h"
//this class is for trained
#define TRAIN_WITH_FEA 1
#define TRAIN_WITH_LBP 0
#define PREDICT_LBP_ID 0
#define PREDICT_FEA_ID 1
#define PREDICT_FEA_NO_ID 2
#define PREDICT_LBP_NO_ID 3
class train
{
public:
	train(){}
	void set(std::shared_ptr<person> &p);
	void Train(int mode);   // 0表示用lbp方法训练,1表示特征脸方式
protected:
	void train_with_fea();
	void train_with_lbp();
	friend static void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, std::vector<std::string>&path_store, char separator = ';');
	//void Resize_with_ratio(double fScale, string Inpath, string Outpath);
	void Resize_with_square(double px, double py, std::string Inpath, std::string Outpath);

private:
	std::shared_ptr<person> ptr;
	cv::Ptr<cv::FaceRecognizer> model;  //可以用不同算法的模型
};

class predict
{
public:
	predict(){}
	void set_mat(std::shared_ptr<cv::Mat> &p);
	void set_pointer(std::shared_ptr<one_photo> &p);
	bool is_person_in(int mode); // 0 1分别表示遍历整个库用lbp和特征方式预测，2 3分别表示只用一个文件夹进行预测，分别对应特征和lbp
	void get_result(cv::Mat &out);   //if user in database，give the first photo he took
	friend void RgbToGray(std::vector<cv::Mat>&,std::vector<cv::Mat>&);
	friend cv::Mat RgbToGray(cv::Mat &in);
	friend static void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, std::vector<std::string>&path_store, char separator);
protected:
	int predict_with_fea(std::vector<std::string> &per_id, cv::Mat &face);
	int predict_with_lbp(std::vector<std::string> &per_id, cv::Mat &face);
	int predict_with_fea(cv::Mat &);
	int predict_with_lbp(cv::Mat &);
	void set_threshold(double num);  //设置阈值
	void resize_with_square(double px, double py, cv::Mat &in, cv::Mat &out);
private:
	std::shared_ptr<cv::Mat> ptr;
	int predicted_lable;
	std::shared_ptr<one_photo> photo;
	cv::Ptr<cv::FaceRecognizer> model;  //可以用不同算法的模型
};

class face_check{
public:
	face_check();
	~face_check();
	void set(cv::Mat &temp);
	bool check_id_exist(std::string &id);
	void set_pointer(std::shared_ptr<one_photo> &p);
	bool is_face_exit_fea();
	bool is_face_exit();  //判断图片中是否有人脸存在，true if exits，else false
	cv::Mat get_image_dealed();  // 获取处理后的image
	friend void RgbToGray(std::vector<cv::Mat>&, std::vector<cv::Mat>&);
	friend cv::Mat RgbToGray(cv::Mat &in);
private:
	ImageNormalize *con;
	cv::Mat image;
	bool status;
	std::vector<cv::Mat> result;
	std::shared_ptr<one_photo> sptr;
};
#endif // !_MODELE_H_
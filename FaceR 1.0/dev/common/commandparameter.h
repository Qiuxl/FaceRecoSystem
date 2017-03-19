#pragma once
#include "../common/common.h"
#include<opencv2\highgui\highgui.hpp>
class person:public ICommandParameter //拍照完成按钮，就是入库按钮用到的数据
{
public:
	person(){};
	~person();
	void set_id(std::string &);
	void set_path(std::string &);
	std::string get_id() const;
	std::string get_path() const;
private:
	std::string id;
	std::string csv_path;
};

class one_photo :public ICommandParameter  //拍照按钮用到的数据,登陆也是这个参数类
{
public:
	~one_photo();
	void set_id(std::string &tmp_id);
	void set_image(cv::Mat &tmp_image);
	std::string get_id();
	cv::Mat get_image();
private:
	std::string id;
	cv::Mat image;
};
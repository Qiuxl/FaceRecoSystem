#include"stdafx.h"
#include"dev\common\commandparameter.h"
/*
	��person��ĳ�ʼ��
*/
person::~person()
{

}
void person::set_id(std::string &str)
{
	id = str;
}
void person::set_path(std::string &str)
{
	csv_path = str;
}


std::string person::get_id() const
{
	return id;
}

std::string person::get_path() const
{
	return csv_path;
}

/*
����one photo��ĳ�ʼ��
*/

void one_photo::set_id(std::string &tmp_id)
{
	id = tmp_id;
}
void one_photo::set_image(cv::Mat &tmp_image)
{
	image = tmp_image;
}
std::string one_photo::get_id()
{
	return id;
}
cv::Mat one_photo::get_image()
{
	return image;
}
one_photo::~one_photo()
{

}

/***************************

**************************/
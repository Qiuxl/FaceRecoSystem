#include"stdafx.h"
#include<fstream>
#include"FILE.h"
#include"dev\model\model.h"
#define length_1 400
#define width_1 300
#define fea_threshold_value 60
#define lbp_threshold_value 60
using namespace std;
using namespace cv;
bool face_check::check_id_exist(string &id)
{
	FileManager managefile;
	personalInfo temp;
	managefile.initial();
	return managefile.getStuinfo(temp, id);
}
face_check::face_check()
{
	con = new ImageNormalize();
}
bool face_check::is_face_exit()
{
	result.clear();
	except temp1;
	string error_message;
	con->DetectAndExtractFace(image, result,HAAR_DETECT_MODE);
	if (result.size() == 0)
	{
		return false;
	}
	FileManager managefile;
	personalInfo temp;
	managefile.initial();
	//if (status == 0 && managefile.getStuinfo(temp, sptr->get_id()))
	//{
	//	error_message = "id exits,please choose another id";
	//	temp1.set(error_message);
	//	throw(temp1);
	//}
	if (!managefile.getStuinfo(temp, sptr->get_id()))
	{
		status = 1;
		temp.name = "aaa";
		temp.sid = sptr->get_id();
		managefile.writeInfo(temp);
	}
	managefile.writeMATtoSource(temp, sptr->get_image());
	managefile.writeMATtoEgiFace(temp, result[0]);
	managefile.close();
	//for (int i = 0; i < result.size(); i++)
	//{
	//	imshow("灰度图",result[i]);
	//	cv::waitKey(0);
	//}
	// 这里需要将原来的跟处理后的照片存起来
	return true;
}
bool face_check::is_face_exit_fea()
{
	con->DetectAndExtractFace(image, result, HAAR_DETECT_MODE);
	if (result.size() == 0)
	{
		return false;
	}
	return true;
}
void face_check::set(Mat &temp)
{
	image = temp;
}
Mat face_check::get_image_dealed()
{
	Mat temp;
	if (result.size() == 0)
	{
		return temp;
	}
	else
	{
		return result[0];
	}
}
void face_check::set_pointer(std::shared_ptr<one_photo> &p)
{
	sptr = p;
	image = p->get_image();
}
face_check::~face_check()
{

}
/************************************
definition of train class

**************************************/
Mat RgbToGray(cv::Mat &in)
{
	Mat dest;
	cvtColor(in, dest, CV_RGB2GRAY, 0);
	return dest;
}
void RgbToGray(std::vector<cv::Mat>&in, vector<cv::Mat>&out)
{
	for (int i = 0; i < in.size(); i++)
	{
		Mat source = in[i];
		Mat dest;
		cvtColor(source, dest, CV_RGB2GRAY, 0);
		out.push_back(dest);
		//		imshow("灰度图",dest);
		//		waitKey(0);
	}
}
void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, vector<string>&path_store, char separator)
{
	ifstream file(filename, ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		except temp;
		temp.set(error_message);
		throw(temp);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
			path_store.push_back(path);
			cout << path << endl;
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

void train::Resize_with_square(double px, double py, string Inpath, string Outpath)
{
	CvSize czSize;              //目标图像尺寸  
	//从文件中读取图像    
	IplImage *pSrcImage = cvLoadImage(Inpath.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;
	//计算目标图像大小  
	czSize.width = px;
	czSize.height = py;
	//创建图像并缩放  
	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_AREA);
	//保存图片  
	cvSaveImage(Outpath.c_str(), pDstImage);
}

void train::train_with_fea()
{
	except temp;
	string error_message;
	string csv_path;
	vector<Mat> out_images;
	if (ptr == NULL)
	{
		error_message = "no images to train!";
		temp.set(error_message);
		throw(temp);
	}
	csv_path = "user\\" + ptr->get_id() + "\\sources\\" + "source.csv";
	ptr->set_path(csv_path);
	vector<Mat> images;
	vector<int> labels;
	vector<string>path_1, target;  //一个用来存放原始的路径，另一个用来存放改写成bmp后的路径
	model = createEigenFaceRecognizer();
	read_csv(ptr->get_path(), images, labels, path_1);

	if (labels.size() <= 1) {
		error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		temp.set(error_message);
		throw(temp);
	}
	for (int i = 0; i < path_1.size(); i++)
	{
		int index;
		index = path_1[i].rfind(".");
		string temp;
		temp.assign(path_1[i], 0, index + 1);
		temp += "bmp";
		target.push_back(temp);
	}

	images.clear();

	for (int i = 0; i < labels.size(); i++)
	{
		Resize_with_square(width_1, length_1, path_1[i], target[i]);
		Mat tmp_mat;
		tmp_mat = imread(target[i]);
		images.push_back(tmp_mat);
	}
	RgbToGray(images, out_images);
	string temp_path = "user\\" + ptr->get_id() + "\\sources\\" + ptr->get_id() + "_1.xml";
	model->train(out_images, labels);
	model->save(temp_path);
}

void train::train_with_lbp()
{
	vector<Mat> images;
	vector<int> labels;
	except temp;
	string error_message, csv_path;
	vector<string>path_1, target;  //一个用来存放原始的路径，另一个用来存放改写成bmp后的路径
	vector<Mat> out_images;
	if (ptr == NULL){
		error_message = "no images to train,share pointer is null";
		temp.set(error_message);
		throw(temp);
	}

	csv_path = "user\\" + ptr->get_id() + "\\egifaces\\" + "egi.csv";
	ptr->set_path(csv_path);
	model = createLBPHFaceRecognizer();
	read_csv(ptr->get_path(), images, labels, path_1);
	if (labels.size() <= 1) {
		error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		temp.set(error_message);
		throw(temp);
	}
	//RgbToGray(images, out_images);
	string temp_path = "user\\" + ptr->get_id() + "\\egifaces\\" + ptr->get_id() + ".xml";
	//model->train(out_images, labels);
	model->train(images, labels);
	model->save(temp_path);
}

void train::Train(int mode)
{
	except temp;
	string error_message;
	if (mode == 0)
	{
		train_with_lbp();
	}
	else if (mode == 1)
	{
		train_with_fea();
	}
	else
	{
		error_message = "the train mode you chose is wrong!";
		temp.set(error_message);
		throw(temp);
	}
}

void train::set(std::shared_ptr<person> &p)
{
	ptr = p;
}
/*************************
definition of class predict

****************************/
void predict::set_threshold(double num)
{
	if (model == NULL)
		return;
	else{
		model->set("threshold", num);
	}
}
void  predict::resize_with_square(double px, double py, Mat &in, Mat &out)
{
	if (in.empty())
	{
		return;
	}
	CvSize czSize;              //目标图像尺寸  
	IplImage imgTmp = in;
	IplImage *pSrcImage = cvCloneImage(&imgTmp);
	//从文件中读取图像    
	//IplImage *pSrcImage = cvLoadImage(Inpath.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	IplImage *pDstImage = NULL;
	//计算目标图像大小  
	czSize.width = px;
	czSize.height = py;
	//创建图像并缩放  
	pDstImage = cvCreateImage(czSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDstImage, CV_INTER_AREA);
	Mat temp(pDstImage, true);
	out = temp;
}

bool predict::is_person_in(int mode)
{

	except temp;
	string error_message;
	vector<string>id;
	FileManager file;
	file.initial();
	Mat face;
	if (mode != 0 && mode != 1 && mode != 2 && mode != 3)
	{
		error_message = "the train mode you chose is wrong!";
		temp.set(error_message);
		throw(temp);
	}

	if (!file.getPersonIndex(id))
	{
		return false;
	}
	if (id.size() == 0)
	{
		error_message = "no data in database! please add user first";
		temp.set(error_message);
		throw(temp);
	}
	face_check temp_check;
	temp_check.set(photo->get_image());
	if (!temp_check.is_face_exit_fea())
	{
		error_message = "the photo you want to login with has no face!!";
		temp.set(error_message);
		throw(temp);
	}
	face = temp_check.get_image_dealed();
	if (mode == 0)
	{
		predicted_lable = predict_with_lbp(id, face);
	}
	else if (mode == 1)
	{
		predicted_lable = predict_with_fea(id, face);
	}
	else if (mode == 2)
	{
		face = photo->get_image();
		predicted_lable = predict_with_fea(face);
	}
	else if (mode == 3)
	{
		predicted_lable = predict_with_lbp(face);
	}
	if (predicted_lable < 0)
		return false;
	return true;
}
int predict::predict_with_fea(cv::Mat &face)
{
	Mat out_face, out_1;
	string xml_path;
	int final_label = -1;
	double com = 0.0;
	cv::Ptr<cv::FaceRecognizer> model_1;
	if (photo == NULL)
	{
		return final_label;
	}
	resize_with_square(width_1, length_1, face, out_face);
	xml_path = "user\\" + photo->get_id() + "\\sources\\" + photo->get_id() + "_1.xml";
	fstream fin(xml_path, ios::in);
	//if (!fin.is_open())   //文件不存在，根本不存在这个人
	//{
	//	return final_label;
	//}
	//fin.close();
	model = createEigenFaceRecognizer(0,(double)fea_threshold_value);
	//model_1 = createEigenFaceRecognizer(0, (double)fea_threshold_value);
	//set_threshold(fea_threshold_value);
	model->load(xml_path);
//	model_1->load("140100784-1.xml");
	predicted_lable = -1;
	out_1=RgbToGray(out_face);
	//imshow("hhh", out_1);
	//waitKey(0);
	model->predict(out_1, predicted_lable, com);
	fstream fout("result.txt", ios::out | ios::app);
	fout << com << endl;
	fout.close();
	return predicted_lable;
}
int predict::predict_with_fea(vector<string> &per_id, Mat &face)
{
	Mat out_face;
	string xml_path;
	resize_with_square(width_1, length_1, face, out_face);
	double confidience = 1e10;
	int final_label = -1;
	double com = 0.0;
	predicted_lable = -1;
	model = createEigenFaceRecognizer();
	set_threshold(fea_threshold_value);
	for (int i = 0; i < per_id.size(); i++)
	{
		xml_path = "user\\" + per_id[i] + "\\sources\\" + per_id[i] + "-1.xml";
		model->load(xml_path);
		model->predict(out_face, predicted_lable, com);
		if (com < confidience)
		{
			confidience = com;
			final_label = predicted_lable;
		}
	}
	return final_label;
}
int predict::predict_with_lbp(vector<string> &per_id, Mat &face)
{
	Mat out_face;
	string xml_path;
	double confidience = 1e10;
	int final_label = -1;
	double com = 0.0;
	predicted_lable = -1;
	model = createLBPHFaceRecognizer();
	set_threshold(lbp_threshold_value);
	for (int i = 0; i < per_id.size(); i++)
	{
		xml_path = "user\\" + per_id[i] + "\\sources\\" + per_id[i] + ".xml";
		model->load(xml_path);
		model->predict(out_face, predicted_lable, com);
		if (com < confidience)
		{
			confidience = com;
			final_label = predicted_lable;
		}
	}
	return final_label;
}
int predict::predict_with_lbp(cv::Mat &face)
{
	Mat out_face;
	string xml_path;
	double confidience = 1e10;
	int final_label = -1;
	double com = 0.0;
	if (photo == NULL)
	{
		return final_label;
	}
	model = createLBPHFaceRecognizer(0,(double)lbp_threshold_value);
	set_threshold(lbp_threshold_value);
	xml_path = "user\\" + photo->get_id() + "\\egifaces\\" + photo->get_id() + ".xml";
	fstream fin(xml_path, ios::in);
	if (!fin.is_open())   //文件不存在，根本不存在这个人
	{
		return final_label;
	}
	fin.close();
	model->load(xml_path);
	model->predict(face, final_label, com);
	fstream fout("result.txt", ios::out | ios::app);
	fout << com << endl;
	fout.close();
	return final_label;
}
void predict::get_result(Mat &out)
{
	except temp;
	string error_message;
	if (predicted_lable < 0)
	{
		error_message = "user not exist!";
		temp.set(error_message);
		throw(temp);
	}
	stringstream sstr;
	string line, first_path;
	sstr << predicted_lable;
	string csv_path = "user\\" + sstr.str() + "\\sources\\source.csv";
	fstream fin(csv_path, ios::in);
	getline(fin, line);
	stringstream liness(line);
	getline(liness, first_path, ';');
	out = imread(first_path);
	if (out.empty())
	{
		error_message = "no images corresponding to the label, please check the given label";
		temp.set(error_message);
		throw(temp);
	}
}
void predict::set_mat(std::shared_ptr<cv::Mat> &p)
{
	ptr = p;
}
void predict::set_pointer(std::shared_ptr<one_photo> &p)
{
	photo = p;
}
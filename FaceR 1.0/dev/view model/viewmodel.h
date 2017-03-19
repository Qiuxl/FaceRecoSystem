#pragma once
#include <vector>
#include "../model/model.h"
#include "command/PhoCommand.h"    
#include "command/RegisterCommand.h"
#include "command/FinishCommand.h"
#include "command/logincommand.h"
class FaceRViewModel : public Proxy_Notification	
{
public:
	FaceRViewModel()
	{
		//让空指针指向实体,用make_shared创建对象，将logincmd赋值
		
		auto p = std::make_shared<LoginCommand<FaceRViewModel>>(this);
		auto pho = std::make_shared<PhoCommand<FaceRViewModel>>(this);
		auto fin = std::make_shared<FinishCommand<FaceRViewModel>>(this);
		logincmd = p;
		phocmd = pho;
		finishcmd = fin;
	}
	//暴露属性
	void set_Infomation(const std::string& ss)
	{
		m_infomation = ss;
	}
	const std::string& get_Information()const throw()
	{
		return m_infomation;
	}
	std::shared_ptr<std::string> get_InformationRef() throw()
	{
		return std::shared_ptr<std::string>(&m_infomation);
	}
	/*
	void set_photo_num(const int& i)
	{
		photo_num = i;
	}
	const int& get_photo_num()const throw()
	{
		return photo_num;
	}
	std::shared_ptr<int> get_photo_num_Ref() throw()
	{
		return std::shared_ptr<int>(&photo_num);
	}
	*/
	//触发通知
	bool Pho(std::string id, cv::Mat image)
	{
		std::shared_ptr <one_photo> ptr(new one_photo());
		ptr->set_id(id);
		ptr->set_image(image);
		m_PhotoModel->set_pointer(ptr);//传递变量，变量从具体cmd.h中来
		bool Phoresult = false;//触发通知
		try {
			Fire_OnPropertyChange(std::string("sample begin"));
			Phoresult = m_PhotoModel->is_face_exit();
			Fire_OnPropertyChange(std::string("sample end"));
			/*
			if (Phoresult)
				set_Infomation("PhoSuccess");
			else
				set_Infomation("PhoFail");
				*/
		}
		catch (except &e)
		{
			Fire_OnExcept(e.get());
		}
		
		return Phoresult;
	}
	bool Login(std::string id, cv::Mat image)
	{
		std::shared_ptr <one_photo> ptr(new one_photo());
		ptr->set_id(id);
		ptr->set_image(image);
		m_LoginModel->set_pointer(ptr);
		bool Loginresult = 0;
		try {
			Fire_OnPropertyChange(std::string("login begin"));
			Loginresult = m_LoginModel->is_person_in(PREDICT_LBP_NO_ID);
			Fire_OnPropertyChange(std::string("login end"));
			cv::Mat temp;
			m_LoginModel->get_result(temp);
			cv::imshow("登陆结果", temp);
			/*
			if (Loginresult)
				set_Infomation("LoginSuccess");
			else
				set_Infomation("LoginFail");
				*/
		}
		catch (except &e)
		{
			Fire_OnExcept(e.get());
		}
		return Loginresult;
		
	}
/*
	bool Register()
	{
		//..
		bool registerresult = m_PhotoModel->set_path();
		Fire_OnPropertyChange(std::string("Information"));
		return registerresult;
	}
*/
	//暴露cmd
	bool Finish(std::string id)
	{
		std::shared_ptr <person> ptr(new person());
		ptr->set_id(id);
		m_FinishModel->set(ptr);
		bool Finishresult = false;
		try {
			m_FinishModel->Train(TRAIN_WITH_LBP);
			Finishresult = true;
		}
		catch (except &e)
		{
			Fire_OnExcept(e.get());
		}
		
		//Fire_OnPropertyChange(std::string("Information"));
		return Finishresult;
	}
	std::shared_ptr<myICommand> get_PhoCommandRef()
	{
		return std::static_pointer_cast<myICommand>(phocmd);
	}
	std::shared_ptr<myICommand> get_LoginCommandRef()
	{
		//std::shared_ptr<ICommand> p;
		return std::static_pointer_cast<myICommand>(logincmd);//类型转换
	}
	std::shared_ptr<myICommand> get_FinishCommandRef()
	{
		return std::static_pointer_cast<myICommand>(finishcmd);
	}
	/*std::shared_ptr<myICommand> get_RegisterCommandRef()
	{
		return std::static_pointer_cast<myICommand>(registercmd);
	}*/
	void set_face_checkRef(const std::shared_ptr<face_check>& fc)
	{
		m_PhotoModel = fc;
	}
	face_check& get_face_check() throw()
	{
		return *m_PhotoModel;
	}
	void set_predict_Ref(const std::shared_ptr<predict>& p)
	{
		m_LoginModel = p;
	}
	predict& get_face_checkRef() throw()
	{
		return *m_LoginModel;
	}
	void set_trainRef(const std::shared_ptr<train>& t)
	{
		m_FinishModel = t;
	}
	train& get_train() throw()
	{
		return *m_FinishModel;
	}
private:
	//创建shared_ptr，暴露出去
	std::string m_infomation;
	int photo_num;
	std::shared_ptr<face_check/*model中的类*/> m_PhotoModel;//采样拍照
	std::shared_ptr<predict> m_LoginModel;
	std::shared_ptr<train> m_FinishModel;
	//暴露cmd
	std::shared_ptr<LoginCommand<FaceRViewModel>> logincmd;//空指针
	//std::shared_ptr<RegisterCommand<FaceRViewModel>> registercmd;
	std::shared_ptr<PhoCommand<FaceRViewModel>> phocmd;
	std::shared_ptr<FinishCommand<FaceRViewModel>> finishcmd;
	//LoginCommand<FaceRViewModel> t_logincmd;
	//PhoCommand<FaceRViewModel> 
};

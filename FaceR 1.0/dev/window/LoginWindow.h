#pragma once
#include "../common/commandparameter.h"
#include "LoginWindowSink.h"

template <typename T>
class LoginWindow : public LoginWindowSink<T>
{
private:
	std::shared_ptr<myICommand> m_cmdLogin;
public:
	virtual void InitUI() throw()
	{

	}
	//登录command设置
	void SetLoginCommand(const std::shared_ptr<myICommand> &cmd) throw()
	{
		m_cmdLogin = cmd;
	}
	//login
	//每隔1s(?)执行一次
	void CallSampleCommand(std::string id, cv::Mat &image) throw()
	{
		one_photo param;
		param.set_id(id);
		param.set_image(image);
		m_cmdLogin->SetParameter(std::make_shared<one_photo>(param));
		m_cmdLogin->Exec();
	}
};
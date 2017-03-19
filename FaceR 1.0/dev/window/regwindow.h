
#pragma once

#include "../common/commandparameter.h"
#include "regwindowsink.h"

template <typename T>
class RegWindow : public RegWindowSink<T>
{
private:
	//采样(sample)的command
	std::shared_ptr<myICommand> m_cmdSample;
	//完成注册的command
	std::shared_ptr<myICommand> m_cmdRegEnd;
public:
	virtual void InitUI() throw()
	{
	}
	//采样command设置
	void SetSampleCommand(const std::shared_ptr<myICommand>& cmd) throw()
	{
		m_cmdSample = cmd;
	}
	//采样
	void CallSampleCommand(std::string &id, cv::Mat &image ) throw()
	{
		one_photo param;
		param.set_id(id);
		param.set_image(image);
		m_cmdSample->SetParameter(std::make_shared<one_photo>(param));
		m_cmdSample->Exec();
	}
	//完成注册command设置
	void SetRegEndCommand(const std::shared_ptr<myICommand>& cmd) throw()
	{
		m_cmdRegEnd = cmd;
	}
	//完成注册
	void CallRegEndCommand(std::string &id, std::string name)
	{
		person param;
		param.set_id(id);
		m_cmdRegEnd->SetParameter(std::make_shared<person>(param));
		m_cmdRegEnd->Exec();
	}
};



#pragma once

#include "../common/commandparameter.h"
#include "regwindowsink.h"

template <typename T>
class RegWindow : public RegWindowSink<T>
{
private:
	//����(sample)��command
	std::shared_ptr<myICommand> m_cmdSample;
	//���ע���command
	std::shared_ptr<myICommand> m_cmdRegEnd;
public:
	virtual void InitUI() throw()
	{
	}
	//����command����
	void SetSampleCommand(const std::shared_ptr<myICommand>& cmd) throw()
	{
		m_cmdSample = cmd;
	}
	//����
	void CallSampleCommand(std::string &id, cv::Mat &image ) throw()
	{
		one_photo param;
		param.set_id(id);
		param.set_image(image);
		m_cmdSample->SetParameter(std::make_shared<one_photo>(param));
		m_cmdSample->Exec();
	}
	//���ע��command����
	void SetRegEndCommand(const std::shared_ptr<myICommand>& cmd) throw()
	{
		m_cmdRegEnd = cmd;
	}
	//���ע��
	void CallRegEndCommand(std::string &id, std::string name)
	{
		person param;
		param.set_id(id);
		m_cmdRegEnd->SetParameter(std::make_shared<person>(param));
		m_cmdRegEnd->Exec();
	}
};


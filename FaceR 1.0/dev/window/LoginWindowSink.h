#pragma once
#include "../common/common.h"

template<typename T>
class LoginWindowSink : public INotification
{
public:
	//提供生成shared_ptr的接口
	std::shared_ptr<INotification> get_notification() throw()
	{
		return std::shared_ptr<INotification>(static_cast<INotification *>(this));
	}

	//正在登录
	virtual void OnPropertyChange(const std::string &str)
	{
		//auto pT(std::make_unique<T>((static_cast<T *>) (this)));
		if (str == "login begin")
		{
			//提示 "第几次采样"
			
		}
		else if(str == "login end")
		{
			//登录结束消除提示信息
		}
	}

	//登录是否成功
	virtual void OnCommandComplete(const std::string &str, bool bResult)
	{
		if (str == "Login")
		{
			T* pT = static_cast<T*>(this);
			if (bResult)
			{
				//MessageBoxW(NULL, TEXT("登录成功"), TEXT("INFORMATION!"), MB_OK);
				pT->set_Login_status(true);
			}
			else
			{
				//MessageBoxW(NULL, TEXT("登录失败"), TEXT("INFORMATION!"), MB_OK);
				//尝试次数减一
				pT->decrease_TryNum();
			}
		}
	}

	virtual void OnExcept(const std::string& str)
	{}
};
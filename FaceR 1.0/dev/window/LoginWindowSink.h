#pragma once
#include "../common/common.h"

template<typename T>
class LoginWindowSink : public INotification
{
public:
	//�ṩ����shared_ptr�Ľӿ�
	std::shared_ptr<INotification> get_notification() throw()
	{
		return std::shared_ptr<INotification>(static_cast<INotification *>(this));
	}

	//���ڵ�¼
	virtual void OnPropertyChange(const std::string &str)
	{
		//auto pT(std::make_unique<T>((static_cast<T *>) (this)));
		if (str == "login begin")
		{
			//��ʾ "�ڼ��β���"
			
		}
		else if(str == "login end")
		{
			//��¼����������ʾ��Ϣ
		}
	}

	//��¼�Ƿ�ɹ�
	virtual void OnCommandComplete(const std::string &str, bool bResult)
	{
		if (str == "Login")
		{
			T* pT = static_cast<T*>(this);
			if (bResult)
			{
				//MessageBoxW(NULL, TEXT("��¼�ɹ�"), TEXT("INFORMATION!"), MB_OK);
				pT->set_Login_status(true);
			}
			else
			{
				//MessageBoxW(NULL, TEXT("��¼ʧ��"), TEXT("INFORMATION!"), MB_OK);
				//���Դ�����һ
				pT->decrease_TryNum();
			}
		}
	}

	virtual void OnExcept(const std::string& str)
	{}
};
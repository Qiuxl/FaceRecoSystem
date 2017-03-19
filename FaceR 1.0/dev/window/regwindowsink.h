#ifndef _REGISTER_WINDOW_SINK_H
#define _REGISTER_WINDOW_SINK_H
#include "../common/common.h"

template<typename T>
class RegWindowSink : public INotification
{
public:
	//�ṩ����shared_ptr�Ľӿ�
	std::shared_ptr<INotification> get_notification() throw()
	{
		return std::shared_ptr<INotification>(static_cast<INotification *>(this));
	}

	//һ�β����Ƿ�ɹ���Ϣ
	virtual void OnPropertyChange(const std::string &str)
	{
		//std::shared_ptr<T> pT(std::make_shared<T>(static_cast<T *> this));
		if (str == "sample begin")
		{
			//��ʾ"���ڲ�����ȴ�..."
			/*
			pT->dlg.Create(0);
			pT->dlg.SetDlgItemText(IDC_WAIT, "���ڲ�����ȴ�...");
			pT->dlg.ShowWindow();
			*/
		}
		else if (str == "sample end")
		{
			//������ʾ��Ϣ
			//pT->dlg.EndDialog(0);
		}
		
	}
	virtual void OnExcept(const std::string& str)
	{}
	//������ע���Ƿ�ɹ�
	virtual void OnCommandComplete(const std::string &str, bool result)
	{
		if (str == "register")
		{
			if (result)
				MessageBoxW(NULL, TEXT("ע��ɹ�"), TEXT("INFORMATION!"), MB_OK);
			else
				MessageBoxW(NULL, TEXT("ע��ʧ��"), TEXT("INFORMATION!"), MB_OK);
			return;
		}
		else if (str == "sample")
		{
			if (result)
			{
				T* pT = static_cast<T*>(this);
				MessageBoxW(NULL, TEXT("�����ɹ�"), TEXT("INFORMATION!"), MB_OK);
				pT->decrease_number();
			}
			else
			{
				MessageBoxW(NULL, TEXT("����ʧ��"), TEXT("INFORMATION!"), MB_OK);
			}
			return;
		}
	}
};
#endif // !_REGISTER_WINDOW_SINK_H

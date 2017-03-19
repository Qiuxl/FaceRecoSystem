#ifndef _REGISTER_WINDOW_SINK_H
#define _REGISTER_WINDOW_SINK_H
#include "../common/common.h"

template<typename T>
class RegWindowSink : public INotification
{
public:
	//提供生成shared_ptr的接口
	std::shared_ptr<INotification> get_notification() throw()
	{
		return std::shared_ptr<INotification>(static_cast<INotification *>(this));
	}

	//一次采样是否成功信息
	virtual void OnPropertyChange(const std::string &str)
	{
		//std::shared_ptr<T> pT(std::make_shared<T>(static_cast<T *> this));
		if (str == "sample begin")
		{
			//提示"正在采样请等待..."
			/*
			pT->dlg.Create(0);
			pT->dlg.SetDlgItemText(IDC_WAIT, "正在采样请等待...");
			pT->dlg.ShowWindow();
			*/
		}
		else if (str == "sample end")
		{
			//消除提示信息
			//pT->dlg.EndDialog(0);
		}
		
	}
	virtual void OnExcept(const std::string& str)
	{}
	//采样、注册是否成功
	virtual void OnCommandComplete(const std::string &str, bool result)
	{
		if (str == "register")
		{
			if (result)
				MessageBoxW(NULL, TEXT("注册成功"), TEXT("INFORMATION!"), MB_OK);
			else
				MessageBoxW(NULL, TEXT("注册失败"), TEXT("INFORMATION!"), MB_OK);
			return;
		}
		else if (str == "sample")
		{
			if (result)
			{
				T* pT = static_cast<T*>(this);
				MessageBoxW(NULL, TEXT("采样成功"), TEXT("INFORMATION!"), MB_OK);
				pT->decrease_number();
			}
			else
			{
				MessageBoxW(NULL, TEXT("采样失败"), TEXT("INFORMATION!"), MB_OK);
			}
			return;
		}
	}
};
#endif // !_REGISTER_WINDOW_SINK_H

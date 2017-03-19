#pragma once
#include "../../common/common.h"
template <class T>
class LoginCommand : public myICommand
{
public:
	LoginCommand(T* p) throw() :m_viewmodel_ptr(p)
	{
	}
	
	virtual void SetParameter(const std::shared_ptr<ICommandParameter>& param)
	{
		m_param = param;
	}
	virtual void Exec()
	{
		//RefPtr<TwoStringParameter> p = RefPtrHelper::TypeCast<ICommandParameter, TwoStringParameter>(m_param);//类型转换
		std::shared_ptr<one_photo> p = std::static_pointer_cast<one_photo>(m_param);//类型转换
		bool bResult = m_viewmodel_ptr->Login(p->get_id(), p->get_image());//执行viewmodel中的Login
		m_viewmodel_ptr->Fire_OnCommandComplete(std::string("Login"), bResult);
	}
private:
	std::shared_ptr<ICommandParameter> m_param;
	T* m_viewmodel_ptr;
};

//使用make_share创建shared_ptr。

//谁暴露谁创建shared_ptr
//mainwindowsink 创建Notification的shared_ptr
//viewmodel 创建Command的shared_ptr
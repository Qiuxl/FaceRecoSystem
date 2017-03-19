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
		//RefPtr<TwoStringParameter> p = RefPtrHelper::TypeCast<ICommandParameter, TwoStringParameter>(m_param);//����ת��
		std::shared_ptr<one_photo> p = std::static_pointer_cast<one_photo>(m_param);//����ת��
		bool bResult = m_viewmodel_ptr->Login(p->get_id(), p->get_image());//ִ��viewmodel�е�Login
		m_viewmodel_ptr->Fire_OnCommandComplete(std::string("Login"), bResult);
	}
private:
	std::shared_ptr<ICommandParameter> m_param;
	T* m_viewmodel_ptr;
};

//ʹ��make_share����shared_ptr��

//˭��¶˭����shared_ptr
//mainwindowsink ����Notification��shared_ptr
//viewmodel ����Command��shared_ptr
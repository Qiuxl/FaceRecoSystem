#pragma once
#include "../../common/common.h"
template <class T>
class RegisterCommand : public ICommand
{
public:
	RegisterCommand(T* p) throw() :m_viewmodel_ptr(p)
	{
	}

	virtual void SetParameter(const std::shared_ptr<ICommandParameter>& param)
	{
		m_param = param;
	}
	virtual void Exec()
	{
		//RefPtr<TwoStringParameter> p = RefPtrHelper::TypeCast<ICommandParameter, TwoStringParameter>(m_param);//类型转换
		std::shared_ptr<RegisterParameter> p = std::static_pointer_cast<ICommandParameter>(m_param);//类型转换

		bool bResult = m_viewmodel_ptr->Register(/*用p->get_\set_来获取相对parameter*/);//执行Login
		m_viewmodel_ptr->Fire_OnCommandComplete(std::string("Register"), bResult);
	}
private:
	std::shared_ptr<ICommandParameter> m_param;
	T* m_viewmodel_ptr;

};
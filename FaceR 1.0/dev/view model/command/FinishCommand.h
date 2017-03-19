#pragma once
#include "../../common/common.h"
#include "../../common/commandparameter.h"
template <class T>
class FinishCommand : public myICommand
{
public:
	FinishCommand(T* p) throw() :m_viewmodel_ptr(p)
	{
	}

	virtual void SetParameter(const std::shared_ptr<ICommandParameter>& param)
	{
		m_param = param;
	}
	virtual void Exec()
	{
		//RefPtr<TwoStringParameter> p = RefPtrHelper::TypeCast<ICommandParameter, TwoStringParameter>(m_param);//类型转换
		std::shared_ptr<person> p = std::static_pointer_cast<person>(m_param);//类型转换

		bool bResult = m_viewmodel_ptr->Finish(p->get_id());//执行Login
		m_viewmodel_ptr->Fire_OnCommandComplete(std::string("register"), bResult);
	}
private:
	std::shared_ptr<ICommandParameter> m_param;
	T* m_viewmodel_ptr;
};
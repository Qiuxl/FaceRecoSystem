#pragma once
#include "../../common/common.h"
//#include "../../common/commandparameter.h"
template <class T>
class PhoCommand : public myICommand
{
public:
	PhoCommand(T* p) throw() :m_viewmodel_ptr(p)
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
		bool bResult = m_viewmodel_ptr->Pho(p->get_id(), p->get_image());//执行viewmodel中的Pho
		m_viewmodel_ptr->Fire_OnCommandComplete(std::string("sample"), bResult);
	}
private:
	std::shared_ptr<ICommandParameter> m_param;
	T* m_viewmodel_ptr;

};
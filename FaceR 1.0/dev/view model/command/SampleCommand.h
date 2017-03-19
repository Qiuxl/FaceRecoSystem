#pragma once
#include "../../common/common.h"

template <typename T>
class SampleCommand : public myICommand
{
private:
	std::shared_ptr<T> m_viewmodel_ptr;
	std::shared_ptr<ICommandParameter> m_param;
public:
	SampleCommand(T *p) throw() : m_viewmodel_ptr(std::make_shared(p))
	{

	}

	std::shared_ptr<myICommand> get_Samplecommand() throw()
	{
		return std::make_shared(this);
	}

	virtual void SetParameter(const std::shared_ptr<ICommandParameter> &param)
	{
		m_param = param;
	}

	virtual void Exec()
	{

	}
};
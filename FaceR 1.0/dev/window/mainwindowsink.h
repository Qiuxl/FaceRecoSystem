#pragma once

#include "../common/common.h"

template <class T>
class MainWindowSink : public INotification
{
public:
	
	std::shared_ptr<INotification> get_notification() throw()
	{
		return std::shared_ptr<INotification>(static_cast<INotification *>(this));
	}
	virtual void OnPropertyChange(const std::string &str)
	{}
	virtual void OnCommandComplete(const std::string &str, bool bResult)
	{}
	virtual void OnExcept(const std::string& str)
	{}
};
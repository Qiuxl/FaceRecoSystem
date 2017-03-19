#include "stdafx.h"
#include "dev\common\common.h"
void except::set(std::string &str)
{
	msg = str;
}
std::string except::get()
{
	return msg;
}
except::~except()
{

}

//..
void Proxy_Notification::Fire_OnPropertyChange(const std::string& str)
{
	std::vector<std::shared_ptr<INotification>>& vec = GetNotificationArray();
	auto iter(vec.begin());
	for (; iter != vec.end(); ++iter) {
		(*iter)->OnPropertyChange(str);
	}
}

void Proxy_Notification::Fire_OnCommandComplete(const std::string& str, bool bOK)
{
	std::vector<std::shared_ptr<INotification>>& vec = GetNotificationArray();
	auto iter(vec.begin());
	for (; iter != vec.end(); ++iter) {
		(*iter)->OnCommandComplete(str, bOK);
	}
}

void Proxy_Notification::Fire_OnExcept(const std::string& str)
{
	std::vector<std::shared_ptr<INotification>>& vec = GetNotificationArray();
	auto iter(vec.begin());
	for (; iter != vec.end(); ++iter) {
		(*iter)->OnExcept(str);
	}
}
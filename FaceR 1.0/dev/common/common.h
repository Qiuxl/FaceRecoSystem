/*  
	**Common层**
	Common层提供基本的类，包括对底层系统的封装，通用性质的数据结构和算法等。
	其它各层都可以调用Common层提供的类。
	确定是对的了，不会有问题。
*/

#ifndef _COMMON_H_
#define _COMMON_H_


#pragma once

#include <string>
#include <vector>
#include <memory>


class INotification
{
public:
	virtual void OnPropertyChange(const std::string& std) = 0;//属性改变
	virtual void OnCommandComplete(const std::string& str, bool bOK) = 0;//CMD完成
	virtual void OnExcept(const std::string& str) = 0;
};
class except{
private:
	std::string msg;

public:
	void set(std::string &);
	std::string get();
	~except();
};

template <class T>
class NotificationImpl
{
public:
	std::vector<std::shared_ptr<T>>& GetNotificationArray() throw() {
		return m_array;
	}
	void AddNotification(const std::shared_ptr<T>& p)
	{
		m_array.push_back(p);
	}
private:
	std::vector<std::shared_ptr<T>> m_array;
};

//Notification触发器
class Proxy_Notification:public NotificationImpl<INotification>
{
public:
	void Fire_OnPropertyChange(const std::string& str);
	void Fire_OnCommandComplete(const std::string& str, bool bOK);
	void Fire_OnExcept(const std::string& str);
};
//...

class ICommandParameter
{

};

class myICommand
{
public:
	virtual void Exec() = 0;
	virtual void SetParameter(const std::shared_ptr<ICommandParameter> & param) = 0;
};
#endif // !_COMMON_H_
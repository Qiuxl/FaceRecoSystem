#pragma once

#include "../common/common.h"
#include <memory>

class Result
{
public:
	void set_s_id(std::shared_ptr<std::string>& ss)//只需要显示
	{
		cannotpass = ss;
	}

private:
	std::shared_ptr<std::string> cannotpass;
	
};

class Photo_after
{
public:
	const photo& get_Photo();
	void set_Photo_ref(const std::shared_ptr<photo>& p)
	{
		image = p;
	}
private:
	std::shared_ptr<photo> image;
};

class S_id
{
public:
	const std::string& get_s_id(std::shared_ptr<std::string>& ss)
	{
		s_id = ss;
	}
	void set_s_id_ref(const std::shared_ptr<std::string>& str)
	{
		s_id = str;
	}
private:
	std::shared_ptr<std::string> s_id;

};

class S_name
{
public:
	const std::string& get_s_name(std::shared_ptr<std::string>& ss)
	{
		s_name = ss;
	}
	void set_s_name_ref(const std::shared_ptr<std::string>& str)//shared_ptr仍有bug
	{
		s_name = str;

	}
private:
	std::shared_ptr<std::string> s_name;
};

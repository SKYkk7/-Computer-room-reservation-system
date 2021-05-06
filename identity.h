#ifndef IDENTITY
#define IDENTITY
#include <iostream>

class Identity
{
public:
	virtual void openMenu() = 0;  //纯虚函数

	std::string m_Name;  //用户名
	std::string m_Pwd;   //密码
};

#endif // !IDENTITY


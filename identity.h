#ifndef IDENTITY
#define IDENTITY
#include <iostream>

class Identity
{
public:
	virtual void openMenu() = 0;  //���麯��

	std::string m_Name;  //�û���
	std::string m_Pwd;   //����
};

#endif // !IDENTITY


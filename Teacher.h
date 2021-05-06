#ifndef TEACHER
#define TEACHER	
#include "identity.h"
#include "orderFile.h"
#include "globalFile.h"

class Teacher : public Identity
{
public:
	//默认构造函数
	Teacher();
	//有参构造函数
	Teacher(int id, std::string name, std::string pwd);

	//菜单界面
	virtual void openMenu();

	//审核预约
	void validOrder();

	//查看所有预约
	void showAllOrder();

public:
	int m_tecId;
};
#endif // !TEACHER


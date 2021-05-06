#ifndef STUDENT
#define STUDENT	
#include<iostream>
#include<vector>
#include "identity.h"
#include "ComputerRoom.h"
#include <string>
#include "globalFile.h"
#include <fstream>
#include "orderFile.h"

class Student: public Identity
{
public:
	//默认构造
	Student();
	//有参构造
	Student(int id, std::string name, std::string pwd);

	//菜单界面，继承父类
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void canceOrder();
public:
	int m_stdId;
	std::vector<ComputerRoom> vCom;
};


#endif // !STUDENT


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
	//Ĭ�Ϲ���
	Student();
	//�вι���
	Student(int id, std::string name, std::string pwd);

	//�˵����棬�̳и���
	virtual void openMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void canceOrder();
public:
	int m_stdId;
	std::vector<ComputerRoom> vCom;
};


#endif // !STUDENT


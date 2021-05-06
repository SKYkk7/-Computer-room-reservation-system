#ifndef MANAGER
#define MANAGER
#include "identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "ComputerRoom.h"
#include <algorithm>

class Manager : public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();
	//�вι���
	Manager(std::string id, std::string pwd);

	//ѡ��˵�
	virtual void openMenu();
	
	//����˺�
	void addPerson();
	
	//�鿴�˺�
	void showPerson();

	//����������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void clearFile();

	//��ʼ������
	void initVector();

	//����ظ�
	bool checkRepeat(int id, int type);

	//ѧ������
	std::vector<Student> vStu;
	//��ʦ����
	std::vector<Teacher> vTea;
	//��������
	std::vector<ComputerRoom> vCom;

};
#endif // !MANAGER


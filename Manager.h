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
	//默认构造
	Manager();
	//有参构造
	Manager(std::string id, std::string pwd);

	//选择菜单
	virtual void openMenu();
	
	//添加账号
	void addPerson();
	
	//查看账号
	void showPerson();

	//产看机房信息
	void showComputer();

	//清空预约记录
	void clearFile();

	//初始化容器
	void initVector();

	//检测重复
	bool checkRepeat(int id, int type);

	//学生容器
	std::vector<Student> vStu;
	//教师容器
	std::vector<Teacher> vTea;
	//机房容量
	std::vector<ComputerRoom> vCom;

};
#endif // !MANAGER


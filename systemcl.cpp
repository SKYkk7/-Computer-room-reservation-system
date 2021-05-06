#include "systemcl.h"

void systemCtl::showMenu()
{
	std::cout << "==================机房预约系统====================================\n";
	std::cout << "请输入你的身份：\n";
	std::cout << "\t\t--------------------------------------------\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       1：学生代表                        |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       2：老师                            |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       3：管理员                          |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       0：退出                            |\n";
	std::cout << "\t\t--------------------------------------------\n";

}

void systemCtl::systemExit()
{
	std::cout << "欢迎下一次使用!" << std::endl;
	system("system");
	exit(0);
}

void systemCtl::loginIn(std::string fileName, int type)
{

	//父类指针，指向子类对象
	Identity* person = NULL;
	//读文件
	std::ifstream ifs;
	ifs.open(fileName, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "文件不存在" << std::endl;
		ifs.close();
		return;
	}
	//准备用户信息
	int id = 0;
	std::string name;
	std::string pwd;

	if (type == 1)
	{
		std::cout << "请输入你的学生号：" << std::endl;
		std::cin >> id;
	}
	else if (type == 2)
	{
		std::cout << "请输入你的职工号：" << std::endl;
		std::cin >> id;
	}

	std::cout << "请输入用户名：" << std::endl;
	std::cin >> name;

	std::cout << "请输入你的密码" << std::endl;
	std::cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId;   //从文件中读取的文件
		std::string fName;   //从文件中读取的名字
		std::string fPwd;   //从文件中读取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				std::cout << "学生登录验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Student(fId, fName, fPwd);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;   //从文件中读取的文件
		std::string fName;   //从文件中读取的名字
		std::string fPwd;   //从文件中读取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				std::cout << "老师登录验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Teacher(fId, fName, fPwd);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		std::string fName;   //从文件中读取的名字
		std::string fPwd;   //从文件中读取的密码
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				std::cout << "管理员登录验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Manager(fName, fPwd);
				managerMenu(person);
				//person = new Manager(fName, fPwd);
				return;
			}
		}
	}

	std::cout << "验证身份失败！" << std::endl;
	system("pause");
	system("cls");
}

//进入学生子菜单
void systemCtl::studentMenu(Identity*& student)
{
	while (true)
	{
		student->openMenu();
		Student* stu = (Student*)student;
		int select = 0;

		std::cin >> select;

		if (select == 1)
		{
			//添加账号
			std::cout << "申请预约" << std::endl;
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//查看账号
			std::cout << "查看自身预约" << std::endl;
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//查看机房信息
			std::cout << "查看所有预约" << std::endl;
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//清空预约
			std::cout << "取消预约" << std::endl;
			stu->canceOrder();
		}
		else
		{
			delete student;
			stu = nullptr;
			std::cout << "注销成功" << std::endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入教师菜单
void systemCtl::teacherMenu(Identity* &teacher)
{
	while (true) {
		teacher->openMenu();
		Teacher* tea = dynamic_cast<Teacher*>(teacher);
		int select = 0;
		cin >> select;
		switch (select) {
		case 1:
			tea->showAllOrder();
			break;
		case 2:
			tea->validOrder();
			break;
		case 0: {
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		default: {
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
		}
	}
}

//进入管理员子菜单
void systemCtl::managerMenu(Identity*& manager)
{
	while (true)
	{
		//管理员菜单
		manager->openMenu();
		Manager* man = (Manager*)manager;
		int select = 0;

		std::cin >> select;

		if (select == 1)
		{
			//添加账号
			std::cout << "添加账号" << std::endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			//查看账号
			std::cout << "查看账号" << std::endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			//查看机房信息
			std::cout << "查看机房信息" << std::endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			//清空预约
			std::cout << "清空预约信息" << std::endl;
			man->clearFile();
		}
		else
		{
			delete manager;
			man = nullptr;
			std::cout << "注销成功" << std::endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
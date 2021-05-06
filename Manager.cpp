#include "Manager.h"

void printStudent(const Student& s)
{
	std::cout << "学号：" << s.m_stdId << "  姓名：" << s.m_Name << "  密码：" << s.m_Pwd << std::endl;
}

void printTeacher(const Teacher& t)
{
	std::cout << "职工号：" << t.m_tecId << "  姓名：" << t.m_Name << "  密码：" << t.m_Pwd << std::endl;
}

Manager::Manager()
{

}
Manager::Manager(std::string name, std::string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	
	//初始化容器，获得学生，老师信息
	this->initVector();
	//初始化机房信息
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "无法打开文件！" << std::endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
	std::cout << "机房的数量为：" << vCom.size() << std::endl;
}

void Manager::openMenu() //选择菜单
{
	std::cout << "欢迎管理员" << this->m_Name << "登录！" << std::endl;
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          1:添加账号                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          2:查看账号                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          3:产看机房信息                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          4:清空预约                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          0:注销登录                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "请选择你的操作：" << std::endl;
}

void Manager::addPerson()  //添加账号
{
	std::cout << "请输入添加账号的类型" << std::endl;
	std::cout << "1:添加学生" << std::endl;
	std::cout << "2:添加教师" << std::endl;

	std::string fileName;
	std::string tip;   //提示id号
	std::string errorIp; //id重复提示
	std::ofstream ofs;

	int select;
	std::cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorIp = "学号重复，请重新输入！";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorIp = "职工号重复，请重新输入！";
	}

	ofs.open(fileName, std::ios::out | std::ios::app);

	int id;
	std::string name;
	std::string pwd;

	std::cout << tip << std::endl;
	//提示用户输入自己的信息
	while(true)  //输入id重复时，提醒用户重新输入
	{
		std::cin >> id;
		bool ret = this->checkRepeat(select, id);
		if (ret)
		{
			std::cout << errorIp << std::endl;
		}
		else
			break;
		
	}
	std::cout << "请输入姓名：" << std::endl;
	std::cin >> name;
	std::cout << "请输入密码：" << std::endl;
	std::cin >> pwd;

	ofs << id << " " << name << " " << pwd << std::endl;
	std::cout << "添加成功!" << std::endl;


	system("pause");
	system("cls");
	ofs.close();

	//及时更新容器
	this->initVector();
}


void Manager::showComputer()   //查看账号
{
	std::cout << "机房信息如下：" << std::endl;
	for (auto iter = vCom.begin(); iter != vCom.end(); ++iter)
	{
		std::cout << "机房id：" << iter->m_ComId << "  最大容量：" << iter->m_MaxNum << std::endl;
	}
	system("pause");
	system("cls");
}

void Manager::showPerson()     //查看机房信息
{
	std::cout << "请选择查看内容：" << std::endl;
	std::cout << "1:查看所有学生" << std::endl;
	std::cout << "2:查看所有教师" << std::endl;

	int select;
	std::cin >> select;

	if (select == 1)
	{
		std::cout << "所有学生信息如下：" << std::endl;
		std::for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		std::cout << "所有教师信息如下：" << std::endl;
		std::for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void Manager::clearFile()    //清空预约记录
{
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::trunc);
	ofs.close();

	std::cout << "清空成功！" << std::endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	//确保容器清空状态
	vStu.clear();
	vTea.clear();
	//读取信息  学生
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "文件读取失败！" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.m_stdId && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	std::cout << "当前学生数量为：" << vStu.size() << std::endl;
	ifs.close();

	//读取信息  教师
	ifs.open(TEACHER_FILE, std::ios::app);
	if (!ifs.is_open())
	{
		std::cout << "文件读取失败！" << std::endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_tecId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	std::cout << "当前教师数量为：" << vTea.size() << std::endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学号
		for (auto iter = vStu.begin(); iter != vStu.end(); ++iter)
		{
			if (iter->m_stdId == id)
			{
				return true;
			}
		}
		//return false;
	}
	else
	{
		//检测职工号 
		for (auto iter = vTea.begin(); iter != vTea.end(); ++iter)
		{
			if (iter->m_tecId == id)
			{
				return true;
			}

		}
		//return false;
	}
	return false;
}
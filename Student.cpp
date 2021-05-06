#include "student.h"

Student::Student()
{

}
Student::Student(int id, std::string name, std::string pwd)
{
	this->m_stdId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
}

void Student::openMenu()
{
	std::cout << "欢迎学生" << this->m_Name << "登录！" << std::endl;
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          1:申请预约                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          2:查看自身预约                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          3:查看所有预约                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          4:取消预约                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          0:注销登录                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "请选择你的操作：" << std::endl;
}

void Student::applyOrder()
{
	std::cout << "机房开放时间为周一到周五！" << std::endl;
	std::cout << "请输入申请预约的时间：" << std::endl;
	std::cout << "1：周一" << std::endl;
	std::cout << "2：周二" << std::endl;
	std::cout << "3：周三" << std::endl;
	std::cout << "4：周四" << std::endl;
	std::cout << "5：周五" << std::endl;

	int data;   //日期
	int interval;   //时间段
	int room;    //机房编号

	while (true)
	{
		std::cin >> data;
		if (data <= 5 && data >= 1)
		{
			break;
		}
		std::cout << "输入有误，请重新再输：" << std::endl;
	}

	std::cout << "请输入申请预约的时间段：" << std::endl;
	std::cout << "1：上午" << std::endl;
	std::cout << "2：下午" << std::endl;

	while (true)
	{
		std::cin >> interval;
		if (interval <= 2 && interval >= 1)
		{
			break;
		}
		std::cout << "输入有误，请重新再输：" << std::endl;
	}

	std::cout << "请选择机房：" << std::endl;
	for (auto iter = vCom.begin(); iter != vCom.end(); ++iter)
	{
		std::cout << iter->m_MaxNum << "号机房容量为：" << iter->m_MaxNum << std::endl;
	}

	while (true)
	{
		std::cin >> room;
		if (room <= vCom.size() && room >= 0)
		{
			break;
		}
		std::cout << "输入有误，请重新再输：" << std::endl;
	}

	std::cout << "预约成功，审核中！" << std::endl;

	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::app);

	ofs << "data:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_stdId << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << " ";

	ofs.close();
	system("pause");
	system("cls");
}

void Student::canceOrder()
{
	OrderFile of;
	if (of.m_size == 0) {
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << std::endl;
	std::vector<int>v;
	std::map<int, int> comparison;
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_stdId) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				comparison.insert(std::make_pair(index, i));
				std::cout << index++ << "、 ";
				std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
				std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				std::cout << " 机房：" << of.m_orderData[i]["roomId"];
				std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "预约成功";
				}
				std::cout << status << std::endl;
			}
		}
	}

	std::cout << "请输入取消的记录,0代表返回" << std::endl;
	int select = 0;

	while (true) {
		std::cin >> select;
		if (select >= 0 && select <= index) {
			if (select == 0)
				break;
			else {
				of.m_orderData[comparison[select]]["status"] = "0";
				of.updateOrder();
				std::cout << "已取消预约" << std::endl;
				break;
			}
		}
		std::cout << "输入有误，请重新输入" << std::endl;
	}
	system("pause");
	system("cls");
	comparison.clear();
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; ++i)
	{
		std::cout << "预约日期： 周" << of.m_orderData[i]["data"];
		std::cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		std::cout << "  机房：" << of.m_orderData[i]["roomId"];
		std::string status = "  状态:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else
			status += "预约以取消";
		std::cout << std::endl;

	}
	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; ++i)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_stdId)
		{
			std::cout << "预约日期： 周" << of.m_orderData[i]["data"];
			std::cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			std::cout << "  机房：" << of.m_orderData[i]["roomId"];
			std::string status = "  状态:";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else
				status += "预约以取消";
			std::cout << std::endl;
		}
	}
	system("pause");
	system("cls");
}
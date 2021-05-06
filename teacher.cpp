#include "Teacher.h"

Teacher::Teacher()
{

}

Teacher::Teacher(int id, std::string name, std::string pwd)
{
	this->m_tecId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::openMenu()
{
	std::cout << "欢迎教师：" << this->m_Name << "登录！" << std::endl;
	std::cout << "\t\t ----------------------------------\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          1.查看所有预约          |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          2.审核预约              |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          0.注销登录              |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t ----------------------------------\n";
	std::cout << "请选择您的操作： " << std::endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0) {
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++) {
		std::cout << i + 1 << "、 ";

		std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
		std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		std::cout << " 学号：" << of.m_orderData[i]["stuId"];
		std::cout << " 姓名：" << of.m_orderData[i]["stuName"];
		std::cout << " 机房：" << of.m_orderData[i]["roomId"];
		std::string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1") {
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1") {
			status += "审核未通过，预约失败";
		}
		else {
			status += "预约已取消";
		}
		std::cout << status << std::endl;
	}

	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0) {
		std::cout << "无预约记录" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "待审核的预约记录如下：" << std::endl;

	std::map<int, int> comparison;
	int index = 0;
	for (int i = 0; i < of.m_size; i++) {
		if (of.m_orderData[i]["status"] == "1") {
			comparison.insert(std::make_pair(index, i));
			std::cout << ++index << "、 ";
			std::cout << "预约日期： 周" << of.m_orderData[i]["date"];
			std::cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			std::cout << " 机房：" << of.m_orderData[i]["roomId"];
			std::string status = " 状态： ";  // 0取消的预约   1 审核中   2 已预约  -1 预约失败
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			std::cout << status << std::endl;
		}
	}
	std::cout << "请输入审核的预约记录,0代表返回" << std::endl;
	int select = 0;
	int ret = 0;
	while (true) {
		std::cin >> select;
		if (select >= 0 && select <= index) {
			if (select == 0)
				break;
			else {
				std::cout << "请输入审核结果" << std::endl;
				std::cout << "1、通过" << std::endl;
				std::cout << "2、不通过" << std::endl;
				std::cin >> ret;

				if (ret == 1) {
					of.m_orderData[comparison[select]]["status"] = "2";
				}
				else {
					of.m_orderData[comparison[select]]["status"] = "-1";
				}
				of.updateOrder();
				std::cout << "审核完毕！" << std::endl;
				break;
			}
		}
		std::cout << "输入有误，请重新输入" << std::endl;
	}
	system("pause");
	system("cls");
	comparison.clear();
}
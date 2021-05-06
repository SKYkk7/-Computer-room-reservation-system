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
	std::cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << std::endl;
	std::cout << "\t\t ----------------------------------\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          2.���ԤԼ              |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t|          0.ע����¼              |\n";
	std::cout << "\t\t|                                  |\n";
	std::cout << "\t\t ----------------------------------\n";
	std::cout << "��ѡ�����Ĳ����� " << std::endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0) {
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++) {
		std::cout << i + 1 << "�� ";

		std::cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
		std::cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		std::cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		std::cout << " ������" << of.m_orderData[i]["stuName"];
		std::cout << " ������" << of.m_orderData[i]["roomId"];
		std::string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		if (of.m_orderData[i]["status"] == "1") {
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1") {
			status += "���δͨ����ԤԼʧ��";
		}
		else {
			status += "ԤԼ��ȡ��";
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
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "����˵�ԤԼ��¼���£�" << std::endl;

	std::map<int, int> comparison;
	int index = 0;
	for (int i = 0; i < of.m_size; i++) {
		if (of.m_orderData[i]["status"] == "1") {
			comparison.insert(std::make_pair(index, i));
			std::cout << ++index << "�� ";
			std::cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
			std::cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			std::cout << " ������" << of.m_orderData[i]["roomId"];
			std::string status = " ״̬�� ";  // 0ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			std::cout << status << std::endl;
		}
	}
	std::cout << "��������˵�ԤԼ��¼,0������" << std::endl;
	int select = 0;
	int ret = 0;
	while (true) {
		std::cin >> select;
		if (select >= 0 && select <= index) {
			if (select == 0)
				break;
			else {
				std::cout << "��������˽��" << std::endl;
				std::cout << "1��ͨ��" << std::endl;
				std::cout << "2����ͨ��" << std::endl;
				std::cin >> ret;

				if (ret == 1) {
					of.m_orderData[comparison[select]]["status"] = "2";
				}
				else {
					of.m_orderData[comparison[select]]["status"] = "-1";
				}
				of.updateOrder();
				std::cout << "�����ϣ�" << std::endl;
				break;
			}
		}
		std::cout << "������������������" << std::endl;
	}
	system("pause");
	system("cls");
	comparison.clear();
}
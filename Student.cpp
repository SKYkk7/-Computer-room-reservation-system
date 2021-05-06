#include "student.h"

Student::Student()
{

}
Student::Student(int id, std::string name, std::string pwd)
{
	this->m_stdId = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ��������Ϣ
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
	std::cout << "��ӭѧ��" << this->m_Name << "��¼��" << std::endl;
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          1:����ԤԼ                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          2:�鿴����ԤԼ                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          3:�鿴����ԤԼ                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          4:ȡ��ԤԼ                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          0:ע����¼                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "��ѡ����Ĳ�����" << std::endl;
}

void Student::applyOrder()
{
	std::cout << "��������ʱ��Ϊ��һ�����壡" << std::endl;
	std::cout << "����������ԤԼ��ʱ�䣺" << std::endl;
	std::cout << "1����һ" << std::endl;
	std::cout << "2���ܶ�" << std::endl;
	std::cout << "3������" << std::endl;
	std::cout << "4������" << std::endl;
	std::cout << "5������" << std::endl;

	int data;   //����
	int interval;   //ʱ���
	int room;    //�������

	while (true)
	{
		std::cin >> data;
		if (data <= 5 && data >= 1)
		{
			break;
		}
		std::cout << "�����������������䣺" << std::endl;
	}

	std::cout << "����������ԤԼ��ʱ��Σ�" << std::endl;
	std::cout << "1������" << std::endl;
	std::cout << "2������" << std::endl;

	while (true)
	{
		std::cin >> interval;
		if (interval <= 2 && interval >= 1)
		{
			break;
		}
		std::cout << "�����������������䣺" << std::endl;
	}

	std::cout << "��ѡ�������" << std::endl;
	for (auto iter = vCom.begin(); iter != vCom.end(); ++iter)
	{
		std::cout << iter->m_MaxNum << "�Ż�������Ϊ��" << iter->m_MaxNum << std::endl;
	}

	while (true)
	{
		std::cin >> room;
		if (room <= vCom.size() && room >= 0)
		{
			break;
		}
		std::cout << "�����������������䣺" << std::endl;
	}

	std::cout << "ԤԼ�ɹ�������У�" << std::endl;

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
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << std::endl;
	std::vector<int>v;
	std::map<int, int> comparison;
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_stdId) {
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				comparison.insert(std::make_pair(index, i));
				std::cout << index++ << "�� ";
				std::cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["date"];
				std::cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				std::cout << " ������" << of.m_orderData[i]["roomId"];
				std::string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "ԤԼ�ɹ�";
				}
				std::cout << status << std::endl;
			}
		}
	}

	std::cout << "������ȡ���ļ�¼,0������" << std::endl;
	int select = 0;

	while (true) {
		std::cin >> select;
		if (select >= 0 && select <= index) {
			if (select == 0)
				break;
			else {
				of.m_orderData[comparison[select]]["status"] = "0";
				of.updateOrder();
				std::cout << "��ȡ��ԤԼ" << std::endl;
				break;
			}
		}
		std::cout << "������������������" << std::endl;
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
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; ++i)
	{
		std::cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["data"];
		std::cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		std::cout << "  ������" << of.m_orderData[i]["roomId"];
		std::string status = "  ״̬:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else
			status += "ԤԼ��ȡ��";
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
		std::cout << "��ԤԼ��¼" << std::endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; ++i)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str()) == this->m_stdId)
		{
			std::cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["data"];
			std::cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			std::cout << "  ������" << of.m_orderData[i]["roomId"];
			std::string status = "  ״̬:";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else
				status += "ԤԼ��ȡ��";
			std::cout << std::endl;
		}
	}
	system("pause");
	system("cls");
}
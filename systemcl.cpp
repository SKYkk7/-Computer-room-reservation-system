#include "systemcl.h"

void systemCtl::showMenu()
{
	std::cout << "==================����ԤԼϵͳ====================================\n";
	std::cout << "�����������ݣ�\n";
	std::cout << "\t\t--------------------------------------------\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       1��ѧ������                        |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       2����ʦ                            |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       3������Ա                          |\n";
	std::cout << "\t\t|                                          |\n";
	std::cout << "\t\t|       0���˳�                            |\n";
	std::cout << "\t\t--------------------------------------------\n";

}

void systemCtl::systemExit()
{
	std::cout << "��ӭ��һ��ʹ��!" << std::endl;
	system("system");
	exit(0);
}

void systemCtl::loginIn(std::string fileName, int type)
{

	//����ָ�룬ָ���������
	Identity* person = NULL;
	//���ļ�
	std::ifstream ifs;
	ifs.open(fileName, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�ļ�������" << std::endl;
		ifs.close();
		return;
	}
	//׼���û���Ϣ
	int id = 0;
	std::string name;
	std::string pwd;

	if (type == 1)
	{
		std::cout << "���������ѧ���ţ�" << std::endl;
		std::cin >> id;
	}
	else if (type == 2)
	{
		std::cout << "���������ְ���ţ�" << std::endl;
		std::cin >> id;
	}

	std::cout << "�������û�����" << std::endl;
	std::cin >> name;

	std::cout << "�������������" << std::endl;
	std::cin >> pwd;

	if (type == 1)
	{
		//ѧ�������֤
		int fId;   //���ļ��ж�ȡ���ļ�
		std::string fName;   //���ļ��ж�ȡ������
		std::string fPwd;   //���ļ��ж�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				std::cout << "ѧ����¼��֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Student(fId, fName, fPwd);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId;   //���ļ��ж�ȡ���ļ�
		std::string fName;   //���ļ��ж�ȡ������
		std::string fPwd;   //���ļ��ж�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				std::cout << "��ʦ��¼��֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Teacher(fId, fName, fPwd);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		std::string fName;   //���ļ��ж�ȡ������
		std::string fPwd;   //���ļ��ж�ȡ������
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				std::cout << "����Ա��¼��֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Manager(fName, fPwd);
				managerMenu(person);
				//person = new Manager(fName, fPwd);
				return;
			}
		}
	}

	std::cout << "��֤���ʧ�ܣ�" << std::endl;
	system("pause");
	system("cls");
}

//����ѧ���Ӳ˵�
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
			//����˺�
			std::cout << "����ԤԼ" << std::endl;
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//�鿴�˺�
			std::cout << "�鿴����ԤԼ" << std::endl;
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//�鿴������Ϣ
			std::cout << "�鿴����ԤԼ" << std::endl;
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//���ԤԼ
			std::cout << "ȡ��ԤԼ" << std::endl;
			stu->canceOrder();
		}
		else
		{
			delete student;
			stu = nullptr;
			std::cout << "ע���ɹ�" << std::endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//�����ʦ�˵�
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
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		default: {
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
		}
	}
}

//�������Ա�Ӳ˵�
void systemCtl::managerMenu(Identity*& manager)
{
	while (true)
	{
		//����Ա�˵�
		manager->openMenu();
		Manager* man = (Manager*)manager;
		int select = 0;

		std::cin >> select;

		if (select == 1)
		{
			//����˺�
			std::cout << "����˺�" << std::endl;
			man->addPerson();
		}
		else if (select == 2)
		{
			//�鿴�˺�
			std::cout << "�鿴�˺�" << std::endl;
			man->showPerson();
		}
		else if (select == 3)
		{
			//�鿴������Ϣ
			std::cout << "�鿴������Ϣ" << std::endl;
			man->showComputer();
		}
		else if (select == 4)
		{
			//���ԤԼ
			std::cout << "���ԤԼ��Ϣ" << std::endl;
			man->clearFile();
		}
		else
		{
			delete manager;
			man = nullptr;
			std::cout << "ע���ɹ�" << std::endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
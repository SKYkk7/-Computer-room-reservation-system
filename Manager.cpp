#include "Manager.h"

void printStudent(const Student& s)
{
	std::cout << "ѧ�ţ�" << s.m_stdId << "  ������" << s.m_Name << "  ���룺" << s.m_Pwd << std::endl;
}

void printTeacher(const Teacher& t)
{
	std::cout << "ְ���ţ�" << t.m_tecId << "  ������" << t.m_Name << "  ���룺" << t.m_Pwd << std::endl;
}

Manager::Manager()
{

}
Manager::Manager(std::string name, std::string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	
	//��ʼ�����������ѧ������ʦ��Ϣ
	this->initVector();
	//��ʼ��������Ϣ
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�޷����ļ���" << std::endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}

	ifs.close();
	std::cout << "����������Ϊ��" << vCom.size() << std::endl;
}

void Manager::openMenu() //ѡ��˵�
{
	std::cout << "��ӭ����Ա" << this->m_Name << "��¼��" << std::endl;
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          1:����˺�                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          2:�鿴�˺�                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          3:����������Ϣ                       |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          4:���ԤԼ                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t|          0:ע����¼                           |\n";
	std::cout << "\t\t|                                               |\n";
	std::cout << "\t\t-----------------------------------------------\n";
	std::cout << "��ѡ����Ĳ�����" << std::endl;
}

void Manager::addPerson()  //����˺�
{
	std::cout << "����������˺ŵ�����" << std::endl;
	std::cout << "1:���ѧ��" << std::endl;
	std::cout << "2:��ӽ�ʦ" << std::endl;

	std::string fileName;
	std::string tip;   //��ʾid��
	std::string errorIp; //id�ظ���ʾ
	std::ofstream ofs;

	int select;
	std::cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorIp = "ѧ���ظ������������룡";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorIp = "ְ�����ظ������������룡";
	}

	ofs.open(fileName, std::ios::out | std::ios::app);

	int id;
	std::string name;
	std::string pwd;

	std::cout << tip << std::endl;
	//��ʾ�û������Լ�����Ϣ
	while(true)  //����id�ظ�ʱ�������û���������
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
	std::cout << "������������" << std::endl;
	std::cin >> name;
	std::cout << "���������룺" << std::endl;
	std::cin >> pwd;

	ofs << id << " " << name << " " << pwd << std::endl;
	std::cout << "��ӳɹ�!" << std::endl;


	system("pause");
	system("cls");
	ofs.close();

	//��ʱ��������
	this->initVector();
}


void Manager::showComputer()   //�鿴�˺�
{
	std::cout << "������Ϣ���£�" << std::endl;
	for (auto iter = vCom.begin(); iter != vCom.end(); ++iter)
	{
		std::cout << "����id��" << iter->m_ComId << "  ���������" << iter->m_MaxNum << std::endl;
	}
	system("pause");
	system("cls");
}

void Manager::showPerson()     //�鿴������Ϣ
{
	std::cout << "��ѡ��鿴���ݣ�" << std::endl;
	std::cout << "1:�鿴����ѧ��" << std::endl;
	std::cout << "2:�鿴���н�ʦ" << std::endl;

	int select;
	std::cin >> select;

	if (select == 1)
	{
		std::cout << "����ѧ����Ϣ���£�" << std::endl;
		std::for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		std::cout << "���н�ʦ��Ϣ���£�" << std::endl;
		std::for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void Manager::clearFile()    //���ԤԼ��¼
{
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::trunc);
	ofs.close();

	std::cout << "��ճɹ���" << std::endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	//ȷ���������״̬
	vStu.clear();
	vTea.clear();
	//��ȡ��Ϣ  ѧ��
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ȡʧ�ܣ�" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.m_stdId && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	std::cout << "��ǰѧ������Ϊ��" << vStu.size() << std::endl;
	ifs.close();

	//��ȡ��Ϣ  ��ʦ
	ifs.open(TEACHER_FILE, std::ios::app);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ȡʧ�ܣ�" << std::endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_tecId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	std::cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << std::endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//���ѧ��
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
		//���ְ���� 
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
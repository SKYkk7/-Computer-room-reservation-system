#include "orderFile.h"

OrderFile::OrderFile()
{
	std::ifstream ifs;
	ifs.open(ORDER_FILE, std::ios::in);

	std::string data;  //����
	std::string interval;   // ʱ���
	std::string stuId;    //ѧ��id
	std::string stuName;   //ѧ������
	std::string roomId;   //����id
	std::string status;   //ԤԼ״̬

	this->m_size = 0;
	while (ifs >> data && ifs >> interval && ifs >> stuId && ifs >> stuName
		&& ifs >> roomId && ifs >> status)
	{
	/*	std::cout << data << std::endl;
		std::cout << interval << std::endl;
		std::cout << stuId << std::endl;
		std::cout << stuName << std::endl;
		std::cout << roomId << std::endl;
		std::cout << status << std::endl;
		std::cout << std::endl;*/

		std::string key;
		std::string value;
		std::map<std::string, std::string> m;

		//��ȡѧ��
		int pos = data.find(":");
		if (pos != -1)
		{
			key = data.substr(0, pos);
			value = data.substr(pos + 1, data.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}
		//std::cout << "key = " << key << std::endl;
		//std::cout << "value = " << value << std::endl;

		//��ȡʱ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}

		//��ȡѧ��
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}

		//��ȡ����
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}

		//��ȡ�������
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value =roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}

		//��ȡԤԼ״̬
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(std::make_pair(key, value));
		}

		this->m_orderData.insert(std::make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();
}

void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;
	}
	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::out | std::ios::trunc);
	for (int i = 0; i < this->m_size; ++i)
	{
		ofs << "data:" << m_orderData[i]["data"] << " ";
		ofs << "interval:" << m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << m_orderData[i]["stuName"] << " ";
		ofs << "stuName:" << m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << m_orderData[i]["roomId"] << " ";
		ofs << "status:" << m_orderData[i]["status"] << std::endl;;

	}
	ofs.close();
	system("pause");
	system("cls");
}
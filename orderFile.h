#ifndef ORDERFILE
#define ORDERFILE

#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();

	//��¼ԤԼ����
	int m_size = 0;
	//��¼����ԤԼ��Ϣ������
	std::map<int, std::map<std::string, std::string>> m_orderData;
};

#endif // !ORDERFILE


#ifndef ORDERFILE
#define ORDERFILE

#include <iostream>
#include <fstream>
#include <map>
#include "globalFile.h"

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_size = 0;
	//记录所有预约信息的容器
	std::map<int, std::map<std::string, std::string>> m_orderData;
};

#endif // !ORDERFILE


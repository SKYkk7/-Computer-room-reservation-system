#ifndef TEACHER
#define TEACHER	
#include "identity.h"
#include "orderFile.h"
#include "globalFile.h"

class Teacher : public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Teacher();
	//�вι��캯��
	Teacher(int id, std::string name, std::string pwd);

	//�˵�����
	virtual void openMenu();

	//���ԤԼ
	void validOrder();

	//�鿴����ԤԼ
	void showAllOrder();

public:
	int m_tecId;
};
#endif // !TEACHER


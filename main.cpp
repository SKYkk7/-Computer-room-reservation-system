#include <iostream>
#include "systemcl.h"

int main()
{
	systemCtl ctl;
	int select = 0;
	while (true)
	{
		ctl.showMenu();
		
		std::cin >> select;
		switch (select)
		{
		case 1:       //ѧ�����
			ctl.loginIn(STUDENT_FILE, 1);
			break;
		case 2:       //��ʦ���
			ctl.loginIn(TEACHER_FILE, 2);
			break;
		case 3:      //����Ա���
			ctl.loginIn(ADMIN_FILE, 3); 
			break;
		case 0:       //�˳�ϵͳ
			ctl.systemExit();
			break;
		default: 
			std::cout << "�����������������룺" << std::endl;
			system("pause");
			system("cls");

			break;
		}
	}

	system("pause");
	return 0;
}
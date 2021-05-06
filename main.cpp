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
		case 1:       //学生身份
			ctl.loginIn(STUDENT_FILE, 1);
			break;
		case 2:       //老师身份
			ctl.loginIn(TEACHER_FILE, 2);
			break;
		case 3:      //管理员身份
			ctl.loginIn(ADMIN_FILE, 3); 
			break;
		case 0:       //退出系统
			ctl.systemExit();
			break;
		default: 
			std::cout << "输入有误，请重新输入：" << std::endl;
			system("pause");
			system("cls");

			break;
		}
	}

	system("pause");
	return 0;
}
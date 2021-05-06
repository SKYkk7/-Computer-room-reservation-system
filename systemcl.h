#ifndef SYSTEMCL
#define SYSTEMCL
#include <iostream>
#include <fstream>
#include <string>
#include "identity.h"
#include "globalFile.h"
#include "Manager.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

class systemCtl {
public:
	void showMenu();
	void systemExit();
	void loginIn(string fileName, int type);
	void managerMenu(Identity*& manager);
	void studentMenu(Identity*& student);
	void teacherMenu(Identity*& teacher);
};

#endif // !SYSTEMCL

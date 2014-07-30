#ifndef TESTFRAME_H
#define TESTFRAME_H

#include <stdio.h>
#include <vector>
#define CHECK(X) if (!(X)) { log=#X; return false; }
#define CHECKNOT(X) if (X) { log=#X; return false; }
#define CASE_SUCCESS return true;

class AbstractCase
{
public:
	virtual bool Go() = 0;
	std::string name;
	std::string log;
};
std::vector<AbstractCase*> __cases;

#define CASE_CLASS(NAME) CASECLASS##NAME

#define DEF_CASE(NAME)\
	class CASE_CLASS(NAME):public AbstractCase\
	{\
	public:\
		CASE_CLASS(NAME)() { name = #NAME; __cases.push_back(this); }\
		bool Go();\
	} CASE_CLASS(NAME)##INSTANCE;\
	bool CASE_CLASS(NAME)::Go()

#define DEF_CASE2(NAME1,NAME2) DEF_CASE(NAME1##_##NAME2)

void TestAllCases() 
{
	int succ_num = 0;
	int fail_num = 0;
	for (int i=0; i<__cases.size(); i++)
	{	
		if (__cases[i]->Go())
			printf("[  OK  ] %s\n",__cases[i]->name.c_str()),
			succ_num++;
		else
			printf("[ FAIL ] %s \t\t\t when %s\n",__cases[i]->name.c_str(),__cases[i]->log.c_str()),
			fail_num++;
	}
	printf(	"\n" "[REPORT]    Success: %d    Fail: %d    Total: %d \n",succ_num,fail_num,succ_num+fail_num);
}

#endif
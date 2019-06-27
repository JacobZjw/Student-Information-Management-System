#include "pch.h"
#include "Student.h"

Student::Student()
{
}
Student ::~Student()
{
}
void Student::Sum()
{
	int Math = atoi(math);//类型转换
	int Program = atoi(program);
	int all = Math + Program;
	_itoa_s(all, sum, 10);//写入类中
}
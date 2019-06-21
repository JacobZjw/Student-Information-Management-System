#pragma once
class Student
{
public:
	Student();
	~Student();
	char name[20];
	int ID;
	bool gender;
	float math;
	float program;
	float sum;
	float Sum();
	friend class Management;
};


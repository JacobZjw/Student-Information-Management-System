#pragma once
class Student
{
public:
	Student();
	~Student();
	char name[20];
	char ID[20];
	bool gender;
	char math[5];
	char program[5];
	char sum[5];
	void Sum();
	friend class Management;
};


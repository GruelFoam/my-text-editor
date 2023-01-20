#pragma once
#include"LinkList.h"

class Line
{
public:
	LinkList<char>* line;
	Line* nextLine;
	Line* preLine;
	int charNum;
	Line();
	int Length();
	bool Insert(int position, char e);
	Line& operator=(const Line& source);
	bool Delete(int position, char& e);
	~Line();
};


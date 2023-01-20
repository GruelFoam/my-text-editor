#pragma once
#include"Line.h"
#include"Helper.h"

class Editor
{
private:
	Line* textBuffer;
	fstream inFile;
	char* inFileDest;
	//ofstream outFile;
	Line* curRowNo;
	int curColNo;

	void Up();
	void Down();
	void Left();
	void Right();
	void Delete_front();
	void Del();
	void StartNewLine();
	void ReadFile();
	Line* ReadHelp(fstream &input, char& last);
	void InsertChar(char c);
public:
	//int lineNum;
	//Editor(char infName[], char outfName[]);
	Editor(char fName[]);
	void ShowText(Node<char>* one);
	void ClearText(Line* templine, int pos);
	bool Empty() const;
	void WriteFile();
	void Run();
	void ClearHelp();
	virtual ~Editor();
};


template<class Type>
void Show(const Type& data) {
	cout << data << ' ';
}

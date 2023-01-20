//#ifdef EDITOR_HEAD
#include"Editor.h"


void Editor::Run() {
	char commend = '\0';
	if (Empty()) {
		curRowNo = nullptr;
		curColNo = 0;
	}
	else {
		system("cls");
		cout << "———————————My file name: "<< inFileDest << "————————————" << endl;
		curRowNo = textBuffer->nextLine;//初始化坐标
		curColNo = 1;
		Line* temp_line = textBuffer->nextLine;
		while (temp_line != nullptr) {//初始化打印
			cout << "|";
			ShowText(temp_line->line->head->next);
			cout << endl;
			temp_line = temp_line->nextLine;
		}
		GoToxy(1, 1);//光标初始化
	}
	while (1) {
		commend = _getch();
		if (commend == -32) {
			char c = _getch();
			switch (c) {
			case 72:
				Up();
				break;
			case 80:
				Down();
				break;
			case 75:
				Left();
				break;
			case 77:
				Right();
				break;
			case 83:
				Del();
				break;
			}
			
		}
		else {//处理常规字符
			if (commend >= 32 && commend <= 127) {
				InsertChar(commend);
			}
			switch (commend) {
			case 19:
				WriteFile();//文件保存
				break;
			case 27://esc强制退出
				ClearHelp();
				return;
				break;
			case 8:
				Delete_front();
				break;
			case 13:
				StartNewLine();
					break;
			}
		}
	}
}

void Editor::StartNewLine() {

	//else {
		ClearText(curRowNo, curColNo);//得先清空！！！！！！！！！！
		cout << endl;
		Line* newLine = new Line;
		int pos = 1;
		char temp = '\0';
		while (curRowNo->Delete(curColNo, temp)) {
			newLine->Insert(pos++, temp);
		}
		newLine->nextLine = curRowNo->nextLine;
		newLine->preLine = curRowNo;
		if (curRowNo->nextLine != nullptr) {
			curRowNo->nextLine->preLine = newLine;
		}
		curRowNo->nextLine = newLine;

		int x, y;
		Getxy(x, y);
		Line* temp_line = newLine;
		while (temp_line != nullptr) {//初始化打印
			int tx, ty;
			Getxy(tx, ty);
			cout << ' ';
			ClearText(temp_line->nextLine, 1);
			GoToxy(tx, ty);
			cout << "|";
			ShowText(temp_line->line->head->next);
			cout << endl;
			temp_line = temp_line->nextLine;
		}
		curRowNo = newLine;
		curColNo = 1;
		GoToxy(1, y);
	//}
}

//---------------------------------------------------------
//---------------------------------------------------------
//删除相关
void Editor::Delete_front() {
	int x, y;
	Getxy(x, y);
	char useless;
	if (x > 1) {
		curColNo--;
		curRowNo->Delete(x - 1, useless);
		Node<char>* temp = curRowNo->line->Getptr(curColNo);
		GoToxy(x - 1, y);
		ShowText(temp);
		GoToxy(x - 1, y);
	}
	else if (curRowNo->preLine == textBuffer) {
		return;
	}
	else {
		ClearText(curRowNo, curColNo);//得先清空！！！！！！！！！！
		char usefull;
		int target_x = curColNo = curRowNo->preLine->Length() + 1;
		int index = curRowNo->preLine->Length();
		while (curRowNo->Delete(1, usefull)) {
			curRowNo->preLine->Insert(++index, usefull);
		}

		Line* temp_line = curRowNo;
		curRowNo = curRowNo->preLine;
		curRowNo->nextLine = temp_line->nextLine;
		if (temp_line->nextLine != nullptr) {
			temp_line->nextLine->preLine = curRowNo;
		}
		delete temp_line;//处理存储结构
		
		GoToxy(1, y - 1);
		
		ShowText(curRowNo->line->head->next);
		cout << endl;
		temp_line = curRowNo->nextLine;
		while (temp_line != nullptr) {//初始化打印
			cout << "|";
			ShowText(temp_line->line->head->next);
			cout << endl;
			int tx, ty;
			Getxy(tx, ty);
			cout << ' ';//消除下一行的”|“
			ClearText(temp_line, 1);
			GoToxy(tx, ty);
			temp_line = temp_line->nextLine;
		}
		cout << ' ';//消除后面不用行的”|“
		GoToxy(curColNo, y - 1);
	}
}

void Editor::Del() {
	int x, y;
	Getxy(x, y);
	if (x <= curRowNo->Length()) {
		char useless;
		curRowNo->Delete(x, useless);
		Node<char>* temp = curRowNo->line->Getptr(x);
		ShowText(temp);
		GoToxy(x, y);
	}
	else if (curRowNo->nextLine == nullptr) {
		return;
	}
	else {
		Line* nextone = curRowNo->nextLine;
		//ShowText(nextone->line->head->next);
		//nextone = nextone->nextLine;
		//cout << endl;
		while (nextone != nullptr) {//初始化打印
			if (nextone != curRowNo->nextLine) {
				cout << "|";
			}
			ShowText(nextone->line->head->next);
			cout << endl;
			int tx, ty;
			Getxy(tx, ty);
			cout << ' ';//消除下一行的”|“
			ClearText(nextone, 1);
			GoToxy(tx, ty);
			nextone = nextone->nextLine;
		}
		cout << ' ';//消除后面不用行的”|“


		nextone = curRowNo->nextLine;
		char usefull;
		int index = curRowNo->Length()+1;
		while (nextone->Delete(1, usefull)) {
			curRowNo->Insert(index, usefull);
			index++;
		}
		curRowNo->nextLine = nextone->nextLine;
		if (nextone->nextLine != nullptr) {
			nextone->nextLine->preLine = curRowNo;
		}
		delete nextone;
		GoToxy(x, y);
	}
}
//---------------------------------------------------------
//---------------------------------------------------------

void Editor::Up() {
	if (curRowNo->preLine == textBuffer) {
		//cout << "first line" << endl;
		return;
	}
	Line* tempLine = curRowNo->preLine;//目标行先赋值给tempLine
	int x, y;
	Getxy(x, y);
	x = min(tempLine->Length()+1, x);
	GoToxy(x, y - 1);//以上处理外部坐标

	curRowNo = curRowNo->preLine;
	curColNo = x;//以上处理内部坐标
}

void Editor::Down() {
	if (curRowNo->nextLine == nullptr) {
		return;
	}
	Line* tempLine = curRowNo->nextLine;//目标行先赋值给tempLine
	int x, y;
	Getxy(x, y);
	x = min(tempLine->Length() + 1, x);//+1！！！！！！
	GoToxy(x, y + 1);//以上处理外部坐标

	curRowNo = curRowNo->nextLine;
	curColNo = x;//以上处理内部坐标
}

void Editor::Left() {
	int x, y;
	Getxy(x, y);
	if (x <= 1) {
		if (curRowNo->preLine == textBuffer) {
			return;
		}
		curRowNo = curRowNo->preLine;
		curColNo = curRowNo->Length() + 1;//处理内部坐标
		GoToxy(curRowNo->Length() + 1, y - 1);
		return;
	}
	GoToxy(x - 1, y);//处理外部坐标
	curColNo--;//处理内部坐标
}

void Editor::Right() {
	int x, y;
	Getxy(x, y);
	if (x > curRowNo->Length()) {//?
		if(curRowNo->nextLine == nullptr){
			return;
		}
		curRowNo = curRowNo->nextLine;
		curColNo = 1;//处理内部坐标
		GoToxy(1, y + 1);
		return;
	}
	GoToxy(x + 1, y);//处理外部坐标
	curColNo++;//处理内部坐标
}




void Editor::ClearHelp() {
	Line* templine = textBuffer->nextLine;
	Line* deleteline;
	textBuffer->nextLine = nullptr;
	while (templine != nullptr) {
		deleteline = templine;
		templine = templine->nextLine;
		delete deleteline;//此处有问题，主要是空的行的删除问题
	}
}

Editor::~Editor() {
	ClearHelp();
}

//Editor::Editor(char infName[], char outfName[]) : inFile(infName), outFile(outfName) {
Editor::Editor(char fName[]) {

	inFile.open(fName, ios::in|ios::app);
	if (!inFile) {
		cout << endl << "打开文件失败！" << endl;
		system("pause");
		exit(1);
	}
	inFileDest = new char[100];
	strcpy_s(inFileDest, strlen(fName)+1, fName);
	
	textBuffer = new Line;
	ReadFile();

}

void Editor::ReadFile() {
	bool proceed = true;
	char terminalchar;
	Line* last = textBuffer;
	while (proceed) {
		Line *temp = 	ReadHelp(inFile, terminalchar);
		if (terminalchar == EOF) {
			proceed = false;
			if (temp->Length() > 0) {
				temp->preLine = last;
				last->nextLine = temp;
				//lineNum++;
			}
		}
		else {
			temp->preLine = last;
			last->nextLine = temp;
			last = last->nextLine;
			//lineNum++;
		}
	}
	if (Empty()) {
		Line* em = new Line;
		curRowNo = em;
		em->preLine = textBuffer;
		textBuffer->nextLine = em;
		curColNo = 1;
	}
	else {
		curRowNo = textBuffer->nextLine;
		curColNo = 1;
	}
}

Line* Editor::ReadHelp(fstream& input, char& last) {
	Line* templist = new Line;
	int position = 1;
	char ch;
	while ((ch = input.peek()) != EOF && (ch = input.get()) != '\n') {
		templist->Insert(position++, ch);
	}
	last = ch;
	//不存回车符
	return templist;
}

void Editor::WriteFile() {
	Line* templist = textBuffer;
	char tempch;
	inFile.close();
	inFile.open(inFileDest, ios::ate | ios::out);//清空之前的文件内容，写入保存内容
	while (templist->nextLine != nullptr) {
		templist = templist->nextLine;
		int i = 1;
		while (templist->line->GetElem(i, tempch)) {
			inFile.put(tempch);
			i++;
		}
		if (templist->nextLine != nullptr) {
			inFile.put('\n');
		}
	}
}

void Editor::ShowText(Node<char>* one) {//从所给的字符节点开始打印（\n与EOF除外)
	if (one == nullptr) {
	}
	else {
		Node<char>* temp = one;
		while (temp != nullptr) {
			cout << temp->data;
			temp = temp->next;
		}
	}
	cout << ' ';//去除删除字符时本行最后字符bug
}

void Editor::ClearText(Line* templine, int pos) {//从所给的字符节点开始clear
	if (templine == nullptr) {
		return;
	}
	for (int i = pos; i <= templine->Length(); i++) {
		cout << ' ';
	}
}

bool Editor::Empty() const{
	return textBuffer->nextLine == nullptr;
}

void Editor::InsertChar(char c) {
	_putch(c);
	curRowNo->Insert(curColNo, c);
	curColNo++;//内部坐标处理

	int now_x, now_y;//外部坐标处理
	Getxy(now_x, now_y);
	Node<char>* now_char = curRowNo->line->Getptr(curColNo);
	ShowText(now_char);
	GoToxy(now_x, now_y);
}

//#endif

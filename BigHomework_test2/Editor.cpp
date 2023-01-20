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
		cout << "����������������������My file name: "<< inFileDest << "������������������������" << endl;
		curRowNo = textBuffer->nextLine;//��ʼ������
		curColNo = 1;
		Line* temp_line = textBuffer->nextLine;
		while (temp_line != nullptr) {//��ʼ����ӡ
			cout << "|";
			ShowText(temp_line->line->head->next);
			cout << endl;
			temp_line = temp_line->nextLine;
		}
		GoToxy(1, 1);//����ʼ��
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
		else {//�������ַ�
			if (commend >= 32 && commend <= 127) {
				InsertChar(commend);
			}
			switch (commend) {
			case 19:
				WriteFile();//�ļ�����
				break;
			case 27://escǿ���˳�
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
		ClearText(curRowNo, curColNo);//������գ�������������������
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
		while (temp_line != nullptr) {//��ʼ����ӡ
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
//ɾ�����
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
		ClearText(curRowNo, curColNo);//������գ�������������������
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
		delete temp_line;//����洢�ṹ
		
		GoToxy(1, y - 1);
		
		ShowText(curRowNo->line->head->next);
		cout << endl;
		temp_line = curRowNo->nextLine;
		while (temp_line != nullptr) {//��ʼ����ӡ
			cout << "|";
			ShowText(temp_line->line->head->next);
			cout << endl;
			int tx, ty;
			Getxy(tx, ty);
			cout << ' ';//������һ�еġ�|��
			ClearText(temp_line, 1);
			GoToxy(tx, ty);
			temp_line = temp_line->nextLine;
		}
		cout << ' ';//�������治���еġ�|��
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
		while (nextone != nullptr) {//��ʼ����ӡ
			if (nextone != curRowNo->nextLine) {
				cout << "|";
			}
			ShowText(nextone->line->head->next);
			cout << endl;
			int tx, ty;
			Getxy(tx, ty);
			cout << ' ';//������һ�еġ�|��
			ClearText(nextone, 1);
			GoToxy(tx, ty);
			nextone = nextone->nextLine;
		}
		cout << ' ';//�������治���еġ�|��


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
	Line* tempLine = curRowNo->preLine;//Ŀ�����ȸ�ֵ��tempLine
	int x, y;
	Getxy(x, y);
	x = min(tempLine->Length()+1, x);
	GoToxy(x, y - 1);//���ϴ����ⲿ����

	curRowNo = curRowNo->preLine;
	curColNo = x;//���ϴ����ڲ�����
}

void Editor::Down() {
	if (curRowNo->nextLine == nullptr) {
		return;
	}
	Line* tempLine = curRowNo->nextLine;//Ŀ�����ȸ�ֵ��tempLine
	int x, y;
	Getxy(x, y);
	x = min(tempLine->Length() + 1, x);//+1������������
	GoToxy(x, y + 1);//���ϴ����ⲿ����

	curRowNo = curRowNo->nextLine;
	curColNo = x;//���ϴ����ڲ�����
}

void Editor::Left() {
	int x, y;
	Getxy(x, y);
	if (x <= 1) {
		if (curRowNo->preLine == textBuffer) {
			return;
		}
		curRowNo = curRowNo->preLine;
		curColNo = curRowNo->Length() + 1;//�����ڲ�����
		GoToxy(curRowNo->Length() + 1, y - 1);
		return;
	}
	GoToxy(x - 1, y);//�����ⲿ����
	curColNo--;//�����ڲ�����
}

void Editor::Right() {
	int x, y;
	Getxy(x, y);
	if (x > curRowNo->Length()) {//?
		if(curRowNo->nextLine == nullptr){
			return;
		}
		curRowNo = curRowNo->nextLine;
		curColNo = 1;//�����ڲ�����
		GoToxy(1, y + 1);
		return;
	}
	GoToxy(x + 1, y);//�����ⲿ����
	curColNo++;//�����ڲ�����
}




void Editor::ClearHelp() {
	Line* templine = textBuffer->nextLine;
	Line* deleteline;
	textBuffer->nextLine = nullptr;
	while (templine != nullptr) {
		deleteline = templine;
		templine = templine->nextLine;
		delete deleteline;//�˴������⣬��Ҫ�ǿյ��е�ɾ������
	}
}

Editor::~Editor() {
	ClearHelp();
}

//Editor::Editor(char infName[], char outfName[]) : inFile(infName), outFile(outfName) {
Editor::Editor(char fName[]) {

	inFile.open(fName, ios::in|ios::app);
	if (!inFile) {
		cout << endl << "���ļ�ʧ�ܣ�" << endl;
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
	//����س���
	return templist;
}

void Editor::WriteFile() {
	Line* templist = textBuffer;
	char tempch;
	inFile.close();
	inFile.open(inFileDest, ios::ate | ios::out);//���֮ǰ���ļ����ݣ�д�뱣������
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

void Editor::ShowText(Node<char>* one) {//���������ַ��ڵ㿪ʼ��ӡ��\n��EOF����)
	if (one == nullptr) {
	}
	else {
		Node<char>* temp = one;
		while (temp != nullptr) {
			cout << temp->data;
			temp = temp->next;
		}
	}
	cout << ' ';//ȥ��ɾ���ַ�ʱ��������ַ�bug
}

void Editor::ClearText(Line* templine, int pos) {//���������ַ��ڵ㿪ʼclear
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
	curColNo++;//�ڲ����괦��

	int now_x, now_y;//�ⲿ���괦��
	Getxy(now_x, now_y);
	Node<char>* now_char = curRowNo->line->Getptr(curColNo);
	ShowText(now_char);
	GoToxy(now_x, now_y);
}

//#endif

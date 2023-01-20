#include "Line.h"

Line::Line() {
	line = new LinkList<char>;
	nextLine = nullptr;
	preLine = nullptr;
	charNum = 0;
}

int Line::Length() {
	return charNum;
}

bool Line::Insert(int position, char e) {
	if (position < 1 || position > charNum + 1) {
		return false;
	}
	line->Insert(position, e);
	charNum++;
	return true;
}

Line& Line::operator=(const Line& source) {
	line->Copy(source.line);
	charNum = source.charNum;
	nextLine = source.nextLine;
	preLine = source.preLine;
	return *this;
}

bool Line::Delete(int position, char& e) {
	if (line->Delete(position, e)) {
		charNum--;
		return true;
	}
	return false;
}

Line::~Line() {
	if (line != nullptr) {
		line->Clear();
	}
}
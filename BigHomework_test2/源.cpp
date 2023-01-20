#include"Editor.h"
void modeset(int w, int h) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = { w, h };
	SetConsoleScreenBufferSize(hOut, size);
	SMALL_RECT rc = { 1,1, w, h };
	SetConsoleWindowInfo(hOut, true, &rc);
	//system("cls");
	return;
}

int main() {
	system("color F0");
	LPCWSTR title = TEXT("Reed's VIM");
	SetConsoleTitle(title);
	modeset(70, 25);

	//system("mode con cols=80 lines=40 ");
	while (1) {
		system("cls");
		cout << "Welcome to use Reed's VIM!" << endl;
		cout << "Please input your file name: ";
		char in[100];
		char c;
		int i = 0;
		while (1) {
			c = _getch();
			if (c == 27) {
				exit(0);
			}
			else if (c >= 32 && c <= 127) {
				cout << c;
				in[i] = c;
				i++;
			}
			else if (c == 8) {
				if (i > 0) {
					int x, y;
					Getxy(x, y);
					GoToxy(x - 1, y);
					cout << ' ';
					GoToxy(x - 1, y);
					i--;
					in[i] = '\0';
				}
			}
			else if (c == 13) {
				if (i == 0) {
					continue;
				}
				in[i] = '\0';
				break;
			}
		}
		Editor first(in);
		first.Run();
		//cout << "complete!";
		//first.WriteFile();
	}
}

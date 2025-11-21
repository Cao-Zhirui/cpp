#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <ctime>

using namespace std;

void waitForEnter();
bool checkWin(int board[4][4]);
void printMenu(), printHelp(), printExit(), printInterface(int board[4][4], int score, int step);
void initBoard(int board[4][4]);
void generateNewNumber(int board[4][4]);
bool hasEmptyCell(int board[4][4]), canMove(int board[4][4]);
void transpose(int board[4][4]), flip(int board[4][4]);
bool moveLeft(int board[4][4], int& score), moveRight(int board[4][4], int& score), 
	 moveUp(int board[4][4], int& score), moveDown(int board[4][4], int& score);

void playGame() {
	int board[4][4] = {};
	int score = 0;
	int step = 0;
	char choice = '\0';
	bool moved;		//是否有效移动
	bool gameWon = false;    //记录是否已达2048

	initBoard(board);	//游戏初始化
	printInterface(board, score, step);	

	while (1) {
		choice = _getch();

		if (choice == 27) break;	//ESC

		switch (choice) {	 //上下左右移动
		case 75: moved = moveLeft(board, score); break;
		case 77: moved = moveRight(board, score); break;
		case 72: moved = moveUp(board, score); break;
		case 80: moved = moveDown(board, score); break;
		default: continue;
		}

		if (moved) {
			step++;
			generateNewNumber(board);
			printInterface(board, score, step);

			if (!gameWon && checkWin(board)) {		//首次合成2048
				gameWon = true;
				cout << "\n恭喜合成了 2048！是否继续游戏？(y/n): ";
				char ch = _getche();
				if (ch != 'y') {
					break;
				}
			}

			if (!canMove(board)) break;		//游戏结束
		}
	}
	printExit();
}

int main(){
	char choice = '\0';		//用户选择
	SetConsoleTitle(TEXT("2048"));
	while (1){	// 主循环
		printMenu();

		choice = _getche();

		switch (choice){
		case 'a':
			playGame();
			break;
		case 'b':
			printHelp();
			break;
		case 'c':
			return 0;
		default:
			cout << "\n输入无效，请从新输入" << endl;
			waitForEnter();
		}
	}
	return 0;
}

void waitForEnter(){
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

void printMenu(){	//显示主菜单
	system("CLS");
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                   2048\n";
	cout << "                a.经典模式\n";
	cout << "                b.游戏规则\n";
	cout << "                c.退出游戏\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "\n请输入你的选择(a-c):";
}

void printHelp(){	//显示帮助
	system("CLS");
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "--------------------------------------------\n";
	cout << "********************************************\n\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "操作说明：\n\n";
	cout << "↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	cout << "游戏介绍：\n\n";
	cout << "每次选择一个方向移动，移动时数字向该方向靠拢\n";
	cout << "相同数字可合并，移动后空格处会生成随机数字2/4\n";
	cout << "如果得到数字2048，则游戏胜利!\n";
	cout << "如果棋盘被数字填满，无法进行移动，则游戏失败!\n\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "********************************************\n";
	cout << "--------------------------------------------\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	waitForEnter();
}

void printExit() {		//游戏结束
	cout << "\n游戏结束！按enter键退出";
	waitForEnter();
}

void printInterface(int board[4][4], int score, int step){		//显示游戏界面
	system("CLS");
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            --------------------------------------------\n";
	cout << "            分数：" << setw(6) << score << "              步数：" << setw(6) << step << endl;
	cout << "            --------------------------------------------\n";
	cout << "            ********************************************\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                       |----|----|----|----|\n";

	for (int i = 0; i < 4; i++){
		cout << "                       |";
		for (int j = 0; j < 4; j++){
			if (board[i][j] != 0){
				cout << setw(4) << board[i][j] << "|";
			}
			else{
				cout << "    |";
			}
		}
		cout << "\n                       |----|----|----|----|\n";
	}

	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "            ********************************************\n";
	cout << "            --------------------------------------------\n";
	cout << "            ↓：下   ←：左  ↑：上  →：右  ESC键：退出\n\n";
	SetConsoleTextAttribute(handle_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void initBoard(int board[4][4]) {		//游戏初始化
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}

	srand(time(0));		//生成随机种子
	int x = rand() % 4;
	int y = rand() % 4;
	board[x][y] = (rand() % 2 == 0) ? 2 : 4;
}

bool canMove(int board[4][4]) {		//检测是否能移动
	if (hasEmptyCell(board)) return true;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j < 4 - 1 && board[i][j] == board[i][j + 1]) return true;
			if (i < 4 - 1 && board[i][j] == board[i + 1][j]) return true;
		}
	}

	return false;
}

bool hasEmptyCell(int board[4][4]) {	//检测是否有空格
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

void generateNewNumber(int board[4][4]) {	//随机生成新数字
	if (!hasEmptyCell(board)) return;

	int x, y;
	do {
		x = rand() % 4;
		y = rand() % 4;
	} while (board[x][y] != 0);

	board[x][y] = (rand() % 2 == 0) ? 2 : 4; 
}

void transpose(int board[4][4]) {	//转置
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			swap(board[i][j], board[j][i]);
		}
	}
}

void flip(int board[4][4]) {	//翻转
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			swap(board[i][j], board[i][3 - j]);
		}
	}
}

bool moveLeft(int board[4][4], int& score) {	//左移
	bool moved = false;

	for (int i = 0; i < 4; i++) {	
		int pos = 0;		
		for (int j = 0; j < 4; j++) {	//紧凑所有数字
			if (board[i][j] != 0) {
				if (j != pos) {
					board[i][pos] = board[i][j];
					board[i][j] = 0;
					moved = true;
				}
				pos++;
			}
		}

		for (int j = 0; j < 3; j++) {	
			if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {	//合并数字
				int newValue = board[i][j] * 2;
				score += newValue;  
				board[i][j] = newValue;
				board[i][j + 1] = 0;
				moved = true;

				for (int k = j + 1; k < 3; k++) {	//后面数字左移一格
					board[i][k] = board[i][k + 1];
				}
				board[i][3] = 0;
			}
		}
	}

	return moved;
}

bool moveRight(int board[4][4], int& score) {	//右移：翻转+左移+翻转
    flip(board);  
    bool moved = moveLeft(board, score);  
    flip(board);  

    return moved;
}

bool moveUp(int board[4][4], int& score) {	  //上移：转置+左移+转置
    transpose(board);  
    bool moved = moveLeft(board, score);
    transpose(board);  

    return moved;
}

bool moveDown(int board[4][4], int& score) {	//下移：转置+翻转+左移+翻转+转置
    transpose(board);  
    flip(board);  
    bool moved = moveLeft(board, score);
    flip(board);  
    transpose(board);  

    return moved;
}

bool checkWin(int board[4][4]) {	//检测是否合成2048
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}
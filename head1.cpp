#include"head1.h"

//全局变量定义                  0   1    2     3   4    5
const string style[4][7] = { {"┌","┐","─","└","┘","│"}
							 ,{"╔","╗","═","╚","╝","║"}
							 ,{"┏","┓","━","┗","┛","┃"}
							 ,{"╭","╮","─","╰","╯","│"} };
static string cur_style[7] = { style[0][0],style[0][1],style[0][2],style[0][3],style[0][4],style[0][5],style[0][6] };
const string Trg = "[]";
const string Blk = "  ";
const string Bok = "  ";
int num_style;
int level_target_line[10] = { 5,15,30,50,75,105,140,180,225,275 };
//按键原子变量
std::atomic<int>Pressedchar(-1);
std::atomic<bool> running(true);
std::atomic<bool> ifReadKey(true);
//方块数组
bool _O[4][4] = { {0,0,0,0},{0,1,1,0},{0,1,1,0,},{0,0,0,0} };

bool _L[4][4][4] = {
{
	{0,0,0,0},
	{0,0,1,0},
	{1,1,1,0},
	{0,0,0,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,0},
	{1,0,0,0},
},
{
	{0,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
}
};

bool _J[4][4][4] = {
{
	{0,0,0,0},
	{1,0,0,0},
	{1,1,1,0},
	{0,0,0,0},
},
{
	{0,0,0,0},
	{0,1,1,0},
	{0,1,0,0},
	{0,1,0,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,0},
	{0,0,1,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{1,1,0,0},
}
};

bool _Z[4][4][4] = {
{
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0},
},
{
	{0,0,0,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,1,0,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{1,1,0,0},
	{1,0,0,0},
}
};

bool _N[4][4][4] = {
{
	{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,1,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
},
{
	{0,0,0,0},
	{1,0,0,0},
	{1,1,0,0},
	{0,1,0,0},
}
};

bool _T[4][4][4] = {
{
	{0,0,0,0},
	{0,1,0,0},
	{1,1,1,0},
	{0,0,0,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,1,0,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,0},
	{0,1,0,0},
},
{
	{0,0,0,0},
	{0,1,0,0},
	{1,1,0,0},
	{0,1,0,0},
}
};

bool _I[4][4][4] = {
{
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
	{0,0,0,0},
},
{
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
	{0,0,1,0},
},
{
	{0,0,0,0},
	{0,0,0,0},
	{1,1,1,1},
	{0,0,0,0},
},
{
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
}
};
//record
long int record_easy = -1;
long int record_mid = -1;
long int record_hard = -1;
double record_40lines = -1;
int record_2min = -1;

//系统控制
/*void tabmove(int row, int list) {
	cout << "\033[" << row << ";" << list << "H";
}
void tabivs(bool a) {
	if (a) {
		cout << "\033[?25h";
	}
	else {
		cout << "\033[?25l";
	}
}
void set_fore_color(int id) {
	cout << "\033[38;5;" << id << "m";
}
void set_back_color(int id) {
	cout << "\033[48;5;" << id << "m";
}
void reset_color() {
	cout << "\033[0m";
}
void screen_clean() {
	system("cls");
}*/

//系统控制
void tabmove(int row, int list) {
	//cout << "\033[" << row << ";" << list << "H";

	COORD pos = { list, row }; // 定义一个COORD结构体来保存坐标
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台的输出句柄
	SetConsoleCursorPosition(output, pos); // 设置光标位置
}
void tabivs(bool a) {
	if (a) {
		//cout << "\033[?25h";
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 20; // 光标大小（1到100的范围）
		cursorInfo.bVisible = TRUE; // 光标是否可见
		SetConsoleCursorInfo(consoleHandle, &cursorInfo); // 应用设置
	}
	else {
		//cout << "\033[?25l";
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.dwSize = 1; // 光标大小（1到100的范围）
		cursorInfo.bVisible = FALSE; // 光标是否可见
		SetConsoleCursorInfo(consoleHandle, &cursorInfo); // 应用设置
	}
}
void set_fore_color(int id) {
	//cout << "\033[38;5;" << id << "m";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	// 获取当前的屏幕缓冲区信息
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	// 应用新的文本颜色，保持背景颜色不变
	SetConsoleTextAttribute(hConsole, (consoleInfo.wAttributes & 0xF0) | id);
}
void set_back_color(int id) {
	//cout << "\033[48;5;" << id << "m";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	// 获取当前的屏幕缓冲区信息
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	// 应用新的背景颜色，保持文本颜色不变
	SetConsoleTextAttribute(hConsole, (id << 4) | (consoleInfo.wAttributes & 0x0F));
}
void reset_color() {
	//cout << "\033[0m";
	set_fore_color(7);
	set_back_color(0);
}
void screen_clean() {
	system("cls");
}


//帧率
int getfps() {
	//静态变量声明，只在开始执行一次
	static auto start = std::chrono::steady_clock::now();
	static auto end = start;
	static int fps = 0;
	static int frame_count = 0;

	frame_count++;
	end = std::chrono::steady_clock::now();
	if (end - start > 1s) {
		start = end;
		fps = frame_count;
		frame_count = 0;
	}
	return fps;
}
//按键检测
void check_key() {
	while (running) {
		if (_kbhit()) {
			Pressedchar = _getch();
			if (Pressedchar == 0 || Pressedchar == 224) {
				Pressedchar = _getch();
			}
		}
	}
	std::this_thread::sleep_for(10ms);
}
int get_key() {
	int tmp = Pressedchar;
	//使用后就重置为1
	Pressedchar = -1;
	return tmp;
}


//画图
/*
	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
Notes┌─┐└─┘
	 │
1.^ As of Unicode version 15.1
*/
void set_style(int id) {
	num_style = id;
	for (int i = 0; i < 7; i++) {
		cur_style[i] = style[id][i];
	}

}
void draw_block(int x, int y, int width, int height, string title, int kind) {//实际内部宽度2*width-4，内部高度height-2     外部宽度2*width-1，外部高度height，
	int _x = 2 * x - 1;
	int _width = 2 * width;
	int x_title_start = width - title.length() / 2;
	int x_title_end = x_title_start + title.length();
	//打印格子
	tabmove(y, _x);//第一行
	for (int j = 0; j < _width; j++) {
		if (j == 0) {
			cout << " " << cur_style[0];
			j++;
		}
		else if (j == x_title_start) {//打印标题
			cout << title;
			j += title.length();
		}
		else if (j == _width - 1) {
			cout << cur_style[1];
		}
		else {
			cout << cur_style[2];
		}
	}
	tabmove(y + height - 1, _x);//最后行
	for (int j = 0; j < _width - 1; j++) {
		if (j == 0) {
			cout << " " << cur_style[3];
			j++;
		}
		else if (j == _width - 2) {
			cout << cur_style[4];
		}
		else {
			cout << cur_style[2];
		}
	}

	//第一列
	for (int i = 1; i < height - 1; ++i) {
		tabmove(y + i, _x);
		cout << ' ' << cur_style[5];
	}
	//最后列
	for (int i = 1; i < height - 1; ++i) {
		tabmove(y + i, _x + width * 2 - 3);
		cout << ' ' << cur_style[5];
	}


}
void draw_gamebroad() {
	tabivs();
	set_style(num_style);
	screen_clean();
	draw_block(1, 1, 8, 4, "Hold");
	draw_block(1, 5, 8, 18, "Status");
	draw_block(9, 1, 12, 22, "Tetris");
	draw_block(21, 1, 8, 16, "Next");
	draw_block(21, 17, 8, 6, "Info");
}
//游戏底层
double time_counter(bool isrenew) {
	static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	static std::chrono::steady_clock::time_point end = start;
	if (isrenew) {
		start = std::chrono::steady_clock::now();
		end = start;
		return 0;
	}
	else {
		end = std::chrono::steady_clock::now();
		return std::chrono::duration<double>(end - start).count();
	}
}
void copy_Group(bool(&arr)[4][4], const bool(&_arr)[4][4]) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			arr[i][j] = _arr[i][j];
		}
	}
}
void tab_move_Grid(int row, int list) {
	tabmove(to_prey_y - row, to_prey_x + 2 * list - 2);
};
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
}
int random_bag7(bool reset) {
	static int bag[7] = { 0, 1, 2, 3, 4, 5, 6 };
	static int index = 0; // 当index为7时，表示需要重新打乱数组
	srand((unsigned)time(NULL));
	if (index == 7 || reset) {
		for (int i = 0; i < 7; i++) {
			swap(bag[i], bag[rand() % 7]);
		}
		index = 0;
	}

	return bag[index++];
}
//游戏高层
void start_game(int mode) {
	Map map = Map(mode);
	map.init();
	map.play();
	map.end();
}
void savegame() {
	std::ofstream savegameFile("savegame");

	// 检查文件是否成功打开
	if (savegameFile) {
		savegameFile << num_style << std::endl;
		savegameFile << record_easy << std::endl;
		savegameFile << record_mid << std::endl;
		savegameFile << record_hard << std::endl;
		savegameFile << record_40lines << std::endl;
		savegameFile << record_2min << std::endl;
	}

	// 关闭文件
	savegameFile.close();
}
void readgame() {
	std::ifstream savegameFile("savegame");

	if (savegameFile) {
		// File exists - read the data
		savegameFile >> num_style;
		savegameFile >> record_easy;
		savegameFile >> record_mid;
		savegameFile >> record_hard;
		savegameFile >> record_40lines;
		savegameFile >> record_2min;
		savegameFile.close();
	}
	else {
		// File doesn't exist - create it with default values
		std::ofstream newFile("savegame");
		if (newFile) {
			// Set default values
			num_style = 0;
			record_easy = 0;
			record_mid = 0;
			record_hard = 0;
			record_40lines = 0;
			record_2min = 0;

			// Write default values to file
			newFile << num_style << " ";
			newFile << record_easy << " ";
			newFile << record_mid << " ";
			newFile << record_hard << " ";
			newFile << record_40lines << " ";
			newFile << record_2min;

			newFile.close();
		}
		else {
			// Handle file creation error
			std::cerr << "Error: Could not create savegame file" << std::endl;
		}
	}
}
void start_() {
	readgame();
	set_style(num_style);
	tabivs();
}
//菜单末端函数
void introduce() {
	draw_block(menu_width + 1, 1, menu_width * 4+1, menu_height, "Info");
	tabmove(2, menu_width * 2 + 3);
	cout << "Menu Control: 1.Up/Down/Left/Right Arrow Keys";
	tabmove(3, menu_width * 2 + 3 + 12);
	cout << "Control menu selection";
	tabmove(4, menu_width * 2 + 3 + 10);
	cout << "2.Esc Key";
	tabmove(5, menu_width * 2 + 3 + 12);
	cout << "Exit";

	tabmove(6, menu_width * 2 + 3);
	cout << "Game Control: 1.Up/Down/Left/Right Arrow Keys";
	tabmove(7, menu_width * 2 + 3 + 12);
	cout << "Control movement, Up key rotates";
	tabmove(8, menu_width * 2 + 3 + 10);
	cout << "2.Spacebar";
	tabmove(9, menu_width * 2 + 3 + 12);
	cout << "Quickly lock the block";
	tabmove(10, menu_width * 2 + 3 + 10);
	cout << "3.C Key";
	tabmove(11, menu_width * 2 + 3 + 12);
	cout << "Store/take out block (limited)";
	tabmove(12, menu_width * 2 + 3 + 10);
	cout << "4.A Key";
	tabmove(13, menu_width * 2 + 3 + 12);
	cout << "Flip (rotate twice)";
	tabmove(14, menu_width * 2 + 3 + 10);
	cout << "5.Esc Key";
	tabmove(15, menu_width * 2 + 3 + 12);
	cout << "Exit, press any key to return";
}
void clean_introduce() {
	for (int i = 1; i < menu_height + 1; i++) {
		tabmove(i, menu_width * 2 + 2);
		cout << "                                                ";
	}

}
void game_easy() {
	start_game(1);
}
void game_mid() {
	start_game(2);
}
void game_hard() {
	start_game(3);
}
void game_40lines() {
	start_game(4);
}
void game_2min() {
	start_game(5);
}
void style_1() {
	set_style(0);
}
void style_2() {
	set_style(1);
}
void style_3() {
	set_style(2);
}
void style_4() {
	set_style(3);
}
void show_record() {
	draw_block(menu_width * 2 + 1, 1, menu_width * 2, menu_height, "Record");

	tabmove(2, menu_width * 4 + 3);
	set_fore_color(2);
	cout << "Classic-Eassy: ";
	if (record_easy == -1) {
		cout << "None";
	}
	else {
		cout << record_easy;
	}


	tabmove(4, menu_width * 4 + 3);
	set_fore_color(1);
	cout << "Classic-Mid: ";
	if (record_mid == -1) {
		cout << "None";
	}
	else {
		cout << record_mid;
	}

	tabmove(6, menu_width * 4 + 3);
	set_fore_color(4);
	cout << "Classic-Hard: ";
	if (record_hard == -1) {
		cout << "None";
	}
	else {
		cout << record_hard;
	}

	std::ios_base::fmtflags original_flags = std::cout.flags();
	std::cout << std::fixed << std::setprecision(2);
	tabmove(8, menu_width * 4 + 3);
	set_fore_color(6);
	cout << "40 Lines: ";
	if (record_40lines == -1) {
		cout << "None";
	}
	else {
		cout << record_40lines << 's';
	}
	std::cout.flags(original_flags);

	tabmove(10, menu_width * 4 + 3);
	set_fore_color(5);
	cout << "2 min: ";
	if (record_2min == -1) {
		cout << "None";
	}
	else {
		cout << record_2min << "lines";
	}

	reset_color();
}
void hide_record() {
	for (int i = 1; i < menu_height + 1; i++) {
		tabmove(i, menu_width * 4 + 2);
		cout << "                                  ";
	}
}
void my__exit() {
	savegame();
}
void support() {
	LPCWSTR url = L"https://github.com/Mis-Mar";
	 //使用默认浏览器打开网址
	ShellExecute(0, L"open", url, 0, 0, SW_SHOW);
}

//菜单类
int Menu::rank = 0;//静态变量
Menu::Menu(const string& title, const int& color_id) :title(title), title_color(color_id) {
}
void Menu::set_title(const string& _title, const int& _color_id) {
	title = _title;
	title_color = _color_id;
}
void Menu::add_option(Menu* submenu) {
	submenu->parent = this;

	subtitles.push_back(submenu->title);
	this->color_id.push_back(submenu->title_color);
	this->actions.push_back(nullptr);
	isbounch.push_back(1);

	submenus.push_back(submenu);
}
void Menu::add_option(const string& subtitle, std::function<void()> action, const int& color_id) {
	subtitles.push_back(subtitle);
	this->color_id.push_back(color_id);
	this->actions.push_back(action);
	isbounch.push_back(0);

	submenus.push_back(nullptr);
}
void Menu::display(bool clear, bool choose) {
	if (clear) {
		clean_self();
	}

	set_fore_color(title_color);
	draw_block(1 + rank * menu_width, 1, menu_width, menu_height, title);

	int gap = (double)(menu_height - 2) / subtitles.size();
	for (int i = 0; i < subtitles.size(); i++) {
		tabmove((gap * i + 3), 3 + rank * menu_width * 2);
		set_fore_color(color_id[i]);
		if (i == option) {
			if (choose) {
				set_back_color(6);
			}
			else {
				set_back_color(8);
			}
		}
		//画sub标题和下划线
		cout << subtitles[i];
		for (int j = 0; j < (menu_width * 2 - 4 - subtitles[i].length()); j++) {
			cout << '_';
		}
		reset_color();
	}
	reset_color();
}
void Menu::clean_self() {

	for (int i = 1; i <= menu_height; i++) {
		tabmove(i, 1 + rank * menu_width * 2);
		for (int j = 1; j <= menu_width * 2; j++) {

			cout << ' ';
		}
	}
}
void Menu::display_parent() {
	if (parent) {
		rank--;
		parent->display(0, 0);
		parent->display_parent();
		rank++;
	}
}
void Menu::excute() {
	bool running = 1;
	int pressedchar = -1;
	bool change_option = 1;
	int last_option = option;
	display(1);
	//
	while (running) {
		//按下按键
		if (_kbhit()) {
			pressedchar = _getch();
			if (pressedchar == 0 || pressedchar == 224) {
				pressedchar = _getch();
			}
			switch (pressedchar)
			{
			case 72://上
				if (0 < option) {
					last_option = option;
					option--;
					change_option = 1;
					display();
				}
				break;
			case 80://下
				if (option < isbounch.size() - 1) {
					last_option = option;
					option++;
					change_option = 1;
					display();
				}
				break;
			case 75://回退
				if (title == "Menu") {
				}
				else {
					running = 0;
				}
				rank++;
				if (subtitles[option] == "Info") {//如果上一个是说明，要消除干净
					clean_introduce();
				}
				else if (subtitles[option] == "Record") {
					hide_record();
				}
				else {
					clean_self();
				}
				rank--;
				break;
			case 77://进入
				if (isbounch[option]) {//有分支
					display(0, 0);
					rank++;
					submenus[option]->excute();
					submenus[option]->display(0, 0);
					rank--;
					display(1);
				}
				else {//无分支
					actions[option]();
					display_parent();
					display(0, 1);
				}

				break;
			case 27:

				if (title == "Menu") {
					running = 0;
				}

				tabmove(menu_height + 2, 1);
				break;
			default:
				break;
			}
		}
		if (change_option) {//刷新子菜单
			if (isbounch[option]) {
				if (subtitles[last_option] == "Info") {//如果上一个是说明，要消除干净
					clean_introduce();
				}
				else if (subtitles[last_option] == "Record") {
					hide_record();
				}
				rank++;
				submenus[option]->display(1, 0);
				rank--;
			}
			else {
				if (subtitles[option] == "Info") {//单独展示说明
					clean_introduce();
					introduce();
				}
				else if (subtitles[option] == "Record") {
					hide_record();
					show_record();
				}
				else {
					if (subtitles[last_option] == "Record") {
						hide_record();
					}
					rank++;
					clean_self();
					set_fore_color(color_id[option]);
					draw_block(1 + rank * menu_width, 1, menu_width, 3, subtitles[option]);
					tabmove(2, 1 + rank * menu_width * 2 + 2);
					cout << "Press->";
					reset_color();
					rank--;
				}

			}
			change_option = 0;
		}

		pressedchar = -1;
		std::this_thread::sleep_for(10ms);
	}

}


//坐标类
Position::Position(int row, int list) :row(row), list(list) {}
//方格类
Grid::Grid(int cdt, int id) : cdt(cdt), id(id) {}
ostream& operator<<(ostream& os, const Grid& grid) {
	switch (grid.cdt)
	{
	case -1:
		set_back_color(grid.id);
		cout << Trg;
		reset_color();
		break;
	case 0:
		cout << Blk;
		break;
	case 1:
		set_back_color(grid.id);
		cout << Bok;
		reset_color();
		break;
	default:
		break;
	}

	return os;
}
Grid& Grid::operator=(const Grid& other) {
	if (this != &other) { // 防止自赋值
		cdt = other.cdt;
		id = other.id;
	}
	return *this; // 返回当前对象的引用
}

//组类
Group::Group(int kind_id) :kind_id(kind_id) {
	switch (kind_id) {
	case 0:
		color_id = 14;
		rotate_rate = 0;
		copy_Group(relative_position, _O);
		break;
	case 1:
		color_id = 6;
		rotate_rate = 0;
		copy_Group(relative_position, _L[0]);
		break;
	case 2:
		color_id = 1;
		rotate_rate = 0;
		copy_Group(relative_position, _J[0]);
		break;
	case 3:
		color_id = 4;
		rotate_rate = 0;
		copy_Group(relative_position, _Z[0]);
		break;
	case 4:
		color_id = 2;
		rotate_rate = 0;
		copy_Group(relative_position, _N[0]);
		break;
	case 5:
		color_id = 5;
		rotate_rate = 0;
		copy_Group(relative_position, _T[0]);
		break;
	case 6:
		color_id = 9;
		rotate_rate = 0;
		copy_Group(relative_position, _I[0]);
		break;
	default:
		color_id = 14;
		rotate_rate = 0;
		copy_Group(relative_position, _O);
		break;
	}
}
void Group::rotate() {
	rotate_rate = (rotate_rate + 1) % 4;
	switch (kind_id) {
	case 0:
		break;
	case 1:
		copy_Group(relative_position, _L[rotate_rate]);
		break;
	case 2:
		copy_Group(relative_position, _J[rotate_rate]);
		break;
	case 3:
		copy_Group(relative_position, _Z[rotate_rate]);
		break;
	case 4:
		copy_Group(relative_position, _N[rotate_rate]);
		break;
	case 5:
		copy_Group(relative_position, _T[rotate_rate]);
		break;
	case 6:
		copy_Group(relative_position, _I[rotate_rate]);
		break;
	}
}
void Group::back_rotate() {
	rotate_rate = (rotate_rate - 1 + 4) % 4;
	switch (kind_id) {
	case 0:
		break;
	case 1:
		copy_Group(relative_position, _L[rotate_rate]);
		break;
	case 2:
		copy_Group(relative_position, _J[rotate_rate]);
		break;
	case 3:
		copy_Group(relative_position, _Z[rotate_rate]);
		break;
	case 4:
		copy_Group(relative_position, _N[rotate_rate]);
		break;
	case 5:
		copy_Group(relative_position, _T[rotate_rate]);
		break;
	case 6:
		copy_Group(relative_position, _I[rotate_rate]);
		break;
	}
}
Group& Group::operator= (const Group& other) {
	if (this != &other) {
		color_id = other.color_id;
		kind_id = other.kind_id;
		rotate_rate = other.rotate_rate;
		copy_Group(relative_position, other.relative_position);
	}
	return *this;
}

//地图类
Map::Map(int mode) :mode(mode) {
	//基础
	grids = vector<vector<Grid>>(23, vector<Grid>(10, Grid()));
	ishold = 0;
	can_hold = 1;
	//游戏性设置
	cdt = 1;
	gravity = 1;
	level = 0;
	//数据
	score = 0;
	num_lines = 0;
}
void Map::init() {
	draw_gamebroad();
	random_bag7(1);
	time_counter(1);
	groups = { Group(random_bag7()),Group(random_bag7()), Group(random_bag7()),Group(random_bag7()),Group(random_bag7()) };
	center = Position(23, 4);
	turn_group();
	running = 1;
}
void Map::play() {
	renew_menu();
	show_group();
	to_down();
	//std::thread keyThread(check_key);
	switch (mode)
	{
	case 4:
		gravity = 1.2;
	default:
		break;
	}

	while (cdt == 1) {
		if (_kbhit()) {
			Pressedchar = _getch();
			if (Pressedchar == 0 || Pressedchar == 224) {
				Pressedchar = _getch();
			}
			if (!ifReadKey) {
				Pressedchar = 0;
			}
		}
		ifReadKey = true;
		//自动下降
		auto_down();
		//操作检测
		switch (get_key()) {
		case 75:
			to_left();
			break;
		case 77:
			to_right();
			break;
		case 80:
			to_down();
			break;
		case 72:
			to_rotate();
			break;
		case 97:
			to_rollover();
			break;
		case 32:
			group_jamp();
			break;
		case 99:
			hold();
			break;
		case 27://
			cdt = 0;
			break;
		}

		//数据处理
		switch (mode)
		{
		case 1:
		case 2:
		case 3:
			if (level < 10 && (num_lines - level_target_line[level]) >= 0) {//level up
				level++;
				gravity += mode * 0.5;
			}
			break;
		case 4:
			if (num_lines >= 40) {
				cdt = 2;
			}
			break;
		case 5:
			if (time_counter() >= 120) {
				cdt = 2;
			}
			break;
		default:
			break;
		}

		//画面展示
		switch (mode)
		{
		case 1:
		case 2:
		case 3:
			show_level();
			show_fps();
			show_score();
			show_time();
			break;
		case 4:
			show_time(7);
			show_targetlines();
			show_fps();
			break;
		case 5:
			show_resttime();
			show_lines();
			show_fps();
			break;
		default:
			break;
		}

		std::this_thread::sleep_for(10ms);
	}
	//结束按键线程
	running = 0;
	//keyThread.join();
}

void Map::end() {
	readgame();
	screen_clean();


	double time = time_counter();
	int lines = num_lines;

	if (cdt == 0) {
		switch (mode)
		{
		case 1:
			if (record_easy == -1) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your First Record:" << score << " +" << score << "new";
				record_easy = score;
				savegame();
				reset_color();
			}
			else if (score > record_easy) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << score << " +" << score - record_easy << "new";
				record_easy = score;
				savegame();
				reset_color();
			}
			else {
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_easy;
			}

			break;
		case 2:
			if (record_mid == -1) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your First Record:" << score << " +" << score << "new";
				record_mid = score;
				savegame();
				reset_color();
			}
			else if (score > record_mid) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << score << " +" << score - record_mid << "new";
				record_mid = score;
				savegame();
				reset_color();
			}
			else {
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_mid;
			}
			break;
		case 3:
			if (record_hard == -1) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your First Record:" << score << " +" << score << "new";
				record_hard = score;
				savegame();
				reset_color();
			}
			else if (score > record_hard) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << score << " +" << score - record_hard << "new";
				record_hard = score;
				savegame();
				reset_color();
			}
			else {
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Score is:" << score;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_hard;
			}
			break;

		default:
			draw_block(end_x, end_y, end_width, end_height, "Game Over");
			break;
		}
	}
	else {
		switch (mode)
		{
		case 1:
		case 2:
		case 3:
			break;
		case 4:


			if (record_40lines == -1) {
				std::ios_base::fmtflags original_flags = std::cout.flags();
				std::cout << std::fixed << std::setprecision(2);
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Time is:" << time << 's';
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your First Record is:" << time << 's';
				record_40lines = time;
				savegame();
				reset_color();
				std::cout.flags(original_flags);
			}
			else if (time < record_40lines) {
				std::ios_base::fmtflags original_flags = std::cout.flags();
				std::cout << std::fixed << std::setprecision(2);
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Time is:" << time << 's';
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << time << 's' << ' ' << time - record_40lines << "new";
				record_40lines = time;
				savegame();
				reset_color();
				std::cout.flags(original_flags);
			}
			else {
				std::ios_base::fmtflags original_flags = std::cout.flags();
				std::cout << std::fixed << std::setprecision(2);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "Your Time is:" << time << 's';
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_40lines << 's';
				std::cout.flags(original_flags);
			}
			break;
		case 5:
			if (record_2min == -1) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "lines:" << lines;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your First Record:" << lines;
				record_2min = lines;
				savegame();
				reset_color();
			}
			else if (lines > record_2min) {
				set_fore_color(6);
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "lines:" << lines;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_2min << " +" << lines - record_2min << "new";
				record_2min = lines;
				savegame();
				reset_color();
			}
			else {
				;
				draw_block(end_x, end_y, end_width, end_height, "Game Over");
				tabmove(end_y + 1, end_x * 2 + 2);
				cout << "lines:" << lines;
				tabmove(end_y + 2, end_x * 2 + 2);
				cout << "Your Record is:" << record_2min;
			}

			break;
		default:
			cout << "Game Over";
			break;
		}
	}
	Sleep(2000);
	bool exit = 0;
	while (!exit) {
		if (_kbhit()) {
			exit = 1;
		}
		std::this_thread::sleep_for(10ms);
	}
	screen_clean();
}

void Map::renew_menu() {
	//hold界面
	if (ishold) {
		if (can_hold) {
			print_group(hold_y, hold_x, hold_group.kind_id);
		}
		else {//变灰
			print_group(hold_y, hold_x, hold_group.kind_id, 8);
		}
	}
	//next界面
	int k = 0;
	for (auto it = groups.begin(); k < 5; k++, it++) {
		print_group(next_y + 3 * k, next_x, it->kind_id);
	}

}
void Map::print_group(int y, int x, int kind_id, int color_id) {
	//清除
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			tabmove(y + i - 1, x + 2 * j);
			cout << Blk;
		}
	}
	//预处理
	bool temp[4][4];
	int _color_id;
	switch (kind_id)
	{
	case 0:
		_color_id = 14;
		copy_Group(temp, _O);
		break;
	case 1:
		_color_id = 6;
		copy_Group(temp, _L[0]);
		x += 1;
		break;
	case 2:
		_color_id = 1;
		copy_Group(temp, _J[0]);
		x += 1;
		break;
	case 3:
		_color_id = 4;
		copy_Group(temp, _Z[0]);
		x += 1;
		break;
	case 4:
		_color_id = 2;
		copy_Group(temp, _N[0]);
		x += 1;
		break;
	case 5:
		_color_id = 5;
		copy_Group(temp, _T[0]);
		x += 1;
		break;
	case 6:
		_color_id = 9;
		copy_Group(temp, _I[0]);
		y += 1;
		break;
	default:
		_color_id = 14;
		copy_Group(temp, _O);
		break;
	}
	if (color_id == -1) {
		set_back_color(_color_id);
	}
	else {
		set_back_color(color_id);
	}
	//绘制
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (temp[i][j]) {
				tabmove(y + i - 1, x + 2 * j);
				cout << Bok;
			}

		}
	}
	reset_color();
}

bool Map::check_position(int row, int list) {
	if (0 < row && row < 23 && 0 < list && list < 11 && grids[row - 1][list - 1].cdt == 0) {
		return true;
	}
	else {
		return false;
	}
}
void Map::renew_gird(int row, int list) {
	if (0 < row && row < 21 && 0 < list && list < 11) {
		tab_move_Grid(row, list);
		cout << grids[row - 1][list - 1];
	}

}

void Map::shine_grid(int row, int list) {
	if (0 < row && row < 21 && 0 < list && list < 11) {
		tab_move_Grid(row, list);
		set_back_color(7);
		cout << Bok;
		reset_color();
		std::this_thread::sleep_for(30ms);
	}
}

void Map::shine_line(int row) {
	if (0 < row && row < 21) {
		set_back_color(7);
		for (int i = 1; i <= List; i++) {
			tab_move_Grid(row, i);
			cout << Bok;
		}
		reset_color();
		std::this_thread::sleep_for(50ms);
	}
}
void Map::renew_map() {
	for (int i = 1; i <= 22; i++) {
		for (int j = 1; j <= 10; j++) {
			renew_gird(i, j);
		}
	}
}

void Map::show_level(int row) {
	tabmove(row, 4);
	cout << "Level:";
	tabmove(row + 1, 6);
	cout << level << " ";
}
void Map::show_fps(int row) {
	tabmove(row, 4);
	cout << "FPS:" << getfps() << " ";
}
void Map::show_score(int row) {
	tabmove(row, 4);
	cout << "Score:";
	tabmove(row + 1, 6);
	cout << score << " ";
}
void Map::show_time(int row) {
	std::ios_base::fmtflags original_flags = std::cout.flags();
	std::cout << std::fixed << std::setprecision(2);

	tabmove(row, 4);
	cout << "Time:";
	tabmove(row + 1, 6);
	cout << time_counter();

	std::cout.flags(original_flags);
}
void Map::show_targetlines(int row) {
	tabmove(row, 4);
	cout << "Lines:";
	tabmove(row + 1, 6);
	cout << num_lines << "/40";
}

void Map::show_lines(int row) {
	tabmove(row, 4);
	cout << "Lines:";
	tabmove(row + 1, 6);
	cout << num_lines << " ";
}

void Map::show_resttime(int row) {
	std::ios_base::fmtflags original_flags = std::cout.flags();
	std::cout << std::fixed << std::setprecision(2);

	tabmove(row, 4);
	cout << "Time:";
	tabmove(row + 1, 6);
	cout << (120 - time_counter());

	std::cout.flags(original_flags);
}

void Map::renew_group() {
	hide_shadow();
	set_shadow();
	show_group();
}
void Map::show_group() {
	show_shadow();
	set_back_color(cur_group.color_id);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j] && 0 < (center.row - i) && (center.row - i) < 21 && 0 < (center.list + j) && (center.list + j) < 11)
			{
				tab_move_Grid(center.row - i, center.list + j);
				cout << Bok;
			}
		}
	}
	reset_color();
}

void Map::hide_group() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j] && 0 < (center.row - i) && (center.row - i) < 21 && 0 < (center.list + j) && (center.list + j) < 11)
			{
				tab_move_Grid(center.row - i, center.list + j);
				cout << Blk;
			}
		}
	}
}

bool Map::check_group_to(int add_row, int add_list) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j])
			{
				if (!check_position(center.row - i + add_row, center.list + j + add_list)) {
					return false;
				}
			}
		}
	}
	return true;
}

void Map::turn_group() {
	cur_group = groups.front();
	groups.pop_front();
	groups.push_back(Group(random_bag7()));
}

void Map::group_to_grid() {
	bool if_line_to_grid[] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j])
			{
				if_line_to_grid[i] = 1;
				grids[center.row - i - 1][center.list + j - 1].cdt = 1;
				grids[center.row - i - 1][center.list + j - 1].id = cur_group.color_id;
				renew_gird(center.row - i, center.list + j);
				shine_grid(center.row - i, center.list + j);//展示动画
			}
		}
	}
	int t = 0;
	for (int i = 0; i < 4; i++) {
		//当鉴定为满时
		if (if_line_to_grid[i] && check_row(center.row - i)) {
			clean_row(center.row - i);
			shine_line(center.row - i);
			num_lines++;//记录
			t++;
		}
	}
	//加分
	score += 100 * t * (1 + 0.2 * (t - 1));
	//刷新地图
	renew_map();
	//刷新hold
	can_hold = 1;
	ifReadKey = false;
	creat_group();
}
void Map::creat_group() {
	center = Position(23, 4);
	turn_group();
	//更新菜单
	renew_menu();

	if (check_group_to(0, 0))
	{
		set_shadow();
		renew_group();
	}//判定输
	else {
		cdt = 0;
	}

}
void Map::group_jamp() {
	hide_group();
	center.list = shadow.list;
	center.row = shadow.row;
	group_to_grid();
}
void Map::auto_down(bool isPause) {
	static auto start = std::chrono::steady_clock::now();
	static auto end = start;

	end = std::chrono::steady_clock::now();
	if (end - start > (1000ms) / gravity) {
		start = end;
		if (to_down()) {
		}
		else {
			group_to_grid();
		}
	}
}

void Map::set_shadow() {
	for (int i = 1;; i++) {
		if (!check_group_to(-i, 0)) {
			shadow.row = center.row - i + 1;
			shadow.list = center.list;
			break;
		}
	}
}

void Map::show_shadow() {
	set_fore_color(cur_group.color_id);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j] && 0 < (shadow.row - i) && (shadow.row - i) < 21 && 0 < (shadow.list + j) && (shadow.list + j) < 11)
			{
				tab_move_Grid(shadow.row - i, shadow.list + j);
				cout << Trg;
			}
		}
	}
	reset_color();
}

void Map::hide_shadow() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cur_group.relative_position[i][j] && 0 < (shadow.row - i) && (shadow.row - i) < 21 && 0 < (shadow.list + j) && (shadow.list + j) < 11)
			{
				tab_move_Grid(shadow.row - i, shadow.list + j);
				cout << Blk;
			}
		}
	}
}

void Map::to_left() {
	hide_group();
	if (check_group_to(0, -1)) {
		center.list--;
	}
	renew_group();
}
void Map::to_right() {
	hide_group();
	if (check_group_to(0, 1)) {
		center.list++;
	}
	renew_group();
}
bool Map::to_down() {
	hide_group();
	if (check_group_to(-1, 0)) {
		center.row--;
		renew_group();
		return 1;
	}
	else {
		show_group();
		return 0;
	}

}
bool Map::to_rotate() {
	hide_group();
	hide_shadow();
	cur_group.rotate();
	int rotate_rate = cur_group.rotate_rate;
	bool can_rotate = 0;
	int move_row = 0;
	int move_list = 0;
	switch (cur_group.kind_id)
	{
	case 0://O
		can_rotate = 1;
		break;
	case 1://L
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, -1)) {
				can_rotate = 1;
				move_row = 1, move_list = -1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, 1)) {
				can_rotate = 1;
				move_row = -1, move_list = 1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(1, 1)) {
				can_rotate = 1;
				move_row = 1, move_list = 1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(-1, -1)) {
				can_rotate = 1;
				move_row = -1, move_list = -1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
		}
		break;
	case 2://J
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, -1)) {
				can_rotate = 1;
				move_row = 1, move_list = -1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, 1)) {
				can_rotate = 1;
				move_row = -1, move_list = 1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(1, 1)) {
				can_rotate = 1;
				move_row = 1, move_list = 1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(-1, -1)) {
				can_rotate = 1;
				move_row = -1, move_list = -1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
		}
		break;
	case 3://Z
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, -1)) {
				can_rotate = 1;
				move_row = 1, move_list = -1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, 1)) {
				can_rotate = 1;
				move_row = -1, move_list = 1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(1, 1)) {
				can_rotate = 1;
				move_row = 1, move_list = 1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(-1, -1)) {
				can_rotate = 1;
				move_row = -1, move_list = -1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
		}
		break;
	case 4://N
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, -1)) {
				can_rotate = 1;
				move_row = 1, move_list = -1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, 1)) {
				can_rotate = 1;
				move_row = -1, move_list = 1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(1, 1)) {
				can_rotate = 1;
				move_row = 1, move_list = 1;
			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(-1, -1)) {
				can_rotate = 1;
				move_row = -1, move_list = -1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
		}
		break;
	case 5://T
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, -1)) {
				can_rotate = 1;
				move_row = 1, move_list = -1;
			}
			else if (check_group_to(-2, 0)) {//无法实现

			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, 1)) {
				can_rotate = 1;
				move_row = -1, move_list = 1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(1, 1)) {//无法实现

			}
			else if (check_group_to(-2, 0)) {
				can_rotate = 1;
				move_row = -2, move_list = 0;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(-1, -1)) {
				can_rotate = 1;
				move_row = -1, move_list = -1;
			}
			else if (check_group_to(2, 0)) {
				can_rotate = 1;
				move_row = 2, move_list = 0;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
		}
		break;
	case 6://I
		if (rotate_rate == 0) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -2)) {
				can_rotate = 1;
				move_row = 0, move_list = -2;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(-1, -2)) {
				can_rotate = 1;
				move_row = -1, move_list = 2;
			}
			else if (check_group_to(2, 1)) {
				can_rotate = 1;
				move_row = 2, move_list = 1;
			}

		}
		else if (rotate_rate == 1) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(0, 2)) {
				can_rotate = 1;
				move_row = 0, move_list = 2;
			}
			else if (check_group_to(2, -1)) {
				can_rotate = 1;
				move_row = 2, move_list = -1;
			}
			else if (check_group_to(-1, 2)) {
				can_rotate = 1;
				move_row = -1, move_list = 2;
			}
		}
		else if (rotate_rate == 2) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 2)) {
				can_rotate = 1;
				move_row = 0, move_list = 2;
			}
			else if (check_group_to(0, -1)) {
				can_rotate = 1;
				move_row = 0, move_list = -1;
			}
			else if (check_group_to(1, 2)) {
				can_rotate = 1;
				move_row = 1, move_list = 2;
			}
			else if (check_group_to(-2, -1)) {
				can_rotate = 1;
				move_row = -2, move_list = -1;
			}
		}
		else if (rotate_rate == 3) {
			if (check_group_to(0, 0)) {
				can_rotate = 1;
				move_row = 0, move_list = 0;
			}
			else if (check_group_to(0, 1)) {
				can_rotate = 1;
				move_row = 0, move_list = 1;
			}
			else if (check_group_to(0, -2)) {
				can_rotate = 1;
				move_row = 0, move_list = -2;
			}
			else if (check_group_to(-2, 1)) {
				can_rotate = 1;
				move_row = -2, move_list = 1;
			}
			else if (check_group_to(1, -2)) {
				can_rotate = 1;
				move_row = 1, move_list = -2;
			}
		}
		break;
	default:
		break;
	}

	if (can_rotate) {
		center.row += move_row;
		center.list += move_list;

		set_shadow();
		show_shadow();
		show_group();
		return true;
	}
	else {
		cur_group.back_rotate();
		renew_group();
		return false;
	}
}

void Map::to_rollover() {
	to_rotate();
	to_rotate();
}

void Map::hold() {
	if (can_hold) {
		if (ishold) {
			hide_group();
			hide_shadow();
			center = Position(23, 4);
			//互换
			Group tmp;
			tmp = hold_group;
			hold_group = Group(cur_group.kind_id);
			cur_group = tmp;
			//
			set_shadow();
			show_group();
			//
			can_hold = 0;
		}
		//第一次hold
		else {
			hide_group();
			hide_shadow();
			hold_group = Group(cur_group.kind_id);
			creat_group();
			ishold = 1;
		}
	}
	//更新菜单
	renew_menu();
}

bool Map::check_row(int row) {
	for (int i = 0; i < 10; i++) {
		if (grids[row - 1][i].cdt == 0) {
			return false;
		}
	}
	return true;
}
void Map::clean_row(int row) {
	//消除
	for (int i = 1; i <= 10; i++) {
		grids[row - 1][i - 1] = 0;
	}
	//grid信息下移
	for (int i = row; i <= 22; i++) {
		for (int j = 1; j <= 10; j++) {
			grids[i - 1][j - 1] = grids[i][j - 1];
		}
	}
}

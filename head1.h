#pragma once
#include<iostream>
#include<vector>
#include <cstdlib>  
#include <ctime> 
#include<thread>
#include<chrono>
#include <windows.h>
#include<locale>
#include<codecvt>
#include <conio.h>
#include<list>
#include <algorithm>
#include <random> 
#include <array>
#include <iomanip>
#include <functional>
#include <fstream>
#include <ostream>
#include <shellapi.h>




using namespace std::chrono_literals;
using std::string;
using std::cout;
using std::cin;
using std::ostream;
using std::vector;
using std::list;
using std::array;

#define CSI "/033["
#define Row 20
#define List 10
#define to_prey_x 19
#define to_prey_y 22
#define hold_x 5
#define hold_y 2
#define next_x 45
#define next_y 2
#define menu_width 6
#define menu_height 16
#define end_x 6
#define end_y 5
#define end_width 19
#define end_height 4

//terminal control
void tabmove(int row, int list);
void tabivs(bool a = false);
void set_fore_color(int id);
void set_back_color(int id);
void reset_color();
void screen_clean();

//帧率
int getfps();
//按键检测
void check_key();
int get_key();

//画图
void set_style(int id);
void draw_block(int x, int y, int width, int height, string title, int kind = 0);
void draw_gamebroad();

//游戏底层
double time_counter(bool isrenew = 0);
void copy_Group(bool(&arr)[4][4], const bool(&_arr)[4][4]);
void tab_move_Grid(int row, int list);
void swap(int& x, int& y);
int random_bag7(bool reset = 0);
//游戏高层
void start_game(int mode = 1);
void savegame();
void readgame();
void start_();
//菜单末端函数
void introduce();
void clean_introduce();
void game_easy();
void game_mid();
void game_hard();
void game_40lines();
void game_2min();
void style_1();
void style_2();
void style_3();
void style_4();
void show_record();
void hide_record();
void my__exit();
void support();


//菜单
class Menu {
public:
	Menu(const string& title, const int& color_id = 7);
	void set_title(const string& title, const int& color_id = 7);
	void add_option(Menu* submenu);
	void add_option(const string& subtitle, std::function<void()> action, const int& color_id = 7);
	void display(bool clear = 0, bool choose = 1);
	void clean_self();
	void display_parent();
	void excute();

	//private:
	int option;
	string title;
	int title_color;
	static int rank;
	Menu* parent = nullptr;

	vector<Menu*> submenus;

	vector<string>subtitles;
	vector<int> color_id;
	vector<std::function<void()>> actions;
	vector<bool> isbounch;
};


//坐标类
class Position {
public:
	int row;
	int list;
	Position(int row = 1, int list = 1);
};

//方格类
class Grid {
public:
	//状态值： 0表空 1表格子
	int cdt;
	//颜色
	int id;
	//构造函数
	Grid(int cdt = 0, int id = 0);
	//重载cout
	friend ostream& operator<<(ostream& os, const Grid& grid);
	//重载等号
	Grid& operator=(const Grid& other);
};
//组类
class Group {
public:
	Group(int kind_id = 0);
	int color_id;
	int kind_id;
	int rotate_rate;
	bool relative_position[4][4];
	void rotate();
	void back_rotate();
	Group& operator= (const Group& other);
};

//地图类
class Map {
public:
	Map(int mode = 1);
	void init();
	void play();
	void end();
	//protected:
	void renew_menu();
	void print_group(int y, int x, int kind_id, int color_id = -1);

	bool check_position(int row, int list);

	void renew_gird(int row, int list);
	void shine_grid(int row, int list);
	void shine_line(int row);
	void renew_map();

	void show_level(int row = 7);
	void show_fps(int row = 21);
	void show_score(int row = 9);
	void show_time(int row = 11);
	void show_targetlines(int row = 9);
	void show_lines(int row = 9);
	void show_resttime(int row = 7);

	void renew_group();
	void show_group();
	void hide_group();

	bool check_group_to(int add_row, int add_list);
	void turn_group();
	void group_to_grid();
	void creat_group();
	void group_jamp();

	void auto_down(bool isPause=false);

	void set_shadow();
	void show_shadow();
	void hide_shadow();

	void to_left();
	void to_right();
	bool to_down();
	bool to_rotate();
	void to_rollover();
	void hold();

	bool check_row(int row);
	void clean_row(int row);
	//private:
	vector<vector<Grid>> grids;
	Position center;
	Position shadow;
	Group cur_group;
	Group hold_group;
	bool ishold;
	list<Group> groups;
	bool can_hold;

	//游戏性设置
	int cdt;
	int mode;
	int level;
	float gravity;
	//数据
	long int score;
	int num_lines;
};



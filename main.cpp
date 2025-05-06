#include"head1.h"

std::string GetCodePageName(UINT codePage) {
	switch (codePage) {
	case CP_UTF8: return "UTF-8";
	case 936: return "GBK (简体中文)";
	case 950: return "Big5 (繁体中文)";
	case 1252: return "Latin-1 (西欧)";
	case 1200: return "UTF-16 (Little Endian)";
	case 1201: return "UTF-16 (Big Endian)";
	default: return "其他编码" ;
	}
}

void testGetConsoleCP() {
	// 获取当前控制台的输入编码（Console Input CP）
	UINT inputCP = GetConsoleCP();
	std::cout << "┌当前控制台输入编码: " << GetCodePageName(inputCP)
		<< " (CP" << inputCP << ")" << std::endl;
}

void game() {
	start_();
	SetConsoleOutputCP(936);
	Menu main_menu("Menu", 6);
	Menu sub2("Start", 1);
	Menu sub3("Setting", 4);

	Menu sub2_sub1("Classic", 2);

	Menu sub3_sub1("Style", 10);
	Menu sub3_sub2("Record", 7);



	main_menu.add_option("Info", introduce, 7);
	main_menu.add_option(&sub2);
	main_menu.add_option(&sub3);

	sub2.add_option(&sub2_sub1);
	sub2.add_option("40 Lines", game_40lines, 6);
	sub2.add_option("2 min", game_2min, 5);
	sub2_sub1.add_option("Easy", game_easy, 2);
	sub2_sub1.add_option("Mid", game_mid, 2);
	sub2_sub1.add_option("Hard", game_hard, 4);

	sub3.add_option(&sub3_sub1);
	sub3.add_option("Record", show_record);
	sub3.add_option("Github", support, 6);
	sub3.add_option("Save", my__exit, 4);
	sub3_sub1.add_option("Style1", style_1, 10);
	sub3_sub1.add_option("Style2", style_2, 10);
	sub3_sub1.add_option("Style3", style_3, 10);
	sub3_sub1.add_option("Style4", style_4, 10);

	main_menu.excute();
}

int main()
{
	game();
}


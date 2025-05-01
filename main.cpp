#include"head1.h"


int main()
{
	start_();
	Menu main_menu("Menu", 6);
	Menu sub2("Start", 1);
	Menu sub3("Setting", 4);

	Menu sub2_sub1("Classic", 2);

	Menu sub3_sub1("Style", 10);
	Menu sub3_sub2("Record",7);



	main_menu.add_option("Info", introduce,7);
	main_menu.add_option(&sub2);
	main_menu.add_option(&sub3);

	sub2.add_option(&sub2_sub1);
	sub2.add_option("40 Lines", game_40lines, 6);
	sub2.add_option("2 min", game_2min, 5);
	sub2_sub1.add_option("Easy", game_easy,2);
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


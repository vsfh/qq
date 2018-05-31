
#include "beauty.h"
#include "common.h"
#include "sfh_Group.h"
#include "sfh_List.h"
#include "sfh_Person.h"
#include "sfh_weibo.h"
#include "sfh_wechat.h"
#include "sfh_qq.h"
#include "sfh_weix.h"
void setColor(unsigned short ForeColor = 2 | 8, unsigned short BackGroundColor = 0) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeColor | BackGroundColor);
}

void print_time() {
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	printf("local time is:%s", asctime(tblock));
}


void mainmenu() {

	sfh_Person * tmp = NULL;
	int choice = -1;
	while (1)
	{
		system("cls");
		fflush(stdin);
		print_time();
		printf("|---------------------------------------------|\n"
			"|   1. qq   2.微信   3.微博   4.微x   5.退出  |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			tmp = new sfh_qq();  break;
		case 2:
			tmp = new sfh_wechat(); break;
		case 3:
			tmp = new sfh_weibo();  break;
		case 4:
			tmp = new sfh_weix();   break;
		case 5:
			exit(0);    break;
		}
		tmp->menu();
	}
}

void sfh_Person::menu_friends() {//搜索 添加 删除 修改好友备注 查询共同好友 ++
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|------------------好友管理-------------------|\n"
			"|好友列表：                            %5d人|\n", friends.size);
		if (friends.size == 0)
			cout << "|" << setfill(' ') << setw(26) << "NULL" << setw(20) << "|" << endl;
		else
			for (int i = 0; i<friends.size; i++) {
				sfh_Person * tmp = get_person(friends.nodes[i].ID);
				printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"));
			}
		printf("|---------------------------------------------|\n"
			"|      1.搜索好友        2.添加好友           |\n"
			"|      3.修改好友备注    4.删除好友           |\n"
			"|      5.查询共同好友    6.退出               |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			find_friend(); break;
		case 2:
			add_friend(); break;
		case 3:
			set_friend_name(); break;
		case 4:
			del_friend(); break;
		case 5:
			find_common_friend(); break;
		case 6:
			return; break;
		}
		system("pause");
	}

}
void sfh_Person::menu_groups() {//搜索 添加 删除  创建 ---成员管理L：添加 删除 设置名称 设置管理员--
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|--------------------群管理-------------------|\n"
			"|群列表：                              %5d个|\n", groups.size);
		if (groups.size == 0)
			cout << "|" << setfill(' ') << setw(26) << "NULL" << setw(20) << "|" << endl;
		else
			for (int i = 0; i<groups.size; i++) {
				sfh_Person * tmp = get_person(groups.nodes[i].ID);
				printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
			}
		printf("|---------------------------------------------|\n"
			"|      1.添加群				  2.删除群     |\n"
			"|      3.选择群并管理            4.创建群     |\n"
			"|      5.返回							       |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 6)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			add_group(); break;
		case 2:
			del_group(); break;
		case 3:
			group_manage(); break;
		case 4:
			create_group(); break;
		case 5:
			return; break;
		}
		system("pause");
	}
}
void sfh_Person::group_manage() {
	int choice = -1;
	char qq[12];
	printf("请输入要管理的群号： ");
	getstring(qq, 12, ' ');
	if (!sfh_Group::is_Group(qq)) {
		printf("这个群不存在\n");
		return;
	}
	sfh_Group * tmp = sfh_Group::getgroup(qq);
	if (tmp->type != type) {
		printf("这个群不存在%d_%d\n", tmp->type, type);
		return;
	}
	if (!tmp->is_manager(ID)) {
		printf("您不是该群的管理员\n");
		return;
	}
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|------------------群内部管理-----------------|\n"
			"|群成员列表：                          %5d人|\n", friends.size);
		tmp->viewallmem();
		printf("|---------------------------------------------|\n"
			"|      1.添加群成员      2.删除群成员         |\n"
			"|      3.更改群名称      4.设置管理员         |\n"
			"|      5.添加临时讨论组  5.退出群管理         |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			tmp->add_member(); break;
		case 2:
			tmp->del_member(); break;
		case 3:
			tmp->set_name(); break;
		case 4:
			tmp->add_manager(); break;
		case 5:
			create_group();
		case 6:
			return; break;
		}
		system("pause");
	}
}
bool sfh_Group::viewallmem() {
	printf("|管理员:                                      |\n");
	for (int i = 0; i<managers.size; i++)
		printf("|      %-12s     %-20s  |\n", managers.nodes[i].ID, managers.nodes[i].name);
	printf("|群成员:                                      |\n");
	for (int i = 0; i<members.size; i++)
		printf("|      %-12s     %-20s  |\n", members.nodes[i].ID, members.nodes[i].name);
	return 1;
}
void sfh_Person::menu_inf() {//改昵称 改地点 改生日 ++
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|----------------个人信息修改-----------------|\n"
			"|昵称：%-20s  生日：%8s   |\n"
			"|地址：%-39s|\n"
			"|账号申请时间：%d年                        |\n"
			"|---------------------------------------------|\n"
			"|      1.改昵称          2.修改位置           |\n"
			"|      3.修改生日        4.返回               |\n"
			"|---------------------------------------------|\n", get_name(), get_birth(), get_location(), get_usryear());
		choice = getint();
		while (choice < 1 || choice > 4)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			set_name(); break;
		case 2:
			set_location(); break;
		case 3:
			set_birthday(); break;
		case 4:
			return; break;
		}
		system("pause");
	}
}
void sfh_Person::menu_safe() {//改密码 绑定--
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|----------------账户安全管理-----------------|\n"
			"|        1.修改密码        2.绑定关系         |\n"
			"|                    3.返回                   |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 3)
		{
			printf("输入错误，请重新输入\n");
			choice = getint();
		}
		switch (choice) {
		case 1:
			set_password(); break;
		case 2:
			bangding(); break;
		case 3:
			return; break;
		}
		system("pause");
	}
}



void sfh_qq::menu() {
	int choice = -1;
	while (1) {
		fflush(stdin);
		if (!is_log_in()) {
			*this = sfh_qq();
			system("cls");
			print_time();
			printf("|----------------------菜单-------------------|\n"
				"|      1.登录        2.注册       3.返回      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			if (choice == 2)
				myregister();
			else if (choice == 1)
			{
				log_in();
			}
			else {
				return;
			}
			system("pause");
		}
		else {
			choice = -1;
			system("cls");
			print_time();
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(14) << "1.个人信息" << setw(14) << "2.账户安全" << setw(14) << "3.安全退出" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "好友列表：" << setfill(' ') << setw(33) << friends.size << "人|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "群列表：" << setfill(' ') << setw(35) << groups.size << "个|" << endl;
			if (groups.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<groups.size; i++)
				{
					printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(18) << "4.群管理" << setw(18) << "5.好友管理" << setw(10) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			switch (choice) {
			case 1:
				menu_inf(); break;
			case 2:
				menu_safe(); break;
			case 4:
				menu_groups(); break;
			case 5:
				menu_friends(); break;
			case 3:
				log_out(); break;
			}

			sync();
			::sync();
		}
	}
}
void sfh_weibo::menu() {
	int choice = -1;
	while (1) {
		fflush(stdin);
		if (!is_log_in()) {
			*this = sfh_weibo();
			system("cls");
			print_time();
			printf("|----------------------菜单-------------------|\n"
				"|      1.登录        2.注册       3.返回      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			if (choice == 2)
				myregister();
			else if (choice == 1)
			{
				log_in();
			}
			else {
				return;
			}
			system("pause");
		}
		else {
			choice = -1;
			system("cls");
			print_time();
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(14) << "1.个人信息" << setw(14) << "2.账户安全" << setw(14) << "3.安全退出" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "关注列表：" << setfill(' ') << setw(33) << friends.size << "人|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(26) << "4.好友管理" << setw(20) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			switch (choice) {
			case 1:
				menu_inf(); break;
			case 2:
				menu_safe(); break;
			case 4:
				menu_friends(); break;
			case 3:
				log_out(); break;
			}

			sync();
			::sync();
		}
	}
}
void sfh_wechat::menu() {
	int choice = -1;
	while (1) {
		fflush(stdin);
		if (!is_log_in()) {
			*this = sfh_wechat();
			system("cls");
			print_time();
			printf("|----------------------菜单-------------------|\n"
				"|      1.登录        2.注册       3.返回      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			if (choice == 2)
				myregister();
			else if (choice == 1)
			{
				log_in();
			}
			else {
				return;
			}
			system("pause");
		}
		else {
			choice = -1;
			system("cls");
			print_time();
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(14) << "1.个人信息" << setw(14) << "2.账户安全" << setw(14) << "3.安全退出" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "好友列表：" << setfill(' ') << setw(33) << friends.size << "人|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "群列表：" << setfill(' ') << setw(35) << groups.size << "个|" << endl;
			if (groups.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<groups.size; i++)
				{
					printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(18) << "4.群管理" << setw(18) << "5.好友管理" << setw(10) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			switch (choice) {
			case 1:
				menu_inf(); break;
			case 2:
				menu_safe(); break;
			case 4:
				menu_groups(); break;
			case 5:
				menu_friends(); break;
			case 3:
				log_out(); break;
			}

			sync();
			::sync();
		}
	}
}
void sfh_weix::menu() {
	int choice = -1;
	while (1) {
		fflush(stdin);
		if (!is_log_in()) {
			*this = sfh_weix();
			system("cls");
			print_time();
			printf("|----------------------菜单-------------------|\n"
				"|      1.登录        2.注册       3.返回      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			if (choice == 2)
				myregister();
			else if (choice == 1)
			{
				log_in();
			}
			else {
				return;
			}
			system("pause");
		}
		else {
			choice = -1;
			system("cls");
			print_time();
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(14) << "1.个人信息" << setw(14) << "2.账户安全" << setw(14) << "3.安全退出" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "好友列表：" << setfill(' ') << setw(33) << friends.size << "人|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(26) << "4.好友管理" << setw(20) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("输入错误，请重新输入\n");
				choice = getint();
			}
			switch (choice) {
			case 1:
				menu_inf(); break;
			case 2:
				menu_safe(); break;
			case 4:
				menu_friends(); break;
			case 3:
				log_out(); break;
			}

			sync();
			::sync();
		}
	}
}

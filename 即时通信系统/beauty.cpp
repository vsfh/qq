
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
			"|   1. qq   2.΢��   3.΢��   4.΢x   5.�˳�  |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("�����������������\n");
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

void sfh_Person::menu_friends() {//���� ��� ɾ�� �޸ĺ��ѱ�ע ��ѯ��ͬ���� ++
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|------------------���ѹ���-------------------|\n"
			"|�����б�                            %5d��|\n", friends.size);
		if (friends.size == 0)
			cout << "|" << setfill(' ') << setw(26) << "NULL" << setw(20) << "|" << endl;
		else
			for (int i = 0; i<friends.size; i++) {
				sfh_Person * tmp = get_person(friends.nodes[i].ID);
				printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "������" : "����"));
			}
		printf("|---------------------------------------------|\n"
			"|      1.��������        2.��Ӻ���           |\n"
			"|      3.�޸ĺ��ѱ�ע    4.ɾ������           |\n"
			"|      5.��ѯ��ͬ����    6.�˳�               |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("�����������������\n");
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
void sfh_Person::menu_groups() {//���� ��� ɾ��  ���� ---��Ա����L����� ɾ�� �������� ���ù���Ա--
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|--------------------Ⱥ����-------------------|\n"
			"|Ⱥ�б�                              %5d��|\n", groups.size);
		if (groups.size == 0)
			cout << "|" << setfill(' ') << setw(26) << "NULL" << setw(20) << "|" << endl;
		else
			for (int i = 0; i<groups.size; i++) {
				sfh_Person * tmp = get_person(groups.nodes[i].ID);
				printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
			}
		printf("|---------------------------------------------|\n"
			"|      1.���Ⱥ				  2.ɾ��Ⱥ     |\n"
			"|      3.ѡ��Ⱥ������            4.����Ⱥ     |\n"
			"|      5.����							       |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 6)
		{
			printf("�����������������\n");
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
	printf("������Ҫ�����Ⱥ�ţ� ");
	getstring(qq, 12, ' ');
	if (!sfh_Group::is_Group(qq)) {
		printf("���Ⱥ������\n");
		return;
	}
	sfh_Group * tmp = sfh_Group::getgroup(qq);
	if (tmp->type != type) {
		printf("���Ⱥ������%d_%d\n", tmp->type, type);
		return;
	}
	if (!tmp->is_manager(ID)) {
		printf("�����Ǹ�Ⱥ�Ĺ���Ա\n");
		return;
	}
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|------------------Ⱥ�ڲ�����-----------------|\n"
			"|Ⱥ��Ա�б�                          %5d��|\n", friends.size);
		tmp->viewallmem();
		printf("|---------------------------------------------|\n"
			"|      1.���Ⱥ��Ա      2.ɾ��Ⱥ��Ա         |\n"
			"|      3.����Ⱥ����      4.���ù���Ա         |\n"
			"|      5.�����ʱ������  5.�˳�Ⱥ����         |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 5)
		{
			printf("�����������������\n");
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
	printf("|����Ա:                                      |\n");
	for (int i = 0; i<managers.size; i++)
		printf("|      %-12s     %-20s  |\n", managers.nodes[i].ID, managers.nodes[i].name);
	printf("|Ⱥ��Ա:                                      |\n");
	for (int i = 0; i<members.size; i++)
		printf("|      %-12s     %-20s  |\n", members.nodes[i].ID, members.nodes[i].name);
	return 1;
}
void sfh_Person::menu_inf() {//���ǳ� �ĵص� ������ ++
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|----------------������Ϣ�޸�-----------------|\n"
			"|�ǳƣ�%-20s  ���գ�%8s   |\n"
			"|��ַ��%-39s|\n"
			"|�˺�����ʱ�䣺%d��                        |\n"
			"|---------------------------------------------|\n"
			"|      1.���ǳ�          2.�޸�λ��           |\n"
			"|      3.�޸�����        4.����               |\n"
			"|---------------------------------------------|\n", get_name(), get_birth(), get_location(), get_usryear());
		choice = getint();
		while (choice < 1 || choice > 4)
		{
			printf("�����������������\n");
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
void sfh_Person::menu_safe() {//������ ��--
	int choice = -1;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("|----------------�˻���ȫ����-----------------|\n"
			"|        1.�޸�����        2.�󶨹�ϵ         |\n"
			"|                    3.����                   |\n"
			"|---------------------------------------------|\n");
		choice = getint();
		while (choice < 1 || choice > 3)
		{
			printf("�����������������\n");
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
			printf("|----------------------�˵�-------------------|\n"
				"|      1.��¼        2.ע��       3.����      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("�����������������\n");
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
				<< "|" << setfill(' ') << setw(14) << "1.������Ϣ" << setw(14) << "2.�˻���ȫ" << setw(14) << "3.��ȫ�˳�" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "�����б�" << setfill(' ') << setw(33) << friends.size << "��|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "������" : "����"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "Ⱥ�б�" << setfill(' ') << setw(35) << groups.size << "��|" << endl;
			if (groups.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<groups.size; i++)
				{
					printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(18) << "4.Ⱥ����" << setw(18) << "5.���ѹ���" << setw(10) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("�����������������\n");
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
			printf("|----------------------�˵�-------------------|\n"
				"|      1.��¼        2.ע��       3.����      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("�����������������\n");
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
				<< "|" << setfill(' ') << setw(14) << "1.������Ϣ" << setw(14) << "2.�˻���ȫ" << setw(14) << "3.��ȫ�˳�" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "��ע�б�" << setfill(' ') << setw(33) << friends.size << "��|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "������" : "����"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(26) << "4.���ѹ���" << setw(20) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("�����������������\n");
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
			printf("|----------------------�˵�-------------------|\n"
				"|      1.��¼        2.ע��       3.����      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("�����������������\n");
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
				<< "|" << setfill(' ') << setw(14) << "1.������Ϣ" << setw(14) << "2.�˻���ȫ" << setw(14) << "3.��ȫ�˳�" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "�����б�" << setfill(' ') << setw(33) << friends.size << "��|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "������" : "����"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "Ⱥ�б�" << setfill(' ') << setw(35) << groups.size << "��|" << endl;
			if (groups.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<groups.size; i++)
				{
					printf("|     %-12s %-20s       |\n", groups.nodes[i].ID, groups.nodes[i].name);
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(18) << "4.Ⱥ����" << setw(18) << "5.���ѹ���" << setw(10) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("�����������������\n");
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
			printf("|----------------------�˵�-------------------|\n"
				"|      1.��¼        2.ע��       3.����      |\n"
				"|---------------------------------------------|\n");
			choice = getint();
			while (choice < 1 || choice > 3)
			{
				printf("�����������������\n");
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
				<< "|" << setfill(' ') << setw(14) << "1.������Ϣ" << setw(14) << "2.�˻���ȫ" << setw(14) << "3.��ȫ�˳�" << setw(4) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << "�����б�" << setfill(' ') << setw(33) << friends.size << "��|" << endl;
			if (friends.size == 0)
				cout << "|" << setw(26) << "NULL" << setw(20) << "|" << endl;
			else
				for (int i = 0; i<friends.size; i++) {
					sfh_Person * tmp = get_person(friends.nodes[i].ID);
					printf("|     %-12s %-20s %-6s|\n", friends.nodes[i].ID, friends.nodes[i].name, (tmp->get_usrlogmod() == 0 ? "������" : "����"));
				}
			cout << "|" << setfill('-') << setw(46) << "|" << endl
				<< "|" << setfill(' ') << setw(26) << "4.���ѹ���" << setw(20) << "|" << endl
				<< "|" << setfill('-') << setw(46) << "|" << endl;
			choice = getint();
			while (choice < 1 || choice > 5)
			{
				printf("�����������������\n");
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

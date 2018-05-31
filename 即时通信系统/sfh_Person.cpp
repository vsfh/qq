#include "sfh_Person.h"
#include "sfh_Group.h"
#include <stdlib.h>
#include  "function_get.h"


sfh_Person::sfh_Person()
{
	usr_mod = 0;
	usr_rank = 0;
	usr_logmod = 0;
	type = 0;
	usr_year = 0;
	strcpy(qq_bund, "0");
	strcpy(wechat, "0");
	strcpy(weibo, "0");
	strcpy(weix, "0");

}

sfh_Person::sfh_Person(const char*filename)
{
	int i, j, k;
	char t[100];
	FILE * fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("�ļ���ʧ��\n");
	}
	fscanf(fin, "%d", &type);
	fgetc(fin);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(ID, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(password, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(name, t);
	fscanf(fin, "%d%d%d", &i,&j,&k);
	fgetc(fin);
	set_others(i,j,k);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(location, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(birth, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(qq_bund, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(weibo, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(wechat, t);
	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(weix, t);

	fclose(fin);
	usr_logmod = 0;

}

sfh_Person::sfh_Person(const sfh_Person &tmp)
{
	type = tmp.type;
	groups = tmp.groups;
	friends = tmp.friends;
	strcpy(ID, tmp.ID);
	strcpy(password, tmp.password);
	strcpy(name, tmp.name);
	strcpy(birth, tmp.birth);
	strcpy(location, tmp.location);
	usr_logmod = tmp.usr_logmod;
	usr_mod = tmp.usr_mod;
	usr_rank = tmp.usr_rank;
	usr_year = tmp.usr_year;
	strcpy(wechat, tmp.wechat);
	strcpy(weibo, tmp.weibo);
	strcpy(weix, tmp.weix);
	strcpy(qq_bund, tmp.qq_bund);

}

sfh_Person::~sfh_Person()
{
	log_out();
}
//�޸���Ϣ
bool sfh_Person::set_ID(const char * usr_ID)
{
	strcpy(ID, usr_ID);
	return 1;
}

bool sfh_Person::set_name()
{
	char name[20];
	fflush(stdin);
	printf("������������: ");
	getstring(name, 20, ' ');
	if (set_name(name) == true)
		return 1;
	else
		return 0;
}

bool sfh_Person::set_name(const char * usr_name)
{
	strcpy(name, usr_name);
	printf("���ڵ����֣� %s\n", name);
	return 1;
}

bool sfh_Person::set_password()
{
	char pass[20];
	printf("������ԭ��������\n");
	getstring(pass, 20, ' ');
	if (strcmp(pass, password) == 0) {
		printf("�������µ�����: ");
		getstring(pass, 20, ' ');
		set_password(pass);
		printf("�������óɹ�\n");
		return 1;
	}
	else {
		printf("�����������\n");
		return 0;
	}
}

bool sfh_Person::set_password(const char * pass)
{
	strcpy(password, pass);
	return 1;
}

bool sfh_Person::set_birthday()
{
	char bir[20];
	int y = 1999, m = 5, d = 4;
	printf("���������ĳ����꣺ ");
	y = getint();
	if (y > 2019 || y < 1949)
		return 0;
	printf("���������ĳ����£� ");
	m = getint();
	if (!(m <= 12 && m >= 1))
		return 0;
	printf("���������ĳ����գ� ");
	d = getint();
	if (!(d <= 30 && d >= 1))
		return 0;
	fflush(stdin);
	sprintf(bir, "%d%02d%02d", y, m, d);
	return set_birthday(bir);
}
bool sfh_Person::set_birthday(const char * bir) {
	strcpy(birth, bir);
	return 1;
}
bool sfh_Person::set_location()
{
	char loc[20];
	printf("������ص㣺 ");
	getstring(loc, 20, ' ');
	return set_location(loc);
}

bool sfh_Person::set_location(const char * loc)
{
	strcpy(location, loc);
	printf("�ص��������\n");
	return 1;
}

bool sfh_Person::set_others(int y, int r, int k)
{
	usr_year = y;
	usr_rank = r;
	usr_mod =  k;
	return 1;
}


//״̬
 bool sfh_Person::log_in()
{
	 char qq[10], passwd[20];
	 printf("\n");
	 printf("_______________��½________________\n");
	 printf("�������˺ţ� ");
	 getstring(qq, 10, ' ');
	 printf("���������룺 ");
	 getstring(passwd, 20, ' ');
	 if (!is_person(qq)) {
		 printf("���޴���1\n");
		 return 0;
	 }
	 sfh_Person * tmp = get_person(qq);
	 if (tmp->type != type) {
		 printf("���޴���2\n");
		 return 0;
	 }
	 if (strcmp(passwd, tmp->get_password()) == 0) {
		 *this = *tmp;
		 usr_logmod = 1;
		 usr_mod = 1;
		 if (strcmp(qq_bund, "0") != 0)
		 {
			 sfh_Person * tmp = get_person(qq_bund);
			 tmp->usr_logmod = 1;
			 printf("QQ���Զ���½\n");
		 }
		 if (strcmp(weibo, "0") != 0)
		 {
			 sfh_Person * tmp = get_person(weibo);
			 tmp->usr_logmod = 1;
			 printf("΢�����Զ���½\n");
		 }
		 if (strcmp(wechat, "0") != 0)
		 {
			 sfh_Person * tmp = get_person(wechat);
			 tmp->usr_logmod = 1;
			 printf("΢�����Զ���½\n");
		 }
		 printf("��½�ɹ�\n");
		 return 1;
	 }
	 else {
		 printf("�������\n");
		 return 0;
	 }
}

 bool sfh_Person::log_out()
 {
	 usr_logmod = 0;
	 usr_mod = 0;
	 return 1;
 }

 bool sfh_Person::is_log_in()
 {
	 return usr_logmod;
 }

 bool sfh_Person::myregister()
 {
	 int num;
	 char qq[10];
	 char passwd[20];
	 printf("\n_________________ע��____________________\n");
	 printf("����������\n");
	 getstring(passwd, 20, ' ');
	 //��ȡ�ʺſ�
	 num = getqqnum();
	 //д����Ϣ
	 sprintf(qq, "%d", num);
	 strcpy(ID, qq);
	 strcpy(password, passwd);
	 strcpy(name, "NULL");
	 set_others(0, 0, 1);
	 strcpy(location, "NuLL");
	 strcpy(birth, "NULL");
	 strcpy(qq_bund, "0");
	 strcpy(weibo, "0");
	 strcpy(weix, "0");
	 strcpy(wechat, "0");
	 usr_year = 0;
	 this->type = type;
	 add_Person(*this);
	 printf("��ϲ��ע��ɹ�,�����˺�Ϊ�� %d\n",num);
	 ::sync();
	 return 1;

 }


 //Ⱥ����

 bool sfh_Person::is_group(const char * ID)
 {
	 for (int i = 0; i < groups.size; i++) {
		 if (strcmp(groups.nodes[i].ID, ID) == 0)
			 return 1;
	 }
	 return 0;
 }

 bool sfh_Person::add_group()
 {
	 char id[10];
	 if (type != 1)
		 printf("wechatȺֻ���Ƽ�����");
	 printf("������Ⱥ����\n");
	 getstring(id, 10, ' ');
	 if (!is_group(id)) {
		 printf("���޴�Ⱥ\n");
		 return 0;
	 }
	 return add_group(id);
 }

 bool sfh_Person::add_group(const char* id)
 {
	 sfh_Group * tmp = sfh_Group::getgroup(id);
	 if (tmp->type != type) {
		 printf("���޴�Ⱥ\n");
		 return 0;
	 }
	 groups.addmem(id, tmp->name);
	 sync();
	 tmp->add_member(this->ID);
	 tmp->sync();
	 return 1;
 }

 bool sfh_Person::create_group()
 {
	 int num;
	 char qq[10];
	 printf("\n_______________����Ⱥ_________________\n");
	 num = getgroupnum();
	 sprintf(qq, "%d", num);
	 sfh_Group qg;
	 strcpy(qg.ID, qq);
	 qg.type = type;
	 qg.managers.addmem(ID, name);
	 sfh_Group::add_group_into_vector(qg);
	 printf("����Ⱥ�ɹ�,Ⱥ�����ǣ� %d\n",num);
	 groups.addmem(qq, qg.name);
	 get_gl(ID) = groups;
	 sync();
	 return 1;

 }

 bool sfh_Person::del_group()
 {
	 char qq[10];
	 printf("������Ҫɾ��Ⱥ\n");
	 getstring(qq, 10, ' ');
	 return del_group(qq);
 }

 bool sfh_Person::del_group(const char * id)
 {
	 if (!is_group(id)) {
		 printf("û���Ⱥ\n");
		 return 0;
	 }
	 sfh_Group* qg = sfh_Group::getgroup(id);
	 qg->del_member(ID);
	 groups.delmem(id);
	 sync();
	 return 1;
 }

 //���Ѳ���


 bool sfh_Person::find_friend(const char  * id) {

	 sfh_Person * tmp = get_person(id);
	 if (tmp->type != type) {
		 return 0;
	 }
	 printf("      %-10s %-20s %-6s %d\n", tmp->get_ID(), tmp->get_name(), (tmp->get_usrlogmod() == 0 ? "������" : "����"), tmp->get_usrrank());
	 return 1;
 }
 bool sfh_Person::find_friend() {
	 char qq[10];
	 printf("������Ҫ��ѯ�ĺ���:  \n");
	 getstring(qq, 10, ' ');
	 if (!is_person(qq))
	 {
		 printf("������벻����\n");
		 return 0;
	 }
	 printf("��ѯ����� \n");
	 return find_friend(qq);
 }
 bool sfh_Person::is_friend(const char * id) {

	 for (int i = 0; i<friends.size; i++)
	 {
		 if (strcmp(friends.nodes[i].ID, id) == 0)
			 return 1;
	 }
	 return 0;
 }
 bool sfh_Person::add_friend() {
	 char qq[10];
	 printf("������Ҫ��ӵĺ��ѵ�id: ");
	 getstring(qq, 10, ' ');
	 if (strcmp(ID, qq) == 0)
	 {
		 printf("��������Լ�Ϊ����");
		 return 0;
	 }
	 if (is_friend(qq)) {
		 printf("�����Ѿ��Ǻ����ˣ������ظ����\n");
		 return 0;
	 }

	 if (!is_person(qq))
	 {
		 printf("û������˺�\n");
		 return 0;
	 }
	 sfh_Person * tmp1 = get_person(qq);
	 if (tmp1->type != type)
	 {
		 printf("û������˺�\n");
		 return 0;
	 }

	 friends.addmem(qq, tmp1->get_name());
	 tmp1->friends.addmem(ID, tmp1->get_name());
	 tmp1->sync();
	 sync();
	 return 1;
 }
 bool sfh_Person::del_friend() {
	 char id[10];
	 printf("��Ҫɾ���ĺ��� ��id:  ");
	 getstring(id, 10, ' ');
	 if (!is_friend(id))
	 {
		 printf("���ǻ����Ǻ��Ѳ���ɾ��\n");
		 return 0;
	 }
	 return del_friend(id);
 }
 bool sfh_Person::del_friend(const char * id) {
	 friends.delmem(id);
	 sfh_Person * tmp = get_person(id);
	 tmp->friends.delmem(ID);
	 sync();
	 return 1;
 }
 bool sfh_Person::set_friend_name() {
	 char qq[10];
	 char name[20];
	 printf("���ú����ǳ�: \n");
	 printf("���������id: ");
	 getstring(qq, 12, ' ');
	 if (!is_friend(qq))
	 {
		 printf("���˲�����ĺ���\n");
		 return 0;
	 }
	 printf("����������ǳ�: ");
	 getstring(name, 20, ' ');
	 return set_friend_name(qq, name);

 }
 bool sfh_Person::set_friend_name(const char * id, const char * name) {
	 for (int i = 0; i<friends.size; i++) {
		 if (strcmp(friends.nodes[i].ID, id) == 0)
			 strcpy(friends.nodes[i].name, name);
	 }
	 sync();
	 return 1;
 }
 bool sfh_Person::find_common_friend() {
	 printf("��ȡ��ͬ����: \n");
	 printf("����������ӵķ���: 1.QQ,2.weibo,3.wechat ");
	 int num;
	 num=getint();
	 while (num < 1 || num > 3)
	 {
		 printf("�����������������\n");
		 num = getint();
	 }
	 if (num == 2)
		 return find_common_friend(weibo);
	 else if (num == 1)
	 {
		  return find_common_friend(qq_bund);
	 }
	 else  {
		 return find_common_friend(wechat);
	 }
 }
 bool sfh_Person::find_common_friend(const char * id) {
	 bool tmp[2][10000] = { 0 };
	 sfh_List t = get_fl(id);
	 sfh_List t2 = get_fl(ID);
	 for(int i=0;i<t.size;i++)
		 for (int j = 0; j < t2.size; j++)
			 if (strcmp(t.nodes[i].ID, t2.nodes[j].ID) == 0)
				 printf("��������ͬ����%s\n", t.nodes[i].name);
	 return 1;
 }

 bool sfh_Person::sync() {
	 *get_person(ID) = *this;
	 return 1;
 }

 bool sfh_Person::del_group_member()
 {
	 char qq[10];
	 printf("��������Ҫɾ����ID�� \n");
	 getstring(qq, 10, ' ');
	 return del_group_member(qq);
 }

 bool sfh_Person::del_group_member(const char * id)
 {
	 sfh_Person *tmp = get_person(id);
	 tmp->del_group();
	 return 1;
 }

 bool sfh_Person::is_person(const char * ID)
 {
	 for (int i = 0; i<People.size(); i++) {
		 if (strcmp(ID, People[i]->get_ID()) == 0)
			 return 1;
	 }
	 return 0;
 }

 sfh_List& sfh_Person::get_fl(const char * id)
 {
	 for (int i = 0; i<People.size(); i++) {
		 if (strcmp(id, People[i]->get_ID()) == 0) {
			 return People[i]->friends;
		 }
	 }
	 printf("error:���id������\n");
	 return *(new sfh_List);
 }

 sfh_Person * sfh_Person::get_person(const char * id)
 {
		 for (int i = 0; i<People.size(); i++)
			 if (strcmp(id, People[i]->get_ID()) == 0)
				 return People[i];
		 return new sfh_Person;
 }

 sfh_List& sfh_Person::get_gl(const char * id)
 {
	 for (int i = 0; i<People.size(); i++) {
		 if (strcmp(id, People[i]->get_ID()) == 0) {
			 return People[i]->groups;
		 }
	 }
	 printf("error:���id������\n");
	 return *(new sfh_List);
 }

 void sfh_Person::add_Person(sfh_Person & tmp)
 {
	 if (!is_person(tmp.get_ID()))
	 {
		 People.push_back(new sfh_Person(tmp));
	 }
	 else {
		 *get_person(tmp.get_ID()) = tmp;
	 }
 }

 void sfh_Person::bangding() {}

 vector<sfh_Person *> sfh_Person::People;


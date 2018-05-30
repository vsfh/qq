#include "sfh_Group.h"
#include "sfh_Person.h"



sfh_Group::sfh_Group()
{
	strcpy(name, "NULL");
	type = 0;
}


sfh_Group::~sfh_Group()
{
}
sfh_Group::sfh_Group(const char * filename) {
	FILE  * fin;
	int a, b, i, j;
	char tmp1[100];
	char tmp2[100];
	if ((fin = fopen(filename, "r")) == NULL) {
		printf("文件打开失败: %s\n", filename);
	}
	fscanf(fin, "%d%d%d", &a, &b, &type);
	fgetc(fin);

	fscanf(fin, "%s%s", ID, name);

	for (i = 0; i<a; i++)
	{
		fscanf(fin, "%s%s", tmp1, tmp2);
		managers.addmem(tmp1, tmp2);
	}
	for (i = 0; i<b; i++)
	{
		fscanf(fin, "%s%s", tmp1, tmp2);
		members.addmem(tmp1, tmp2);
	}
	fclose(fin);
}



bool sfh_Group::sync(int mode) {
	char filename[100];
	int i, j, k;
	if (mode == 1) {
		*getgroup(ID) = *this;
		return 1;
	}
	else {
		*this = *getgroup(ID);
		return 1;
	}
}



bool sfh_Group::add_member() {
	char qq[12];
	printf("添加: 请输入成员的qq号码: ");
	getstring(qq, 12, ' ');

	return 	add_member(qq);
}
bool sfh_Group::add_member(const char * id) {
	int n;
	if (is_member(id))
	{
		printf("%s 已经是群成员，无需重复添加\n", id);
		return 1;
	}
	if (!sfh_Person::is_person(id)) {
		printf("这个账号不存在\n");
		return 0;
	}
	sfh_Person * tmp = sfh_Person::get_person(id);
	if (tmp->type != this->type) {
		printf("这个账号不存在\n");
		return 0;
	}
	members.addmem(id, tmp->name);
	sfh_Person::get_gl(id).addmem(this->ID, name);
	sync();
	return 1;
}
bool sfh_Group::del_member() {
	char qq[12];
	printf("删除:请输入成员的qq号码: ");
	getstring(qq, 12, ' ');

	return 	del_member(qq);
}
bool sfh_Group::del_member(const char * id) {
	char filename[100];
	int n, i;
	if (!is_member(id))
	{
		printf("该人不在群列表里面\n");
		return 0;
	}
	sfh_Person::get_gl(id).delmem(this->ID);
	members.delmem(id);
	if (is_manager(id))
	{
		managers.delmem(id);
	}
	sync();
	return 1;
}
bool sfh_Group::add_manager(const char * id) {

	if (!is_member(id))
	{
		printf(" 这个人不是群成员 \n");
		return 0;
	}
	if (is_manager(id)) {
		printf("这个人已经是管理员,不用再次添加了\n");
		return 1;
	}
	sfh_Person * tmp = sfh_Person::get_person(id);
	managers.addmem(id, tmp->name);
	sync();
	return 1;
}
bool sfh_Group::add_manager() {
	char qq[12];
	int i;
	printf("添加管理员：请输入管理员的id:   ");
	getstring(qq, 12, ' ');
	return add_manager(qq);
};



bool sfh_Group::set_name(const char * na) {
	sprintf(name, "%s", na);
	sync();
	return 1;
}
bool sfh_Group::set_name() {
	char name[20];
	printf("设置群名字 ： ");
	getstring(name, 20, ' ');
	strcpy(this->name, name);
	return set_name(name);
}

bool sfh_Group::is_member(const char * id) {
	int i;
	for (i = 0; i<members.size; i++)
	{
		if (strcmp(members.nodes[i].ID, id) == 0)
			break;
	}
	return !(i == members.size);
}
bool sfh_Group::is_manager(const char * id) {
	int i;
	for (i = 0; i<managers.size; i++)
	{
		if (strcmp(managers.nodes[i].ID, id) == 0)
			break;
	}
	return !(i == managers.size);
}
void sfh_Group::add_group_into_vector(sfh_Group &g) {
	if (!is_Group(g.ID)) {
		Groups.push_back(new sfh_Group(g));
	}
	else
	{
		*getgroup(g.ID) = g;
	}
}

sfh_Group * sfh_Group::getgroup(const char * id)
{
	for (int i = 0; i < Groups.size(); i++) {
		if (strcmp(Groups[i]->ID, id) == 0)
			return Groups[i];
	}
	return (new sfh_Group);
}

bool sfh_Group::is_Group(const char * id) {
	for (int i = 0; i<Groups.size(); i++)
	{
		if (strcmp(id, Groups[i]->ID) == 0)
			return 1;
	}
	return 0;
}


vector<sfh_Group *> sfh_Group::Groups;

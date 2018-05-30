#include "function_get.h"
#include "sfh_Group.h"
#include "sfh_List.h"
#include "sfh_Person.h"
#include "sfh_qq.h"
#include "sfh_wechat.h"
#include "sfh_weibo.h"
#include "sfh_weix.h"
int qqregisternum = 1000;
int groupregisternum = 1000;
int getqqnum() {
	return qqregisternum++;
}
int getgroupnum(){
	return groupregisternum++;
}

void getstring(char *src, int n, char limit) {
	char tmp[200];
	printf("请输入: ");
	fgets(tmp, 200, stdin);
	tmp[strlen(tmp) - 1] = '\0';
	while (strlen(tmp) >= n)
	{
		printf("长度超出了限制，请重新输入\n");
		scanf("%s", tmp);
	}
	for (int i = 0; i < strlen(tmp); i++){
		if (tmp[i] == limit) {
			printf("包含违法字符：\'%c\'，已经替换\'_\'\n", limit);
			tmp[i] = '_';
		}
	}
	strcpy(src, tmp);
}

int getint() {
	char tmp[100];
	int num = 0;
	getstring(tmp, 100, 0);
	for (int i = 0; i < strlen(tmp); i++) {
		if (!(tmp[i] <= '9'&&tmp[i] >= '0')) {
			printf("包含非法符号，请重新输入\n");
			return getint();
		}
	}
	for (int i = 0; i < strlen(tmp); i++) {
		num = num * 10 + tmp[i] - '0';
	}
	return num;
}

void Init() {
	char filename[100];
	char id[10];
	int n;
	sprintf(filename, "memberlist.dat");
	FILE * fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("用户数据文件不存在,正在尝试新建...\n");
		FILE * pout = fopen(filename, "w");
		fprintf(pout, "%d\n", 0);
		fclose(pout);
	}
	if (fin != NULL)
		fclose(fin);
	fin = fopen(filename, "r");
	fscanf(fin, "%d", &n);

	fgetc(fin);
	for (int i = 0; i<n; i++) {
		fscanf(fin, "%s", id);
		fgetc(fin);
		sprintf(filename, "%s.member", id);
		sfh_Person * tmp = NULL;
		FILE * tmpin = fopen(filename, "r");
		int tmptype = 0;
		fscanf(tmpin, "%d", &tmptype);

		fclose(tmpin);

		switch (tmptype) {
		case 1:
			tmp = new sfh_qq(filename); break;
		case 2:
			tmp = new sfh_weibo(filename); break;
		case 3:
			tmp = new sfh_wechat(filename); break;
		case 4:
			tmp = new sfh_weix(filename);  break;
		default:
			printf("数据文件出现了错误\n");
			tmp = NULL;
			break;
		}
		sprintf(filename, "%s.fl", id);
		tmp->friends = sfh_List(filename);
		sprintf(filename, "%s.gl", id);
		tmp->groups = sfh_List(filename);
		sfh_Person::People.push_back(tmp);
	}

	fclose(fin);

	sprintf(filename, "grouplist.dat");
	fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("群数据文件不存在,正在尝试新建...\n");
		FILE * pout = fopen(filename, "w");
		fprintf(pout, "%d\n", 0);
		fclose(pout);
	}
	if (fin != NULL)
		fclose(fin);
	fin = fopen(filename, "r");
	fscanf(fin, "%d", &n);
	fgetc(fin);
	for (int i = 0; i<n; i++) {
		fscanf(fin, "%s", id);
		fgetc(fin);
		sprintf(filename, "%s.group", id);
		sfh_Group::Groups.push_back(new sfh_Group(filename));
	}
	fclose(fin);


	sprintf(filename, "qq.dat");
	fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("号码库数据文件不存在,正在尝试新建...\n");
		FILE * pout = fopen(filename, "w");
		fprintf(pout, "%d\n", 1000);
		fclose(pout);
	}
	else {
		fscanf(fin, "%d", &qqregisternum);
		fscanf(fin, "%d", &groupregisternum);
		fclose(fin);
	}
	printf("加载数据文件完成\n");
}

//保存
void sync() {
	char filename[100];
	char id[10];
	int n;
	sprintf(filename, "memberlist.dat");
	FILE * pout = fopen(filename, "w");
	fprintf(pout, "%d\n", (int)sfh_Person::People.size());
	for (int i = 0; i<sfh_Person::People.size(); i++) {
		fprintf(pout, "%s\n", sfh_Person::People[i]->get_ID());
		sprintf(filename, "%s.fl", sfh_Person::People[i]->get_ID());
		FILE * fout = fopen(filename, "w");

		fprintf(fout, "%d\n", sfh_Person::People[i]->friends.size);
		for (int j = 0; j<sfh_Person::People[i]->friends.size; j++)
			fprintf(fout, "%s %s\n",sfh_Person::People[i]->friends.nodes[j].ID, sfh_Person::People[i]->friends.nodes[j].name);
		fclose(fout);

		sprintf(filename, "%s.gl", sfh_Person::People[i]->get_ID());
		fout = fopen(filename, "w");
		fprintf(fout, "%d\n", sfh_Person::People[i]->groups.size);
		for (int j = 0; j<sfh_Person::People[i]->groups.size; j++)
			fprintf(fout, "%s %s\n", sfh_Person::People[i]->groups.nodes[j].ID, sfh_Person::People[i]->groups.nodes[j].name);
		fclose(fout);

		sprintf(filename, "%s.member", sfh_Person::People[i]->get_ID());
		fout = fopen(filename, "w");
		fprintf(fout, "%d\n%s\n%s\n%s\n%d %d %d\n%s\n%s\n%s\n%s\n%s\n%s\n", sfh_Person::People[i]->type, sfh_Person::People[i]->get_ID(), sfh_Person::People[i]->get_password(), sfh_Person::People[i]->get_name(), sfh_Person::People[i]->get_usryear(), sfh_Person::People[i]->get_usrrank(), sfh_Person::People[i]->get_usrlogmod(), sfh_Person::People[i]->get_location(), sfh_Person::People[i]->get_birth(), sfh_Person::People[i]->getqq(), sfh_Person::People[i]->getwb(), sfh_Person::People[i]->getwc(), sfh_Person::People[i]->getwx());
		fclose(fout);
	}
	fclose(pout);

	sprintf(filename, "grouplist.dat");
	pout = fopen(filename, "w");
	fprintf(pout, "%d\n", (int)sfh_Group::Groups.size());
	for (int i = 0; i<sfh_Group::Groups.size(); i++) {
		fprintf(pout, "%s\n", sfh_Group::Groups[i]->ID);
		sprintf(filename, "%s.group", sfh_Group::Groups[i]->ID);
		FILE * fout = fopen(filename, "w");
		fprintf(fout, "%d %d %d\n", sfh_Group::Groups[i]->managers.size, sfh_Group::Groups[i]->members.size, sfh_Group::Groups[i]->type);
		fprintf(fout, "%s %s\n", sfh_Group::Groups[i]->ID, sfh_Group::Groups[i]->name);
		for (int j = 0; j<sfh_Group::Groups[i]->members.size; j++)
			fprintf(fout, "%s %s\n", sfh_Group::Groups[i]->members.nodes[j].ID, sfh_Group::Groups[i]->members.nodes[j].name);
		for (int j = 0; j<sfh_Group::Groups[i]->managers.size; j++)
			fprintf(fout, "%s %s\n", sfh_Group::Groups[i]->managers.nodes[j].ID, sfh_Group::Groups[i]->managers.nodes[j].name);
		fclose(fout);
	}
	fclose(pout);

	sprintf(filename, "qq.dat");
	pout = fopen(filename, "w");
	fprintf(pout, "%d\n", qqregisternum);
	fprintf(pout, "%d\n", groupregisternum);
	fclose(pout);

}

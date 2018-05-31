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
		printf("文件打开失败\n");
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
//修改信息
bool sfh_Person::set_ID(const char * usr_ID)
{
	strcpy(ID, usr_ID);
	return 1;
}

bool sfh_Person::set_name()
{
	char name[20];
	fflush(stdin);
	printf("请输入新名称: ");
	getstring(name, 20, ' ');
	if (set_name(name) == true)
		return 1;
	else
		return 0;
}

bool sfh_Person::set_name(const char * usr_name)
{
	strcpy(name, usr_name);
	printf("现在的名字： %s\n", name);
	return 1;
}

bool sfh_Person::set_password()
{
	char pass[20];
	printf("请输入原来的密码\n");
	getstring(pass, 20, ' ');
	if (strcmp(pass, password) == 0) {
		printf("请输入新的密码: ");
		getstring(pass, 20, ' ');
		set_password(pass);
		printf("密码设置成功\n");
		return 1;
	}
	else {
		printf("密码输入错误\n");
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
	printf("请输入您的出生年： ");
	y = getint();
	if (y > 2019 || y < 1949)
		return 0;
	printf("请输入您的出生月： ");
	m = getint();
	if (!(m <= 12 && m >= 1))
		return 0;
	printf("请输入您的出生日： ");
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
	printf("请输入地点： ");
	getstring(loc, 20, ' ');
	return set_location(loc);
}

bool sfh_Person::set_location(const char * loc)
{
	strcpy(location, loc);
	printf("地点设置完成\n");
	return 1;
}

bool sfh_Person::set_others(int y, int r, int k)
{
	usr_year = y;
	usr_rank = r;
	usr_mod =  k;
	return 1;
}


//状态
 bool sfh_Person::log_in()
{
	 char qq[10], passwd[20];
	 printf("\n");
	 printf("_______________登陆________________\n");
	 printf("请输入账号： ");
	 getstring(qq, 10, ' ');
	 printf("请输入密码： ");
	 getstring(passwd, 20, ' ');
	 if (!is_person(qq)) {
		 printf("查无此人1\n");
		 return 0;
	 }
	 sfh_Person * tmp = get_person(qq);
	 if (tmp->type != type) {
		 printf("查无此人2\n");
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
			 printf("QQ已自动登陆\n");
		 }
		 if (strcmp(weibo, "0") != 0)
		 {
			 sfh_Person * tmp = get_person(weibo);
			 tmp->usr_logmod = 1;
			 printf("微信已自动登陆\n");
		 }
		 if (strcmp(wechat, "0") != 0)
		 {
			 sfh_Person * tmp = get_person(wechat);
			 tmp->usr_logmod = 1;
			 printf("微博已自动登陆\n");
		 }
		 printf("登陆成功\n");
		 return 1;
	 }
	 else {
		 printf("密码错误\n");
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
	 printf("\n_________________注册____________________\n");
	 printf("请输入密码\n");
	 getstring(passwd, 20, ' ');
	 //读取帐号库
	 num = getqqnum();
	 //写入信息
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
	 printf("恭喜您注册成功,您的账号为： %d\n",num);
	 ::sync();
	 return 1;

 }


 //群操作

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
		 printf("wechat群只能推荐加入");
	 printf("请输入群号码\n");
	 getstring(id, 10, ' ');
	 if (!is_group(id)) {
		 printf("查无此群\n");
		 return 0;
	 }
	 return add_group(id);
 }

 bool sfh_Person::add_group(const char* id)
 {
	 sfh_Group * tmp = sfh_Group::getgroup(id);
	 if (tmp->type != type) {
		 printf("查无此群\n");
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
	 printf("\n_______________创建群_________________\n");
	 num = getgroupnum();
	 sprintf(qq, "%d", num);
	 sfh_Group qg;
	 strcpy(qg.ID, qq);
	 qg.type = type;
	 qg.managers.addmem(ID, name);
	 sfh_Group::add_group_into_vector(qg);
	 printf("创建群成功,群号码是： %d\n",num);
	 groups.addmem(qq, qg.name);
	 get_gl(ID) = groups;
	 sync();
	 return 1;

 }

 bool sfh_Person::del_group()
 {
	 char qq[10];
	 printf("请输入要删的群\n");
	 getstring(qq, 10, ' ');
	 return del_group(qq);
 }

 bool sfh_Person::del_group(const char * id)
 {
	 if (!is_group(id)) {
		 printf("没这个群\n");
		 return 0;
	 }
	 sfh_Group* qg = sfh_Group::getgroup(id);
	 qg->del_member(ID);
	 groups.delmem(id);
	 sync();
	 return 1;
 }

 //好友操作


 bool sfh_Person::find_friend(const char  * id) {

	 sfh_Person * tmp = get_person(id);
	 if (tmp->type != type) {
		 return 0;
	 }
	 printf("      %-10s %-20s %-6s %d\n", tmp->get_ID(), tmp->get_name(), (tmp->get_usrlogmod() == 0 ? "不在线" : "在线"), tmp->get_usrrank());
	 return 1;
 }
 bool sfh_Person::find_friend() {
	 char qq[10];
	 printf("请输入要查询的号码:  \n");
	 getstring(qq, 10, ' ');
	 if (!is_person(qq))
	 {
		 printf("这个号码不存在\n");
		 return 0;
	 }
	 printf("查询结果： \n");
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
	 printf("请输入要添加的好友的id: ");
	 getstring(qq, 10, ' ');
	 if (strcmp(ID, qq) == 0)
	 {
		 printf("不能添加自己为好友");
		 return 0;
	 }
	 if (is_friend(qq)) {
		 printf("你们已经是好友了，不用重复添加\n");
		 return 0;
	 }

	 if (!is_person(qq))
	 {
		 printf("没有这个账号\n");
		 return 0;
	 }
	 sfh_Person * tmp1 = get_person(qq);
	 if (tmp1->type != type)
	 {
		 printf("没有这个账号\n");
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
	 printf("将要删除的好友 的id:  ");
	 getstring(id, 10, ' ');
	 if (!is_friend(id))
	 {
		 printf("你们还不是好友不用删除\n");
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
	 printf("设置好友昵称: \n");
	 printf("请输入好友id: ");
	 getstring(qq, 12, ' ');
	 if (!is_friend(qq))
	 {
		 printf("此人不是你的好友\n");
		 return 0;
	 }
	 printf("请输入好友昵称: ");
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
	 printf("获取共同好友: \n");
	 printf("请输入想添加的服务: 1.QQ,2.weibo,3.wechat ");
	 int num;
	 num=getint();
	 while (num < 1 || num > 3)
	 {
		 printf("输入错误，请重新输入\n");
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
				 printf("检索到共同好友%s\n", t.nodes[i].name);
	 return 1;
 }

 bool sfh_Person::sync() {
	 *get_person(ID) = *this;
	 return 1;
 }

 bool sfh_Person::del_group_member()
 {
	 char qq[10];
	 printf("输入你想要删除的ID： \n");
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
	 printf("error:这个id不存在\n");
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
	 printf("error:这个id不存在\n");
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


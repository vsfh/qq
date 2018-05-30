#pragma once
#include "sfh_List.h"
#include "function_get.h"
#include "common.h"
#pragma warning( disable : 4996) 
class sfh_Person
{
public:
	char	weibo[10];
	char	wechat[10];
	char	weix[10];
	int type;
	sfh_Person();
	sfh_Person(const char *filename);
	sfh_Person(const sfh_Person &tmp);
	~sfh_Person();
	//�˺�״̬
	virtual bool log_in();
	virtual bool log_out();
	virtual bool is_log_in();
	virtual bool myregister();
	//������Ϣ����
	char * get_ID()			{ return ID; }
	char * get_password()	{ return password; }
	char * get_birth()		{ return birth; }
	char * get_name()		{ return name; }
	char * get_location()	{ return location; }
	int get_usryear()		{ return usr_year; }
	int get_usrlogmod()		{ return usr_logmod; }
	int get_usrrank()		{ return usr_rank; }
	char * getqq()			{ return qq_bund; }
	char * getwb()			{ return weibo; }
	char * getwc()			{ return wechat; }
	char * getwx()			{ return weix; }
	int get_usr_mod()		{ return usr_mod; }
	char * get_qq_bund()	{ return qq_bund; }
	//������Ϣ�޸�
	virtual bool set_ID(const char * ID);
	virtual bool set_name();
	virtual bool set_name(const char * name);
	virtual bool set_password();
	virtual bool set_password(const char * password);
	virtual bool set_birthday(const char * birthday);
	virtual bool set_birthday();
	virtual bool set_location();
	virtual bool set_location(const char * location);
	virtual bool set_others(int y, int r, int m);
	void menu_safe();			//�޸�����Ͱ󶨵Ĳ˵�
	//�Ժ��ѵĲ���
	virtual bool is_friend(const char * ID);
	virtual bool add_friend();
	virtual bool del_friend();
	virtual bool find_friend();
	virtual bool find_common_friend();
	virtual bool del_friend(const char * ID);
	virtual bool set_friend_name();
	virtual bool set_friend_name(const char * id, const char * name);
	virtual bool find_friend(const char * ID);
	virtual bool find_common_friend(const char * ID);
	//��Ⱥ��Ĳ���
	virtual bool create_group();
	virtual bool is_group(const char * ID);
	virtual bool add_group();
	virtual bool add_group(const char * ID);
	virtual bool del_group();
	virtual bool del_group(const char * ID);
	virtual bool del_group_member();
	virtual bool del_group_member(const char * ID);
	virtual void group_manage();
	//�˵�
	virtual void menu() {};
	virtual void bangding();
	virtual void menu_friends();
	virtual void menu_groups();
	void menu_inf();
	//�ж����޴���
	static bool is_person(const char * ID);
	//��ȡĳ�˻��ĺ����б�
	static sfh_List& get_fl(const char * id);
	//��ȡ���˻�
	static sfh_Person * get_person(const char * id);
	//��ȡĳ�˻���Ⱥ�б�
	static sfh_List& get_gl(const char * id);
	//�����˻�
	static void add_Person(sfh_Person & tmp);
	virtual bool sync();
	static vector<sfh_Person *>People;
	sfh_List friends;
	sfh_List groups;
protected:
	char	ID[10];
	char	password[20];
	char	birth[20];
	char	name[20];
	char	location[10];
	int		usr_year;
	int		usr_mod;
	int		usr_rank;
	int		usr_logmod;
	char	qq_bund[12];			//�󶨹�ϵ
	friend class sfh_Group;

};


#pragma once
#include "sfh_List.h"
#include "function_get.h"
#include "common.h"
class sfh_Group
{
	friend class sfh_List;
	friend class sfh_Person;
public:
	sfh_Group();
	sfh_Group(const char * filename);
	~sfh_Group();
	bool is_member(const char * ID);
	bool is_manager(const char * ID);
	char * get_Group_ID() { return ID; }
	char * get_Group_name() { return name; }
	bool del_member();
	bool viewallmem();
	virtual bool add_member();
	virtual bool del_member(const char * ID);
	virtual bool add_member(const char * ID);
	bool add_manager(const char * id);
	bool set_name();
	bool set_name(const char * na);
	bool add_manager();
	static bool is_Group(const char * ID);
	//获取该群
	static sfh_Group * getgroup(const char * id);
	static vector<sfh_Group *> Groups; 
	static void add_group_into_vector(sfh_Group &);
	bool sync(int mode =1);
	sfh_List	members;
	sfh_List	managers;
	char		ID[10];
	char		name[20];
	int			type;
};


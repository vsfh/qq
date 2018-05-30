#pragma once
#include "sfh_Person.h"
class sfh_wechat :
	public sfh_Person
{
public:
	sfh_wechat(){strcpy(qq_bund, "0"); type = 2; }
	sfh_wechat(const char * filename);
	sfh_wechat(const sfh_wechat & tmp);
	void bangding();
	void menu();
	~sfh_wechat();
};


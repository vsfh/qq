#pragma once
#include "sfh_Person.h"
class sfh_weibo :
	public sfh_Person
{
public:
	sfh_weibo() { strcpy(qq_bund, "0"); type = 1; }
	sfh_weibo(const sfh_Person & tmp);
	sfh_weibo(const char * filename);
	~sfh_weibo();
	void menu();
};


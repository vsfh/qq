#pragma once
#include "sfh_Person.h"
class sfh_weix :
	public sfh_Person
{
public:
	sfh_weix() { strcpy(qq_bund, "0"); type = 3; }
	sfh_weix(const sfh_Person & tmp);
	sfh_weix(const char * filename);
	~sfh_weix();
	void menu();
};


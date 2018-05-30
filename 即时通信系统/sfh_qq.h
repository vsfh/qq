#pragma once
#include "sfh_Person.h"

class sfh_qq :
	public sfh_Person
{
public:
	sfh_qq() { type = 1; }
	sfh_qq(const sfh_Person & tmp);
	sfh_qq(const char * filename);
	void menu();
	void bangding();
	~sfh_qq();
};


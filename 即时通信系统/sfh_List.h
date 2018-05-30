#pragma once
#include "common.h"
using std::vector;

typedef struct Node {
	char	ID[12];
	char	name[20];
}node;

class sfh_List
{
public:
	sfh_List();
	sfh_List(const char * filename);

	virtual ~sfh_List();
	virtual bool addmem(node n);
	virtual bool addmem(const char * ID, const char * name);
	virtual bool delmem(const char * ID);
	virtual bool ismem(const char * ID);
	virtual bool findmem(const char * ID);
	vector<node> nodes;
	int size;


};


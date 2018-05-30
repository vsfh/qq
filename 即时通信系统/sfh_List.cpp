#include "sfh_List.h"
#pragma warning( disable : 4996)



sfh_List::sfh_List()
{
	size = 0;
}


sfh_List::~sfh_List()
{
	size = 0;
	nodes.clear();
}

bool sfh_List::ismem(const char * ID)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(nodes[i].ID, ID) == 0)
			return 1;
	}
	return 0;
}

bool sfh_List::findmem(const char * ID)
{
	for (int i = 0; i < size; i++) {
		if (strcmp(nodes[i].ID, ID) == 0)
			return i;
	}
	return -1;
}

bool sfh_List::delmem(const char * ID)
{
	vector<node>::iterator it;								//��Ϊ��һ��Ҫ��erase�����õ�����
	for (it = nodes.begin(); it != nodes.end(); it++) {
		if (strcmp((*it).ID, ID) == 0) {
			nodes.erase(it);
			size--;
			return 1;
		}
	}
	return 0;
}

bool sfh_List::addmem(node n)
{
	if (ismem(n.ID))
		return 0;
	nodes.push_back(n);
	++size;
	return 1;
}

sfh_List::sfh_List(const char * filename)
{
	node tmp;
	int num;
	FILE *fin = fopen(filename, "r");

	if (fin == NULL)
		printf("�ļ���ɶҲû��");
	fscanf(fin, "%d", &num);
	fgetc(fin);

	for (int i = 0; i < num; i++) {
		fscanf(fin, "%s%s", tmp.ID, tmp.name);
		addmem(tmp);
	}
}



bool sfh_List::addmem(const char * ID, const char * name)
{
	node tmp;
	strcpy(tmp.ID, ID);						//tmp���ǿ���ֱ���޸ĵ���ֵ����Ҫ��strcpy����
	strcpy(tmp.name, name);
	return addmem(tmp);
}

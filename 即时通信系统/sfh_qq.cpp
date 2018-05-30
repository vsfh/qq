#include "sfh_qq.h"



sfh_qq::sfh_qq(const sfh_Person & tmp)
{
}

sfh_qq::sfh_qq(const char * filename)
{
	int i, j, k;
	char t[100];
	FILE * fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("�����ļ���ʧ��\n");
	}
	fscanf(fin, "%d", &type);
	fgetc(fin);    //type

	fscanf(fin, "%s", t);
	fgetc(fin);    //id
	strcpy(ID, t);

	fscanf(fin, "%s", t);
	fgetc(fin);
	strcpy(password, t);

	fscanf(fin, "%s", t);
	fgetc(fin);   //name
	strcpy(name, t);

	fscanf(fin, "%d%d%d", &i, &j, &k);
	fgetc(fin);//others year and rank and mod
	set_others(i, j, k);

	fscanf(fin, "%s", t);
	fgetc(fin); //location
	strcpy(location, t);

	fscanf(fin, "%s", t);
	fgetc(fin); //birthday
	strcpy(birth, t);


	fscanf(fin, "%s", t);
	fgetc(fin); //qq
	strcpy(qq_bund, t);

	fscanf(fin, "%s", t);
	fgetc(fin); //wb
	strcpy(weibo, t);

	fscanf(fin, "%s", t);
	fgetc(fin); //wc
	strcpy(wechat, t);


	fscanf(fin, "%s", t);
	fgetc(fin); //wx
	strcpy(weix, t);

	fclose(fin);
	usr_logmod = 0;
}

sfh_qq::~sfh_qq()
{
}

void sfh_qq::bangding() {
	if (!strcmp(weibo, "0") && !strcmp(this->wechat, "0"))
		printf("δ��ͨ΢��΢��\n");
	else {
		if (strcmp(weibo, "0"))
			printf("�󶨵�΢���� %s\n",weibo);
		if (strcmp(this->wechat, "0"))
			printf("�󶨵�΢�ţ� %s\n", wechat);
	}
}

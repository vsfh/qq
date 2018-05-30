#include "sfh_wechat.h"



sfh_wechat::sfh_wechat(const char * filename)
{
	int i, j, k;
	char t[100];
	FILE * fin = fopen(filename, "r");
	if (fin == NULL) {
		printf("配置文件打开失败\n");
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

sfh_wechat::sfh_wechat(const sfh_wechat & tmp)
{
	strcpy(ID, tmp.ID);
	friends = tmp.friends;
	groups = tmp.groups;
	strcpy(name, tmp.name);
	strcpy(password, tmp.password);
	strcpy(location, tmp.location);
	strcpy(birth, tmp.birth);
	usr_year = tmp.usr_year;
	usr_rank = tmp.usr_rank;
	usr_mod = tmp.usr_mod;
	usr_logmod = tmp.usr_logmod;
	type = tmp.type;
	strcpy(qq_bund, tmp.qq_bund);
}

sfh_wechat::~sfh_wechat()
{
}

void sfh_wechat::bangding()
{
	char qqnum[12];
	if (strcmp(qq_bund, "0") != 0)
	{
		printf("这个号码，已经被绑定了qq\n");
		return;
	}
	printf("请输入要绑定的qq号码:\n");
	getstring(qqnum, 12, ' ');
	if (!is_person(qqnum)) {
		printf("这个qq号码不存在\n");
		return;
	}
	sfh_Person * tmp = get_person(qqnum);
	if (tmp->type != 1) {
		printf("这个qq号码不存在\n");
		return;
	}
	else
	{
		if (strcmp(tmp->weix, "0")) {
			printf("这个qq已经绑定了微信账号\n");
			return;
		}
		strcpy(tmp->weix, ID);
		strcpy(qq_bund, qqnum);
		printf("绑定成功\n");
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
# define LEN sizeof(struct Student)

struct Student {
char num[10];      /*学号*/
char name[20];     /*姓名*/
char sex[10];      /*性别*/
int age;           /*年龄*/
char phone[12];    /*电话*/
float Math;        /*高数成绩*/
float C_language;  /*C语言成绩*/
float English;     /*英语成绩*/
float physics;     /*物理成绩*/
float DL_math;     /*数字逻辑成绩*/
float SUM;         /*总成绩*/
float AVERAG;      /*平均成绩*/
struct Student *next;
};

char filename[30];

/*生成链表*/
struct Student *Creat(int n) {
	void menu_print_in(void);
	struct Student *head;
	struct Student *p1, *p2;

	system("cls");
	for(int i=1;i<n+1;i++) {
		p1 = (struct Student*)malloc(LEN);
		menu_print_in();
		scanf("%s%s%s%d%s%f%f%f%f%f",p1->num,p1->name,p1->sex,&p1->age,p1->phone,&p1->Math,&p1->C_language,&p1->English,&p1->physics,&p1->DL_math);
		p1->next = NULL;
		if(i==1) {
			head = p2 = p1;
		}
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	return(head);
}

/*数据存盘(wb只写)*/
void WriteData_wb(struct Student *head) 
{
	FILE *fp;
	struct Student *p;
	if((fp = fopen(filename, "wb"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) 
	{
		if(fwrite(p,LEN,1,fp)!=1) {
			printf("写入数据出错\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}

/*数据存盘(ab追加)*/
void WriteData_ab(struct Student *head) {
	FILE *fp;
	struct Student *p;
	if((fp = fopen(filename, "ab"))==NULL)
	printf("\a error! Can not open the file!");
	p = head;
	while(p!=NULL) {
	if(fwrite(p,LEN,1,fp)!=1) {
			printf("写入数据出错\n");
			fclose(fp);
			return;
		}
		p=p->next;
	}
	fclose(fp);
}


/*读取数据*/
/*读取数据文件保存到链表中 ，返回指向此链表头指针*/
struct Student *ReadData(void) 
{
	struct Student *head = NULL;
	struct Student *p1, *p2;

	FILE *fp;
	if((fp=fopen(filename,"rb+"))==NULL)
	{
		printf("打开文件出错\n");
		exit(0);
	}
	while(!feof(fp)) 
	{
		if((p1=(struct Student*)malloc(LEN))==NULL)
		{
			printf("内存申请出错\n");
			fclose(fp);
			exit(0);
		}
		if(fread(p1,LEN,1,fp)!=1)
		{
			free(p1);
			break;
		}
		if(head==NULL)
		head=p2=p1;
		else{
			p2->next=p1;
			p2=p1;
		}
	}
	fclose(fp);
	return (head);
}

/*【1】全量查询*/
void Print_inquire_all(void) 
{
	void menu_print_out(void);
	struct Student *pt;
	pt = ReadData();
	menu_print_out();
	do {
		printf("%-10s%6s%8s%4d%13s  %4.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f\n",pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->Math,pt->C_language,pt->English,pt->physics,pt->DL_math,(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math),(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math)/5);
		pt = pt->next;
	}while(pt!=NULL);
	printf("\n\n");
}

/*【2】学号查询*/
int Print_inquire_num() {
	void menu_print_out(void);
	struct Student *pt;
	char str_num[10];
	printf("◎请输入您要查询的学号:");
	scanf("%s", str_num);
	pt = ReadData();
	menu_print_out();
	do {
		if(strcmp(pt->num,str_num)==0) 
		{
			printf("%-10s%6s%8s%4d%13s  %4.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f\n",pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->Math,pt->C_language,pt->English,pt->physics,pt->DL_math,(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math),(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math)/5);
			printf("\n\n");
			return 0;
		}
		pt = pt->next;
	}while(pt!=NULL);
	printf("数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}

/*【3】姓名查询*/
int Print_inquire_name() {
	void menu_print_out(void);
	struct Student *pt;
	char str_name[20];
	printf("◎请输入您要查询的姓名:");
	scanf("%s", str_name);
	pt = ReadData();
	menu_print_out();
	do {
		if(strcmp(pt->name,str_name)==0) {
			printf("%-10s%6s%8s%4d%13s  %4.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f\n",pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->Math,pt->C_language,pt->English,pt->physics,pt->DL_math,(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math),(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math)/5);
			printf("\n\n");
			return 0;
		}
		pt = pt->next;
	}while(pt!=NULL);
	printf("数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}

/*【4】模糊查询*/
int Print_inquire_fuzzy(void) {
	void menu_print_out(void);
	struct Student *pt;
	char str_find[20];
	int m = 0;
	printf("◎请输入您要查询的关键词:");
	scanf("%s", str_find);
	pt = ReadData();
	menu_print_out();
	do {
		if(strstr(pt->num,str_find)!=0||strstr(pt->name,str_find)!=0||strstr(pt->sex,str_find)!=0||strstr(pt->phone,str_find)!=0) 
		{
			printf("%-10s%6s%8s%4d%13s  %4.1f %6.1f %6.1f %6.1f %6.1f %6.1f %6.1f\n",pt->num,pt->name,pt->sex,pt->age,pt->phone,pt->Math,pt->C_language,pt->English,pt->physics,pt->DL_math,(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math),(pt->Math+pt->C_language+pt->English+pt->physics+pt->DL_math)/5);
			m = 1;
		}
		pt = pt->next;
	}while(pt!=NULL);
	if(m==0)
		printf("数据库中没有存储您要查询的数据！\n");
	printf("\n\n");
	return 0;
}

/*成绩统计*/
int Print_inquire_stats(void) {
	struct Student *head, *p1;
	float CMIN, CMAX, EMIN, EMAX, SMIN, SMAX, PMAX, PMIN, DMAX, DMIN, MMAX, MMIN;
	head = ReadData();
	p1 = head;
	MMIN = MMAX = p1->Math;
	CMIN = CMAX = p1->C_language;
	EMIN = EMAX = p1->English;
	PMIN = PMAX = p1->physics;
	DMIN = DMAX = p1->DL_math;
	SMIN = SMAX = p1->Math+p1->C_language+p1->English+p1->physics+p1->DL_math;
	while(p1->next!=NULL) 
	{
		if(p1->Math > MMAX)
		{
			MMAX = p1->Math;
		}
		if(p1->Math < MMIN) 
		{
			MMIN = p1->Math;
		}
		if(p1->C_language > CMAX)
		{
			CMAX = p1->C_language;
		}
		if(p1->C_language < CMIN) 
		{
			CMIN = p1->C_language;
		}
		if(p1->English > EMAX) 
		{
			EMAX = p1->English;
		}
		if(p1->English < EMIN) 
		{
			EMIN = p1->English;
		}
		if(p1->physics > PMAX)
		{
			PMAX = p1->physics;
		}
		if(p1->physics < PMIN) 
		{
			PMIN = p1->physics;
		}
		if(p1->DL_math > DMAX)
		{
			DMAX = p1->DL_math;
		}
		if(p1->DL_math < DMIN) 
		{
			DMIN = p1->DL_math;
		}
		if((p1->Math+p1->C_language+p1->English+p1->physics+p1->DL_math) > SMAX) 
		{
			SMAX = (p1->Math+p1->C_language+p1->English+p1->physics+p1->DL_math);
		}
		if((p1->Math+p1->C_language+p1->English+p1->physics+p1->DL_math) < SMIN)
		{
			SMIN = (p1->Math+p1->C_language+p1->English+p1->physics+p1->DL_math);
		}
		p1 = p1->next;
	}
	printf("\n");
	printf("◎数据库中高数最高分为:%4.1f \n", MMAX);
	printf("◎数据库中高数最低分为:%4.1f \n\n", MMIN);
	printf("◎数据库中C语言最高分为:%4.1f \n", CMAX);
	printf("◎数据库中C语言最低分为:%4.1f \n\n", CMIN);
	printf("◎数据库中英语最高分为:%4.1f \n", EMAX);
	printf("◎数据库中英语最低分为:%4.1f \n\n", EMIN);
	printf("◎数据库中物理最高分为:%4.1f \n", PMAX);
	printf("◎数据库中物理最低分为:%4.1f \n\n", PMIN);
	printf("◎数据库中数字逻辑最高分为:%4.1f \n", DMAX);
	printf("◎数据库中数字逻辑最低分为:%4.1f \n\n", DMIN);
	printf("◎数据库中总成绩最高分为:%4.1f \n", SMAX);
	printf("◎数据库中总成绩最低分为:%4.1f \n\n", SMIN);
	printf("\n");
	return 0;
}

/*【1】修改数据之删除记录*/
int Delete() {
	struct Student *pt1, *pt2, *head;
	char str_num[20];
	printf("\n◎请输入您要删除的学号信息:");
	scanf("%s", str_num);
	pt1 = ReadData();
	pt2 = pt1->next;
	head = pt1;
	while(pt2!=NULL) 
	{
		if(strcmp(pt1->num,str_num)==0) 
		{
			WriteData_wb(pt2);
		}
		else if(strcmp(pt2->num,str_num)==0)
		{
			pt1->next = pt2->next;
			WriteData_wb(head);
		}
		pt2 = pt2->next;
		pt1 = pt1->next;
	}
	if(pt2!=NULL)
	printf("数据库中没有存储您要删除的数据！\n");
	printf("\n\n");
	return 0;
}

/*【2】修改数据之修改记录*/
int Amend() {
	void menu_print_in(void);
	struct Student *pt1, *pt2, *head;
	char str_num[20];
	printf("◎请输入您要修改的学号信息:");
	scanf("%s", str_num);
	pt1 = ReadData();
	pt2 = pt1->next;
	head = pt1;
	while(pt2!=NULL) {
		if(strcmp(pt1->num,str_num)==0) {
			menu_print_in();
			scanf("%s%s%s%d%s%f%f%f%f%f",pt1->num,pt1->name,pt1->sex,&pt1->age,pt1->phone,&pt1->Math,&pt1->C_language,&pt1->English,&pt1->physics,&pt1->DL_math);
			WriteData_wb(head);
		}
		else if(strcmp(pt2->num,str_num)==0) {
			menu_print_in();
			scanf("%s%s%s%d%s%f%f%f%f%f",pt1->num,pt1->name,pt1->sex,&pt1->age,pt1->phone,&pt1->Math,&pt1->C_language,&pt1->English,&pt1->physics,&pt1->DL_math);
			WriteData_wb(head);
		}
		pt2 = pt2->next;
		pt1 = pt1->next;
	}
	if(pt2!=NULL)
	printf("数据库中没有存储您要删除的数据！\n");
	return 0;
}

/*【3】修改数据之整理数据*/
int Neaten() {
	struct Student *first;
	struct Student *tail;
	struct Student *p_min;
	struct Student *min;
	struct Student *p;
	struct Student *head;
		head = ReadData();
	first = NULL;
	while(head!=NULL) {
		for(p=head,min=head; p->next!=NULL; p=p->next) {
			if(strcmp(p->next->num,min->num)<0) {
				p_min = p;
				min = p->next;
			}
		}
		if(first==NULL) {
			first = min;
			tail = min;
		}
		else {
			tail->next = min;
			tail = min;
		}
		if(min==head) {
			head = head->next;
		}
		else {
			p_min->next = min->next;
		}
	}
	if(first!=NULL) {
		tail->next = NULL;
	}
	head = first;

	WriteData_wb(head);
	return 0;
}

/*输入写入数据的数量*/
int Creat_num(void) {
	printf("\n◎请输入您此次要添加的数据个数:");
	int n;
	if(scanf("%d",&n)!=1) 
	{
		printf("\a error!");
	}
	return n;
}

/*选择将要打开的文件*/
int File_name() {
	printf("\n◎请输入您想要打开的文件:");
	if(scanf("%s", filename)!=1)
	printf("\a error!");
	return 0;
}

/*主菜单*/
void menu(void) 
{
	void menu_add(void);
	void menu_inquire(void);
	void menu_amend(void);
	printf("               ╭ ================╮              \n");
	printf("╭ =============╣ 学生成绩管理系统╠===========╮\n");
	printf("║              ╰ ================╯           ║\n");
	printf("║   【1】添加数据           【3】修改数据    ║\n");
	printf("║                                            ║\n");
	printf("║   【2】查询数据           【4】退出系统    ║\n");
	printf("║                                            ║\n");
	printf("╰ ===========================================╯\n");
	printf("◎请输入功能前的序号进入相应的工具:【   】\b\b");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') 
	{
		printf("请输入正确的数字，你是猪吗？\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");
		a = getchar();
	}
	switch(a) {
		case '1': File_name();menu_add();
		break;
		case '2': File_name();menu_inquire();
		break;
		case '3': File_name();menu_amend();
		break;
		case '4': exit(0);
		break;
	}
	getchar();
}

/*二级菜单之添加数据*/
void menu_add(void) 
{
	system("cls");
	getchar();
	printf("             ╔================╗             \n");
	printf("╔============╣  添加数据方式  ╠============╗\n");
	printf("║            ╚================╝            ║\n");
	printf("║ 【1】新建文件 【2】增添数据 【3】返回菜单║\n");
	printf("║                                          ║\n");
	printf("╚==========================================╝\n");
	printf("◎请输入功能前的序号进入相应的工具:【   】\b\b\b\b");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b\b\b");
		a = getchar();
	}
	switch(a) {
		case '1': WriteData_wb(Creat(Creat_num()));
		 printf("\n◎新建文件成功且数据已成功保存◎\n");
			 system("pause");
		 system("cls");
		 menu_add();
		break;
		case '2': WriteData_ab(Creat(Creat_num()));
			 printf("\n◎数据已成功添加◎\n");
			 system("pause");
		 system("cls");
		 menu_add();
		break;
		case '3': system("cls");
		 getchar();
		 menu();
		break;
	}
}

/*二级菜单之查询数据*/
void menu_inquire(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ╭════════╮              \n");
	printf("╭══════╣  查询数据方式  ╠══════╮\n");
	printf("║            ╰════════╯            ║\n");
	printf("║    【1】全量查询         【4】模糊查询     ║\n");
	printf("║                                            ║\n");
	printf("║    【2】学号查询         【5】成绩统计     ║\n");
	printf("║                                            ║\n");
	printf("║    【3】姓名查询         【6】返回菜单     ║\n");
	printf("╰══════════════════════╯\n");
	printf("◎请输入功能前的序号进入相应的工具:【   】\b\b");
	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='3'&&a!='4'&&a!='5'&&a!='6') {
			printf("error! please input the right number!\n");
			putchar('\a');
			getchar();
			printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");
			a = getchar();
		}
		switch(a) {
			case '1': Print_inquire_all();system("pause");getchar();
			break;
			case '2': Print_inquire_num();system("pause");getchar();
			break;
			case '3': Print_inquire_name();system("pause");getchar();
			break;
			case '4': Print_inquire_fuzzy();system("pause");getchar();;
			break;
			case '5': Print_inquire_stats();system("pause");getchar();
			break;
			case '6': system("cls");getchar();menu();
			break;
		}
	}
}

/*二级菜单之修改数据*/
void menu_amend(void) {
	system("cls");
	getchar();
	while(1) {
	system("cls");
	printf("              ╭════════╮              \n");
	printf("╭══════╣  修改数据方式  ╠══════╮\n");
	printf("║            ╰════════╯            ║\n");
	printf("║    【1】删除记录          【3】整理数据    ║\n");
	printf("║                                            ║\n");
	printf("║    【2】修改记录          【4】返回菜单    ║\n");
	printf("╰══════════════════════╯\n");
	printf("◎请输入功能前的序号进入相应的工具:【   】\b\b");

	int a = 0;
	a = getchar();

	while(a!='1'&&a!='2'&&a!='3'&&a!='4') {
		printf("error! please input the right number!\n");
		putchar('\a');
		getchar();
		printf("◎请重新输入功能前的序号进入相应的工具:【   】\b\b");
		a = getchar();
		}
		switch(a) {
			case '1': Delete();
			 printf("\n\n◎已成功删除指定数据◎\n");
			 system("pause");
			 getchar();
			break;
			case '2': Amend();
				 printf("\n\n◎已成功修改指定数据◎\n");
			 system("pause");
				 getchar();
			break;
			case '3': Neaten();
			 printf("\n\n◎数据已成功按照学号重新排列◎\n");
			 system("pause");
			 getchar();
			break;
			case '4': system("cls");
			 getchar();
			 menu();
			break;
		}
	}
}

/*输入输出提示栏*/
void menu_print_in(void) {
	printf("-------------------------------------------------------------------------------------\n");
	printf("学号      姓名     性别  年龄    电话      Math   C_l   Engl   Phyf   DL_m   \n");
	printf("-------------------------------------------------------------------------------------\n");
}
void menu_print_out(void) {
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("学号      姓名     性别  年龄    电话      Math   C_l   Engl   Phyf   DL_m   SUM   AVERAG  \n");
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/*主函数*/
int main(void) {
	SetConsoleTitle(L"学生成绩管理系统");
	menu();
	return 0; 
}
/*升序*/
void ascend_sort()
{
	struct Student *p1,*p2,*p,*head,*p3,*p4;
	p=ReadData();
	p->SUM=p->Math+p->C_language+p->English+p->physics+p->DL_math;
	p->AVERAG=(p->Math+p->C_language+p->English+p->physics+p->DL_math)/5;
	menu_print_out();
	for(p3=head=p1=ReadData();p1!=NULL;p1=p1->next)
	{
		for(p4=p2=p1->next;p2!=NULL;p2=p2->next)
		{
			if(p1->SUM>p2->SUM)
			{
				if(p1=head)
				{
					head=p1->next;
					p4->next=p2->next;
					p2->next=head;
					head=p2;
					p1->next=p4->next;
					p4->next=p1;
				}
				else
				{
					p4->next=p2->next;
					p3->next=p1->next;
					p1->next=p4->next;
					p4->next=p1;
					p2->next=p3->next;
					p3->next=p2;
				}
			}
			p4=p2;
		}
		p3=p1;
	}
}


					



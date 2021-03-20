#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct
{
	char number[MAXSIZE];
	char name[MAXSIZE];
	char author[MAXSIZE];
}BookInfo;

typedef struct
{
	BookInfo* book;
	int len;
}BookList;

typedef struct
{
	char account[MAXSIZE];
	char password[16];
}MemberInfo;

typedef struct
{
	MemberInfo* member;
	int len;
}MemberList;

void Menu1()
{
	printf("*********************************\n");
	printf("*         管理员菜单            *\n");
	printf("*********************************\n");
	printf("*      1.添加书籍信息           *\n");
	printf("*********************************\n");
	printf("*      2.删除书籍信息           *\n");
	printf("*********************************\n");
	printf("*      3.修改书籍信息           *\n");
	printf("*********************************\n");
	printf("*      4.显示全部书籍           *\n");
	printf("*********************************\n");
	printf("*      5.添加会员信息           *\n");
	printf("*********************************\n");
	printf("*          6.退出               *\n");
	printf("*********************************\n");
	printf("请输入想要执行的操作:");
}

void Menu2()
{
	printf("******************************\n");
	printf("*         会员菜单           *\n");
	printf("******************************\n");
	printf("*         1.借书             *\n");
	printf("******************************\n");
	printf("*         2.还书             *\n");
	printf("******************************\n");
	printf("*      3.显示全部书籍        *\n");
	printf("******************************\n");
	printf("*      4.查找书籍信息        *\n");
	printf("******************************\n");
	printf("*         5.退出             *\n");
	printf("******************************\n");
	printf("请输入想要执行的操作:");
}

int InitBook(BookList& B)
{
	B.book = new BookInfo[MAXSIZE];
	if (!B.book) exit(-1);
	B.len = 0;
	return 0;
}

int InitMember(MemberList& M)
{
	M.member = new MemberInfo[MAXSIZE];
	if (!M.member) exit(-1);
	M.len = 0;
	return 0;
}

int Login(MemberList& M)
{
	FILE* fp; int i=1,flag=-1;
	char acc[MAXSIZE] = "account:", pass[MAXSIZE] = "password:";
	fp = fopen("c:\\new\\member.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	printf("请输入账号:");
	scanf("%s", M.member[0].account);
	printf("请输入密码:");
	scanf("%s", M.member[0].password);
	strcat(acc, M.member[0].account);
	strcat(pass, M.member[0].password);
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", &M.member[i].account, &M.member[i].password);
		if (strcmp(acc, M.member[i].account) == 0 && strcmp(pass, M.member[i].password) == 0)
		{
			if (i == 1)
			{
				flag = 0;
				fclose(fp);
				break;
			}
			else
			{
				flag = 1;
				fclose(fp);
				break;
			}
		}
		i++;
	}
	if (flag==0)
	{
		printf("\n管理员登陆成功！\n");
		return 0;
	}
	if (flag == 1)
	{
		printf("\n会员登陆成功！\n");
		return 1;
	}
	if (flag==-1)
	{
		printf("\n会员登陆失败！\n");
		return -1;
	}
}

void AddMemberInfo(MemberList M)
{
	FILE* fp; int i = 1; char acc[MAXSIZE] = "account:";
	fp = fopen("c:\\new\\member.txt", "a+");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	printf("请输入账号:");
	scanf("%s", &M.member[0].account);
	strcat(acc, M.member[0].account);
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", &M.member[i].account, &M.member[i].password);
		if (strcmp(acc, M.member[i].account) == 0)
		{
			printf("该账号已存在！\n");
			return;
		}
		i++;
	}
	printf("\n\n%d\n\n", strcmp(acc, M.member[4].account));
	printf("请输入密码:");
	scanf("%s", &M.member[0].password);
	fprintf(fp, "account:%s\npassword:%s\n", M.member[0].account, M.member[0].password);
	fclose(fp);
	printf("添加会员成功！\n");
	return;
}

void AddBookInfo(BookList B)
{
	FILE* fp; int n;
	fp = fopen("c:\\new\\book.txt", "a");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	printf("请输入编号:");
	scanf("%s", &B.book[0].number);
	printf("请输入书名:");
	scanf("%s", &B.book[0].name);
	printf("请输入作者:");
	scanf("%s", &B.book[0].author);
	printf("是否保存当前书籍信息？1.是 2.否");
	scanf("%d", &n);
	if (n == 1)
	{
		fprintf(fp, "number:%s\tname:%s\tauthor:%s\n", B.book[0].number, B.book[0].name, B.book[0].author);
		fclose(fp);
		printf("添加图书成功！\n");
	}
	else if (n == 2)
	{
		fclose(fp);
		printf("添加图书失败！\n");
	}
	else printf("error!");
}

void ShowBook(BookList B)
{
	FILE* fp; int i = 1;
	fp = fopen("c:\\new\\book.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author);
		i++;
	}
	fclose(fp);
	for (int j = 1; j <= i-2; j++)
		printf("%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
}

int Inquire(BookList B,char info[])
{
	FILE* fp; int i = 1, j;
	char aut[MAXSIZE] = "author:",nam[MAXSIZE]="name:",num[MAXSIZE]="number:";
	strcat(aut, info); strcat(nam, info); strcat(num, info);
	fp = fopen("c:\\new\\book.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author);
		i++;
	}
	fclose(fp);
	for (j = 1; j <= i-1; j++)
	{
		if (strcmp(aut, B.book[j].author) == 0 || strcmp(nam, B.book[j].name) == 0 || strcmp(num, B.book[j].number) == 0)
		{
			printf("该书信息:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
			return 1;
		}
	}
	if (j > i - 2)
		printf("该书不存在或已被借出！\n");
	return 0;
}

int Inquire2(BookList B, MemberList M, char info[])
{
	FILE* fp; int i = 1, j;
	char aut[MAXSIZE] = "author:", nam[MAXSIZE] = "name:", num[MAXSIZE] = "number:";
	strcat(aut, info); strcat(nam, info); strcat(num, info);
	fp = fopen("c:\\new\\book2.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author, &M.member[i].account);
		i++;
	}
	fclose(fp);
	for (j = 1; j <= i - 1; j++)
	{
		if ((strcmp(aut, B.book[j].author) == 0 || strcmp(nam, B.book[j].name) == 0 || strcmp(num, B.book[j].number) == 0) && strcmp(M.member[0].account, M.member[j].account) == 0)
		{
			printf("该书信息:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
			return 1;
		}
	}
	if (j > i - 2)
		printf("该书已还或未借出！\n");
	return 0;
}

void DeleteBook(BookList B,char info[])
{
	FILE* fp; int i = 1,j=1;
	char aut[MAXSIZE] = "author:", nam[MAXSIZE] = "name:", num[MAXSIZE] = "number:";
	strcat(aut, info); strcat(nam, info); strcat(num, info);
	fp = fopen("c:\\new\\book.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author);
		i++;
	}
	fclose(fp);
	for (j; j <= i - 2; j++)
	{
		if (strcmp(aut, B.book[j].author) == 0 || strcmp(nam, B.book[j].name) == 0 || strcmp(num, B.book[j].number) == 0)
		{
			for (j; j < i - 2; j++)
				B.book[j] = B.book[j + 1];
			break;
		}
		
	}
	fp = fopen("c:\\new\\book.txt", "w");	
	if (fp == NULL) { printf("error!\n"); exit(0); }
	for (j = 1; j <= i - 3; j++)
	{
		fprintf(fp, "%s\t%s\t%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
	}
	printf("删除成功！\n");
	fclose(fp);
	return;
}

/*void xiugaibook(BookList B, char info[])
{
	FILE* fp; int i = 1, j, n;
	char aut[MAXSIZE] = "author:", nam[MAXSIZE] = "name:", num[MAXSIZE] = "number:";
	strcat(aut, info); strcat(nam, info); strcat(num, info);
	fp = fopen("c:\\new\\book.txt", "r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author);
		i++;
	}fclose(fp);
	for (j = 1; j <= i - 2; j++)

		if (strcmp(aut, B.book[j].author) == 0 || strcmp(nam, B.book[j].name) == 0 || strcmp(num, B.book[j].number) == 0)break;

	printf("该书信息:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
	printf("请选择修改选项\n");
	printf("1,书号\n");
	printf("2，书名\n");
	printf("3，作者\n");
	int x; scanf("%d", &x); char rr[20]; printf("请输入新的修改项,修改数值前面要加类型和冒号\n");
	switch (x) {
	case 1:scanf("%s", B.book[j].number); break;
	case 2:scanf("%s", B.book[j].name); break;
	case 3:scanf("%s", B.book[j].author); break;
	default:printf("error\n"); break;
	}printf("修改成功\n");
	fp = fopen("c:\\new\\book.txt", "w");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	for (j = 1; j <= i - 3; j++)
	{
		fprintf(fp, "%s\t%s\t%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
	}
	printf("修改成功！\n");
	fclose(fp);
	return;

}*/

void BorrowBook(BookList B,MemberList& M)
{
	FILE* fp; int i = 1, j = 1, n = 1, flag = 0;
	char nam[MAXSIZE] = "name:";
	fp = fopen("c:\\new\\book2.txt","r");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%s%s", &B.book[n].number, &B.book[n].name, &B.book[n].author, &M.member[n].account);
		if (strcmp(M.member[0].account, M.member[n].account) == 0)
			flag++;
		n++;
	}
	if (flag >= 0 && flag < 2)
	{
		printf("请输入需要借出的书籍的名称:");
		scanf("%s", &B.book[0].name);
		if (Inquire(B,B.book[0].name) == 1)
		{
			strcat(nam, B.book[0].name);
			fp = fopen("c:\\new\\book.txt", "r");
			if (fp == NULL) { printf("error!\n"); exit(0); }
			while (!feof(fp))
			{
				fscanf(fp, "%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author);
				i++;
			}
			fclose(fp);
			for (j; j <= i - 2; j++)
			{
				if (strcmp(nam, B.book[j].name) == 0)
				{
					B.book[0] = B.book[j];
					for (j; j < i - 2; j++)
						B.book[j] = B.book[j + 1];
					break;
				}
			}
			fp = fopen("c:\\new\\book.txt", "w");
			if (fp == NULL) { printf("error!\n"); exit(0); }
			for (j = 1; j <= i - 3; j++)
			{
				fprintf(fp, "%s\t%s\t%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
			}
			fclose(fp);
			fp = fopen("c:\\new\\book2.txt", "a+");
			if (fp == NULL) { printf("error!\n"); exit(0); }
			fprintf(fp, "%s\t%s\t%s\t%s\n", B.book[0].number, B.book[0].name, B.book[0].author, M.member[0].account);
			fclose(fp);
			printf("借出成功！\n");
			return;
		}
	}
	else printf("error!\n");
}

void ReturnBook(BookList B,MemberList& M)
{
	FILE* fp; int i = 1, j = 1; char nam[MAXSIZE] = "name:", a[2] = "0";
	printf("请输入需要归还的书籍的名称:");
	scanf("%s", &B.book[0].name);
	strcat(nam, B.book[0].name);
	if (Inquire2(B, M, B.book[0].name) == 1)
	{
		fp = fopen("c:\\new\\book2.txt", "r");
		if (fp == NULL) { printf("error!\n"); exit(0); }
		while (!feof(fp))
		{
			fscanf(fp, "%s%s%s%s", &B.book[i].number, &B.book[i].name, &B.book[i].author, &M.member[i].account);
			i++;
		}
		fclose(fp);
		for (j; j <= i - 2; j++)
		{
			if (strcmp(nam, B.book[j].name) == 0 && strcmp(M.member[0].account, M.member[j].account) == 0)
			{
				printf("\n\n%s	%s\n\n", M.member[0].account, M.member[j].account);
				B.book[0] = B.book[j];
				for (j; j < i - 2; j++)
				{
					M.member[j] = M.member[j + 1];
					B.book[j] = B.book[j + 1];
					break;
				}
			}
		}

		fp = fopen("c:\\new\\book2.txt", "w");
		if (fp == NULL) { printf("error!\n"); exit(0); }
		for (j = 1; j <= i - 3; j++)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\n", B.book[j].number, B.book[j].name, B.book[j].author, M.member[j].account);
		}
		fclose(fp);
		fp = fopen("c:\\new\\book.txt", "a+");
		if (fp == NULL) { printf("error!\n"); exit(0); }
		fprintf(fp, "%s\t%s\t%s\n", B.book[0].number, B.book[0].name, B.book[0].author);
		fclose(fp); printf("归还成功！\n");
	}
	for (j = 1; j < i; j++)
	{
		strcat(M.member[j].account, a);
	}
	return;
}

int main()
{
	system("title 图书管理系统");
	system("mode con cols=48 lines=25");
	system("color 09");
	system("date /T");
	system("TIME /T");
	int flag = -1, n = 1;
	MemberList M;
	BookList B;
	InitBook(B);
	InitMember(M);
	flag = Login(M);
	if (flag == 0)
	{
		while (n > 0)
		{
			Menu1();
			int a;
			scanf("%d", &a);
			switch (a)
			{
			case 1:
				AddBookInfo(B);
				break;
			case 2:
				printf("请输入需要删除的书名或书号:");
				char info[MAXSIZE];
				scanf("%s", info);
				DeleteBook(B, info);
				break;
			/*case 3:
				printf("请输入需要修改的书名:");
				char info2[MAXSIZE];
				scanf("%s", info2);
				xiugaibook(B, info2);*/
			case 4:
				ShowBook(B);
				break;
			case 5:
				AddMemberInfo(M);
				break;
			case 6:
				n = -1;
				break;
			}
		}
	}
	else if (flag == 1)
	{
		while (n > 0)
		{
			Menu2();
			int a;
			scanf("%d", &a);
			switch (a)
			{
			case 1:
				BorrowBook(B, M);
				break;
			case 2:
				ReturnBook(B, M);
				printf("%s", M.member[1].account);
				break;
			case 3:
				ShowBook(B);
				break;
			case 4:
				printf("请输入需要查找的书名:");
				char info3[MAXSIZE];
				scanf("%s", info3);
				Inquire(B, info3);
				break;
			case 5:
				n = -1;
				break;
			}
		}
	}
	else printf("账号或密码错误!\n");
	return 0;
}
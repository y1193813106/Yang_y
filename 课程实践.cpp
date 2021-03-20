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
	printf("*         ����Ա�˵�            *\n");
	printf("*********************************\n");
	printf("*      1.����鼮��Ϣ           *\n");
	printf("*********************************\n");
	printf("*      2.ɾ���鼮��Ϣ           *\n");
	printf("*********************************\n");
	printf("*      3.�޸��鼮��Ϣ           *\n");
	printf("*********************************\n");
	printf("*      4.��ʾȫ���鼮           *\n");
	printf("*********************************\n");
	printf("*      5.��ӻ�Ա��Ϣ           *\n");
	printf("*********************************\n");
	printf("*          6.�˳�               *\n");
	printf("*********************************\n");
	printf("��������Ҫִ�еĲ���:");
}

void Menu2()
{
	printf("******************************\n");
	printf("*         ��Ա�˵�           *\n");
	printf("******************************\n");
	printf("*         1.����             *\n");
	printf("******************************\n");
	printf("*         2.����             *\n");
	printf("******************************\n");
	printf("*      3.��ʾȫ���鼮        *\n");
	printf("******************************\n");
	printf("*      4.�����鼮��Ϣ        *\n");
	printf("******************************\n");
	printf("*         5.�˳�             *\n");
	printf("******************************\n");
	printf("��������Ҫִ�еĲ���:");
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
	printf("�������˺�:");
	scanf("%s", M.member[0].account);
	printf("����������:");
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
		printf("\n����Ա��½�ɹ���\n");
		return 0;
	}
	if (flag == 1)
	{
		printf("\n��Ա��½�ɹ���\n");
		return 1;
	}
	if (flag==-1)
	{
		printf("\n��Ա��½ʧ�ܣ�\n");
		return -1;
	}
}

void AddMemberInfo(MemberList M)
{
	FILE* fp; int i = 1; char acc[MAXSIZE] = "account:";
	fp = fopen("c:\\new\\member.txt", "a+");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	printf("�������˺�:");
	scanf("%s", &M.member[0].account);
	strcat(acc, M.member[0].account);
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", &M.member[i].account, &M.member[i].password);
		if (strcmp(acc, M.member[i].account) == 0)
		{
			printf("���˺��Ѵ��ڣ�\n");
			return;
		}
		i++;
	}
	printf("\n\n%d\n\n", strcmp(acc, M.member[4].account));
	printf("����������:");
	scanf("%s", &M.member[0].password);
	fprintf(fp, "account:%s\npassword:%s\n", M.member[0].account, M.member[0].password);
	fclose(fp);
	printf("��ӻ�Ա�ɹ���\n");
	return;
}

void AddBookInfo(BookList B)
{
	FILE* fp; int n;
	fp = fopen("c:\\new\\book.txt", "a");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	printf("��������:");
	scanf("%s", &B.book[0].number);
	printf("����������:");
	scanf("%s", &B.book[0].name);
	printf("����������:");
	scanf("%s", &B.book[0].author);
	printf("�Ƿ񱣴浱ǰ�鼮��Ϣ��1.�� 2.��");
	scanf("%d", &n);
	if (n == 1)
	{
		fprintf(fp, "number:%s\tname:%s\tauthor:%s\n", B.book[0].number, B.book[0].name, B.book[0].author);
		fclose(fp);
		printf("���ͼ��ɹ���\n");
	}
	else if (n == 2)
	{
		fclose(fp);
		printf("���ͼ��ʧ�ܣ�\n");
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
			printf("������Ϣ:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
			return 1;
		}
	}
	if (j > i - 2)
		printf("���鲻���ڻ��ѱ������\n");
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
			printf("������Ϣ:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
			return 1;
		}
	}
	if (j > i - 2)
		printf("�����ѻ���δ�����\n");
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
	printf("ɾ���ɹ���\n");
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

	printf("������Ϣ:\n%s	%s	%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
	printf("��ѡ���޸�ѡ��\n");
	printf("1,���\n");
	printf("2������\n");
	printf("3������\n");
	int x; scanf("%d", &x); char rr[20]; printf("�������µ��޸���,�޸���ֵǰ��Ҫ�����ͺ�ð��\n");
	switch (x) {
	case 1:scanf("%s", B.book[j].number); break;
	case 2:scanf("%s", B.book[j].name); break;
	case 3:scanf("%s", B.book[j].author); break;
	default:printf("error\n"); break;
	}printf("�޸ĳɹ�\n");
	fp = fopen("c:\\new\\book.txt", "w");
	if (fp == NULL) { printf("error!\n"); exit(0); }
	for (j = 1; j <= i - 3; j++)
	{
		fprintf(fp, "%s\t%s\t%s\n", B.book[j].number, B.book[j].name, B.book[j].author);
	}
	printf("�޸ĳɹ���\n");
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
		printf("��������Ҫ������鼮������:");
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
			printf("����ɹ���\n");
			return;
		}
	}
	else printf("error!\n");
}

void ReturnBook(BookList B,MemberList& M)
{
	FILE* fp; int i = 1, j = 1; char nam[MAXSIZE] = "name:", a[2] = "0";
	printf("��������Ҫ�黹���鼮������:");
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
		fclose(fp); printf("�黹�ɹ���\n");
	}
	for (j = 1; j < i; j++)
	{
		strcat(M.member[j].account, a);
	}
	return;
}

int main()
{
	system("title ͼ�����ϵͳ");
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
				printf("��������Ҫɾ�������������:");
				char info[MAXSIZE];
				scanf("%s", info);
				DeleteBook(B, info);
				break;
			/*case 3:
				printf("��������Ҫ�޸ĵ�����:");
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
				printf("��������Ҫ���ҵ�����:");
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
	else printf("�˺Ż��������!\n");
	return 0;
}
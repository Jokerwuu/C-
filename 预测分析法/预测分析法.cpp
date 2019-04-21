#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<dos.h>
#define _KEY_WORD_END "waiting for your expanding"

char input[255];//输入缓冲区
char token[255]="";//单词缓冲区
char A[20];//分析栈
char B[20];//剩余串
char v1[15] = {'b','e',';','I','=','+','-','*','/','N','(',')','#'}; //终结符
char v2[6] = {'E','T','S','F','X','Y'};//非终结符
int j = 0, b = 0, top = 0, l;//l为输入串长度

char *rwtab[]={"begin","if","then","while","do","end",_KEY_WORD_END};     //可扩充的关键字数组
int p_input;
int p_token;
char ch;

typedef struct type//产生式类型定义
{
	char origin;//大写字符
	char array[20];//产生式右边字符
	int length;//字符个数
}type;
type e, t,t1,t2,s,f,f1,f2,f3,x,x1,x2,x3,y,y1,y2;//结构体变量
type C[9][12];//预测分析表

void print()//输出分析栈
{ 
	int a;//指针
	for (a = 0; a <= top + 1; a++)
	{
		printf("%c", A[a]);
	}
	printf("\t\t");
}/*print*/

void print1()/*输出剩余串*/
{ 
	int j;
	for (j = 0; j<b; j++)/*输出对齐符*/
	{
		printf(" ");
	}
	for (j = b; j <= l; j++)
	{
		printf("%c", B[j]);
	}
	printf("\t\t"); 
}/*print1*/

char m_getch()//从输入缓冲区得到一个字符到ch中
{
	ch=input[p_input];
	p_input=p_input+1;
	return (ch);
}

void getbc()
{
	while(ch==' '||ch==10){
		ch=input[p_input];
		p_input=p_input+1;
	}
}


void concat()
{
	token[p_token]=ch;
	p_token=p_token+1;
	token[p_token]='\0';
}

int letter()
{
	if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') return 1;
	else return 0;
}

int digit()
{
	if(ch>='0'&&ch<='9') return 1;
	else return 0;
}

int reserve(){             //检索关键字
	int i=0;
	while(strcmp(rwtab[i],_KEY_WORD_END)){
		if(!strcmp(rwtab[i],token)){
			return i+1;
		}
		i=i+1;
	}
	return 10;
}

void retract(){             //回退一个字符
	p_input=p_input-1;
}


void main() 
{
	int m, n, k = 0, flag = 0, finish = 0;
	char ch1, z;
	type cha;/*用来接受C[m][n]*/ /*把文法产生式赋值结构体*/
	e.origin='E';
	strcpy(e.array, "bTe");
	e.length = 3;
	t.origin = 'T';
	strcpy(t.array, "ST");
	t.length = 2;
	t1.origin= 'T';
	strcpy(t1.array,"^");
	t1.length=1;
	t2.origin= 'T';
	strcpy(t2.array,";ST");
	t2.length=3;
	s.origin='S';
	strcpy(s.array,"I=F");
	s.length=3;
	f.origin='F';
	strcpy(f.array,"XF");
	f.length=2;
	f1.origin='F';
	strcpy(f1.array,"+XF");
	f1.length=3;
	f2.origin='F';
	strcpy(f2.array,"-XF");
	f2.length=3;
	f3.origin='F';
	strcpy(f3.array,"^");
	f3.length=1;
	x.origin='X';
	strcpy(x.array,"YX");
	x.length=2;
	x1.origin='X';
	strcpy(x1.array,"^");
	x1.length=1;
	x2.origin='X';
	strcpy(x2.array,"*YX");
	x2.length=3;
	x3.origin='X';
	strcpy(x3.array,"/YX");
	x3.length=3;
	y.origin='Y';
	strcpy(y.array,"I");
	y.length=1;
	y1.origin='Y';
	strcpy(y1.array,"N");
	y1.length=1;
	y2.origin='Y';
	strcpy(y2.array,"(F)");
	y2.length=3;

	for (m = 0; m <= 5; m++)/*初始化分析表*/
	{
		for (n = 0; n <= 11; n++)
		{
			C[m][n].origin = 'N';/*全部赋为空*/
		}
	}
	/*填充分析表*/
	C[0][0] = e;
	C[1][3] = t; 
	C[1][1] = t1; C[1][2] = t2;
	C[2][3] = s;
	C[3][3] = f; C[3][9] = f; C[3][10] = f;
	C[3][5] = f1; C[3][6] = f2; C[3][1] = f3; C[3][2] = f3; C[3][11] = f3;
	C[4][3] = x; C[4][9] = x; C[4][10] = x; C[4][5] = x1; C[4][6] = x1; C[4][11] = x1;
	C[4][1] = x1; C[4][2] = x1; C[4][7] = x2; C[4][8] = x3;
	C[5][3] = y; C[5][9] = y1; C[5][10] = y2;
	printf("\n预测分析表为：\n\n");
	printf("非终结符\tbegin\tend\t;\tID\t:=\t+\t-\t*\t/\tNUM\t(\t)\n");
	for (m = 0; m <= 5; m++)
	{
		printf("%c",v2[m]);
		printf("\t\t");
		for (n = 0; n <= 11; n++)
		{
			if(C[m][n].origin!='N')
			{
				printf("%c->%s",C[m][n].origin,C[m][n].array);
				printf("\t");
			}
			else
			{
				printf("  \t");
			}
		}
		printf("\n");
	}

	
	printf("\n请输入要分析的字符串,以#号结束:");
	scanf("%[^#]s", input);
	p_input=0;
	do
	{
		p_token=0;
		m_getch();
		getbc();
		if(letter())
		{
			while(letter()||digit())
			{
				concat();
				m_getch();
			}
			retract();
			int res=reserve();
			switch(res)
			{
				case 1:
					B[j]='b';
					j++;
					break;
				case 6:
					B[j]='e';
					j++;
					break;
				case 10:
					B[j]='I';
					j++;
					break;
				default:
					printf("输入错误！");

			}

		}
		else if(digit())
		{
			while(digit())
			{
				concat();
				m_getch();
			}
			retract();
			B[j]='N';
			j++;
		}
		else switch(ch)
		{
			case ':':
				m_getch();
				if(ch=='=')
				{
					B[j]='=';
					j++;
				}
				else
				{
					printf("输入错误！");
					exit(1);
				}
				break;
			case ';':
				B[j]=';';
				j++;
				break;
			case '+':
				B[j]='+';
				j++;
				break;
			case '-':
				B[j]='-';
				j++;
				break;
			case '*':
				B[j]='*';
				j++;
				break;
			case '/':
				B[j]='/';
				j++;
				break;
			case '(':
				B[j]='(';
				j++;
				break;
			case ')':
				B[j]=')';
				j++;
				break;
			default:
				printf("输入错误！\n");
				exit(1);
		}
	}while(ch!='\0');
	B[j]='#';
	j++;
	printf("\n你输入的字符串为：\n %s\n",input);
	l = j;/*分析串长度*/
	ch1 = B[0];/*当前分析字符*/
	A[top] = '#';
	A[++top] = 'E';/*'#','E'进栈*/
	printf("\n步骤\t\t分析栈\t\t剩余字符\t\t所用产生式\n");
	do {
		z = A[top--];/*x为当前栈顶字符*/
		printf("%d", k++);
		printf("\t\t");
		for (j = 0; j <= 12; j++)/*判断是否为终结符*/
			if (z == v1[j])
			{
				flag = 1;
				break; 
			}
		if (flag == 1)/*如果是终结符*/
		{
			if (z == '#')
			{
				finish = 1;/*结束标记*/
				printf("匹配成功!\n");/*接受*/
				getchar();
				getchar();
				exit(1);
			}/*if*/
			if (z == ch1)
			{
				print();
				print1();
				printf("%c匹配\n", ch1);
				ch1 = B[++b];/*下一个输入字符*/
				flag = 0;/*恢复标记*/ 
			}/*if*/
			else/*出错处理*/ 
			{ 
				print(); 
				print1();
				printf("%c出错\n", ch1);/*输出出错终结符*/
				exit(1); 
			}/*else*/

		}/*if*/
		else/*非终结符处理*/
		{
			for (j = 0; j <= 5; j++)
				if (z == v2[j])
				{
					m = j;/*行号*/
					break;
				}
			for (j = 0; j <= 11; j++)
				if (ch1 == v1[j])
				{ 
					n = j;/*列号*/ 
					break;
				}
			cha = C[m][n];
			if (cha.origin != 'N')/*判断是否为空*/
			{ 
				print();
				print1();
				printf("%c->", cha.origin);/*输出产生式*/
				for (j = 0; j<cha.length; j++)
						printf("%c", cha.array[j]);
				printf("\n");
				for (j = (cha.length - 1); j >= 0; j--)/*产生式逆序入栈*/
					A[++top] = cha.array[j];
				if (A[top] == '^')/*为空则不进栈*/
					top--;
			}/*if*/
			else/*出错处理*/ 
			{ 
				print();
				print1();
				printf("%c出错\n", z);/*输出出错非终结符*/
				exit(1);
			}/*else*/

		}/*else*/
	}while (finish == 0);
}

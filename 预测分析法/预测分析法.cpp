#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<dos.h>
#define _KEY_WORD_END "waiting for your expanding"

char input[255];//���뻺����
char token[255]="";//���ʻ�����
char A[20];//����ջ
char B[20];//ʣ�മ
char v1[15] = {'b','e',';','I','=','+','-','*','/','N','(',')','#'}; //�ս��
char v2[6] = {'E','T','S','F','X','Y'};//���ս��
int j = 0, b = 0, top = 0, l;//lΪ���봮����

char *rwtab[]={"begin","if","then","while","do","end",_KEY_WORD_END};     //������Ĺؼ�������
int p_input;
int p_token;
char ch;

typedef struct type//����ʽ���Ͷ���
{
	char origin;//��д�ַ�
	char array[20];//����ʽ�ұ��ַ�
	int length;//�ַ�����
}type;
type e, t,t1,t2,s,f,f1,f2,f3,x,x1,x2,x3,y,y1,y2;//�ṹ�����
type C[9][12];//Ԥ�������

void print()//�������ջ
{ 
	int a;//ָ��
	for (a = 0; a <= top + 1; a++)
	{
		printf("%c", A[a]);
	}
	printf("\t\t");
}/*print*/

void print1()/*���ʣ�മ*/
{ 
	int j;
	for (j = 0; j<b; j++)/*��������*/
	{
		printf(" ");
	}
	for (j = b; j <= l; j++)
	{
		printf("%c", B[j]);
	}
	printf("\t\t"); 
}/*print1*/

char m_getch()//�����뻺�����õ�һ���ַ���ch��
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

int reserve(){             //�����ؼ���
	int i=0;
	while(strcmp(rwtab[i],_KEY_WORD_END)){
		if(!strcmp(rwtab[i],token)){
			return i+1;
		}
		i=i+1;
	}
	return 10;
}

void retract(){             //����һ���ַ�
	p_input=p_input-1;
}


void main() 
{
	int m, n, k = 0, flag = 0, finish = 0;
	char ch1, z;
	type cha;/*��������C[m][n]*/ /*���ķ�����ʽ��ֵ�ṹ��*/
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

	for (m = 0; m <= 5; m++)/*��ʼ��������*/
	{
		for (n = 0; n <= 11; n++)
		{
			C[m][n].origin = 'N';/*ȫ����Ϊ��*/
		}
	}
	/*��������*/
	C[0][0] = e;
	C[1][3] = t; 
	C[1][1] = t1; C[1][2] = t2;
	C[2][3] = s;
	C[3][3] = f; C[3][9] = f; C[3][10] = f;
	C[3][5] = f1; C[3][6] = f2; C[3][1] = f3; C[3][2] = f3; C[3][11] = f3;
	C[4][3] = x; C[4][9] = x; C[4][10] = x; C[4][5] = x1; C[4][6] = x1; C[4][11] = x1;
	C[4][1] = x1; C[4][2] = x1; C[4][7] = x2; C[4][8] = x3;
	C[5][3] = y; C[5][9] = y1; C[5][10] = y2;
	printf("\nԤ�������Ϊ��\n\n");
	printf("���ս��\tbegin\tend\t;\tID\t:=\t+\t-\t*\t/\tNUM\t(\t)\n");
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

	
	printf("\n������Ҫ�������ַ���,��#�Ž���:");
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
					printf("�������");

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
					printf("�������");
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
				printf("�������\n");
				exit(1);
		}
	}while(ch!='\0');
	B[j]='#';
	j++;
	printf("\n��������ַ���Ϊ��\n %s\n",input);
	l = j;/*����������*/
	ch1 = B[0];/*��ǰ�����ַ�*/
	A[top] = '#';
	A[++top] = 'E';/*'#','E'��ջ*/
	printf("\n����\t\t����ջ\t\tʣ���ַ�\t\t���ò���ʽ\n");
	do {
		z = A[top--];/*xΪ��ǰջ���ַ�*/
		printf("%d", k++);
		printf("\t\t");
		for (j = 0; j <= 12; j++)/*�ж��Ƿ�Ϊ�ս��*/
			if (z == v1[j])
			{
				flag = 1;
				break; 
			}
		if (flag == 1)/*������ս��*/
		{
			if (z == '#')
			{
				finish = 1;/*�������*/
				printf("ƥ��ɹ�!\n");/*����*/
				getchar();
				getchar();
				exit(1);
			}/*if*/
			if (z == ch1)
			{
				print();
				print1();
				printf("%cƥ��\n", ch1);
				ch1 = B[++b];/*��һ�������ַ�*/
				flag = 0;/*�ָ����*/ 
			}/*if*/
			else/*������*/ 
			{ 
				print(); 
				print1();
				printf("%c����\n", ch1);/*��������ս��*/
				exit(1); 
			}/*else*/

		}/*if*/
		else/*���ս������*/
		{
			for (j = 0; j <= 5; j++)
				if (z == v2[j])
				{
					m = j;/*�к�*/
					break;
				}
			for (j = 0; j <= 11; j++)
				if (ch1 == v1[j])
				{ 
					n = j;/*�к�*/ 
					break;
				}
			cha = C[m][n];
			if (cha.origin != 'N')/*�ж��Ƿ�Ϊ��*/
			{ 
				print();
				print1();
				printf("%c->", cha.origin);/*�������ʽ*/
				for (j = 0; j<cha.length; j++)
						printf("%c", cha.array[j]);
				printf("\n");
				for (j = (cha.length - 1); j >= 0; j--)/*����ʽ������ջ*/
					A[++top] = cha.array[j];
				if (A[top] == '^')/*Ϊ���򲻽�ջ*/
					top--;
			}/*if*/
			else/*������*/ 
			{ 
				print();
				print1();
				printf("%c����\n", z);/*���������ս��*/
				exit(1);
			}/*else*/

		}/*else*/
	}while (finish == 0);
}

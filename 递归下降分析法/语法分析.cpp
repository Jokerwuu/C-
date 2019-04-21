
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _KEY_WORD_END "waiting for your expanding"

typedef struct
{
	int typenum;
	char *word;
}WORD;

int count=1;
char input[255];    //���뻻������
char token[255]="";  //���ʻ�����
char typnumber[255]="";//�����ֱ��뻺����
int p_input;         //���뻻������ָ��
int p_token;         //���ʻ�����ָ��
int p_typ;           //�����ֱ��뻺����ָ��

int kk=0;
char ch;                  //��ǰ�����ַ�
int syn;                  //��ǰ�����ֱ���
char *rwtab[]={"begin","if","then","while","do","end",_KEY_WORD_END};     //������Ĺؼ�������

WORD* scaner();      //ɨ�躯��
void lrparser();
void yucu();
void statement();
void expression();
void term();
void factor();

void main()
{
	int over=1;
	WORD *oneword=new WORD;
	printf("�����뵥�ʴ����ԡ�#��������\n");
	scanf("%[^#]s",input);
	printf("\n");
	p_input=0;
	p_typ=0;
	printf("��ĵ��ʴ�Ϊ: \n% s \n",input);
	printf("\n");
	printf("��Ķ�Ԫ������Ϊ:\n");
	while(over<1000&&over!=-1){
		oneword=scaner();
		if(oneword->typenum<1000){
			printf("(% d,% s )",oneword->typenum,oneword->word);
			typnumber[p_typ]=oneword->typenum;
			p_typ+=1;
		}
		over=oneword->typenum;
	}
	printf("\n");
	int i=0;
	printf("\n");
	printf("������ĵ����ֱ���Ϊ:\n");
	while(typnumber[i]!='\0'){
		printf("% d",typnumber[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	p_typ=0;
	printf("�ʷ��������Ϊ��\n");
	lrparser();
	printf("\n");
}


char m_getch(){             //�����뻺������ȡһ���ַ���ch��
	ch=input[p_input];
	p_input=p_input+1;
	return (ch);
}


void getbc(){              //ȥ���ո�
	while(ch==' '||ch==10){
		ch=input[p_input];
		p_input=p_input+1;
	}
}


void concat(){          //ƴ�ӵ���
	token[p_token]=ch;
	p_token=p_token+1;
	token[p_token]='\0';
}

int letter(){              //�ж��Ƿ�Ϊ��ĸ
	if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') return 1;
	else return 0;
}

int digit(){                //�ж��Ƿ�Ϊ����
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


char *dtb(){
	return NULL;
}

int m_getsyn(){          //��ȡһ�������ֱ���
	syn=typnumber[p_typ];
	p_typ+=1;
	return (syn);
}

void factor(){
	if(syn>0)
		printf("%d������factor���ɹ���\n",count++);
	if(syn==10||syn==11)
	{
		printf("\t��ʶ�������ֳɹ�!\n");
		m_getsyn();
	}
	else if(syn==27)
	{
		printf("\t( �ɹ�!\n");
		m_getsyn();
		expression();
		if(syn==28)
		{
			printf("\t) �ɹ�!\n");
			m_getsyn();
		}
		else{
			printf("\t')'����error!");
			kk=1;
		}
	}
	else{
		printf("\t���ʽ����error!");
		kk=1;
	}
	return;
}

void term(){
	if(syn>0)
		printf("%d������term���ɹ���\n",count++);
	factor();
	while(syn==15||syn==16)
	{
		printf("\t* /�ɹ�!\n");
		m_getsyn();
		factor();
	}
	return;
}

void expression()
{
	if(syn>0)
		printf("%d������expression���ɹ���\n",count++);
	term();
	while(syn==13||syn==14)
	{
		printf("\t+ -�ɹ�!\n");
		m_getsyn();
		term();
	}
	return;
}

void statement(){
	if(syn>0)
		printf("%d������statement���ɹ���\n",count++);
	if(syn==10)
	{
		printf("\t��ʶ���ɹ���\n");
		m_getsyn();
		if(syn==18)
		{
			printf("\t:=�ɹ���\n");
			m_getsyn();
			expression();
		}
		else
		{
			printf("\t��ֵ�Ŵ���error!");
			kk=1;
		}
	}else
	{
		printf("\t������error!");
		kk=1;
	}
	return;
}


void yucu(){
	if(syn>0)
		printf("%d������yucu���ɹ���\n",count++);
	statement();
	while(syn==26){
		printf("\t���ɹ�!\n");
		m_getsyn();
		statement();
	}
	return;
}


void lrparser(){
	m_getsyn();
	if(syn>0)
		printf("%d������lrparser���ɹ���\n",count++);
	if(syn==1)
	{
		printf("\tbegin�ɹ���\n");
		m_getsyn();
		yucu();
		if(syn==6)
		{
			printf("\tend�ɹ���\n");
			m_getsyn();
			if(syn==0&&kk==0)
				printf("success!\n");
		}
		else{
			if(kk!=1){
				printf("\tȱ'end'����error!\n");
				kk=1;
			}
		}
	}
	else{
		printf("\t'begin'����\n");
			kk=1;
	}
	return;
}

WORD* scaner(){
	WORD *myword=new WORD;
	myword->typenum=10;
	myword->word="";
	p_token=0;
	m_getch();
	getbc();
	if(letter()){
		while(letter()||digit()){
			concat();
			m_getch();
		}
		retract();
		myword->typenum=reserve();
		myword->word=token;
		return(myword);
	}
	else if(digit()){
		while(digit()){
			concat();
			m_getch();
		}
		retract();
		myword->typenum=11;
		myword->word=token;
		return (myword);
	}
	else switch(ch){
		case '=':  m_getch();
			if(ch=='='){
				myword->typenum=39;
				myword->word="==";
				return (myword);
			}
			retract();
			myword->typenum=25;
			myword->word="=";
			return (myword);
			break;
		case '+':  
				myword->typenum=13;
				myword->word="+";
				return (myword);
				break;
		case '-':  
				myword->typenum=14;
				myword->word="-";
				return (myword);
				break;
		case '*':  
				myword->typenum=15;
				myword->word="*";
				return (myword);
				break;
		case '/':  
				myword->typenum=16;
				myword->word="/";
				return (myword);
				break;
		case '(':  
				myword->typenum=27;
				myword->word="(";
				return (myword);
				break;
		case ')':  
				myword->typenum=28;
				myword->word=")";
				return (myword);
				break;
		case '[':  
				myword->typenum=29;
				myword->word="[";
				return (myword);
				break;
		case ']':  
				myword->typenum=30;
				myword->word="]";
				return (myword);
				break;
		case '{':  
				myword->typenum=31;
				myword->word="{";
				return (myword);
				break;
		case '}':  
				myword->typenum=32;
				myword->word="}";
				return (myword);
				break;
		case ',':  
				myword->typenum=33;
				myword->word=",";
				return (myword);
				break;
		case ':':
				m_getch();
				if(ch=='='){
					myword->typenum=18;
					myword->word=":=";
					return (myword);
				}
				retract();
				myword->typenum=17;
				myword->word=":";
				return (myword);
				break;
		case ';':  
				myword->typenum=26;
				myword->word=";";
				return (myword);
				break;
		case '>':  m_getch();
				if(ch=='='){
					myword->typenum=24;
					myword->word=">=";
					return (myword);
				}
				retract();
				myword->typenum=23;
				myword->word=">";
				return (myword);
				break;
		case '<':  m_getch();
				if(ch=='='){
					myword->typenum=22;
					myword->word="<=";
					return (myword);
				}
				else if(ch=='>'){
					myword->typenum=21;
					myword->word="<>";
					return (myword);
				}
				retract();
				myword->typenum=20;
				myword->word="<";
				return (myword);
				break;
		case '!':  m_getch();
				if(ch=='='){
					myword->typenum=40;
					myword->word="!=";
					return (myword);
				}
				retract();
				myword->typenum=-1;
				myword->word="ERROR";
				return (myword);
				break;
		case '\0':
			myword->typenum=1000;
			myword->word="OVER";
			return (myword);
			break;
		default: myword->typenum=-1;
			myword->word="ERROR";
			return (myword);
	}
}
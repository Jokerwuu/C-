
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
char input[255];    //输入换缓冲区
char token[255]="";  //单词缓冲区
char typnumber[255]="";//单词种别码缓冲区
int p_input;         //输入换缓冲区指针
int p_token;         //单词缓冲区指针
int p_typ;           //单词种别码缓冲区指针

int kk=0;
char ch;                  //当前读入字符
int syn;                  //当前单词种别码
char *rwtab[]={"begin","if","then","while","do","end",_KEY_WORD_END};     //可扩充的关键字数组

WORD* scaner();      //扫描函数
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
	printf("请输入单词串，以“#”结束：\n");
	scanf("%[^#]s",input);
	printf("\n");
	p_input=0;
	p_typ=0;
	printf("你的单词串为: \n% s \n",input);
	printf("\n");
	printf("你的二元组序列为:\n");
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
	printf("你输入的单词种别码为:\n");
	while(typnumber[i]!='\0'){
		printf("% d",typnumber[i]);
		i++;
	}
	printf("\n");
	printf("\n");
	p_typ=0;
	printf("词法分析结果为：\n");
	lrparser();
	printf("\n");
}


char m_getch(){             //从输入缓冲区读取一个字符到ch中
	ch=input[p_input];
	p_input=p_input+1;
	return (ch);
}


void getbc(){              //去除空格
	while(ch==' '||ch==10){
		ch=input[p_input];
		p_input=p_input+1;
	}
}


void concat(){          //拼接单词
	token[p_token]=ch;
	p_token=p_token+1;
	token[p_token]='\0';
}

int letter(){              //判断是否为字母
	if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') return 1;
	else return 0;
}

int digit(){                //判断是否为数字
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


char *dtb(){
	return NULL;
}

int m_getsyn(){          //读取一个单词种别码
	syn=typnumber[p_typ];
	p_typ+=1;
	return (syn);
}

void factor(){
	if(syn>0)
		printf("%d、调用factor语句成功！\n",count++);
	if(syn==10||syn==11)
	{
		printf("\t标识符或数字成功!\n");
		m_getsyn();
	}
	else if(syn==27)
	{
		printf("\t( 成功!\n");
		m_getsyn();
		expression();
		if(syn==28)
		{
			printf("\t) 成功!\n");
			m_getsyn();
		}
		else{
			printf("\t')'错误！error!");
			kk=1;
		}
	}
	else{
		printf("\t表达式错误！error!");
		kk=1;
	}
	return;
}

void term(){
	if(syn>0)
		printf("%d、调用term语句成功！\n",count++);
	factor();
	while(syn==15||syn==16)
	{
		printf("\t* /成功!\n");
		m_getsyn();
		factor();
	}
	return;
}

void expression()
{
	if(syn>0)
		printf("%d、调用expression语句成功！\n",count++);
	term();
	while(syn==13||syn==14)
	{
		printf("\t+ -成功!\n");
		m_getsyn();
		term();
	}
	return;
}

void statement(){
	if(syn>0)
		printf("%d、调用statement语句成功！\n",count++);
	if(syn==10)
	{
		printf("\t标识符成功！\n");
		m_getsyn();
		if(syn==18)
		{
			printf("\t:=成功！\n");
			m_getsyn();
			expression();
		}
		else
		{
			printf("\t赋值号错误！error!");
			kk=1;
		}
	}else
	{
		printf("\t语句错误！error!");
		kk=1;
	}
	return;
}


void yucu(){
	if(syn>0)
		printf("%d、调用yucu语句成功！\n",count++);
	statement();
	while(syn==26){
		printf("\t；成功!\n");
		m_getsyn();
		statement();
	}
	return;
}


void lrparser(){
	m_getsyn();
	if(syn>0)
		printf("%d、调用lrparser语句成功！\n",count++);
	if(syn==1)
	{
		printf("\tbegin成功！\n");
		m_getsyn();
		yucu();
		if(syn==6)
		{
			printf("\tend成功！\n");
			m_getsyn();
			if(syn==0&&kk==0)
				printf("success!\n");
		}
		else{
			if(kk!=1){
				printf("\t缺'end'错误！error!\n");
				kk=1;
			}
		}
	}
	else{
		printf("\t'begin'错误\n");
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
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
bool GAME_OVER=false;
const int ROW=4;
const int COL=4;
const int row[]={4,14,24,34};
const int col[]={4,8,12,16};
static int SCORE1=0;
static int SCORE=0;
const int SEED_1=2;
const int SEED_2=4;
const int CONSTANT=3;
typedef struct pos{
	COORD p;
	int num;
}POS; 
POS element[ROW*COL];
void print(){
	for(int j=0;j<16;j++){
		if(element[j].num==0)
		continue;
		SetConsoleCursorPosition(hout,element[j].p);
		cout<<element[j].num;
	}
}
void random(){
	bool flag=false;
	for(int j=0;j<16;j++){
		if(element[j].num==0)
		flag=true;
	}
	if(!flag) return;
	srand(time(NULL));
	int r=2;
	int p;
	do{
		p=rand()%16;
	}while(element[p].num!=0);
	if(r!=3){
		element[p].num=SEED_1;
	}else if(r==3){
		element[p].num=SEED_2;
	}
}
void init(){
	int t=0;
	for(int j=0;j<ROW;j++){
		for(int k=0;k<COL;k++){
			element[t].p.X=row[k];
			element[t].p.Y=col[j];
			element[t].num=0;
			t++;
		}
	}
}
void screen(){
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD size={80,25};
	SetConsoleScreenBufferSize(hout,size);
	SetConsoleTitle("2 0 4 8 made by chencaijin");
	CONSOLE_CURSOR_INFO in;
	in.bVisible=FALSE;
	in.dwSize=1;
	SetConsoleCursorInfo(hout,&in);
	cout<<"---------------2 0 4 8---------------"<<endl;
	COORD c;
	for(int j=2;j<=18;j++){
		if((j-2)%4!=0){
			for(int k=0;k<=40;k+=10){
				c.X=k;
				c.Y=j;
				SetConsoleCursorPosition(hout,c);
				putchar('|');
			}
		}else{
			cout<<endl<<"+---------+---------+---------+---------+";
		}
	}
	cout<<endl<<endl<<" 得  分 :"<<endl;
}
void change(const int begin,const int end,const int jump,const int dist){
	int temp;
	for(int a=begin;a<=end;a+=jump){
		for(int j=0;j<CONSTANT;j++){
			temp=a;
			for(int k=j;k<CONSTANT;k++){
				if(element[temp].num==0){
					element[temp].num=element[temp+dist].num;
					element[temp+dist].num=0;
				}else if(element[temp].num==element[temp+dist].num){
					element[temp].num=element[temp].num*2;
					if(element[temp].num==4)
					SCORE1+=4;
					element[temp+dist].num=0;
				}			
				temp+=dist;
			}
		}
	}		
}
void update(){
	COORD coord={10,20};
	SetConsoleCursorPosition(hout,coord);
	cout<<"       ";
	coord.X=10;
	SetConsoleCursorPosition(hout,coord);
	cout<<SCORE<<"分";
}
void check(){
	for(int j=0;j<16;j++){
		if(element[j].num==0)
		return;
	}
	for(int j=0;j<4;j++){
		if(element[j].num==element[j+4].num||element[j+4].num==element[j+8].num||element[j+8].num==element[j+12].num)
		return;
	}
	for(int j=0;j<12;j+=4){
		if(element[j].num==element[j+1].num||element[j+1].num==element[j+2].num||element[j+2].num==element[j+3].num)
		return;
	}
	GAME_OVER=true;
}
void clear(){
	for(int j=0;j<16;j++){
		SetConsoleCursorPosition(hout,element[j].p);
		cout<<"     ";
	}
}
void compute(){
	SCORE=0;
	for(int j=0;j<16;j++){
		if(element[j].num>8)
		SCORE+=element[j].num;
	}
	SCORE+=SCORE1;
}
int main()
{
	screen();
	update();
	init();
	random();
	random();
	print();
	char command;
	do{
		command=_getch();
		switch(command){
			case 72://上 
				change(0,3,1,4);
				random();
				break;
			case 75://左 
				change(0,12,4,1);
				random();
				break;
			case 77://右 
				change(3,15,4,-1);
				random();
				break;
			case 80://下
				change(12,15,1,-4);
				random();
				break;
			default:break; 
		}		
		check();		
		if(GAME_OVER) {
			COORD center={13,10};				
			SetConsoleCursorPosition(hout,center);
			SetConsoleTextAttribute(hout,FOREGROUND_RED|BACKGROUND_BLUE);
			cout<<"G A M E O V E R"<<endl;
			SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
			break;
		}
		clear();
		print();
		compute();			
		update();
	}while(true);
	getchar();	
	return 0;
}


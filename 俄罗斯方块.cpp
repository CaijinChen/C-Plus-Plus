#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
const int HEIGHT=20;
const int WIDTH=40;
typedef struct game{
	COORD pos;
	bool have;
}GAME;
clock_t SPEED=0.4*CLOCKS_PER_SEC;
static int TOP=18;
bool IS_GAME_OVER=false;
GAME box[HEIGHT][WIDTH];
const COORD lineW[4]={{18,0},{20,0},{22,0},{24,0}};
const COORD lineN[4]={{20,-2},{20,-1},{20,0},{20,1}};
const COORD rect[4]={{20,0},{22,0},{20,1},{22,1}};
const COORD seven1[4]={{18,-1},{20,-1},{20,0},{20,1}};
const COORD seven2[4]={{18,1},{20,1},{22,1},{22,0}};
const COORD seven3[4]={{20,-1},{20,0},{20,1},{22,1}};
const COORD seven4[4]={{20,0},{22,0},{24,0},{20,1}};
const COORD Seven1[4]={{22,-1},{20,-1},{20,0},{20,1}};
const COORD Seven2[4]={{18,0},{20,0},{22,0},{22,1}};
const COORD Seven3[4]={{20,-1},{20,0},{20,1},{18,1}};
const COORD Seven4[4]={{20,1},{22,1},{24,1},{20,0}};
const COORD tUp[4]={{22,0},{22,1},{20,1},{24,1}};
const COORD tDown[4]={{22,0},{20,0},{24,0},{22,1}};
const COORD tLeft[4]={{22,-1},{22,0},{22,1},{20,0}};
const COORD tRight[4]={{22,-1},{22,0},{22,1},{24,0}};
const COORD z1[4]={{18,0},{20,0},{20,1},{22,1}};
const COORD z2[4]={{22,0},{22,-1},{20,0},{20,1}};
const COORD Z1[4]={{18,1},{20,1},{20,0},{22,0}};
const COORD Z2[4]={{20,-1},{20,0},{22,0},{22,1}};
COORD temp[4];
int state=0;
int X;
int Y;
static int SCORE=0;
bool STOP=false;

void compute(){
	COORD temp={10,21};
	SetConsoleTextAttribute(hout,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hout,temp);
	cout<<SCORE<<"分";
	SetConsoleTextAttribute(hout,BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);	 
}
void clear(COORD p[]){
	SetConsoleTextAttribute(hout,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	for(int j=0;j<4;j++){
		if(p[j].Y<=0) continue;
		SetConsoleCursorPosition(hout,p[j]);
		cout<<"  ";
	}
	SetConsoleTextAttribute(hout,BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
}
void brush(COORD k){
	SetConsoleTextAttribute(hout,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hout,k);
	cout<<"  ";
	SetConsoleTextAttribute(hout,BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
}
void paint(COORD k){
	SetConsoleCursorPosition(hout,k);
	cout<<"  ";
}
void getValue(const COORD p[]){
	for(int j=0;j<4;j++){
		temp[j].X=p[j].X;
		temp[j].Y=p[j].Y;
	}
}
void choose(int flag){
	switch(flag){
		case 1:
		case 2:
		case 3:
		case 4:
			getValue(rect);state=1;break;//return
		case 5:
		case 8:
			getValue(z1);state=2;break;	//+5		
		case 6:
		case 7:
			getValue(z2);state=3;break;
		case 11:
		case 10:
			getValue(Z1);state=4;break;//+5
		case 9:
		case 12:
			getValue(Z2);state=5;break;
		case 16:
		case 14:
			getValue(lineW);state=6;break;//+9			
		case 15:
		case 13:
			getValue(lineN);state=7;break;								
		case 20:
			getValue(seven1);state=8;break;//+9
		case 17:
			getValue(seven2);state=9;break;
		case 18:
			getValue(seven3);state=10;break;
		case 19:
			getValue(seven4);state=11;break;
		case 24:
			getValue(Seven1);state=12;break;//+9
		case 21:
			getValue(Seven2);state=13;break;
		case 22:
			getValue(Seven3);state=14;break;
		case 23:
			getValue(Seven4);state=15;break;		 
		case 28:
			getValue(tUp);state=16;break;//+9
		case 25:
			getValue(tRight);state=17;break;
		case 26:
			getValue(tDown);state=18;break;
		case 27:
			getValue(tLeft);state=19;break;
		default:break;
	}
}
void random(){
	srand(time(NULL));
	int flag=rand()%28+1;
	choose(flag);
}
void printObj(COORD p[]){
	for(int j=0;j<4;j++){
		if(p[j].Y<=0) continue;
		SetConsoleCursorPosition(hout,p[j]);
		cout<<"  ";
	}
}
void dataInit(){
	for(int j=0;j<HEIGHT;j++){
		for(int k=0;k<WIDTH;k++){
			box[j][k].pos.X=k;
			box[j][k].pos.Y=j;
			box[j][k].have=false;
		}
	}
}
void screen(){
	putchar('+');
	for(int j=1;j<=WIDTH-2;j++){
		putchar('-');
	}
	putchar('+');
	for(int l=1;l<HEIGHT-1;l++){
		SetConsoleCursorPosition(hout,box[l][0].pos);
		cout<<"||";
		SetConsoleCursorPosition(hout,box[l][WIDTH-2].pos);
		cout<<"||";
		box[l][0].have=true;
		box[l][WIDTH-2].have=true;	
	}
	SetConsoleCursorPosition(hout,box[HEIGHT-1][0].pos); 
	putchar('+');
	for(int j=1;j<=WIDTH-2;j++){
		putchar('-');
		box[HEIGHT-1][j].have=true;
	}
	putchar('+');
	COORD t={0,21};
	SetConsoleCursorPosition(hout,t);
	cout<<"得  分 :";
}
void init(){
	SetConsoleTitle("俄罗斯方块 BY SKATER");
	CONSOLE_CURSOR_INFO in;
	in.bVisible=FALSE;
	in.dwSize=1;
	SetConsoleCursorInfo(hout,&in); 
	SetConsoleTextAttribute(hout,BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	COORD size={80,25};
	SetConsoleScreenBufferSize(hout,size); 
}
void reset(){
	COORD t={0,HEIGHT};
	SetConsoleTextAttribute(hout,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hout,t);
}
void move(){
	int y;
	bool f;
	for(int j=0;j<4;j++){
		y=temp[j].Y+1;
		if(y<0) continue;
		if(box[y][temp[j].X].have==true){
			for(int k=0;k<4;k++){
				TOP=TOP<temp[k].Y?TOP:temp[k].Y;
				if(TOP<=1){
					STOP=true; 
					IS_GAME_OVER=true;
					return;
				}
				box[temp[k].Y][temp[k].X].have=true;
			}
			STOP=true;
			return;
		}
	}
	clear(temp);
	for(int j=0;j<4;j++){
		temp[j].Y++;
	}
	Y++;
	printObj(temp);
}
void moveLR(int i){
	int x;
	for(int j=0;j<4;j++){
		x=temp[j].X+i;
		if(box[temp[j].Y][x].have==true){
			return;
		}
	}
	clear(temp);
	for(int j=0;j<4;j++){
		temp[j].X+=i;
	}
	X+=i;
	printObj(temp);
}
void change(){
	int sign;
	if(state==1)	return;
	else if(state>=2&&state<=5) sign=state+5;
	else if(state>=6&&state<=19) sign=state+9;
	clear(temp);
	choose(sign);	
	for(int j=0;j<4;j++){
		temp[j].X+=X;
		temp[j].Y+=Y;
	}
	for(int k=0;k<4;k++){
		if(temp[k].X==0){
			for(int i=0;i<4;i++){
				temp[i].X+=2;
			}
		}
		if(temp[k].X==38){
			for(int i=0;i<4;i++){
				temp[i].X-=2;
			}
		}
	}
	printObj(temp);
}
void clearPaint(int j,int k){
	for(int o=j;o<=k;o++){
		for(int p=2;p<=WIDTH-4;p+=2){
			if(box[o][p].have==true)
			brush(box[o][p].pos);
		}
	}
}
void newPaint(int j,int k){
	for(int o=j;o<=k;o++){
		for(int p=2;p<=WIDTH-4;p+=2){
			if(box[o][p].have==true)
			paint(box[o][p].pos);
		}
	}
}
void check(){
	bool f;
	int j=TOP;
	for(;j<=18;j++){
		f=true;
		for(int k=2;k<=WIDTH-4;k+=2){
			if(box[j][k].have==false){
				f=false; 
			}	
		}
		if(!f) continue;		
		SCORE++;
		clearPaint(TOP,j);
		for(int l=2;l<=WIDTH-4;l+=2){
			box[j][l].have=false;
		}
		for(int o=j-1;o>=TOP;o--){
			for(int p=2;p<=WIDTH-4;p+=2){
				if(box[o][p].have==true){
					box[o][p].have=false;
					box[o+1][p].have=true;
				}
			}
		}
		TOP++;
		newPaint(TOP,j);		
	}
}
void gameover(){
	COORD center={13,7};				
	SetConsoleCursorPosition(hout,center);
	SetConsoleTextAttribute(hout,FOREGROUND_RED|BACKGROUND_BLUE);
	cout<<"G A M E  O V E R"<<endl;		SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}
int main()
{	
	dataInit();
	screen();
	init();	
	int sign;
	char ch;
	compute();
	while(true){
		random();
		printObj(temp);
		while(!STOP){
			clock_t start=clock();
			while(clock()-start<=SPEED&&(sign=(!kbhit())));
			if(sign){
				move();
				if(!STOP)
				continue;
				else 
				break;
			}
			ch=getch();
			switch(ch){
				case 72://UP
					change();
					break;
				case 75://Left
					moveLR(-2);
					break;
				case 77://Right
					moveLR(2);
					break;
				case 80://Down 
					move();
					break;
				default:break;
			}
		}
		STOP=false;
		X=0;
		Y=0;
		check();
		compute();
		if(IS_GAME_OVER){
			gameover();
			break;
		}	
	}	
	reset();
	getchar();
	return 0;
}


#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
const int amount=100;
static int a=39;
static int b=0;
static int c=0;
static int LEN=1;
static int OLD=0;
static int BEFORE=0;
static int SCORE=0;
static int TIME=50;
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
const clock_t SPEED=0.02*CLOCKS_PER_SEC;
const clock_t S=0.001*CLOCKS_PER_SEC; 
const int HEIGHT=18;
const int WIDTH=80;
const COORD s={39,14};
bool IS_GAME_OVER=false; 
const COORD many[4]={{1,0},{0,-1},{1,-1},{2,-1}};
const COORD fight[7]={{38,17},{39,17},{40,17},{38,16},{39,16},{40,16},{39,15}};
typedef struct look{
	COORD same;
	char ch;
}LOOK;
class Fight{
private:
	LOOK pos[7];
	LOOK b[15];
	int length;
public:
	Fight(const COORD[]=fight,int =1,COORD =s);
	void move(int);
	int getPosX(int k){
		return pos[k].same.X;
	}
	int getPosY(int k){
		return pos[k].same.Y;
	}
	int getX(int k){
		return b[k].same.X;
	}
	int getY(int k){
		return b[k].same.Y;
	}
	void setCh(int k,char c){
		pos[k].ch=c;
	}
	void print();
	void display();
	void shoot(); 
};
Fight::Fight(const COORD j[],int n,COORD p):length(n){
	for(int k=0;k<7;k++){
		pos[k].same=fight[k];
	}
	pos[0].ch=pos[1].ch=pos[2].ch='^';
	pos[3].ch=pos[5].ch='-';
	pos[4].ch='+';
	pos[6].ch='|';
	b[0].same=p;
	b[0].ch='.';
}
void Fight::display(){
	for(int j=0;j<length;j++){
		SetConsoleCursorPosition(hout,b[j].same);
		putchar(b[j].ch); 
	}
}
void Fight::shoot(){
	for(int j=0;j<length;j++){
		SetConsoleCursorPosition(hout,b[j].same);
		putchar(' '); 
	}
	if(length<15){
		for(int j=0;j<length;j++){
			b[j].same.Y--;
		}
		length++;
		b[length-1].same.X=pos[6].same.X;
		b[length-1].same.Y=pos[6].same.Y-1;
		b[length-1].ch='.';
	}else if(length=15){
		for(int j=1;j<length;j++){
			b[j-1].same.X=b[j].same.X; 
		}
		b[14].same.X=pos[6].same.X;
		b[14].same.Y=pos[6].same.Y-1;
	}
	
}
void Fight::move(int j){
	for(int k=0;k<7;k++){
		SetConsoleCursorPosition(hout,pos[k].same);
		putchar(' ');
	}
	if((pos[0].same.X+j)>=0&&(pos[2].same.X+j)<=79){
		for(int l=0;l<7;l++){
			pos[l].same.X+=j;
		}		
	}
}
void Fight::print(){
	for(int j=0;j<7;j++){
		SetConsoleCursorPosition(hout,pos[j].same);
		putchar(pos[j].ch);
	}
}
class Enemy{
private:
	LOOK pos[4];
public:
	Enemy(const COORD[]=many);
	bool check(Fight);
	void move();
	void random();
	void print();
	int getY(int);
	void hit(Fight);
	friend class Fight;
};
Enemy::Enemy(const COORD p[]){
	for(int j=0;j<4;j++){
		pos[j].same=p[j];
	}
	pos[2].ch='+';
	pos[1].ch=pos[3].ch='_';
	pos[0].ch='|';
}
void Enemy::hit(Fight temp){
	int t=pos[1].same.Y;	
	for(int j=t;j<t+1;j++){
		for(int k=0;k<4;k++){
			if(k==2) continue;
			if(temp.getX(t)==pos[k].same.X&&temp.getY(t)==t){
				for(int l=0;l<4;l++){
					SetConsoleCursorPosition(hout,pos[l].same);
					putchar(' ');
					pos[l].same=many[l];
				}
				random();
				print(); 
				temp.setCh(k,' ');
				SCORE++;
				if(LEN<amount){
					LEN+=1;
				}				
				return;
			}
		}	
	}
}
int Enemy::getY(int k){
	return pos[k].same.Y;
}
void Enemy::random(){
	srand(time(NULL));
	int x;
	bool flag;
	do{
		flag=false;
		x=rand()%78;
		for(int j=-1;j<4;j++){
			if(x==a+j||x==b+j||x==c+j){
				flag=true;
				break;
			}		
		}
	}while(flag);
	a=b;
	b=c;
	c=x;	
	for(int j=0;j<4;j++){
		pos[j].same.X+=x;
	} 
}
void Enemy::print(){
	for(int j=0;j<4;j++){
		if(pos[j].same.Y<0||pos[j].same.Y>17)
		continue;		
		SetConsoleCursorPosition(hout,pos[j].same);
		putchar(pos[j].ch);
	}
}
void Enemy::move(){
	for(int j=0;j<4;j++){
		if((pos[j].same.Y)==19){
			for(int k=0;k<4;k++){
				pos[k].same=many[k];
			}
			IS_GAME_OVER=true;
			break;
		}
		if(pos[j].same.Y<18){
			SetConsoleCursorPosition(hout,pos[j].same);
			putchar(' ');
		}		
		pos[j].same.Y+=2;		
	}
}
bool Enemy::check(Fight temp){
	for(int j=0;j<4;j++){
		if(j==2) continue;
		for(int k=3;k<7;k++){
			if(k==4) continue;
			if(pos[j].same.X==temp.getPosX(k)&&pos[j].same.Y==temp.getPosY(k)){
				IS_GAME_OVER=true;
				return true;
			}		
		}
	}
	return false;	
}
Enemy sss[amount];
void init(){
	COORD t={0,18};
	SetConsoleTitle("雷霆战机  BY SKATER");
	SetConsoleTextAttribute(hout,FOREGROUND_RED|FOREGROUND_INTENSITY);
	CONSOLE_CURSOR_INFO in;
	in.bVisible=FALSE;
	in.dwSize=1;
	SetConsoleCursorInfo(hout,&in); 
	COORD size={80,25};
	SetConsoleScreenBufferSize(hout,size);
	SetConsoleCursorPosition(hout,t);
	for(int j=0;j<80;j++){
		putchar('-');
	}
	COORD e={0,19};
	SetConsoleCursorPosition(hout,e);
	cout<<"得  分 ："<<SCORE<<" 分"; 
} 
void Compute(){
	COORD e={9,19};
	if(TIME>50&&BEFORE!=SCORE){
		TIME-=1;
		BEFORE=SCORE;
	}	
	SetConsoleCursorPosition(hout,e);
	cout<<"      ";
	SetConsoleCursorPosition(hout,e);
	cout<<SCORE<<" 分";
}
void Control(){
	for(int j=0;j<LEN;j++){
		sss[j].move();
	}
	for(int j=0;j<LEN;j++){
		sss[j].print();
	}
}
void Check(Enemy e[],Fight f){
	for(int j=0;j<LEN;j++){
		for(int k=0;k<4;k++){
			if(e[j].getY(k)>=14){
				if(e[j].check(f))
				return;
				break;
			}
		} 	 
	}
}
void gameover(){
	COORD center={33,7};
	SetConsoleCursorPosition(hout,center);
	SetConsoleTextAttribute(hout,FOREGROUND_RED|BACKGROUND_BLUE);
	cout<<"G A M E  O V E R"<<endl;
	SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}
void Hit(Enemy s[],Fight f){
	for(int j=0;j<LEN;j++){
		s[j].hit(f);
	}
}
int main()
{
	init();
	int sign;
	char ch;
	int temp=0;
	Fight fff;
	fff.print();
	fff.display();
	while(true){
		clock_t start1=clock();
		while(clock()-start1<=S);
		if(OLD!=LEN){
			for(int j=OLD;j<LEN;j++){
				sss[j].random();
				sss[j].print();			 
			}
			OLD=LEN;
		}
		temp++;
		if(temp==TIME){
			Control();		
			temp=0;
		}					
		clock_t start2=clock();
		while(clock()-start2<=SPEED&&(sign=(!kbhit())));
		if(sign){
			fff.shoot();
			fff.display();
		}else{
			ch=_getch();
			switch(ch){
				case 75://Left				
					fff.move(-2);
					fff.print();
					break;
				case 77://Right
					fff.move(2);
					fff.print();
					break;
				default:break;
			}
		}	
		fff.shoot();
		fff.display();		
		Hit(sss,fff);
		Check(sss,fff);
		Compute();
		if(IS_GAME_OVER){
			gameover();
			break;
		}
	}
	COORD t={0,20};
	SetConsoleCursorPosition(hout,t);
	getchar(); 
	return 0;
}


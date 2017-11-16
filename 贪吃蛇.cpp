#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#define HEIGHT 15
#define WIDTH 40
using namespace std;
HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
class Snake{
private:
	COORD snake[(HEIGHT-1)*(WIDTH-1)];
	int length;
	bool live;
	COORD f;
public:
	Snake();	
	void move(char);
	void update();	
	void change();
	void food();
	void eat();
	bool getLive();
	bool test();
	bool wall();
};
Snake::Snake():length(3){
	food();
	live=true;
	snake[0].X=WIDTH/2;
	snake[0].Y=HEIGHT/2;
	snake[1].X=WIDTH/2-1;
	snake[1].Y=HEIGHT/2;
	snake[2].X=WIDTH/2-2;
	snake[2].Y=HEIGHT/2;
}
void Snake::update(){	
	for(int j=length-1;j>=1;j--){
		SetConsoleCursorPosition(hout,snake[j]);
		putchar('*');
	}
	SetConsoleCursorPosition(hout,snake[0]);
	putchar('#');
}
void Snake::change(){
	for(int j=0;j<length;j++){
		SetConsoleCursorPosition(hout,snake[j]);
		putchar(' ');
	}
	for(int j=length-1;j>=1;j--){
		snake[j].X=snake[j-1].X;
		snake[j].Y=snake[j-1].Y;
	}
}
void Snake::move(char ch){
	eat();	
	change();
	switch(ch){
		case 72:
		 		snake[0].Y--;//上 
			 	break;
		case 75:
				snake[0].X--;//左 
 				break;
		case 80:
				snake[0].Y++;//下 
				break;
		case 77:
				snake[0].X++;//右 
				break;
		default:break;
	}
	if(test()||wall()){
		COORD center={WIDTH/2-6,HEIGHT/2};
		SetConsoleCursorPosition(hout,f);
		putchar(' ');
		SetConsoleCursorPosition(hout,center);
		SetConsoleTextAttribute(hout,FOREGROUND_RED|BACKGROUND_BLUE);
		cout<<"G A M E  O V E R"<<endl;
		SetConsoleTextAttribute(hout,FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		live=false;
		return;
	}
	update();	
}
void Snake::eat(){
	if(snake[0].X==f.X&&snake[0].Y==f.Y){	
		length++;
		SetConsoleCursorPosition(hout,f);
		putchar(' ');
		food();
	}		
}
bool Snake::getLive(){
	return live;
}
bool Snake::test(){
	for(int j=1;j<length;j++){
		if(snake[j].X==snake[0].X&&snake[j].Y==snake[0].Y)
		return true;
	}
	return false;
}
bool Snake::wall(){
	if(snake[0].X==0||snake[0].Y==HEIGHT+1||snake[0].X==WIDTH+1||snake[0].Y==0)
	return true;
	else
	return false;
}
void map(){
	COORD temp={0,0};
	for(int j=1;j<=WIDTH;j++){
		temp.X=j;
		SetConsoleCursorPosition(hout,temp);
		putchar('-');
		temp.Y=HEIGHT+1; 
		SetConsoleCursorPosition(hout,temp);
		putchar('-');
		temp.Y=0;
	}
	temp.X=0;
	for(int j=1;j<=HEIGHT;j++){
		temp.Y=j;
		SetConsoleCursorPosition(hout,temp);
		putchar('|');
		temp.X=WIDTH+1; 
		SetConsoleCursorPosition(hout,temp);
		putchar('|');
		temp.X=0;
	}
}
void Snake::food(){
	srand(time(NULL));
	bool flag;
	do{
		flag=false;
		f.X=rand()%WIDTH+1;
		f.Y=rand()%HEIGHT+1;
		for(int j=0;j<=length;j++){
			if(f.X==snake[j].X&&f.Y==snake[j].Y){
				flag=true;
				break;
			}		
		}
	}while(flag);
	SetConsoleCursorPosition(hout,f); 
	putchar('*');
}
int main()
{
	SetConsoleTitle("贪 吃 蛇 游 戏 ||作者：(:陈 彩 金:)");
	COORD size={80,25};
	SetConsoleScreenBufferSize(hout,size);
	char ch;
	CONSOLE_CURSOR_INFO in;
	in.bVisible=FALSE;
	in.dwSize=1;
	SetConsoleCursorInfo(hout,&in);		
	map();
	Snake sss;
	sss.update();
	int flag;
	static char temp=77;
	while(true){
		flag=1;
		clock_t start=clock();
		while((clock()-start<=0.3*CLOCKS_PER_SEC)&&(flag=!kbhit()));				
		if(flag!=0){
			sss.move(temp);
			if(!sss.getLive())
			break;	
			continue;
		}
		ch=getch();		
		switch(ch){
			case 72://上 
				if(temp==80);	
				else {
					sss.move(72);
					temp=ch;
				}					
				break;
			case 75://左 
				if(temp==77);					
				else {
					sss.move(75);
					temp=ch;
				} 					
				break;
			case 80://下  
				if(temp==72);					
				else {
					sss.move(80);
					temp=ch;
				}					
				break;
			case 77://右 
				if(temp==75);					
				else {
					sss.move(77);
					temp=ch;
				}					
				break;
			default:break;
		}
		if(!sss.getLive())
		break;			
	}
	COORD last={0,HEIGHT+1};
	SetConsoleCursorPosition(hout,last);
	CloseHandle(hout);
	return 0;
}


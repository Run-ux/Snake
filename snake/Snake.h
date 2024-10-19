#include<iostream>
#include<graphics.h>
#include<list>
#include<vector>
#include<time.h>
#include"Item.h"
#include<cmath>
using namespace std;

const int LEN=37.5;

void drawTail(int x,int y) //画尾巴 
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/snakeTail.png");
	PIMAGE tail=newimage(37.5,37.5);
	putimage(tail,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(x,y,tail);
	delimage(tail);
}

void drawHead(int x,int y,char dir) //画头 
{
	if(dir=='n')
	{
		PIMAGE temp=newimage();
		getimage(temp,"resource/snakeHeadUp.png");
		PIMAGE head=newimage(37.5,37.5);
		putimage(head,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
		delimage(temp);
		putimage(x,y,head);
		delimage(head);
	}
	if(dir=='s')
	{
		PIMAGE temp=newimage();
		getimage(temp,"resource/snakeHeadDown.png");
		PIMAGE head=newimage(37.5,37.5);
		putimage(head,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
		delimage(temp);
		putimage(x,y,head);
		delimage(head);
	}
	if(dir=='w')
	{
		PIMAGE temp=newimage();
		getimage(temp,"resource/snakeHeadLeft.png");
		PIMAGE head=newimage(37.5,37.5);
		putimage(head,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
		delimage(temp);
		putimage(x,y,head);
		delimage(head);
	}
	if(dir=='e')
	{
		PIMAGE temp=newimage();
		getimage(temp,"resource/snakeHeadRight.png");
		PIMAGE head=newimage(37.5,37.5);
		putimage(head,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
		delimage(temp);
		putimage(x,y,head);
		delimage(head);
	}
}

struct imgPos
{
	//x,y表示位置坐标 
	double x;
	double y;
	imgPos(double n1,double n2):x(n1),y(n2){}
};

class snake
{
	private:
		int speed; //蛇的速度，即图像刷新的时间
		char direction; //n表示北，s表示南，w表示西，e表示东
		list<imgPos> pos; //记录蛇头和蛇身的位置 
		
	public:
		snake(wall walls[],int num):speed(120),direction('s')
		{
			srand(time(0));
			int a=1,b=17;	 
			int n1=(rand() % (b-a+1))+ a;
			int n2=(rand() % (b-a+1))+ a;
			double x=n1*LEN,y=n2*LEN;
			while(this->snakeCheck(x,y,walls,num)) //蛇头不能与障碍物重叠 
			{
				n1+=LEN;
				n2-=LEN;
				x=n1*LEN;
				y=n2*LEN;
			}
			pos.push_back(imgPos(x,y));
		}
		
		int getSpeed(){return speed;} //获取速度 
		
		char getDirection(){return direction;} //获取方向 
		
		list<imgPos> getPos(){return pos;}; //获取位置
		 
		void changeSpeed(int x){speed=x;}; //改变速度 
		
		void changeDirection(char ch){direction=ch;} //改变方向 
		
		int snakeCheck(double x,double y,wall walls[],int num) //检查蛇头是否与障碍物重叠 
		{
			for(int i=0;i<num;i++)
			{
				if(abs(x-walls[i].x)<10 && abs(y-walls[i].y)<10)
					return 1;
			}
			return 0;
		}
		
		void grow()  //吃到食物后可以加长 
		{
			char dir=getDirection();
			imgPos tail=pos.back();
			if(dir=='n')
			{
				imgPos temp(tail.x,tail.y+LEN);
				pos.push_back(temp);
			}
			if(dir=='s')
			{
				imgPos temp(tail.x,tail.y-LEN);
				pos.push_back(temp);
			}
			if(dir=='w')
			{
				imgPos temp(tail.x+LEN,tail.y);
				pos.push_back(temp);
			}
			if(dir=='e')
			{
				imgPos temp(tail.x-LEN,tail.y);
				pos.push_back(temp);
			}
		}
		
		void move(key_msg keyMsg) //移动 
		{
			int key=keyMsg.key;
			imgPos head=pos.front();
				
			//当是北朝向 
			if(direction=='n')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //按下A键 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='w';
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //按下D键 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='e';
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //按下w键 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //按下s键
				{
					if(pos.size()==1)
					{
						this->direction='s';
					}
				} 
			}				
			//当是南朝向 
			else if(direction=='s')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //按下A键 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='w';
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //按下D键 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='e';
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //按下w键 
				{
					if(pos.size()==1)
					{
						this->direction='n';
					}	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //按下s键
				{
					imgPos temp(head.x,head.y+LEN);
					pos.push_front(temp);
					pos.pop_back();
				} 
			}
			//当是西朝向 
			else if(direction=='w')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //按下A键 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //按下D键 
				{
					if(pos.size()==1)
					{
						this->direction='e';
					}
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //按下w键 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='n';	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //按下s键
				{
					imgPos temp(head.x,head.y+LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='s';
				} 
			}
			//当是东朝向
			else if(direction=='e')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //按下A键 
				{						
					if(pos.size()==1)
					{
						this->direction='w';
					}
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //按下D键 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //按下w键 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='n';	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //按下s键
				{
					imgPos temp(head.x,head.y+LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='s';
				} 
			}	
		} 
		
		void move()
		{
			imgPos head=pos.front();
			if(direction=='n')
			{
				imgPos temp(head.x,head.y-LEN);
				pos.push_front(temp);
				pos.pop_back();
			}
			if(direction=='s')
			{
				imgPos temp(head.x,head.y+LEN);
				pos.push_front(temp);
				pos.pop_back();
			}
			if(direction=='w')
			{
				imgPos temp(head.x-LEN,head.y);
				pos.push_front(temp);
				pos.pop_back();
			}
			if(direction=='e')
			{
				imgPos temp(head.x+LEN,head.y);
				pos.push_front(temp);
				pos.pop_back();
			}
		}
		
		void show() //把蛇显示出来 
		{
			for(auto it=pos.begin();it!=pos.end();it++)
			{
				if(it==pos.begin())
					drawHead(it->x,it->y,this->direction);
				else
					drawTail(it->x,it->y);
			}
		} 
		
		int checkRange() //检查蛇是否越界,越界返回1，否则返回0 
		{
			imgPos head=pos.front();
			if(head.x>=0 && head.x<=825 && head.y>=0 && head.y<=825)
				return 0;
			else
				return 1;
		} 
		
		int checkWall(wall walls[],int num) //检查蛇头是否撞墙，撞墙返回1，否则返回0 
		{
			imgPos head=pos.front();
			int flag=0;
			for(int i=0;i<num;i++)
			{
				if(abs(head.x-walls[i].x)<1 && abs(head.y-walls[i].y)<1)
				{
					flag=1;
					break;
				}
			}
			return flag;				
		}
		
		int checkCircle() //检查蛇头是否碰到蛇身，碰到返回1，否则返回0 
		{
			imgPos head=pos.front();
			for(auto it=pos.begin();it!=pos.end();it++)
			{
				if(it!=pos.begin())
				{
					if(abs(head.x-it->x)<1 && abs(head.y-it->y)<1)
						return 1;
				}
			}
			return 0; 
		}
		
		void sReplay() //重置蛇的状态 
		{
			direction='s';
			speed=120;
			while(pos.size())
				pos.pop_back();
			srand(time(0));
			int a=1,b=20;	 
			int n1=(rand() % (b-a+1))+ a;
			int n2=(rand() % (b-a+1))+ a;
			pos.push_back(imgPos(n1*LEN,n2*LEN));
		}
};

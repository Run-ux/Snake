#include<iostream>
#include<graphics.h>
#include<list>
#include<time.h>
#include<cmath>
#include<vector>
using namespace std;

class wall
{
	public:
		double x,y;
		wall():x(0),y(0){}
		wall(vector<wall> &walls)
		{
			int n1=1+random(20);
			int n2=1+random(20);
			x=n1*37.5;
			y=n2*37.5;
			if(walls.size()==0)
			{
				wall temp(x,y);
				walls.push_back(temp);
			}
			else //保证新生成的障碍物不与先前的重复 
			{
				while(this->wallCheck(x,y,walls))
				{
					n1+=37.5;
					n2-=37.5;
					x=n1*37.5;
					y=n2*37.5; 
				}
				walls.push_back(wall(x,y));				
			}
		}
		wall(double n1,double n2):x(n1),y(n2){}
		void drawWall()
		{
			PIMAGE temp=newimage();
			getimage(temp,"resource/wall.png");
			PIMAGE wall=newimage(37.5,37.5);
			putimage(wall,0,0,37.5,37.5,temp,0,0,getwidth(temp),getheight(temp));	
			delimage(temp);
			putimage(x,y,wall);
			delimage(wall);
		}
		
		int wallCheck(double x,double y,vector<wall> walls) //检查墙是否与先前已生成的墙重叠 
		{
			for(auto wll:walls)
			{
				if(abs(x-wll.x)<10 && abs(y-wll.y)<10)
					return 1;
			}
			return 0;
		}
};

class food
{
	public:
		double x,y;
		food(wall walls[],int num)
		{ 
			int n1=1+random(17);
			int n2=1+random(17);
			x=n1*37.5;
			y=n2*37.5;
			while(this->foodCheck(x,y,walls,num)) //保证生成的食物不与障碍物重叠 
			{
				n1+=37.5;
				n2-=37.5;
				x=n1*37.5;
				y=n2*37.5; 
			}
		}
		void drawFood()
		{
			PIMAGE temp=newimage();
			getimage(temp,"resource/china.png");
			PIMAGE food=newimage(37.5,37.5);
			putimage(food,0,0,37.5,37.5,temp,0,0,getwidth(temp),getheight(temp));	
			delimage(temp);
			putimage(x,y,food);
			delimage(food);			
		}
		int foodCheck(double x,double y,wall walls[],int num) //检查食物的位置是否与障碍物重叠,返回1表示重叠 
		{
			for(int i=0;i<num;i++)
			{
				if(abs(x-walls[i].x)<10 && abs(y-walls[i].y)<10)
					return 1;
			}
			return 0;
		}
};

class randSpeed
{
	public:
		double x,y;
		int id; //id=0表示是减速剂，速度减为200, id=1恢复表示正常速度120，id=2表示加速剂，速度变为80
		randSpeed(wall walls[],int num)
		{
			int n1=1+random(17);
			int n2=1+random(17);
			int n3=random(3);
			x=n1*37.5;
			y=n2*37.5;
			id=n3;
			while(this->speedCheck(x,y,walls,num)) //保证速度剂不与障碍物重叠 
			{
				n1+=37.5;
				n2-=37.5;
				x=n1*37.5;
				y=n2*37.5; 
			}
		} 
		void drawRandSpeed()
		{
			PIMAGE temp=newimage();
			getimage(temp,"resource/randSpeed.png");
			PIMAGE randSpeed=newimage(37.5,37.5);
			putimage(randSpeed,0,0,37.5,37.5,temp,0,0,getwidth(temp),getheight(temp));	
			delimage(temp);
			putimage(x,y,randSpeed);
			delimage(randSpeed);
		}
		int speedCheck(double x,double y,wall walls[],int num) //检查速度剂的位置是否与障碍物重叠,返回1表示重叠 
		{
			for(int i=0;i<num;i++)
			{
				if(abs(x-walls[i].x)<10 && abs(y-walls[i].y)<10)
					return 1;
			}
			return 0;
		}
};

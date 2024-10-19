#include<iostream>
#include<graphics.h>
#include<list>
#include<cmath>
using namespace std;

class startBtn
{
	private:
		int left,top,right,bottom;
	public:
		int click; //click=0说明此时应该显示“开始”，click=1说明此时应该显示“暂停”
		startBtn():left(865),top(200),right(985),bottom(310),click(0){}
		void drawBtn()
		{
			if(!click)
			{
				PIMAGE temp=newimage();
				getimage(temp,"resource/start.png");
				PIMAGE start=newimage(right-left,bottom-top);
				putimage(start,0,0,right-left,bottom-top,temp,0,0,getwidth(temp),getheight(temp));	
				delimage(temp);
				putimage(left,top,start);
				delimage(start);
			} 
			else
			{
				PIMAGE temp=newimage();
				getimage(temp,"resource/stop.png");
				PIMAGE stop=newimage(right-left,bottom-top);
				putimage(stop,0,0,right-left,bottom-top,temp,0,0,getwidth(temp),getheight(temp));	
				delimage(temp);
				putimage(left,top,stop);
				delimage(stop);
			}
	    }
		int isClicked(double x,double y)
		{
			if(x>=left && x<=right && y>=top && y<=bottom)
			{
				this->click=1-this->click;
				return 1;
			}
			else
				return 0;
		}
		int getClick(){return click;}
};

class replayBtn
{
	private:
		double left,top,right,bottom;
	public:
		replayBtn():left(350),top(450),right(650),bottom(560){}
		void drawBtn1()
		{
			PIMAGE temp=newimage();
			getimage(temp,"resource/replayBtn.png");
			PIMAGE replay=newimage(right-left,bottom-top);
			putimage(replay,0,0,right-left,bottom-top,temp,0,0,getwidth(temp),getheight(temp));	
			delimage(temp);
			putimage(left,top,replay);
			delimage(replay);
		}
		
		int isClicked1(double x,double y)
		{
			if(x>=left && x<=right && y>=top && y<=bottom)
				return 1;
			else
				return 0;
		}
};

class exitBtn
{
	private:
		double left,top,right,bottom;
	public:
		exitBtn():left(350),top(580),right(650),bottom(690){}
		void drawBtn2()
		{
			PIMAGE temp=newimage();
			getimage(temp,"resource/exitBtn.png");
			PIMAGE exit=newimage(right-left,bottom-top);
			putimage(exit,0,0,right-left,bottom-top,temp,0,0,getwidth(temp),getheight(temp));	
			delimage(temp);
			putimage(left,top,exit);
			delimage(exit);
		}
		
		int isClicked2(double x,double y)
		{
			if(x>=left && x<=right && y>=top && y<=bottom)
				return 1;
			else
				return 0;
		}
};

class checkBtn
{
	public:
		double x,y;
		double r;
		int flag;  //0表示没被点击，画圆弧，1表示被点击，画圆 
		checkBtn(double n1,double n2, double n3):x(n1),y(n2),r(n3),flag(0){}
		void drawBtn3()
		{
			setcolor(EGERGB(0,0,0)); //线条颜色为黑
			if(!flag) //没被点击
				setfillcolor(EGERGB(255,255,255)); //填充颜色为白 
			else
				setfillcolor(EGERGB(0,255,0)); //填充颜色为绿
			fillellipse(x, y, r, r); 
		}
		int isClicked3(double x,double y)
		{
			double a=pow(x-this->x,2);
			double b=pow(y-this->y,2);
			if(a+b<=pow(r,2))
				return 1;
			else
				return 0;
		}
};


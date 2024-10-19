#include<iostream>
#include<cstdlib>
#include<graphics.h>
#include<list>
#include<vector>
#include<windows.h> 
#include"Snake.h"
#include"Btn.h" 
using namespace std;

//开场画面 
void openingScene()
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/gameBk.png");
	PIMAGE opening=newimage(1025,825);
	putimage(opening,0,0,1025,825,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(0,0,opening);
	delimage(opening);
	setcolor(BLACK);			//文字的颜色
	setbkmode(TRANSPARENT);		//设置文字背景色为透明	
	int height = 20;			//文字高度
	setfont(height, 0, "楷体");	//设置文字宽度和字体
	outtextxy(360,750,"按任意键进入游戏（除了关机键）");
}

int chooseMap() //返回1选择草地地图，返回2选择篮球场地图 
{
	cleardevice();
	setbkcolor(EGERGB(255,255,255));
	setcolor(EGERGB(30, 144 ,255));
	setbkmode(TRANSPARENT);
	setfont(100, 50, "楷体");	//设置文字宽度和字体
	outtextxy(180,100,"请选择你的地图");
	
	//草地 
	PIMAGE temp1=newimage();
	getimage(temp1,"resource/map.png");
	PIMAGE map1=newimage(250,250);
	putimage(map1,0,0,250,250,temp1,0,0,getwidth(temp1),getheight(temp1));	
	delimage(temp1);
	putimage(200,300,map1);
	delimage(map1);
	setcolor(EGERGB(171, 213, 67));
	setfont(50, 0, "楷体");	//设置文字宽度和字体
	outtextxy(270,580,"草地");
	
	//篮球场
	PIMAGE temp2=newimage();
	getimage(temp2,"resource/map2.png");
	PIMAGE map2=newimage(250,250);
	putimage(map2,0,0,250,250,temp2,0,0,getwidth(temp2),getheight(temp2));	
	delimage(temp2);
	putimage(600,300,map2);
	delimage(map2);
	setcolor(EGERGB(41, 129, 120));
	setfont(50, 0, "楷体");	//设置文字宽度和字体
	outtextxy(650,580,"篮球场");
	
	checkBtn ckBtn1(325,675,25);
	checkBtn ckBtn2(725,675,25);
	ckBtn1.flag=0;
	ckBtn2.flag=0;
	ckBtn1.drawBtn3();
	ckBtn2.drawBtn3();
	//鼠标事件
	while(1)
	{
		while(mousemsg()) //鼠标点击 
		{
			mouse_msg mouseMsg=getmouse();
			if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置） 
			{
				if(mouseMsg.is_down())
				{
					if(ckBtn1.isClicked3(mouseMsg.x,mouseMsg.y))
					{
						ckBtn1.flag=1;
						ckBtn1.drawBtn3();
						Sleep(300);
						return 1;
					}
					if(ckBtn2.isClicked3(mouseMsg.x,mouseMsg.y))
					{
						ckBtn2.flag=1;
						ckBtn2.drawBtn3();
						Sleep(300);
						return 2;
					}
				}
			}
		}
		Sleep(60);
	}
	return 1;
}

void initMap1() //加载草地地图 
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/map.png");
	PIMAGE map=newimage(825,825);
	putimage(map,0,0,825,825,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(0,0,map);
	delimage(map);
}

void initMap2() //加载篮球场地图 
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/map2.png");
	PIMAGE map=newimage(825,825);
	putimage(map,0,0,825,825,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(0,0,map);
	delimage(map);
}

int main()
{
	initgraph(1025,825,0);
	setcaption("贪吃蛇游戏");
	//开场动画 
	openingScene();	
	getch(); //在键盘上按下一个键后才继续执行 
	//选择地图
	REPLAY:int choice=chooseMap();
	//初始化障碍物 
	int num=14;
	wall walls[14];
	double xArray[14]={LEN,3*LEN,5*LEN,7*LEN,9*LEN,11*LEN,13*LEN,2*LEN,15*LEN,17*LEN,19*LEN,11*LEN,11*LEN,12*LEN};
	double yArray[14]={4*LEN,6*LEN,8*LEN,10*LEN,12*LEN,14*LEN,2*LEN,16*LEN,18*LEN,20*LEN,10*LEN,12*LEN,10*LEN};
	for(int i=0;i<num;i++)
	{
			walls[i].x=xArray[i];
			walls[i].y=yArray[i];
	}
	
	setbkcolor(EGERGB(255,255,255),NULL);
	cleardevice();
	
	//初始化开始/暂停按钮
	startBtn btn;
	
	//初始化蛇
	snake s1(walls,num);
	
	//初始化食物
	food f(walls,num); 
	int foodCnt=1; //记录食物的数量 
	
	//初始化randSpeed
	randSpeed speedPotion(walls,num);
	int speedCnt=1; //记录速度剂的数量
	
	int score=0; //记录得分
	 
	int isPaused=1; 
	while(1)
	{	
		if(!isPaused) //如果没有暂停 
		{
			if(s1.checkRange() || s1.checkWall(walls,num) || s1.checkCircle()) //判断蛇是否出界/撞墙/撞到蛇身 
			{
				flushkey();
				flushmouse();
				if(s1.checkWall(walls,num))
				{
					setbkcolor(EGERGB(255,255,255));
					cleardevice();
					setcolor(EGERGB(255,0,0));
					setfont(50,0,"宋体"); 
					outtextxy(220,300,"游戏结束，蛇撞到了障碍物");
					xyprintf(220,360,"你的得分是：%d",score);
					replayBtn btn1;  //初始化重新开始按钮 
					exitBtn btn2;    //初始化退出按钮 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //鼠标点击 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置，抬起为执行时刻） 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y)) //如果点了重新开始按钮 
									{
										btn.click=0; //重置暂停按钮的状态 
										isPaused=1; //将游戏暂停 
										s1.sReplay(); //重置蛇的状态 
										foodCnt=1; //重置食物的数量 
										speedCnt=1; //重置速度剂的数量 
										score=0; //重置得分 
										goto REPLAY;
									}
									if(btn2.isClicked2(mouseMsg.x,mouseMsg.y)) //如果点了退出按钮 
										goto EXIT;
								}
							}
						}
						Sleep(60);
					}
				}
				if(s1.checkRange())
				{
					setbkcolor(EGERGB(255,255,255));
					cleardevice();
					setcolor(EGERGB(255,0,0));
					setfont(50,0,"宋体"); 
					outtextxy(220,300,"游戏结束，蛇跑出了地图");
					xyprintf(220,360,"你的得分是：%d",score);
					replayBtn btn1;  //初始化重新开始按钮 
					exitBtn btn2;    //初始化退出按钮 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //鼠标点击 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置，抬起为执行时刻） 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y))
									{
										btn.click=0; //重置暂停按钮的状态 
										isPaused=1; //将游戏暂停 
										s1.sReplay(); //重置蛇的状态 
										foodCnt=1; //重置食物的数量 
										speedCnt=1; //重置速度剂的数量 
										score=0; //重置得分 
										goto REPLAY;
									}
									if(btn2.isClicked2(mouseMsg.x,mouseMsg.y))
										goto EXIT;
								}
							}
						}
						Sleep(60);
					}				
				}
				if(s1.checkCircle())
				{
					setbkcolor(EGERGB(255,255,255));
					cleardevice();
					setcolor(EGERGB(255,0,0));
					setfont(50,0,"宋体"); 
					outtextxy(220,300,"游戏结束，蛇头撞到了蛇身");
					xyprintf(220,360,"你的得分是：%d",score);
					replayBtn btn1;  //初始化重新开始按钮 
					exitBtn btn2;    //初始化退出按钮 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //鼠标点击 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置，抬起为执行时刻） 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y))
									{
										btn.click=0; //重置暂停按钮的状态 
										isPaused=1; //将游戏暂停 
										s1.sReplay(); //重置蛇的状态 
										foodCnt=1; //重置食物的数量 
										speedCnt=1; //重置速度剂的数量 
										score=0; //重置得分 
										goto REPLAY;
									}
									if(btn2.isClicked2(mouseMsg.x,mouseMsg.y))
										goto EXIT;
								}
							}
						}
						Sleep(60);
					}				
				}
			}
			else  //如果蛇没有出界/撞墙/撞到蛇身
			{
				setbkcolor(EGERGB(255,255,255));
				cleardevice();
				setcolor(EGERGB(0,0,255));
				setfont(25,0,"宋体");
				xyprintf(850,400,"得分：%d",score);
				if(s1.getSpeed()==120)
					outtextxy(850,500,"当前速度：正常");
				else if(s1.getSpeed()==200)
					outtextxy(850,500,"当前速度：减速");
				else
					outtextxy(850,500,"当前速度：加速");
				//画地图
				if(choice==1)
					initMap1(); 
				else
					initMap2(); 
				for(int i=0;i<num;i++) //画障碍物
					walls[i].drawWall(); 
				if(foodCnt==0) //如果没有食物就随机刷新食物位置 
				{
					food temp(walls,num);
					f=temp;
					f.drawFood();
					foodCnt=1;
				}
				else //如果还有食物就不用重新刷新位置 
				{
					f.drawFood();
				}
				if(speedCnt==0) //如果没有速度剂就随机刷新速度剂位置
				{
					randSpeed temp(walls,num);
					speedPotion=temp;
					speedPotion.drawRandSpeed();
					speedCnt=1;
				}
				else //如果还有速度剂就不用重新刷新位置 
				{
					speedPotion.drawRandSpeed();
				}
				btn.drawBtn();
				s1.show();
			}
			while(mousemsg()) //鼠标点击 
			{
				mouse_msg mouseMsg=getmouse();
				if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置） 
				{
					if(mouseMsg.is_down())
					{
						if(btn.isClicked(mouseMsg.x,mouseMsg.y))
						{
							btn.drawBtn(); // 更新按钮外观
        					isPaused = !isPaused; // 切换暂停状态
						}
					}	
				}		
			}
			if(kbmsg()) //键盘输入 
			{
				key_msg kbMsg=getkey();
				if(kbMsg.msg==key_msg_down) //按下wsad键才反应 
				{
					if(kbMsg.key==0x57 || kbMsg.key==0x41 || kbMsg.key==0x44 || kbMsg.key==0x53) 
					{
						s1.move(kbMsg);
						//蛇头碰到食物就变长 
						if(foodCnt==1)
						{
							imgPos head=s1.getPos().front();
							if(abs(head.x-f.x)<20 && abs(head.y-f.y)<20)
							{
								s1.grow();
								score++;
								foodCnt=0;								
							}
						}
						//蛇头碰到加速剂就改变速度
						if(speedCnt==1)
						{
							imgPos head=s1.getPos().front();
							if(abs(head.x-speedPotion.x)<20 && abs(head.y-speedPotion.y)<20)
							{
								if(speedPotion.id==0)
									s1.changeSpeed(200);
								else if(speedPotion.id==1)
									s1.changeSpeed(120);
								else
									s1.changeSpeed(80);
								speedCnt=0;							
							}
						}
					}
				}
			}
			else //如果没有按下wsad键，则按照原来的方向移动 
			{
				s1.move();
				//蛇头碰到食物就变长
				if(foodCnt==1)
				{
					imgPos head=s1.getPos().front();
					if(abs(head.x-f.x)<20 && abs(head.y-f.y)<20)
					{
						s1.grow();
						score++;
						foodCnt=0; 
					}
				}
				//蛇头碰到速度剂 
				if(speedCnt==1)
				{
					imgPos head=s1.getPos().front();
					if(abs(head.x-speedPotion.x)<20 && abs(head.y-speedPotion.y)<20)
					{
						if(speedPotion.id==0)
							s1.changeSpeed(200);
						else if(speedPotion.id==1)
							s1.changeSpeed(120);
						else
							s1.changeSpeed(80);
						speedCnt=0;									
					}
				}	
			}
		}
		else //如果暂停了 
		{
			setbkcolor(EGERGB(255,255,255));
			cleardevice();
			setcolor(EGERGB(0,0,255));
			setfont(25,0,"宋体");
			xyprintf(850,400,"得分：%d",score);
			if(s1.getSpeed()==120)
				outtextxy(850,500,"当前速度：正常");
			else if(s1.getSpeed()==200)
				outtextxy(850,500,"当前速度：减速");
			else
				outtextxy(850,500,"当前速度：加速");
			//画地图
			if(choice==1)
				initMap1(); 
			else
				initMap2();
			for(int i=0;i<num;i++) //画障碍物
				walls[i].drawWall(); 
			f.drawFood(); //画食物 
			speedPotion.drawRandSpeed(); //画速度剂 
			btn.drawBtn();
			s1.show();
			while(mousemsg()) //鼠标点击 
			{
				mouse_msg mouseMsg=getmouse();
				if(mouseMsg.is_left()) //判断鼠标左键点击（左键按下确定位置） 
				{
					if(mouseMsg.is_down())
					{
						if(btn.isClicked(mouseMsg.x,mouseMsg.y))
						{
							btn.drawBtn(); // 更新按钮外观
        					isPaused = 1-isPaused; // 切换暂停状态
						}
					}
				}
			}
			flushkey();
		}
		Sleep(s1.getSpeed());	
	}

	EXIT:closegraph();
	return 0;
}

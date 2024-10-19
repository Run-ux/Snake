#include<iostream>
#include<cstdlib>
#include<graphics.h>
#include<list>
#include<vector>
#include<windows.h> 
#include"Snake.h"
#include"Btn.h" 
using namespace std;

//�������� 
void openingScene()
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/gameBk.png");
	PIMAGE opening=newimage(1025,825);
	putimage(opening,0,0,1025,825,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(0,0,opening);
	delimage(opening);
	setcolor(BLACK);			//���ֵ���ɫ
	setbkmode(TRANSPARENT);		//�������ֱ���ɫΪ͸��	
	int height = 20;			//���ָ߶�
	setfont(height, 0, "����");	//�������ֿ�Ⱥ�����
	outtextxy(360,750,"�������������Ϸ�����˹ػ�����");
}

int chooseMap() //����1ѡ��ݵص�ͼ������2ѡ�����򳡵�ͼ 
{
	cleardevice();
	setbkcolor(EGERGB(255,255,255));
	setcolor(EGERGB(30, 144 ,255));
	setbkmode(TRANSPARENT);
	setfont(100, 50, "����");	//�������ֿ�Ⱥ�����
	outtextxy(180,100,"��ѡ����ĵ�ͼ");
	
	//�ݵ� 
	PIMAGE temp1=newimage();
	getimage(temp1,"resource/map.png");
	PIMAGE map1=newimage(250,250);
	putimage(map1,0,0,250,250,temp1,0,0,getwidth(temp1),getheight(temp1));	
	delimage(temp1);
	putimage(200,300,map1);
	delimage(map1);
	setcolor(EGERGB(171, 213, 67));
	setfont(50, 0, "����");	//�������ֿ�Ⱥ�����
	outtextxy(270,580,"�ݵ�");
	
	//����
	PIMAGE temp2=newimage();
	getimage(temp2,"resource/map2.png");
	PIMAGE map2=newimage(250,250);
	putimage(map2,0,0,250,250,temp2,0,0,getwidth(temp2),getheight(temp2));	
	delimage(temp2);
	putimage(600,300,map2);
	delimage(map2);
	setcolor(EGERGB(41, 129, 120));
	setfont(50, 0, "����");	//�������ֿ�Ⱥ�����
	outtextxy(650,580,"����");
	
	checkBtn ckBtn1(325,675,25);
	checkBtn ckBtn2(725,675,25);
	ckBtn1.flag=0;
	ckBtn2.flag=0;
	ckBtn1.drawBtn3();
	ckBtn2.drawBtn3();
	//����¼�
	while(1)
	{
		while(mousemsg()) //����� 
		{
			mouse_msg mouseMsg=getmouse();
			if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã� 
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

void initMap1() //���زݵص�ͼ 
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/map.png");
	PIMAGE map=newimage(825,825);
	putimage(map,0,0,825,825,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(0,0,map);
	delimage(map);
}

void initMap2() //�������򳡵�ͼ 
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
	setcaption("̰������Ϸ");
	//�������� 
	openingScene();	
	getch(); //�ڼ����ϰ���һ������ż���ִ�� 
	//ѡ���ͼ
	REPLAY:int choice=chooseMap();
	//��ʼ���ϰ��� 
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
	
	//��ʼ����ʼ/��ͣ��ť
	startBtn btn;
	
	//��ʼ����
	snake s1(walls,num);
	
	//��ʼ��ʳ��
	food f(walls,num); 
	int foodCnt=1; //��¼ʳ������� 
	
	//��ʼ��randSpeed
	randSpeed speedPotion(walls,num);
	int speedCnt=1; //��¼�ٶȼ�������
	
	int score=0; //��¼�÷�
	 
	int isPaused=1; 
	while(1)
	{	
		if(!isPaused) //���û����ͣ 
		{
			if(s1.checkRange() || s1.checkWall(walls,num) || s1.checkCircle()) //�ж����Ƿ����/ײǽ/ײ������ 
			{
				flushkey();
				flushmouse();
				if(s1.checkWall(walls,num))
				{
					setbkcolor(EGERGB(255,255,255));
					cleardevice();
					setcolor(EGERGB(255,0,0));
					setfont(50,0,"����"); 
					outtextxy(220,300,"��Ϸ��������ײ�����ϰ���");
					xyprintf(220,360,"��ĵ÷��ǣ�%d",score);
					replayBtn btn1;  //��ʼ�����¿�ʼ��ť 
					exitBtn btn2;    //��ʼ���˳���ť 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //����� 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣� 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y)) //����������¿�ʼ��ť 
									{
										btn.click=0; //������ͣ��ť��״̬ 
										isPaused=1; //����Ϸ��ͣ 
										s1.sReplay(); //�����ߵ�״̬ 
										foodCnt=1; //����ʳ������� 
										speedCnt=1; //�����ٶȼ������� 
										score=0; //���õ÷� 
										goto REPLAY;
									}
									if(btn2.isClicked2(mouseMsg.x,mouseMsg.y)) //��������˳���ť 
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
					setfont(50,0,"����"); 
					outtextxy(220,300,"��Ϸ���������ܳ��˵�ͼ");
					xyprintf(220,360,"��ĵ÷��ǣ�%d",score);
					replayBtn btn1;  //��ʼ�����¿�ʼ��ť 
					exitBtn btn2;    //��ʼ���˳���ť 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //����� 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣� 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y))
									{
										btn.click=0; //������ͣ��ť��״̬ 
										isPaused=1; //����Ϸ��ͣ 
										s1.sReplay(); //�����ߵ�״̬ 
										foodCnt=1; //����ʳ������� 
										speedCnt=1; //�����ٶȼ������� 
										score=0; //���õ÷� 
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
					setfont(50,0,"����"); 
					outtextxy(220,300,"��Ϸ��������ͷײ��������");
					xyprintf(220,360,"��ĵ÷��ǣ�%d",score);
					replayBtn btn1;  //��ʼ�����¿�ʼ��ť 
					exitBtn btn2;    //��ʼ���˳���ť 
					btn1.drawBtn1();
					btn2.drawBtn2();
					while(1)
					{
						while(mousemsg()) //����� 
						{
							mouse_msg mouseMsg=getmouse();
							if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣� 
							{
								if(mouseMsg.is_down())
								{
									if(btn1.isClicked1(mouseMsg.x,mouseMsg.y))
									{
										btn.click=0; //������ͣ��ť��״̬ 
										isPaused=1; //����Ϸ��ͣ 
										s1.sReplay(); //�����ߵ�״̬ 
										foodCnt=1; //����ʳ������� 
										speedCnt=1; //�����ٶȼ������� 
										score=0; //���õ÷� 
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
			else  //�����û�г���/ײǽ/ײ������
			{
				setbkcolor(EGERGB(255,255,255));
				cleardevice();
				setcolor(EGERGB(0,0,255));
				setfont(25,0,"����");
				xyprintf(850,400,"�÷֣�%d",score);
				if(s1.getSpeed()==120)
					outtextxy(850,500,"��ǰ�ٶȣ�����");
				else if(s1.getSpeed()==200)
					outtextxy(850,500,"��ǰ�ٶȣ�����");
				else
					outtextxy(850,500,"��ǰ�ٶȣ�����");
				//����ͼ
				if(choice==1)
					initMap1(); 
				else
					initMap2(); 
				for(int i=0;i<num;i++) //���ϰ���
					walls[i].drawWall(); 
				if(foodCnt==0) //���û��ʳ������ˢ��ʳ��λ�� 
				{
					food temp(walls,num);
					f=temp;
					f.drawFood();
					foodCnt=1;
				}
				else //�������ʳ��Ͳ�������ˢ��λ�� 
				{
					f.drawFood();
				}
				if(speedCnt==0) //���û���ٶȼ������ˢ���ٶȼ�λ��
				{
					randSpeed temp(walls,num);
					speedPotion=temp;
					speedPotion.drawRandSpeed();
					speedCnt=1;
				}
				else //��������ٶȼ��Ͳ�������ˢ��λ�� 
				{
					speedPotion.drawRandSpeed();
				}
				btn.drawBtn();
				s1.show();
			}
			while(mousemsg()) //����� 
			{
				mouse_msg mouseMsg=getmouse();
				if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã� 
				{
					if(mouseMsg.is_down())
					{
						if(btn.isClicked(mouseMsg.x,mouseMsg.y))
						{
							btn.drawBtn(); // ���°�ť���
        					isPaused = !isPaused; // �л���ͣ״̬
						}
					}	
				}		
			}
			if(kbmsg()) //�������� 
			{
				key_msg kbMsg=getkey();
				if(kbMsg.msg==key_msg_down) //����wsad���ŷ�Ӧ 
				{
					if(kbMsg.key==0x57 || kbMsg.key==0x41 || kbMsg.key==0x44 || kbMsg.key==0x53) 
					{
						s1.move(kbMsg);
						//��ͷ����ʳ��ͱ䳤 
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
						//��ͷ�������ټ��͸ı��ٶ�
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
			else //���û�а���wsad��������ԭ���ķ����ƶ� 
			{
				s1.move();
				//��ͷ����ʳ��ͱ䳤
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
				//��ͷ�����ٶȼ� 
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
		else //�����ͣ�� 
		{
			setbkcolor(EGERGB(255,255,255));
			cleardevice();
			setcolor(EGERGB(0,0,255));
			setfont(25,0,"����");
			xyprintf(850,400,"�÷֣�%d",score);
			if(s1.getSpeed()==120)
				outtextxy(850,500,"��ǰ�ٶȣ�����");
			else if(s1.getSpeed()==200)
				outtextxy(850,500,"��ǰ�ٶȣ�����");
			else
				outtextxy(850,500,"��ǰ�ٶȣ�����");
			//����ͼ
			if(choice==1)
				initMap1(); 
			else
				initMap2();
			for(int i=0;i<num;i++) //���ϰ���
				walls[i].drawWall(); 
			f.drawFood(); //��ʳ�� 
			speedPotion.drawRandSpeed(); //���ٶȼ� 
			btn.drawBtn();
			s1.show();
			while(mousemsg()) //����� 
			{
				mouse_msg mouseMsg=getmouse();
				if(mouseMsg.is_left()) //�ж�������������������ȷ��λ�ã� 
				{
					if(mouseMsg.is_down())
					{
						if(btn.isClicked(mouseMsg.x,mouseMsg.y))
						{
							btn.drawBtn(); // ���°�ť���
        					isPaused = 1-isPaused; // �л���ͣ״̬
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

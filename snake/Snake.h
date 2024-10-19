#include<iostream>
#include<graphics.h>
#include<list>
#include<vector>
#include<time.h>
#include"Item.h"
#include<cmath>
using namespace std;

const int LEN=37.5;

void drawTail(int x,int y) //��β�� 
{
	PIMAGE temp=newimage();
	getimage(temp,"resource/snakeTail.png");
	PIMAGE tail=newimage(37.5,37.5);
	putimage(tail,0,0,LEN,LEN,temp,0,0,getwidth(temp),getheight(temp));	
	delimage(temp);
	putimage(x,y,tail);
	delimage(tail);
}

void drawHead(int x,int y,char dir) //��ͷ 
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
	//x,y��ʾλ������ 
	double x;
	double y;
	imgPos(double n1,double n2):x(n1),y(n2){}
};

class snake
{
	private:
		int speed; //�ߵ��ٶȣ���ͼ��ˢ�µ�ʱ��
		char direction; //n��ʾ����s��ʾ�ϣ�w��ʾ����e��ʾ��
		list<imgPos> pos; //��¼��ͷ�������λ�� 
		
	public:
		snake(wall walls[],int num):speed(120),direction('s')
		{
			srand(time(0));
			int a=1,b=17;	 
			int n1=(rand() % (b-a+1))+ a;
			int n2=(rand() % (b-a+1))+ a;
			double x=n1*LEN,y=n2*LEN;
			while(this->snakeCheck(x,y,walls,num)) //��ͷ�������ϰ����ص� 
			{
				n1+=LEN;
				n2-=LEN;
				x=n1*LEN;
				y=n2*LEN;
			}
			pos.push_back(imgPos(x,y));
		}
		
		int getSpeed(){return speed;} //��ȡ�ٶ� 
		
		char getDirection(){return direction;} //��ȡ���� 
		
		list<imgPos> getPos(){return pos;}; //��ȡλ��
		 
		void changeSpeed(int x){speed=x;}; //�ı��ٶ� 
		
		void changeDirection(char ch){direction=ch;} //�ı䷽�� 
		
		int snakeCheck(double x,double y,wall walls[],int num) //�����ͷ�Ƿ����ϰ����ص� 
		{
			for(int i=0;i<num;i++)
			{
				if(abs(x-walls[i].x)<10 && abs(y-walls[i].y)<10)
					return 1;
			}
			return 0;
		}
		
		void grow()  //�Ե�ʳ�����Լӳ� 
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
		
		void move(key_msg keyMsg) //�ƶ� 
		{
			int key=keyMsg.key;
			imgPos head=pos.front();
				
			//���Ǳ����� 
			if(direction=='n')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //����A�� 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='w';
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //����D�� 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='e';
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //����w�� 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //����s��
				{
					if(pos.size()==1)
					{
						this->direction='s';
					}
				} 
			}				
			//�����ϳ��� 
			else if(direction=='s')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //����A�� 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='w';
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //����D�� 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='e';
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //����w�� 
				{
					if(pos.size()==1)
					{
						this->direction='n';
					}	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //����s��
				{
					imgPos temp(head.x,head.y+LEN);
					pos.push_front(temp);
					pos.pop_back();
				} 
			}
			//���������� 
			else if(direction=='w')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //����A�� 
				{						
					imgPos temp(head.x-LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //����D�� 
				{
					if(pos.size()==1)
					{
						this->direction='e';
					}
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //����w�� 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='n';	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //����s��
				{
					imgPos temp(head.x,head.y+LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='s';
				} 
			}
			//���Ƕ�����
			else if(direction=='e')
			{
				if(keyMsg.msg==key_msg_down && key==0x41) //����A�� 
				{						
					if(pos.size()==1)
					{
						this->direction='w';
					}
				}
				else if(keyMsg.msg==key_msg_down && key==0x44) //����D�� 
				{
					imgPos temp(head.x+LEN,head.y);
					pos.push_front(temp);
					pos.pop_back();
				}
				else if(keyMsg.msg==key_msg_down && key==0x57) //����w�� 
				{
					imgPos temp(head.x,head.y-LEN);
					pos.push_front(temp);
					pos.pop_back();
					this->direction='n';	
				}
				else if(keyMsg.msg==key_msg_down && key==0x53) //����s��
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
		
		void show() //������ʾ���� 
		{
			for(auto it=pos.begin();it!=pos.end();it++)
			{
				if(it==pos.begin())
					drawHead(it->x,it->y,this->direction);
				else
					drawTail(it->x,it->y);
			}
		} 
		
		int checkRange() //������Ƿ�Խ��,Խ�緵��1�����򷵻�0 
		{
			imgPos head=pos.front();
			if(head.x>=0 && head.x<=825 && head.y>=0 && head.y<=825)
				return 0;
			else
				return 1;
		} 
		
		int checkWall(wall walls[],int num) //�����ͷ�Ƿ�ײǽ��ײǽ����1�����򷵻�0 
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
		
		int checkCircle() //�����ͷ�Ƿ�����������������1�����򷵻�0 
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
		
		void sReplay() //�����ߵ�״̬ 
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

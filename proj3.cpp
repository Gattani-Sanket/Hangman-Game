//============================================================================
// Name        : Hangman.cpp
// Author      : v
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <cstring>
using namespace std;
#include<fstream>
#include<vector>
#include<cstdlib>
#include<graphics.h>
class level
{
	char ch;
	int in;
public:
	level()
{
		in = 0;
		ch='\0';
}
	friend class stack;
	friend class hang;
};
class stack
{
private:
	level a[20];
	int top;
public:
	stack()
{
		top=-1;
}
	void push(char x, int y)
	{
		top++;
		a[top].ch=x;
		a[top].in=y;
	}
	void pushch(char c)
	{
		top++;
		a[top].ch=c;
	}
	void pop()
	{
		top--;
	}
	void dis_stack()
	{
		for(int j=top;j>=0;j--)
		{
			cout<<a[j].ch<<" "<<a[j].in<<endl;
		}
	}
	friend class hang;
};
class hang
{
	int cat;
	string target;
	string dis;
	int wrong;
	stack correct;
	stack user;
public:
	hang()
{
		wrong=0;
}
	void select();
	void fill();
	void show();
	void input();
	void check(char);
	void call();
	bool win();
	bool lost();
	void graphics(int);
};
void hang::select()
{
	string words[100];
	string line;
	int i=0, rand(), size;
	cout<<"Select the category."<<endl<<"1.Movies\n2.Countries\n3.Food Items\n";
	cin>>cat;
	ifstream file;
	switch(cat)
	{
	case 1:
		file.open("movies.txt");
		break;
	case 2:
		file.open("countries.txt");
		break;
	case 3:
		file.open("food.txt");
		break;
	}
	while(!file.eof())
	{
		getline(file,line);
		words[i] = line;
		i++;
	}
	size = i-1;
	srand(time(0));
	target = words[rand()%size];
	file.close();
	for(int j=0;target[j]!='\0';j++)
	{
		correct.push(target[j],j);
	}
	//correct.dis_stack();
}
void hang::fill()
{
	int len;
	len = target.length();
	for(int i=0;i<len;i++)
	{
		if(isspace(target[i]))
		{
                	dis = dis + " ";
		}
		else
		{
			dis = dis + "_";
		}
	}
}
void hang::show()
{
	for(int i=0;dis[i]!='\0';i++)
	{
		cout<<dis[i]<<" ";
	}
	cout<<endl;
}
void hang::input()
{
	char in;
	cout<<"Guess the character: ";
	cin>>in;
	check(in);
}
void hang::check(char input)
{
	int flag=0;
	for(int j=user.top;j>=0;j--)
	{
		if(user.a[j].ch==input)
		{
			flag=1;
			cout<<"Character already guessed!\n";
			break;
		}
	}
	if(flag==0)
	{
		int flag2=0;
		for(int i=correct.top;i>=0;i--)
		{
			if(correct.a[i].ch==input)
			{
				flag2=1;
				dis[correct.a[i].in]=input;
			}
		}
		if(flag2==0)
		{
			wrong++;
			cout<<"Try Again!"<<endl;
			graphics(wrong);
		}
		else
		{
			show();
		}
		user.pushch(input);
	}
}
void hang::call()
{
	while(!lost() && !win())
	{
		input();
		//cout<<wrong;
	}
}
bool hang::win()
{
	int flag=0;
	for(int i=0;dis[i]!='\0';i++)
	{
		if(dis[i]=='_')
		{
			flag=1;
			return false;
		}
	}
	return true;
}
bool hang::lost()
{
	if(wrong==8)
		return true;
	else
		return false;
}
void hang::graphics(int count)
{
	switch(count)
	{
	case 1:
	line(25,420,175,420);
	line(100,50,100,420);
	line(100,50,425,50);
	delay(1500);
	break;
	case 2:
	line(425,50,425,100);
	delay(1500);
	break;
	case 3:
	 circle(425,145,45);
	delay(1500);
	break;
	case 4:
	line(425,190,425,290);
	delay(1500);
	break;
	case 5:
	line(375,255,425,240);
	delay(1500);
	break;
	case 6:
	line(425,240,475,255);
	delay(1500);
	break;
	case 7:
	line(350,305,425,290);
	delay(1500);
	break;
	case 8:
	line(425,290,500,305);
	delay(2000);
	break;
	}
}
int main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	setbkcolor(8);
	setcolor(7);
	rectangle(0,0,630,470);
	delay(1500);
	cout<<"\n--------------------------------HANGMAN-----------------------------------------\n";
	int count=0;
	hang h;
	h.select();
	h.fill();
	h.show();
	h.call();
	if(h.win())
	{
		cout<<"You Won!"<<endl;
		return 0;
	}
	if(h.lost())
	{
		cout<<"You Lost!"<<endl;
		return 0;
	}
	return 0;
}


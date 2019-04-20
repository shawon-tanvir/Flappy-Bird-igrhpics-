# include "iGraphics.h"
#include<stdio.h>
#include<conio.h>
#include<string>


#define bgspeed 1;

void bricks();
void scoring();
void collision();
void scoreupdate();
void highscore();
void initialvalue();
void highscoreshow();

void readScore();
/* 
	function iDraw() is called again and again by the system.
*/
int bird_x=170,bird_y=180;

int win_w=600,win_h=400;

int bkgspeed=2,pillarspeed=2,gravitycontrol=2;

int pillargap=300,birdtimer=2,life=3;

int pd1x=500,pd1y=0,pd2x=pd1x+1*pillargap,pd2y=0,pd3x=pd1x+2*pillargap,pd3y=0;

int brickcountd1=0,brickcountd2=0,brickcountd3=0;

char str1[50],str2[50],str3[50],str4[5],str5[40];

int score=0,highwidth=500,len=0,mode=0,menu=1,highflag=0,place=280,lifecheck=0;

char apple[2][15]={"apple2.bmp","apple2.bmp"};

char backgroundimage[10][15]={"bg\\bg11.bmp","bg\\bg12.bmp","bg\\bg13.bmp","bg\\bg14.bmp","bg\\bg15.bmp","bg\\bg16.bmp","bg\\bg17.bmp","bg\\bg18.bmp","bg\\bg19.bmp","bg\\bg20.bmp"};

char totalscore[50];


/*struct appleaxis{
	int x;
	int y;
};
appleaxis app[2];*/


struct background{
	int x;
	int y;
};
background bg[10];

struct players{
	char name[100];
	int score;
};
struct players user[10],temp;

FILE *fp;


int scoredplayer=0;


int flag1=0;
void iDraw()
{
	//place your drawing codes here	
	iClear();

	if (menu==1){
		iShowBMP(0,0,"firstmenu.bmp");
		iSetColor(0,0,255);
		iFilledRectangle(200,180,200,30);
		iSetColor(0,255,0);
		iText(120,60,"Click to activate the box and write your name",GLUT_BITMAP_HELVETICA_18);
		if(mode == 1)
	    {
		iSetColor(0, 255, 0);
		iText(205,190 ,str1,GLUT_BITMAP_HELVETICA_18);
	    }
	}

	else if(menu==2)
		iShowBMP(0,0,"menu1.bmp");


	else if(menu==3){
		for(int i=0;i<10;i++){
			iShowBMP(bg[i].x,bg[i].y,backgroundimage[i]);
		}

		/*for(int i=0;i<2;i++){
			iShowBMP2(app[i].x,app[i].y,apple[i],0);
		}*/
		bricks();
		iShowBMP2(bird_x,bird_y,"bird.bmp",255);
		iShowBMP(0,0,"bg\\SideScreen.bmp");
		iSetColor(0,0,255);
		//sprintf(str3,"Player,s Name:\n  %s",str2); 
		iText(0,200,"Plyer's",GLUT_BITMAP_HELVETICA_18);
		iText(0,180,"Name:",GLUT_BITMAP_HELVETICA_18);
		iSetColor(0,254,0);
		iText(0,160,str2,GLUT_BITMAP_HELVETICA_18);
		iSetColor(255,0,0);
		sprintf(str4,"LIFE : %d",life);
		iText(10,60,str4,GLUT_BITMAP_HELVETICA_18);
		scoring();
		collision();
	}
	else if(menu==4){
		highscoreshow();
	}
	else if(menu==5){
		iShowBMP(0,0,"credit.bmp");
	}
}


int random1=3;
int random2=2;
int random3=4;


void bricks()
{
	if(menu==3){
		int height1=0;
		if(brickcountd1==1){
			random1=4+rand()%8;
		}
		for(int i=0;i<random1;i++){
			iShowBMP(pd1x,height1,"brick4.bmp");
			height1+=23;
		}
		iShowBMP(pd1x,height1,"pillerdowntop.bmp");
		iShowBMP(pd1x,random1*23+85,"pillerup.bmp");
		int height2=0;
		if(brickcountd2==1){
			random2=4+rand()%8;
		}
		for(int i=0;i<random2;i++){
			iShowBMP(pd2x,height2,"brick4.bmp");
			height2+=23;
		}
		iShowBMP(pd2x,height2,"pillerdowntop.bmp");
		iShowBMP(pd2x,random2*23+85,"pillerup.bmp");
		int height3=0;
		if(brickcountd3==1){
			random3=4+rand()%8;
		}
		for(int i=0;i<random3;i++){
			iShowBMP(pd3x,height3,"brick4.bmp");
			height3+=23;
		}
		iShowBMP(pd3x,height3,"pillerdowntop.bmp");
		iShowBMP(pd3x,random3*23+85,"pillerup.bmp");
	}
}


/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/


char str[50];
void scoring()
{
	if(menu==3){
		sprintf(str,"Score : %d",score);
		iText(10,300,str,GLUT_BITMAP_HELVETICA_18);
	}
}

void collision()
{
	if(menu==3){
		if(bird_x+32==pd1x && bird_y<=(random1+1)*23||bird_x+32==pd1x && bird_y>=(random1+1)*23+62  || bird_x+32==pd2x && bird_y<=(random2+1)*23 || bird_x+32==pd2x && bird_y>=(random2+1)*23+62||bird_x+32==pd3x && bird_y<=(random3+1)*23 ||bird_x+32==pd3x && bird_y>(random3+1)*23+62){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);

			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if((bird_y <= (random1+1)*23) && (bird_x+32>=pd1x) && (bird_x<=pd1x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if((bird_y <= (random2+1)*23) && (bird_x+32>=pd2x) && (bird_x<=pd2x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if((bird_y <= (random3+1)*23) && (bird_x+32>=pd3x) && (bird_x<=pd3x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
		
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if((bird_y+28 >= (random1+1)*23+62) && (bird_x+32>=pd1x) && (bird_x<=pd1x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
		
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if((bird_y+28 >= (random2+1)*23+62) && (bird_x+32>=pd2x) && (bird_x<=pd2x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);		
		}
		else if((bird_y+28 >= (random3+1)*23+62) && (bird_x+32>=pd3x) && (bird_x<=pd3x+35)){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
		
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if(bird_y<=0||bird_y+28>=win_h || bird_x<=0 || bird_x+32>=win_w){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
	
			life--;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if(life==0 ){
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			if(flag1==0){
				highscore();
			}
			if(highflag==1){
				highscoreshow();
			}
			else{
				menu=2;
			}
		}
	}
}

void pillarmove()
{
	if(menu==3){
		pd1x-=pillarspeed;
		pd2x-=pillarspeed;
		pd3x-=pillarspeed;
		if(pd1x<=40 ){
			pd1x=pd3x+pillargap;
			brickcountd1=1;
		}
		if(pd1x<=600 ){
			brickcountd1=0;
		}
		if(pd2x<=40 ){
			pd2x=pd1x+pillargap;
			brickcountd2=1;
		}
		if(pd2x<=600 ){
			brickcountd2=0;
		}
		if(pd3x<=40 ){
			pd3x=pd2x+pillargap;
			brickcountd3=1;
		}
		if(pd3x<=600 ){
			brickcountd3=0;
		}
		if(bird_x==pd1x+38||bird_x==pd2x+38||bird_x==pd3x+38)
			score++;
		if(score>6){
			pillarspeed=4;
		}
		if(score>14){
			pillarspeed=6;
		}
		if(score>24){
			gravitycontrol=3;
		}
		/*if(score>19){
			//pillarspeed=4;
		}*/

	}
}

void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(menu==2 && mx>=230 && mx<=365 && my>=280 && my<=365){
			pillargap=300;
			//birdtimer=2;
			menu=3;
			life=3;
			score=0;
			highflag=0;
			flag1=0;
			gravitycontrol=2;
			pillarspeed=2;
			initialvalue();
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
		}
		else if(menu==2 && mx>=150 && mx<=455 && my>=200 && my<=272){
			menu=4;
		}
		else if(menu==2 && mx>=185 && mx<=375 && my>=139 && my<=183){
			menu=5;
		}
		else if(menu==2 && mx>=220 && mx<=340 && my>=60 && my<=113){
			exit(0);
		}
		else if(menu==1 && mx>=200 && mx<=400 && my>=180 && my<=210){
			mode=1;
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}
/*iPassiveMouseMove is called to detect and use 
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here
	
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/
 
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == ' ')
	{
		bird_y+=15;
	}

	if(mode==1){
		if(key == '\r')
		{
			menu=2;
			mode = 0;
			strcpy(str2, str1);
			printf("%s\n", str2);
			for(int i = 0; i < len; i++)
				str1[i] = 0;
			len = 0;
		}
		else if (key == '\b'){
			if (len != 0)
			{						
				str1[--len] = '\0';
			}
		}
		else
		{
			str1[len] = key;
			len++;
		}
	}

	if(highflag==1){
		if(key=='\r'){
			menu=2;
		}
	}
	
	if(menu==4){
		if(key=='\r'){
			menu=2;
		}
	}
	if(menu==5){
		if(key=='\r'){
			menu=2;
		}
	}

	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_UP)
	{
		bird_y+=10;	
	}
	else if(key== GLUT_KEY_RIGHT)
	{
		bird_x+=10;
	}
	else if(key== GLUT_KEY_LEFT)
	{
		bird_x-=10;
	}
	else if(key== GLUT_KEY_DOWN)
	{
		bird_y-=10;
	}
	//place your codes for other keys here
}

void birdgravity(){
	if(menu==3){
		if(bird_y>=1)
			bird_y-=gravitycontrol;
		/*if(score>5)
			bird_y-=3;
		if(score>6)
			bird_y-=4;*/
	}

}

void setAll()
{
	int sum=0;
	for(int i=0;i<10;i++){
		bg[i].y=0;
		bg[i].x=sum;
		sum+=60;
	}
	/*app[0].x=475;
	app[1].x=975;
	app[0].y=50+ rand() % 350;
	app[1].y=50+ rand() % 350;*/
}

void bgchange()
{
	if(menu==3){
		for(int i=0;i<10;i++){
			bg[i].x-=2;
			if(bg[i].x<=0){
				bg[i].x=win_w-2;
			}
		}
	}
}

/*void applechange(){
	for(int i=0;i<2;i++){
		app[i].x-=1;
		if(app[0].x<=0)
			app[0].x=475;
		if(app[1].x<=0)
			app[1].x=950;
	}
}*/


void highscoreshow(){
	iShowBMP(0,0,"highscorescreen.bmp");
	FILE *fp;
	fp=fopen("score.txt","r");
	if(fp==NULL){
       printf("Error!");
       exit(1);
	}

    for(int j=0;j<10;j++)
    {  
		fscanf(fp,"%s %d",&user[j].name,&user[j].score);
		fscanf(fp,"\n");
    }
    fclose(fp);
	for(int j=0;j<10;j++)
	   {  
		   
	      sprintf(str5,"%d",user[j].score);
		  iText(230,place,user[j].name,GLUT_BITMAP_HELVETICA_18);
		  iText(330,place,str5,GLUT_BITMAP_HELVETICA_18);
		  place-=30;

       }
		 place=280;
}



void highscore(){

	int j,min,flag;

	flag1=1;
	FILE *fp;
	fp=fopen("score.txt","r");
	if(fp==NULL){
       printf("Error!");
       exit(1);
	}

    for(j=0;j<10;j++)
    {  
		fscanf(fp,"%s %d",&user[j].name,&user[j].score);
	    printf("%s %d\n",user[j].name,user[j].score);
		fscanf(fp,"\n");
    }
    fclose(fp);
    
   if(score>user[9].score){
		highflag=1;
		strcpy(user[9].name,str2);
		user[9].score=score;

		for (int i = 0; i <10; i++){
			for (int j = i + 1; j <10; j++){
				if (user[i].score < user[j].score){
					temp = user[i];
					user[i] = user[j];
					user[j] = temp;
				}
			}
		}

		for(j=0;j<10;j++)
		{   
			printf("%s %d\n",user[j].name,user[j].score);
		}
  
		fp=fopen("score.txt","w");
		for(j=0;j<10;j++)
		{

			fprintf(fp,"%s %d\n",user[j].name,user[j].score);
        }
		fprintf(fp,"\n");
		fclose(fp);
		 
	}  
    else{
	   printf("No Highscore");
    }
}

void initialvalue(){
	bird_x=170;
	bird_y=180;
	pd1x=400,pd1y=0,pd2x=pd1x+1*pillargap,pd2y=0,pd3x=pd1x+2*pillargap,pd3y=0;
	brickcountd1=0,brickcountd2=0,brickcountd3=0;
}

int main()
{
	str2[0];
	setAll();
	iSetTimer(5,pillarmove);
	iSetTimer(birdtimer,birdgravity);
	iSetTimer(5,bgchange);
	//iSetTimer(5,applechange);
	iInitialize(win_w, win_h, "Flappy Bird");
	return 0;
}	
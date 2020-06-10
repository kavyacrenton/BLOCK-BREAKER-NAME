#include<GL/glut.h>
#include"stdafx.h"
#include<stdlib.h>

void initialize()	//To set the initial co-ordinates of the objects on the screen
{
	for(int n=0,x=4,y=390;n<45;n++,x+=66) //n is the number of bricks
	{
	   if(x>560)
	   {
	     x=4;
	     y-=25;
	   }
	   b[n].x=x;
	   b[n].y=y;
	   b[n].w=60;
	   b[n].h=20;
	   b[n].alive=true;
	}

	block.myx=300;   //blocks initial x  co-ordinate
	block.myy=0;     //blocks initial y  co-ordinate
	block.width=80;  //blocks width
	block.height=20; //blocks height
	block.lft=false; //initially at rest
	block.rgt=false; //initially at rest

	ball.ballx=300;  //ball's initials x co-ordinate
	ball.bally=200;  //ball's initials x co-ordinate
	ball.ballwh=30;  //ball's width and height
	ball.velx=1.0;   //ball's velocity in x direction
	ball.vely=1.0;   //ball's velocity in x direction

	red1=0.96;
 	green1=0.8;
 	blue1=0.69;
 	red2=0.6;
 	green2=0.8;
	blue2=0.196078;

	ball.red=0.65;
	ball.green=0.49;
	ball.blue=0.24;

	block.red=0.137255;
	block.green=0.556863;
	block.blue=0.419608;

}
bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{
  if ( Ay+Ah < By ) return false;      //if the ball reached the brick
  else if ( Ay > By+Bh ) return false; //if ball is above brick and misses
  else if ( Ax+Aw < Bx ) return false; //ball left of brick
  else if ( Ax > Bx+Bw ) return false; //ball right of brick

  return true; //There is a collision because none of above returned false
}

void reshape()		               //Modify the co-ordinates according to the key-presses and collisions etc...
{
	if(block.myx<0)                //position of block outside window is left
	  block.myx=0;
	if(block.myx+block.width>600)  //extreme right
	  block.myx=520;
	if(block.lft==true)            //motion of the block
	  block.myx=block.myx-2.0;
	if(block.rgt==true)
	  block.myx=block.myx+2.0;
	ball.ballx+=0.05*ball.velx;    //motion of the ball
	ball.bally+=0.05*ball.vely;
	for(int n=0;n<45;n++)
	{
	   if(b[n].alive==true)
	   {
	   	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,b[n].x,b[n].y,b[n].w,b[n].h)==true) //function checking if ball collides with brick/bricks
	   	{
	   	  ball.vely=-ball.vely;  //goes up and comes down, reduce velocity
	   	  b[n].alive=false;      //to make the brick/bricks disappear
	   	  ball.down=true;        //bool value down set to "true"
	   	  ball.up=false;         //bool value up set to "true"
	   	  ball.red+=0.08;
	   	  ball.green+=0.02;
	   	  ball.blue+=0.08;
	   	  break;
	   	}
	   }
	}
	if(ball.ballx<0)           //Ball at extreme left of window
	{
		ball.velx=-ball.velx;  //To move the ball back inside the window
		ball.right=true;
		ball.left=false;
	}
	if(ball.ballx+ball.ballwh>600) //Ball at extreme right of window
	{
		ball.right=false;
		ball.left=true;
		ball.velx=-ball.velx;
	}
	if(ball.bally+ball.ballwh>400) //Ball goes above the window
		ball.vely=-ball.vely;
	else if(ball.bally<0)          //Ball goes below the window
		exit(0);

	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,block.myx,block.myy,block.width,block.height)==true)
	{
			ball.vely=-ball.vely;  //To make the ball move in the opposite direction
			ball.up=true;          //The bool value up is set to "true"
			ball.down=false;
			block.red+=0.095000;
			block.green+=0.050000;
			block.blue+=0.150000;

	}
	draw();
}
void specialUp(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=false;break;  //If the block is at the extreme right end do not move
		case (GLUT_KEY_RIGHT): block.rgt=false;break; //If the block is at the extreme left end do not move
	}
}
void specialDown(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=true;break;  //Move block if not at any extreme end
		case (GLUT_KEY_RIGHT): block.rgt=true;break; //Move block if not at any extreme end
	}
}
void keyboard(unsigned char key,int x,int y)
{
	if(key==27) 		//27 corresponds to the esc key
	{
		ball.velx=0;
		ball.vely=0;	//To stop the ball from moving
		ball.ballx=275;
		ball.bally=20;
		block.myx=250;
		block.myy=0;
	}
}
void myinit()
{
	glViewport(0,0,600,400);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);  //To select the kind of shading (flat or smooth)
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,600,0,400);
}
void draw()		//Render the objects on the screen using the latest updated co-ordinates
{
	for(int i=0;i<45;i++) //To go through all bricks and draw
	{
		if(b[i].alive==true)
		{
		   if(i==0 && i<9) glColor3f(1,0,0);                 //Color the first row of bricks
		   else if(i==9 && i<18) glColor3f(0.5,0.4,0.6);     //Color the second row of bricks
           else if(i==18 && i<27) glColor3f(0,1,0);          //Color the third row of bricks
           else if(i==27 && i<36) glColor3f(0.95,0.95,0);    //Color the fourth row of bricks
           else if(i==36 && i<45) glColor3f(0,0,0.5);        //Color the fifth row of bricks
		   glBegin(GL_POLYGON);
			   glVertex2f(b[i].x,b[i].y);
			   glVertex2f(b[i].x+b[i].w,b[i].y);
			   glVertex2f(b[i].x+b[i].w,b[i].y+b[i].h);
			   glVertex2f(b[i].x,b[i].y+b[i].h);
		   glEnd();
		}
	}

	glColor3f(block.red,block.green,block.blue);      //To draw the block
	glBegin(GL_POLYGON);
		glVertex2f(block.myx,block.myy);
		glVertex2f(block.myx+block.width,block.myy);
		glVertex2f(block.myx+block.width,block.myy+block.height);
		glVertex2f(block.myx,block.myy+block.height);
	glEnd();

	glColor3f(ball.red,ball.green,ball.blue);         //To draw the ball
	glBegin(GL_POLYGON);
		glVertex2f(ball.ballx,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally);
		glVertex2f(ball.ballx+ball.ballwh,ball.bally+ball.ballwh);
		glVertex2f(ball.ballx,ball.bally+ball.ballwh);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();

}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red,green,blue,1);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	reshape();
}

void processmenu(int opt)
{
	switch(opt)
	{
		case CONTINUE:
			revert();
			break;
		case INC:
			ball.velx++;
			ball.vely++;
			break;

		case QUIT: exit(0);
	}

}
void revert()
{
	ball.velx=0.35;
	ball.vely=0.35;
	if(ball.up==true)
	{
		if(ball.right==true)
		{
			ball.velx=ball.velx;
			ball.vely=ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=ball.vely;
		}
	}
	else if(ball.down=true)
	{
		if(ball.right=true)
		{
			ball.velx=ball.velx;
			ball.vely=-ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=-ball.vely;
		}
	}
}

void myMenu (int option)        //To select between "easy","medium","hard" difficulties
{
 if(option==1)                  //This is the "easy mode"
    ball.velx+=1.0;
	ball.vely+=1.0;
	block.myx=block.myx-2.0;
	block.myx=block.myx+2.0;

    myinit();
	draw();

 if(option==2)                  //This is the "medium mode"
    ball.velx+=2.0;
	ball.vely+=2.0;
	block.myx=block.myx-3.0;
	block.myx=block.myx+3.0;

    myinit();
	draw();

 if(option==3)                 //This is the "hard mode"
    ball.velx+=3.0;
	ball.vely+=3.0;
	block.myx=block.myx-4.0;
	block.myx=block.myx+4.0;

    myinit();
	draw();

}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Block Breaker");
	glutCreateMenu(myMenu);                               // menu items
	glutAddMenuEntry("SELECT THE LEVEL OF DIFFICULTY",0);
    glutAddMenuEntry("Easy",1);
    glutAddMenuEntry("Medium",2);
    glutAddMenuEntry("Hard",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    initialize();
	glutDisplayFunc(display);
        glutSpecialFunc(specialDown);                    //Keyboard and direction
    	glutSpecialUpFunc(specialUp);
    	glutKeyboardFunc(keyboard);
	glutIdleFunc(reshape);                              //Perform background processing tasks or continuous animation
	glutMainLoop();
	return 0;
}


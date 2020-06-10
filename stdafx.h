#define CONTINUE 1
#define QUIT 0
#define RED 2 
#define GREEN 3
#define BLUE 4
#define BLACK 5
#define INC 6
#define DEC 7
#define C1 8
#define C2 9
#define C3 10 
#define GOLD 11
#define ORCHID 12
#define BLACK1 13
#define WHITE 14


struct bricks
{
	float x,y,w,h;
	bool alive;
} b[45];

float red1,red2,green1,green2,blue1,blue2;

struct ball
{
	float ballx,bally,ballwh,velx,vely;
	float red;
	float green;
	float blue;
	bool left,right,up,down;
} ball;

struct block
{
	float myx;
	float myy;
	float width;
	float height;
	bool lft;
	bool rgt;
	float red;
	float green;
	float blue;
}block;

float red=0.0;
float green=0.0;
float blue=0.0;

void specialUp(int,int,int);	//To check for key press
void specialDown(int,int,int);  //To check for key release
void reshape(void);		//To Modify the co-ordinates of the game objects according to the events
void draw(void);		//To Render the Game objects on the screen
void callMenu(void);		//To create the main pause menu
void processmenu(int);		//To process the pause menu
void revert(void);
void main_menu(int);

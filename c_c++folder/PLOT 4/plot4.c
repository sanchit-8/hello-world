#include<stdio.h>
#include<conio.h>
#include<windows.h>

COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void SetColor(int ForgC)
{
     WORD wColor;
                          //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

                           //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                     //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
char check(int re[8][6])
{   int count=0,row=0,col=0,x=0,y=0,z=0;
char cursor;

  /////////////////////check column start////////////////////////
	for(row=0;row<8;row++)
	{
		count=0;
		for(col=0;col<5;col++)
		{
			if(re[row][col]==re[row][col+1]&&re[row][col]!=0)
			{
				count++;
				if(count==3)
				{
					break;
				}
			 }
			 else
				count=0;

		}
		if(count==3)
		{
			if(re[row][col]==1)
			{
				SetColor(61);
				gotoxy(8,12); printf("PLAYER 1");
				gotoxy(8,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
			if(re[row][col]==2)
			{
				SetColor(22);
				gotoxy(60,12); printf("PLAYER 2");
				gotoxy(60,13); printf(" WINS.. ");
				cursor='q';
				break;
			}

		}
	}
	//////////////check column ends/////////////
	//////////////check row start///////////////
	for(col=0;col<5;col++)
	{
		count=0;
		for(row=0;row<8;row++)
		{
			if(re[row][col]==re[row+1][col]&&re[row][col]!=0)
			{
				count++;
				if(count==3)
				{
					break;
				}
			}
			else
				count=0;
		}
		if(count==3)
		{
			if(re[row][col]==1)
			{
				SetColor(61);
				gotoxy(8,12); printf("PLAYER 1");
				gotoxy(8,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
			if(re[row][col]==2)
			{
				SetColor(22);
				gotoxy(60,12); printf("PLAYER 2");
				gotoxy(60,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
		}
	}
	////////////////////check row ends/////////////////////
	///////////////////check diagonal stars////////////////

	count=0;
	///////////////////PLAYER 1////////////////////////////
	for(z=0;z<5;z++)
	{
		count=0;
		x=z;
		for(y=0;x<z+5&&y<5;y++,x++)
		{
			if(re[x][y]==1&&re[x+1][y+1]==1)
			{
				count++;
				if(count==3)
				{
					break;
				}
			}
			else
				count=0;
		}
		if(count==3)
		{
			SetColor(61);
			gotoxy(8,12); printf("PLAYER 1");
			gotoxy(8,13); printf(" WINS.. ");
			cursor='q';
			break;
		}
	}
	count=0;
	for(x=0,y=1;x<4&&y<5;x++,y++)
	{
		if(re[x][y]==1&&re[x+1][y+1]==1)
		{
			count++;
			if(count==3)
			{
				SetColor(61);
				gotoxy(8,12); printf("PLAYER 1");
				gotoxy(8,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
		}
      }
      for(z=7;z>2;z--)
      {
		count=0;
		x=z;
		for(y=0;x>z-5&&y<5;x--,y++)
		{
			if(re[x][y]==1&&re[x-1][y+1]==1)
			{
				count++;
				if(count==3)
				{
					break;
				}
			}
		}
		if(count==3)
		{
			SetColor(61);
			gotoxy(8,12); printf("PLAYER 1");
			gotoxy(8,13); printf(" WINS.. ");
			cursor='q';
			break;
		}
      }
      for(x=7,y=1;x>3&&y<5;x--,y++)
      {
		if(re[x][y]==1&&re[x-1][y+1]==1)
		{
			count++;
			if(count==3)
			{
				SetColor(61);
				gotoxy(8,12); printf("PLAYER 1");
				gotoxy(8,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
		}
      }
      ////////////////////PLAYER 2//////////////
      for(z=0;z<5;z++)
      {
		count=0;
		x=z;
		for(y=0;x<z+5&&y<5;y++,x++)
		{
			if(re[x][y]==2&&re[x+1][y+1]==2)
			{
				count++;
				if(count==3)
				{
					break;
				}
			}
		}
		if(count==3)
		{
			SetColor(22);
			gotoxy(60,12); printf("PLAYER 2");
			gotoxy(60,13); printf(" WINS.. ");
			cursor='q';
			break;
		}
	}
	count=0;
	for(x=0,y=1;x<4&&y<5;x++,y++)
	{
		if(re[x][y]==2&&re[x+1][y+1]==2)
		{
			count++;
			if(count==3)
			{
				SetColor(22);
				gotoxy(60,12); printf("PLAYER 2");
				gotoxy(60,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
		}
       }
       for(z=7;z>2;z--)
       {
		count=0;
		x=z;
		for(y=0;x>z-5&&y<5;x--,y++)
		{
			if(re[x][y]==2&&re[x-1][y+1]==2)
			{
				count++;
				if(count==3)
				{
					break;
				}
			}
		}
		if(count==3)
		{
			SetColor(22);
			gotoxy(60,12); printf("PLAYER 2");
			gotoxy(60,13); printf(" WINS.. ");
			cursor='q';
			break;
		}
      }
      for(x=7,y=1;x>3&&y<5;x--,y++)
      {
		if(re[x][y]==2&&re[x-1][y+1]==2)
		{
			count++;
			if(count==3)
			{
				SetColor(22);
				gotoxy(60,12); printf("PLAYER 2");
				gotoxy(60,13); printf(" WINS.. ");
				cursor='q';
				break;
			}
		}
      }
      int draw=0;
      for(row=0;row<8;row++)
      {
	for(col=0;col<5;col++)
	{
	  if(re[row][col]!=0)
	  {

	   draw++;
	  }
	}
      }
      if(draw==40)
      {
	gotoxy(39,22);
	printf("DRAW");
	cursor='q';
      }
      return cursor;
}
////////////////////////CHECKING ENDS/////////////////////
//////////////// UDF FOR GRID/////////////////////////////
void grid()
{
	system("cls");
	int x,y;
	gotoxy(37,3);
	SetColor(0); printf("PLOT - 4");
	gotoxy(37,4);
	SetColor(0); printf("--------");
	char box[16][33];
	for(x=0;x<16;x++)
	{
		for(y=0;y<33;y++)
		{
			box[x][y]=' ';
		}
	}
	for(x=0;x<16;x=x+3)
	{
		for(y=0;y<33;y++)
		{
		box[x][y]='_';
		}
	}
	for(y=0;y<33;y=y+4)
	{
		for(x=0;x<16;x++)
		{
			box[x][y]='|';
		}
	}
	box[0][0]=' ';
	for(y=0,x=0;y<33;y++)
	{
		if(y%4==0)
		{
			box[x][y]=' ';
		}
	}

	for(x=0;x<16;x++)
	{
		for(y=0;y<33;y++)
		{       gotoxy(y+24,x+5);
			SetColor(0);
			putch(box[x][y]);
		}
		printf("\n");
	}

}
//////////////////////////////////// UDF FOR INSERT//////////////////////

int insert(int re[8][6],int row_ret,int col_ret,int x_ax,int flag)
{   int yaxist=4;
    for(;yaxist<22;yaxist=yaxist+3,col_ret++)
    {
	if(re[row_ret][col_ret]!=1||re[row_ret][col_ret]!=2||re[row_ret][col_ret]!=3)
	{
		gotoxy(x_ax,yaxist);
	}
	if(re[row_ret][col_ret]==1||re[row_ret][col_ret]==2||re[row_ret][col_ret]==3)
	{
		if(re[row_ret][col_ret-1]==0)
		{
			gotoxy(x_ax,yaxist);
			re[row_ret][col_ret-1]=flag;
			if(re[row_ret][col_ret-1]==1)
				SetColor(61);
			if(re[row_ret][col_ret-1]==2)
				SetColor(22);
			putch(2);
			break;
		}
	  }
    }
    return re[8][6];
}
///////////////UDF FOR BORDER///////////////////////////////////////////
void border()
{
      int ro,co;
      SetColor(61);
      for(co=1,ro=0;ro<79;ro++)
      {
	 gotoxy(ro,co);
	 putch(178);
      }
      for(co=25,ro=0;ro<79;ro++)
      {
	 gotoxy(ro,co);
	 putch(178);
      }
      for(co=1,ro=1;co<25;co++)
      {
	 gotoxy(ro,co);
	 putch(178);
	 gotoxy(ro+1,co);
	 putch(178);
      }
      for(co=1,ro=79;co<25;co++)
      {
	 gotoxy(ro,co);
	 putch(178);
	 gotoxy(ro-1,co);
	 putch(178);
      }
}
void menu()
{

	SetColor(0);
	gotoxy(24,4); printf("@@@  @      @@@  @@@@@       @  @");
	gotoxy(24,5); printf("@  @ @     @   @   @         @  @") ;
	gotoxy(24,6); printf("@@@  @     @   @   @   @@@@  @@@@")  ;
	gotoxy(24,7); printf("@    @     @   @   @            @")   ;
	gotoxy(24,8); printf("@    @@@@@  @@@    @            @")    ;
	gotoxy(24,9); printf("---------------------------------")    ;
	SetColor(5);
	gotoxy(35,12);printf("MAIN MENU");
	gotoxy(24,15);printf("PLAY GAME.......................1");
	gotoxy(24,16);printf("CONTROLS........................2");
	gotoxy(24,17);printf("RULES...........................3");
	gotoxy(24,18);printf("EXIT............................0");
	gotoxy(24,20);printf("ENTER YOUR CHOICE:");
}

//////////////////////////////////////void main//////////
void main()
{
 system("cls");
 border();
 char pass[20];
 int l,tri=0,win;
 while(tri!=3)
 {
	system("cls");
	border();
	SetColor(1);
	gotoxy(25,11);
	printf("Enter password to access the game");
	gotoxy(70,3);
	printf("try:");printf("%d",tri);
	gotoxy(35,12);
	printf("Password: ");
	for(l=0;l<20;l++)
	{
		pass[l]=getch();
			if(pass[l]==13)
				break;
			else
				printf("*");
	}
	pass[l]='\0';
		if(strcmp(pass,"s")==0)
		{
			gotoxy(33,12);
			printf("\nAccess granted.");
			getch();
			break;
		}
		else
		{
			tri++;
		}
 }
	if(tri==3)
	{

		system("cls");
		border();
		gotoxy(30,12);
		printf("access denied");
		getch();
		exit(0);
	}
 char ch='1';
 while(ch=='0'||ch=='1'||ch=='2'||ch=='3')
 {
	start:
	system("cls");
	border();
	menu();
	scanf("%c",&ch);
	if(ch=='1')
	{
		system("cls");
		border();
		grid();
		border();
  /////////////////////initialisation of re////////////////
		int re[8][6],i,j;
		for(i=0;i<8;i++)
		{
			for(j=0;j<6;j++)
			{
				re[i][j]=0;
			}
		}
		for(j=5,i=0;i<8;i++)
		{
			re[i][j]=3;
		}
  /////////////////////////////////////////////////////////////
		gotoxy(26,7);
		char cursor='\0';
		int x_ax=26,y_ax=7,row_re=0,col_re=0,row_ret=0,col_ret=0,flag=1;
		while(cursor!='q')
		{
			cursor=getch();
   ////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////PLAYER 1//////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////
			while(flag==1&&cursor=='a'||cursor=='d'||cursor=='q')
			{
				if(cursor=='q')
				break;
				if(cursor=='a')
				{
					x_ax=x_ax-4;
					row_re=row_re-1;
					row_ret=row_re;
					col_ret=col_re;
					if((x_ax<=54)&&(x_ax>=24)&&(y_ax<=22)&&(y_ax>=4))
					{
						gotoxy(x_ax,y_ax);
						cursor=getch();
						if(cursor==13)
						{
							re[8][6]=insert(re,row_ret,col_ret,x_ax,flag);
							cursor=check(re);
							flag=2;
							}
					}
				}
				if(cursor=='d')
				{
					x_ax=x_ax+4;
					row_re=row_re+1;
					row_ret=row_re;
					col_ret=col_re;
					if((x_ax<=54)&&(x_ax>=24)&&(y_ax<=30)&&(y_ax>=4))
					{
						gotoxy(x_ax,y_ax);
						cursor=getch();
						if(cursor==13)
						{
							re[8][6]=insert(re,row_ret,col_ret,x_ax,flag);
							cursor=check(re);
							flag=2;
						}
					}
				}
			}
			if(cursor=='q')
			{
			getch();
			break;
			}
			if(flag==1)
			{
				cursor='\0';
				cursor=getch();
			}
			else
			{
				cursor=getch();
			}
				while(flag==2&&cursor=='a'||cursor=='d'||cursor=='q')
			{
				if(cursor=='q')
					break;
				if(cursor=='a')
				{
					x_ax=x_ax-4;
					row_re=row_re-1;
					row_ret=row_re;
					col_ret=col_re;
					if((x_ax<=54)&&(x_ax>=24)&&(y_ax<=16)&&(y_ax>=0))
					{
						gotoxy(x_ax,y_ax);
						cursor=getch();
						if(cursor==13)
						{
							re[8][6]=insert(re,row_ret,col_ret,x_ax,flag);
							cursor=check(re);
							flag=1;
						}
					}
				}
				if(cursor=='d')
				{
					x_ax=x_ax+4;
					row_re=row_re+1;
					row_ret=row_re;
					col_ret=col_re;
					if((x_ax<=54)&&(x_ax>=24)&&(y_ax<=16)&&(y_ax>=0))
					{
						gotoxy(x_ax,y_ax);
						cursor=getch();
						if(cursor==13)
						{
							re[8][6]=insert(re,row_ret,col_ret,x_ax,flag);
							cursor=check(re);
							flag=1;
						}
					}
				}
			}
			if(cursor=='q')
			{
			getch();
			break;
			}
			if(flag==2)
			{
				cursor='\0';
				cursor=getch();
			}
		}
	}
	if(ch=='2')
	{
		system("cls");
		border();

		SetColor(0);
		gotoxy(18,4); printf(" @@@  @@@  @   @ @@@@@ @@@   @@@  @    @@@");
		gotoxy(18,5); printf("@    @   @ @@  @   @   @  @ @   @ @   @    ") ;
		gotoxy(18,6); printf("@    @   @ @ @ @   @   @@@  @   @ @    @@@ ")  ;
		gotoxy(18,7); printf("@    @   @ @  @@   @   @ @  @   @ @       @")   ;
		gotoxy(18,8); printf(" @@@  @@@  @   @   @   @  @  @@@  @@@@ @@@ ")    ;
		gotoxy(18,9); printf("-------------------------------------------")     ;
		SetColor(61);
		gotoxy(32,13);printf("CURSOR CONTROLS");
		gotoxy(32,14);printf("---------------");
		gotoxy(20,16);printf("TO MOVE LEFT ..................PRESS a" ) ;
		gotoxy(20,17);printf("TO MOVE RIGHT..................PRESS d" )  ;
		gotoxy(20,19);printf("         PRESS ENTER TO INSERT        " );
		gotoxy(20,21);printf("     PRESS Q TWICE TO EXIT THE GAME   " );
		getch();
	}
	if(ch=='3')
	{
		system("cls");
		border();

		SetColor(0);
		gotoxy(18,4); printf("@@@  @   @ @    @@@@  @@@ ");
		gotoxy(18,5); printf("@  @ @   @ @    @    @    ");
		gotoxy(18,6); printf("@@@  @   @ @    @@@   @@@ ");
		gotoxy(18,7); printf("@ @  @   @ @    @       @");
		gotoxy(18,8); printf("@  @  @ @  @@@@ @@@@ @@@ ");
		gotoxy(18,9); printf("--------------------------");
		getch();


	}
	if(ch=='0')
	{
		system("cls");
		border();

		SetColor(0);
		gotoxy(20,4); printf(" @   @   @   @@@   @@@@     @@@  @   @   ");
		gotoxy(20,5); printf(" @@ @@  @ @  @  @  @        @  @  @ @  @ ") ;
		gotoxy(20,6); printf(" @ @ @ @@@@@ @   @ @@       @@@    @    ")  ;
		gotoxy(20,7); printf(" @   @ @   @ @  @  @        @  @   @   @  ")   ;
		gotoxy(20,8); printf(" @   @ @   @ @@@   @@@@     @@@    @    ")    ;
		gotoxy(20,9); printf("**************************************")     ;

		gotoxy(20,17);printf("  @@@    @   @   @  @@@ @  @ @@@ @@@@@ ");
		gotoxy(20,18);printf(" @      @ @  @@  @ @    @  @  @    @   " ) ;
		gotoxy(20,19);printf("  @@@  @@@@@ @ @ @ @    @@@@  @    @   " )  ;
		gotoxy(20,20);printf("     @ @   @ @  @@ @    @  @  @    @   " );
		gotoxy(20,21);printf("  @@@  @   @ @   @  @@@ @  @ @@@   @   " );
		gotoxy(20,22);printf("***************************************");
		getch();
		getch();
		exit(0);
	}
	else
		goto start;
 }
 getch();
}

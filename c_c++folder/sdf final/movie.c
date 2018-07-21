#include<stdio.h>
#include<conio.h>
#include<windows.h>

COORD coord={0,0}; // this is global variable  //center of axis is set to the top left cornor of the screen

struct details
{
    char c_name[50],phn_no[10];
    int no_t,mov_cd,book_id;
    int chairs[2][10];
};
struct movie
{
    char m_name[50];
    int mv_cd,c_o_t,tno_s,s_rev;
    int seat[11][20];
};
struct node
{
    int b_id;
    struct node *next;
};

void gotoxy(int x,int y);                       //for positioning of cursor
void SetColor(int ForgC);                       //for setting color
void seats(int n,int code,int id);              //displays the seating arrangements
void mov(int n,int code,int id);                //movement of the cursor and book the required seats
void box();                                     //displaying the outer border
void mscr();                                    //displays the details of movies on the get data scree
void getdet();                                  //accepting details
void reset_data();                              //to reset all the files and enter the new movies
void canc_tics();                               //cancel already booked tickets
void check_det();                               //check the details of the booked tickets
void waitlist(int id,int num,int code);         //put member in the waiting list
struct node *enque(int x,struct node *rear);                        //enque
struct node *deque(int *x,struct node *front,struct node *rear);    //deque
void allot(int id,int a,int b);                 //allot the seats to the waiting list members

void main()
{
    char opt;
    int ch=1;
    while(ch==1)
    {
        system("cls");
        SetColor(15);
        box();
        gotoxy(72,3) ;printf("WELCOME TO SHOW BOX");
        gotoxy(71,4) ;printf("---------------------");
        gotoxy(77,6) ;printf("MAIN MENU");
        gotoxy(50,10);printf("BOOK TICKETS");
        gotoxy(50,11);printf("CANCEL TICKETS");
        gotoxy(50,12);printf("CHECK BOOKING DETAILS");
        gotoxy(50,13);printf("CHANGE MOVIES");
        gotoxy(50,14);printf("EXIT");

        gotoxy(100,10);printf("1");
        gotoxy(100,11);printf("2");
        gotoxy(100,12);printf("3");
        gotoxy(100,13);printf("4");
        gotoxy(100,14);printf("5");

        gotoxy(62,17);printf("ENTER YOUR OPTION :         ");
        scanf("%c",&opt);
        switch(opt)
        {
            case '1': getdet();
                break;
            case '2': canc_tics();
                break;
            case '3': check_det();
                break;
            case '4': reset_data();
                break;
            case '5': ch=0;
                break;
            default : //wrong input
                break;
         }
         getch();
    }
    //mscr();
    //seats(1,1);
    //waitlist(5,5,1);
    //allot(1,2);

}

void gotoxy(int x,int y)                    //to position the pointer
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC)                    //to set color
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

void seats(int n,int code,int id)           //displays the seating arrangement
{
    system("cls");
    struct movie m2;
    int i=0,j=0,z=0,x;
    int seats_a[11][20];
    char a;

    FILE *f2;
    f2 = fopen("movies.dat", "rb");
    fseek(f2,(sizeof(m2)*(code-1)),SEEK_SET);          //moves the pointer to the start of the record of the codeth movie
    fread(&m2, sizeof(m2), 1, f2);                     //stores the details of the required movie in the structure m2
    fclose(f2);

    box();                                             //displays border

    for(j=0;j<11;j++)                                  //displays the seats booked in blue and empty in white
    {
        gotoxy(25,4+(2*j));
        printf("%c - ",(j+65));
        for(i=0;i<20;i++)
        {
            if(m2.seat[j][i]==0)            //unreserved seats
            {
                SetColor(15);               //white
            }
            else if(m2.seat[j][i]==1)       //reserved seats
            {
                SetColor(9);                //blue
            }
            printf("|%2d| ",i+1);
            if(i==9)
            {
                SetColor(15);
                printf("%c -- %c ",j+65,j+65);
            }
        }
        SetColor(15);
        printf("- %c\n\n",j+65);
    }
    gotoxy(18,3);  SetColor(12);printf("|EXIT|");
    gotoxy(18,25); SetColor(12);printf("|EXIT|");
    gotoxy(140,3); SetColor(12);printf("|EXIT|");
    gotoxy(140,25);SetColor(12);printf("|EXIT|");
    gotoxy(68,27); SetColor(15);printf("<---- SCREEN THIS SIDE ---->");
    gotoxy(60,29);              printf("MOVIE CODE : %d",m2.mv_cd);
    gotoxy(87,29);              printf("MOVIE NAME : %s",m2.m_name);

//-----------------displays controls to book seats---------------------
    gotoxy(28,34);printf("PRESS->  A: TO MOVE LEFT    D: TO MOVE RIGHT   W: TO MOVE UP");
                  printf("   S: TO MOVE DOWN   SPACEBAR: TO SELECT THE SEAT");

    gotoxy(25,32);printf("%c",218);             //border for the controls
    for(i=0;i<113;i++)
        {gotoxy(26+i,32);printf("%c",196);}
    gotoxy(138,32);printf("%c",191);
    for(i=0;i<3;i++)
        {gotoxy(25,33+i); printf("%c",179);
         gotoxy(138,33+i);printf("%c",179);}
    for(i=0;i<113;i++)
        {gotoxy(26+i,36);printf("%c",196);}
    gotoxy(138,36);printf("%c",217);
    gotoxy(25,36); printf("%c",192);
//----------------------------------------------------------------
    mov(n,code,id);                         //
}

void box()                                  //displays the outer box
{
    int i=0;
    gotoxy(16,1); printf("%c",201);         // upper horizontal
    for(i=0;i<130;i++)
        printf("%c",205);
    printf("%c",187);

    gotoxy(16,30);printf("%c",200);         //lower horizontal
    for(i=0;i<130;i++)
        printf("%c",205);
    printf("%c",188);

    for(i=1;i<29;i++)                       //vertical lines
    {
        gotoxy(16,1+i); printf("%c",186);
        gotoxy(147,1+i);printf("%c",186);
    }
}

void mov(int n,int code,int id)             //movement of the cursor and book the required seats
{

    int arr[11][20],i=0,j=0,ctr=0;
    struct movie m3;
    struct details d1;
    int count=1,flag=0,x=0,y=0;
    char a;

    FILE *f1;
    f1 = fopen("details.dat","rb+");
    fseek(f1,(sizeof(d1)*(id-1)),SEEK_SET);             //moves the pointer to the start of the idth record
    fread(&d1, sizeof(d1), 1, f1);

    FILE *f2;
    f2 = fopen("movies.dat", "rb+");
    fseek(f2,(sizeof(m3)*(code-1)),SEEK_SET);           //moves the pointer to the start of the codeth movie record
    fread(&m3, sizeof(m3), 1, f2);

    int k=0;
    while(count<=n)                                     // no of tickets booked is less than no of tickets req.
    {
        gotoxy(0,0);
        printf("   ");
        a=getch();              //takes input for movement of cursor
        if(flag!=1)             //if seat is not reserved change to seat to appropriate color
        {
            gotoxy(x,y);
            if(m3.seat[j][i]==0)        //if unreserved
                SetColor(15);           //white
            else if(arr[j][i]==1)       //if already reserved recently reserved
                SetColor(12);           //red
            else                        //if already reserved
                SetColor(9);            //blue
            printf("|%2d|",i+1);
        }
        switch(a)
        {
            case 'a':               //moves the cursor left
            case 'A':
                if(i>0)             //so that cursor doesn't move out or matrice
                {
                    i--;
                    flag=0;
                }
                break;
            case 'd':               //moves the cursor right
            case 'D':
                if(i<19)            //so that cursor doesn't move out of matrice
                {
                    i++;
                    flag=0;
                }
                break;
            case 'w':               //moves the cursor up
            case 'W':
                if(j>0)             //so that cursor doesn't move out of the matrice
                {
                    j--;
                    flag=0;
                }
                break;
            case 's':               //moves the cursor down
            case 'S':
                if(j<10)            //so that cursor doesn't move out of the matrice
                {
                    j++;
                    flag=0;
                }
                break;
            case ' ':               //for selection of the seat
                if(m3.seat[j][i]==0)//check if the seat is already reserved
                {
                    count++;        //increment no. of seats booked
                    flag=1;
                    m3.seat[j][i]=1;//change status of seat to booked
                    arr[j][i]=1;
                    d1.chairs[0][k]=j;//store the seat no in details
                    d1.chairs[1][k]=i;
                    k++;
                    m3.s_rev++;      //increase the no. of seats reserved
                }
                break;
            default :;
        }
        x=29+(i*5);                 //position the x co-ordinate
        y=4+(j*2);                  //position the y co-ordinate
        if(i>=10)
        {
            x=x+7;
        }
        gotoxy(x,y);                //move the cursor to the right position
        SetColor(12);
        printf("|%2d|",i+1);        //display the seat on which the cursor is present
    }

    fseek(f2,-sizeof(m3),SEEK_CUR);         //moves the pointer to the start of the current record
    fwrite(&m3, sizeof(m3), 1, f2);         //overwrites the record with the the edited details
    fclose(f2);

    fseek(f1,-sizeof(d1),SEEK_CUR);         //move the pointer to the start of the current record
    fwrite(&d1, sizeof(d1), 1, f1);         //overwrites the record with new details
    fclose(f1);

    gotoxy(40,40);                          //moves to pointer to the position out of the layout
}

void mscr()                                 //displays the details of movies on the get data screen
{
    int i=0;
    struct movie m1;
    box();                                  //display the outer box
    gotoxy(72,3);printf("WELCOME TO SHOW BOX");
    gotoxy(71,4);printf("---------------------");
    FILE *fm;
    fm=fopen("movies.dat","rb");
    gotoxy(40,7);printf("MOVIE NAME");
    gotoxy(60,7);printf("COST OF TICKET");
    gotoxy(85,7);printf("MOVIE CODE");
    gotoxy(105,7);printf("NO. OF SEATS LEFT");
    for(i=0;i<5;i++)
    {
       fread(&m1,sizeof(m1),1,fm);
       gotoxy(40,10+i);printf("%s",m1.m_name);
       gotoxy(65,10+i);printf("%d",m1.c_o_t);
       gotoxy(90,10+i);printf("%d",m1.mv_cd);
       gotoxy(110,10+i);printf("%d/%d",(m1.tno_s-m1.s_rev),m1.tno_s);
    }
    fclose(fm);
//------------------small box-----------------------------------
    gotoxy(25,6);printf("%c",218);
    for(i=0;i<110;i++)
        {gotoxy(26+i,6);printf("%c",196);}
    gotoxy(135,6);printf("%c",191);
    for(i=0;i<9;i++)
        {gotoxy(25,7+i);printf("%c",179);
         gotoxy(135,7+i);printf("%c",179);}
    gotoxy(25,16);printf("%c",192);
    for(i=0;i<110;i++)
        {gotoxy(26+i,16);printf("%c",196);}
    gotoxy(135,16);printf("%c",217);
//------------------box ends-------------------------------

}

void getdet()                               //accepting details
{
    struct details d1,d2;
    struct movie m3;
    char ans='N';
    int check=1,i=0;
    while(ans=='N'||ans=='n')              //accepts details after checking all the details
    {
        system("cls");
        mscr();                            //displays the details of all movies
        fflush(stdin);
        gotoxy(40,18);printf("ENTER THE FOLLOWING DETAILS : ");
        gotoxy(40,20);printf("NAME");gotoxy(68,20);printf(":");
        gotoxy(40,21);printf("PHONE NUMBER");gotoxy(68,21);printf(":");
        gotoxy(40,22);printf("MOVIE CODE");gotoxy(68,22);printf(":");
        gotoxy(40,23);printf("NUMBER OF TICKET");gotoxy(68,23);printf(":");

        gotoxy(73,20);gets(d1.c_name);   //accepts name
        for(i=0;i<strlen(d1.c_name);i++) //change the case of each letter to upper
        {
            d1.c_name[i]=toupper(d1.c_name[i]);
        }

        check=1;
        while(check==1)                  //accepts the phn no. & check if its 10-digits
        {
            gotoxy(73,21);gets(d1.phn_no);
            if(strlen(d1.phn_no)==10)
            {
                check=0;
                gotoxy(90,21);printf("                               ");
                break;
            }
            gotoxy(73,21);printf("                   ");
            gotoxy(90,21);printf("PLEASE ENTER A 10-DIGIT NUMBER");
        }

        check=1;
        while(check==1)                 //accepts the movie code b/w 1&5
        {
            gotoxy(73,22);scanf("%d",&d1.mov_cd);
            if(d1.mov_cd==1||d1.mov_cd==2||d1.mov_cd==3||d1.mov_cd==4||d1.mov_cd==5)
            {
                check=0;
                gotoxy(95,22);printf("                                          ");
                break;
            }
            gotoxy(73,22);printf("      ");
            gotoxy(95,22);printf("PLEASE INPUT A VALID MOVIE CODE");

        }
        check=1;

        while(check==1)                 //accepts no. tickets to be booked not more the 10
        {
            gotoxy(73,23);scanf("%d",&d1.no_t);
            if(d1.no_t<=10&&d1.no_t>0)
            {
                check=0;
                gotoxy(95,23);printf("                                                   ");
                break;
            }
            gotoxy(73,23);printf("      ");
            gotoxy(95,23);printf("YOU CAN NOT BOOK MORE THAN 10 TICKETS AT A TIME");

        }
        check=1;

        gotoxy(40,18);printf("PLEASE CONFIRM YOUR DETAIS  :");      //confirms the details
        gotoxy(73,20);puts(d1.c_name);                              //displays all the details accepted
        gotoxy(73,21);puts(d1.phn_no);
        gotoxy(73,22);printf("%d",d1.mov_cd);
        gotoxy(73,23);printf("%d",d1.no_t);
        fflush(stdin);
        gotoxy(40,25);printf("ARE YOUR DETAILS CORRECT (Y/N) : ");
        scanf("%c",&ans);
        ans=toupper(ans);
    }
    for(i=0;i<10;i++)               //set the seats to be -1 -1 (no seats)  in details
    {
        d1.chairs[0][i]=-1;
        d1.chairs[1][i]=-1;
    }

    fflush(stdin);
    long size;
    FILE *f1;
    f1 = fopen("details.dat", "rb");
    fseek (f1, 0, SEEK_END);
    size=ftell(f1);
    if(size==0)                     //to check if any record already present if not give booking id=1
    {
            d1.book_id=1;
    }
    else                                 //give booking id=(booking id of previous record +1)
    {
        fseek(f1, -sizeof(d2), SEEK_END);//move the cursor to start of last record
        fread(&d2, sizeof(d2),1,f1);
        d1.book_id=d2.book_id+1;
    }
    fclose(f1);
    gotoxy(40,26);printf("YOUR BOOKING ID IS : %d",d1.book_id);
    getch();
    FILE *f3;
    f3 = fopen("details.dat", "ab");     //write the details in details.dat file
    fwrite(&d1, sizeof(d1), 1, f3);
    fclose(f3);

//--------------to check the availability-----------------------------------
    FILE *f2;
    f2 = fopen("movies.dat", "rb");
    fseek(f2,(sizeof(m3)*(d1.mov_cd-1)),SEEK_SET);           //moves the pointer to the start of the codeth movie record
    fread(&m3, sizeof(m3), 1, f2);
    fclose(f2);

    if(m3.tno_s-m3.s_rev==0)                                 //if not available put the record in wait list
    {
        //wait list
        printf("seats not available");
        waitlist(d1.book_id,d1.no_t,d1.mov_cd);
    }
    else                //if available book tickets ;
    {
        seats(d1.no_t,d1.mov_cd,d1.book_id);
    }
    //-----------------------------------------------------------
}

void reset_data()                           //to reset all the files and enter the new movies
{
    system("cls");
    struct movie m1,m2;
    int i=0,k=0,j=0;
    char ans='n';
    FILE *f1,*f2;
    fflush(stdin);
    printf("do you want to reset every thing : ");
    scanf("%c",&ans);
    if(ans=='y'||ans=='Y')
    {
        f1=fopen("movies.dat","wb");
        for(k=0;k<5;k++)
        {
            ans='n';
            fflush(stdin);
            printf("enter the movie name ");
            gets(m1.m_name);
            printf("enter the cost of ticket ");
            scanf("%d",&m1.c_o_t);
            m1.mv_cd=(k+1);
            printf("movie code is %d \n",m1.mv_cd);
            fflush(stdin);

            m1.tno_s=220;
            m1.s_rev=0;
            for(i=0;i<11;i++)
            {
                for(j=0;j<20;j++)
                {
                    m1.seat[i][j]=0;
                }
            }
            fwrite(&m1,sizeof(m1),1,f1);
            fflush(stdin);
        }
        fclose(f1);

        FILE *f1;                           //clears the details in details.dat file
        f1 = fopen("details.dat", "wb");
        fclose(f1);
        f1 = fopen("mov1.dat","wb");        //clears wait list for movie 1
        fclose(f1);
        f1 = fopen("mov2.dat","wb");        //clears wait list for movie 2
        fclose(f1);
        f1 = fopen("mov3.dat","wb");        //clears wait list for movie 3
        fclose(f1);
        f1 = fopen("mov4.dat","wb");        //clears wait list for movie 4
        fclose(f1);
        f1 = fopen("mov5.dat","wb");        //clears wait list for movie 5
        fclose(f1);
    }

    f2=fopen("movies.dat","rb");            //display the details entered just now
    for(k=0;k<5;k++)
    {
       fread(&m2,sizeof(m2),1,f2);
       printf("\n movie name:");
       puts(m2.m_name);
       printf("\n cost of ticket:%d \n ",m2.c_o_t);
       printf("movie code : %d \n",m2.mv_cd);
       printf("total no of seats:%d\n",m2.tno_s);
       printf("no. of seats reserved:%d\n",m2.s_rev);
       for(i=0;i<11;i++)
       {
           for(j=0;j<20;j++)
            {
                printf("%d",m2.seat[i][j]);
            }
           printf("\n");
       }
    }
    fclose(f2);
}

void canc_tics()                            //cancel already booked tickets
{
    system("cls");
    int id,i=0;
    char ans='n';
    struct details d1;
    struct movie m1;

    printf("ENTER THE BOOKING ID : ");          //accepts the booking id whose tics have to be canceled
    scanf("%d",&id);

    FILE *fd,*fm;
    fd=fopen("details.dat","rb+");              //open the details of booking id
    fseek(fd,(sizeof(d1)*(id-1)),SEEK_SET);
    fread(&d1, sizeof(d1), 1, fd);
    //fclose(fd);

    fm=fopen("movies.dat","rb+");               //open details of the movie whose tics have to be deleted
    fseek(fm,(sizeof(m1)*(d1.mov_cd-1)),SEEK_SET);
    fread(&m1, sizeof(m1), 1, fm);
    //fclose(fm);

    fflush(stdin);

    printf("\n\n");                               //display the details of the id
    printf("NAME              : ");puts(d1.c_name);
    printf("PHONE NO.         : ");puts(d1.phn_no);
    printf("MOVIE CODE        : ");printf("%d\n",m1.mv_cd);
    printf("NO. OF TICKETS    : ");printf("%d\n",d1.no_t);
    printf("BOOKING ID        : ");printf("%d\n",d1.book_id);
    printf("NAME OF THE MOVIE : ");printf("%s\n",m1.m_name);
    printf("SEATS      : ");

    i=0;
    int kur[2][10];
    while(i<10)                                    //display already booked seats & save the seat no to be deleted in kur[][]
    {
        if(d1.chairs[0][i]==-1)
        {
           //no seats booked
        }
        else if(d1.chairs[0][i]==-2)
        {
            //printf(" W%d ",d1.chairs[1][i]);
            //call check wl function (to be made) and break
        }
        else
        {
           kur[0][i]=d1.chairs[0][i];              //save details of the seats to be deleted in kur
           kur[1][i]=d1.chairs[1][i];
           printf(" %C%d ",d1.chairs[0][i]+65,d1.chairs[1][i]+1);
        }
        i++;
    }

    printf("\n\n DO YOU WANT TO CANNCEL THIS TICKET(Y/N) : ");
    scanf("%c",&ans);
    if(ans='y'||ans=='Y')
    {

        int code=m1.mv_cd;
//--------------------import the waiting list of the movie to be canceled-------------------------------
        int x=0;
        FILE *f3;
        struct node *front,*rear,*ptr;
        switch(code)
        {
            case 1 : f3=fopen("mov1.dat","rb+");
                break;
            case 2 : f3=fopen("mov2.dat","rb+");
                break;
            case 3 : f3=fopen("mov3.dat","rb+");
                break;
            case 4 : f3=fopen("mov4.dat","rb+");
                break;
            case 5 : f3=fopen("mov5.dat","rb+");
                break;
            default: ;//wrong input
        }

        if(f3==NULL)            //check if the file opens properly
        {
            printf(" not ok");
        }

        front=NULL;               //initializing the new queue for the wait list
        rear=NULL;
        int a=0,b=0;
        if(fread(&x, sizeof(x), 1, f3)!=1)
        {
            //no one in the waiting list
            //change the status of the booked seats to be -1,-1 again
            i=0;
            while(i<10)
            {
                if(d1.chairs[0][i]==-1)
                {
                    //no seats booked
                }
                else if(d1.chairs[0][i]==-2)
                {
                    //printf(" W%d ",d1.chairs[1][i]);
                }
                else
                {
                    a=d1.chairs[0][i];
                    b=d1.chairs[1][i];
                    m1.seat[a][b]=0;                    //change the status to 0 i.e empty
                    d1.chairs[0][i]=-1;                 // change the status of the seats to be -1,-1
                    d1.chairs[1][i]=-1;
                }
                i++;

            }
            m1.s_rev=m1.s_rev-d1.no_t;                  //reduce the no of  seats reserved
            d1.no_t=0;
        }
        else                //allot the unreserved seats to the waiting members
        {
            int count=1;
            fseek(f3,0,SEEK_SET);
            while(fread(&x, sizeof(x), 1, f3)==1)       //accept the wait list in the queue
            {
                count++;
                rear=enque(x,rear);
                if(front==NULL)
                {
                    front=rear;
                }
            }
            fclose(f3);
//------------------------------------------------------------------------

            int a=0,b=0;
            i=0;
            while(i<10)
            {
                if(d1.chairs[0][i]==-1)
                {
                    // no seats booked
                }
                else if(d1.chairs[0][i]==-2)
                {
                    //printf(" W%d ",d1.chairs[1][i]);
                }
                else
                {
                    a=d1.chairs[0][i];
                    b=d1.chairs[1][i];
                    m1.seat[a][b]=0;
                    d1.chairs[0][i]=-1;                 // change the status of the seats to be -1,-1
                    d1.chairs[1][i]=-1;
                }
                i++;
            }
            //-----------deque n.o.t times
            int d_id=0;
            for(i=0;i<d1.no_t;i++)
            {
                front = deque(&d_id,front,rear);
                if(front=NULL)                      //QUEUE IS EMPTY
                {
                    rear=NULL;
                }
                allot(d_id,kur[0][i],kur[1][i]);        //allot kur[][i] to the d_id

            }
            switch(code)                                    //to overwrite the waitinglist
            {
                case 1 : f3=fopen("mov1.dat","wb");
                    break;
                case 2 : f3=fopen("mov2.dat","wb");
                    break;
                case 3 : f3=fopen("mov3.dat","wb");
                    break;
                case 4 : f3=fopen("mov4.dat","wb");
                    break;
                case 5 : f3=fopen("mov5.dat","wb");
                    break;
                default: ;//wrong input
            }
            ptr=front;
            while(ptr->next!=NULL)
            {
                a=ptr->b_id;
                fwrite(&a,sizeof(a),1,f3);
            }
            fclose(f3);


        }

        fseek(fd,-(sizeof(d1)),SEEK_CUR);               //overwrite the details of the customer
        fwrite(&d1, sizeof(d1), 1, fd);
        fclose(fd);

        fseek(fm,-(sizeof(m1)),SEEK_CUR);               //overwrite the details of the movie
        fwrite(&m1, sizeof(m1), 1, fm);
        fclose(fm);



    }
    printf("\nTICKETS HAVE BEEN CANCLED");
    getch();
}

void check_det()
{
    system("cls");

    int id,i=0;
    struct details d1;
    struct movie m1;

    printf("ENTER THE BOOKING ID : ");
    scanf("%d",&id);
    FILE *f1,*f2;

    f1=fopen("details.dat","rb+");
    fseek(f1,(sizeof(d1)*(id-1)),SEEK_SET);
    fread(&d1, sizeof(d1), 1, f1);
    int q=d1.mov_cd;

    f2=fopen("movies.dat","rb+");
    fseek(f2,(sizeof(m1)*(q-1)),SEEK_SET);
    fread(&m1, sizeof(m1), 1, f2);
    fflush(stdin);

     printf("\n\n");
     printf("NAME              : ");puts(d1.c_name);
     printf("PHONE NO.         : ");puts(d1.phn_no);
     printf("MOVIE CODE        : ");printf("%d\n",m1.mv_cd);
     printf("NO. OF TICKETS    : ");printf("%d\n",d1.no_t);
     printf("BOOKING ID        : ");printf("%d\n",d1.book_id);
     printf("NAME OF THE MOVIE : ");puts(m1.m_name);
     printf("SEATS             : ");i=0;
     i=0;
     while(i<10)
     {
         if(d1.chairs[0][i]==-1)
         {

         }
         else if(d1.chairs[0][i]==-2)           //if waiting print w
         {
             printf(" W ");
         }
         else                                   //nahi toh seat no.
         {
         printf(" %C%d ",d1.chairs[0][i]+65,d1.chairs[1][i]+1);
         }
         i++;
     }
     fclose(f1);
     fclose(f2);
}

void waitlist(int id,int num,int code)              //add members to the waitlist if house full
{
    system("cls");
    int count=1;
    char ans='y';
    printf("SEATS ARE NOT AVAILABLE \nDO YOU WANT TO BOOK TICKETS IN THE WAITLIST");
    scanf("%c",&ans);
    if(ans=='y'||ans=='Y')
    {
        //enque the booking id number of tickets times
        int x=0,a=0;
        struct node *front,*rear,*ptr;
        FILE *f1;
        switch(code)                  //open the file whose tics have to be waitlisted
        {
            case 1 : f1=fopen("mov1.dat","rb+");
                break;
            case 2 : f1=fopen("mov2.dat","rb+");
                break;
            case 3 : f1=fopen("mov3.dat","rb+");
                break;
            case 4 : f1=fopen("mov4.dat","rb+");
                break;
            case 5 : f1=fopen("mov5.dat","rb+");
                break;
            default: ;//wrong input
        }
        if(f1==NULL)
        {
            printf("ok");
        }

        front=NULL;         //initialize a new queue for storing the waitlist
        rear=NULL;

        /*if(fread(&x, sizeof(x), 1, f1)!=1)
            printf("file empty");
        else
            printf("file exist");*/


        count=1;
        while(fread(&x, sizeof(x), 1, f1)==1)
        {
            count++;
            rear=enque(x,rear);
            if(front==NULL)
            {
                front=rear;
            }
        }
        int i=0;
        for(i=0;i<num;i++)
        {
            count++;
            rear=enque(id,rear);
            if(front==NULL)
            {
                front=rear;
            }
        }

        fseek(f1,0,SEEK_SET);
        ptr=front;                  //write the queue in the file of the respective movie file
        while(ptr!=NULL)
        {
            a=ptr->b_id;
            fwrite(&a, sizeof(a), 1, f1);
            ptr=ptr->next;
        }
        fclose(f1);

        int j=0;
        FILE *fd;
        struct details d1;
        fd=fopen("details.dat","rb+");
        fseek(fd,(sizeof(d1)*(id-1)),SEEK_SET);
        fread(&d1, sizeof(d1), 1, fd);
        j=0;
        printf("\nYOUR WAITING LIST NO. ARE :");
        for(i=num;i>0;i--)              //store the waiting status to the seat no. in
        {
            d1.chairs[0][j]=-2;
            d1.chairs[1][j]=count-i;
            printf(" %d ",count-i);
            j++;
        }
        fseek(fd,(sizeof(d1)*(id-1)),SEEK_SET);
        fwrite(&d1, sizeof(d1), 1, fd);
        fclose(fd);

       // printf("%d %d",d1.chairs[0][0],d1.chairs[1][0]);
    }
    else
    {
        printf("BYE BYE");
    }

    printf("\nYOUR BOOKIG ID IS : %d",id);
}

struct node *enque(int x,struct node *rear)
{
    struct node *q = (struct node*)malloc(sizeof(struct node));
    q->b_id=x;
    q->next=NULL;
    if(rear==NULL)
    {
        rear=q;
    }
    else
    {
        rear->next = q;
        rear=rear->next;
    }
    return rear;
}

struct node *deque(int *x,struct node *front,struct node * rear)
{
    *x=front->b_id;
    if(front==rear)
    {
        front=NULL;
        rear=NULL;
    }
    else
        front=front->next;
    return front;
}

void allot(int id ,int a,int b)                 //allot the waiting details to
{
    // details of id and overwrite the the seat no.
    struct details d1;
    FILE *fz;
    fz=fopen("details.dat","rb+");
    fseek(fz,(sizeof(d1)*(id-1)),SEEK_SET);
    fread(&d1,sizeof(d1),1,fz);
    int i=0;
    for(i=0;i<10;i++)                           //allot the seat to first waiting position approached
    {
        if(d1.chairs[0][i]==-2)
        {
            d1.chairs[0][i]=a;
            d1.chairs[1][i]=b;
            break;
        }
    }
    fseek(fz,(-sizeof(d1)*1),SEEK_CUR);
    fwrite(&d1,sizeof(d1),1,fz);
    fclose(fz);
}

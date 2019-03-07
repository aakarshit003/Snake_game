#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
struct food
{
    int x,y;
};
struct poison
{
    int x,y;
};
struct snake
{
    int x,y;
    char val;
    snake *next;
};
void create_food(food *f,char b[25][60])
{
    f->x=(rand()%23)+1;
    f->y=(rand()%55)+1;
    b[f->x][f->y]='F';
}
void create_poison(poison *p,char b[25][60])
{
    p->x=(rand()%20)+1;
    p->y=(rand()%58)+1;
    b[p->x][p->y]='P';
}
snake *head=NULL;
class snake_game
{
public:
    snake *create(char c)
    {
        snake *ptr=new snake;
        ptr->val=c;
        ptr->next=NULL;
        return ptr;
    }

    void create_snake(char ch)
    {
        snake *temp,*t;
        temp=create(ch);
        if(head==NULL)
            head=temp;
        else
        {
            t=head;
            while(t->next!=NULL)
            {
                t=t->next;
            }
            t->next=temp;
            temp->next=NULL;
        }
    }
    void insert_in_snake(char g)
    {
        snake *te=create(g);
        snake *prev=head;
        snake *t1=head;
        while( t1->next != NULL )
        {
            if( t1->val == '#')
                break;
            prev = t1;
            t1=t1->next;
        }
        prev->next=te;
        te->next=t1;
    }
    void delete_in_snake(char g1)
    {
        snake *h1=head;
        snake *prev=head;
        while(h1->next!=NULL)
        {
            if( h1->val == '#' )
                break;
            prev=h1;
            h1=h1->next;
        }
        prev->next=h1->next;
        delete h1;
    }
};
void print_score( char b[25][60], int score)
{
    char ch[20] = "SCORE IS";
    int k=0;
    for( int i=0; i<25; i++)
    {
        for(int j=0; j<60; j++)
        {
            if( i == 8 && (25 <= j && j<=32 ))
            {
                b[i][j]=ch[k++];
                cout<<b[i][j];
            }
            else if( i == 9 && j == 29)
                cout<<score;
            else if(i==0 || i==24 || j==0 || j==59)
                cout<<"*";
            else
                cout<<" ";

        }
        cout<<endl;
    }
}
void print_board(char b[25][60],int counter,char dir,int xh,int yh,int xt,int yt)
{
    snake *h1=head;
    snake *h2=h1->next;
    snake *nh=head;
    while(nh->next!=NULL)
    {
        nh=nh->next;             // nh points to the tail of the snake.
    }

    for(int i=0; i<25; i++)
    {
        for(int j=0; j<60; j++)
        {
            if(i==xh && j==yh && b[i][j]=='v')
            {
                cout<<h1->val;
            }
            else if(i==xt && j==yt && b[i][j]=='v')
                cout<<nh->val;
            else if(b[i][j]=='v')
            {
                cout<<h2->val;
                h2=h2->next;
            }
            else
                cout<<b[i][j];
        }
        cout<<endl;
    }
}
void move_snake(char b[25][60],int xh,int yh,int counter,int xt,int yt,char dir,int score,snake_game s,food *f,poison *p)
{
    char m,c1;
    int q=1;
    while(q)
    {
        if(counter == 2)
        {
            print_score( b,score );
            break;
        }
        else if( xh == 0 || xh == 24 || yh == 0 || yh == 59)
        {
            print_score(b,score);
            break;
        }
        cin>>m;
        c1=dir;
        cout<<"\x1b[2J\x1b[1;1H"<<flush;
        if(m=='w')
        {
            dir='u';
            b[xh-1][yh]='v';
            b[xt][yt]=' ';
            if( xh-1 < xt && (yh < yt || yh==yt))   //for left movements
            {
                if(b[xt][yt-1]!=' ')
                {
                    xh--;
                    yt--;
                }
                else
                {
                    xt--;
                    xh--;
                }
            }
            else if( xh-1 < xt && (yh > yt))   // for right movements
            {
                if(b[xt][yt+1]!=' ')
                {
                    xh--;
                    yt++;
                }
                else
                {
                    xt--;
                    xh--;
                }
            }
           /* else if( xh-1 < xt)
            {
                if( b[xt][yt-1] != ' ')
                {
                    xh--;
                    yt--;
                }
                else
                {
                    xh--;
                    xt--;
                }
            }*/
            if( xh == f->x && yh == f->y )   // for food
            {
                score++;
                counter++;
                s.insert_in_snake('#');
                b[xh-1][yh] = 'v';
                xh--;
                counter++;
                create_food(f,b);
            }
            if( xh == p->x && yh == p->y)   //  for poison
            {
                score--;
                counter--;
                s.delete_in_snake('#');
                b[xt][yt] = ' ';
                if( b[xt][yt-1] != ' ')
                    yt--;
                else
                    xt--;
                create_poison(p,b);
            }
            print_board(b,counter,dir,xh,yh,xt,yt);
        }
        else if(m=='a')
        {
            dir='l';
            b[xh][yh-1]='v';
            b[xt][yt]=' ';
            if(xh == xt && yh-1 < yt-1)  // For simple movements.
            {
                yh--;
                yt--;                                     //__
            }                                              //|
            else if(xh < xt)  // For movement like           |_____
            {
                if( b[xt][yt-1] != ' ')
                {
                    yh--;
                    yt--;
                }
                else
                {
                    yh--;
                    xt--;
                }
            }
            else if( xh > xt )
            {
                if( b[xt][yt-1] != ' ')
                {
                    yt--;
                    yh--;
                }
                else
                {
                    yh--;
                    xt++;
                }
            }
            if( xh == f->x && yh == f->y )   // for food
            {
                score++;
                counter++;
                s.insert_in_snake('#');
                b[xh][yh-1] = 'v';
                yh--;
                create_food(f,b);
            }
            if( xh == p->x && yh == p->y)   //for poison
            {
                score--;
                counter--;
               // cout<<"counter is:"<<counter;
                b[xt][yt]= ' ';
                s.delete_in_snake('#');
                if( b[xt][yt-1] != ' ')
                    yt--;
                else
                    xt--;
                create_poison(p,b);
            }
            print_board(b,counter,dir,xh,yh,xt,yt);
        }
        else if(m=='s')
        {
            dir='b';
            b[xh+1][yh]='v';
            b[xt][yt]=' ';
            if( xh+1 > xt && (yh < yt || yh==yt))
            {
                if( b[xt][yt-1] != ' ')
                {
                    xh++;
                    yt--;
                }
                else
                {
                    xh++;
                    xt++;
                }
            }
            else  if( xh+1 > xt && yh > yt )
            {
                if( b[xt][yt+1] != ' ')
                {
                    xh++;
                    yt++;
                }
                else
                {
                    xh++;
                    xt++;
                }
            }
            else if( xh+1 > yh)
            {
                if( b[xt][yt-1] != ' ')
                {
                    xh++;
                    yt--;
                }
                else
                {
                    xh++;
                    xt++;
                }
            }
            if( xh == f->x && yh == f->y )   // for food
            {
                score++;
                counter++;
                s.insert_in_snake('#');
                b[xh+1][yh] = 'v';
                xh++;
                create_food(f,b);
            }
            if( xh == p->x && yh == p->y)   // for poison
            {
                score--;
                counter--;
                b[xt][yt] = ' ';
                s.delete_in_snake('#');
                if( b[xt][yt+1] != ' ')
                    yt++;
                else
                    xt++;
                create_poison(p,b);
            }
            print_board(b,counter,dir,xh,yh,xt,yt);
        }
        else if(m=='d')
        {
            if(dir=='l')
            {

            }
            else
            {
                dir='r';
                b[xh][yh+1]='v';
                b[xt][yt]=' ';
                if( xh == xt && yh > yt)
                {
                    yh++;
                    yt++;
                }
                else if(xh < xt)
                {
                    if( b[xt][yt+1] != ' ')
                    {
                        yh++;
                        yt++;
                    }
                    else
                    {
                        yh++;
                        xt--;
                    }
                }
                else if( xh > xt )
                {
                    if( b[xt][yt+1] != ' ')
                    {
                        yt++;
                        yh++;
                    }
                    else
                    {
                        yh++;
                        xt++;
                    }
                }
                if( xh == f->x && yh == f->y )   // for food
                {
                    score++;
                    counter++;
                    s.insert_in_snake('#');
                    b[xh][yh+1] = 'v';
                    yh++;
                    create_food(f,b);
                }
                if( xh == p->x && yh == p->y)    //  for poison
                {
                    score--;
                    counter--;
                    cout<<"counter is:"<<counter;
                    b[xt][yt]= ' ';
                    s.delete_in_snake('#');
                    if( b[xt][yt+1] != ' ')
                        yt++;
                    else
                        xt++;
                    create_poison(p,b);
                }
                print_board(b,counter,dir,xh,yh,xt,yt);
            }
        }
        else
        {
            cout<<"Exiting"<<endl;
            q=0;
        }
    }
}
int main()
{
    snake_game s;
    int n,xh=15,yh=35,counter=5,xt=15,yt=yh+counter-1,j1=0,score=0;
    food f;
    poison p;
    char food='A',b[25][60],dir='l';
    s.create_snake('H');
    s.create_snake('#');
    s.create_snake('#');
    s.create_snake('#');
    s.create_snake('T');
    for(int i=0; i<25; i++)
    {
        for(int j=0; j<60; j++)
        {

            if(i==0 || i==24 || j==0 || j==59)
                b[i][j]='*';
            else if(i==xh && j==yh)
            {
                while(j1!=counter)
                {
                    b[i][j]='v';
                    j1++;
                    j++;
                }
                j--;
            }
            else
                b[i][j]=' ';
        }
    }
    create_food(&f,b);
    create_poison(&p,b);
    print_board(b,counter,dir,xh,yh,xt,yt);
    move_snake(b,xh,yh,counter,xt,yt,dir,score,s,&f,&p);
}


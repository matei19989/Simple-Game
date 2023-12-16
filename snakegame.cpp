#include<iostream>
#include<windows.h>
#include<conio.h>
#include <time.h>
using namespace std;
#define ll long long;
bool gameOver;
const int width=20;
const int height=20;
int x,y,fruitX,fruitY,score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{ STOP=0, LEFT , RIGHT , UP , DOWN};
eDirection dir;
void Setup(){
    ios::sync_with_stdio(false);
    gameOver = false;
    dir=STOP;
    x = width / 2;
    y = height / 2;
    fruitX= rand() % width;
    fruitY= rand() % height;
    score=0;
}
void Draw(){

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    for(int i=0; i<width+2; i++)
        cout<<"#";
    cout<<"\n!";

    for (int i=0;i<height;i++){

        for(int j=0;j<width;j++){

            if( j==0)
                cout<<"#";
             if( i==y && j==x)
                cout <<"O";
             else if( i==fruitY && j==fruitX)
                cout<<"F";
             else 
             {  
                bool print=false;
                for( int k = 0; k < nTail; k++ )
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print=true;
                    }
                }
                if(!print)
                       cout<<" ";

             }

            if(j==width-1)
             cout<<"#";
        }
    cout<<"\n!" ;
    }

    for (int i=0; i<width+2; i++)
        cout<<"#";
    cout<<"\n!";
    cout<< "Score: "<< score<<endl;

}

void Input(){
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                  dir=LEFT;
                  break;
             case 'd':
                  dir=RIGHT;
                  break;
             case 'w':
                  dir=UP;
                  break;
             case 's':
                  dir=DOWN;
                  break;
             case'x':
                  gameOver=true;
                  break;
        }
    }
}
void Logic(){
    
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y= tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;   
        default:
            break;  

    }
    // if(x > width || x < 0 || y > height || y < 0)
         // gameOver=true;
    if(x >= width)
        x=0;
    else if ( x< 0)
        x = width-1;
    if(y >= height)
        y=0;
    else if ( y< 0)
        y = height-1;
    for( int i = 0; i< nTail; i++)
        if(tailX[i] == x && tailY[i] == y)
           gameOver=true;

    if ( x == fruitX && fruitY == y )
    {
        score +=10;
        fruitX= rand() % width;
        fruitY= rand() % height;
        nTail++;
    }
}
int main(){
    srand(time(NULL));
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        if (dir == LEFT || dir == RIGHT)
        {
             Sleep(5);
        }

        Sleep(50);

        if (dir == UP || dir == DOWN)
        {
           Sleep(60);
        }
    }
}

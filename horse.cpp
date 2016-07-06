#include <iostream>
#include <queue>

using namespace std;

struct point
{
    int x;
    int y;
    point(int _x, int _y):x(_x),y(_y){}

};
void print(int**map,int size )
{
    for(int i(0);i<size;i++)
    {
        for(int j(0);j<size;j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}
bool NoNullMass(int**map,int size)
{
    for(int i(0);i<size;i++)
    {
        for(int j(0);j<size;j++)
        {
            if(map[i][j]==0)
            {
                return false;
            }
        }
      }
    return true;
}
bool ekzem(int **map, int size, point& nau)
{
  if(nau.x>-1 && nau.x <size && nau.y >-1 && nau.y <size)
  {
      if(map[nau.x][nau.y]==0)
      {
          return true;
      }
      else
      {
          return false;
      }
  }
  else
  {
      return false;
  }
}
void proverka(int **map, int size,point nau, queue <point>& cord)
{
    if(ekzem(map,size,nau)==true)
    {
        map[nau.x][nau.y]=map[cord.front().x][cord.front().y]+1;
        cord.push(nau);

    }



}
void hod(int **map, int size, queue <point>& cord)
{
    int x(cord.front().x),y(cord.front().y);

   proverka(map,size,point(x+1,y+2),cord);
    proverka(map,size,point(x+1,y-2),cord);
   proverka(map,size,point(x+2,y+1),cord);
    proverka(map,size,point(x+2,y-1),cord);
    proverka(map,size,point(x-1,y+2),cord);
  proverka(map,size,point(x-1,y-2),cord);
    proverka(map,size,point(x-2,y+1),cord);
   proverka(map,size,point(x-2,y-1),cord);
    cord.pop();





}

void prohod(int **map, int size, queue <point>& cord)
{
    if(NoNullMass(map,size)==false )
    {
        hod(map,size,cord);
          if(cord.size()!=0)
          {
        prohod(map,size,cord);
          }
          else
          {
              cout << "невозможно!!!" << endl;
          }

    }
    else
    {
        cout << "карта заполнима конем" <<endl;
    }

}
int main()
{
    int size;
    cin >> size;
    int **map=new int*[size];
    for(int i(0);i<size;i++)
    {
        map[i]=new int[size];
    }
    int x,y;
    cin >> x >> y;
    point start(x,y);
    queue <point> cord;
    map[start.x][start.y]=1;
    cord.push(start);
    print(map,size);
    cout << endl;
    prohod(map,size,cord);
   print(map,size);


}


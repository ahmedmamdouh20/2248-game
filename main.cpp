#include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int Size=8;
vector <int> path;
int visited[Size][Size];
int counter = 0;
int nums[]= {2,4,8};
struct node
{
    int data;
    vector <node*> v;
};
node* grid[Size][Size];
void print_grid()
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            cout<<grid[i][j]->data<<" ";
        }
        cout<<endl;
    }
}
void intialize_grid()
{
    srand(time(0));
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            node *s=new node();
            s->data=nums[rand()%3];
            grid[i][j]=s;
        }
    }
    print_grid();
}
void add_edge()
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            if(i==0&&j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
            }
            else if(i==0&&j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
            }
            else if(i==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
            }
            else if(i==Size-1&&j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);
            }
            else if(j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);

            }
            else if(i==Size-1&&j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);

            }
            else if(i==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);
            }
            else if(j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);
            }
            else
            {
                int dx[]= {0,1,0,-1,1,-1,1,-1};
                int dy[]= {1,0,-1,0,1,-1,-1,1};
                for(int k=0; k<8; k++)
                {
                    grid[i][j]->v.push_back(grid[i+dx[k]][j+dy[k]]);
                }

            }
        }
    }
}
void adjacency_matrix()
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            visited[i][j]=0;
        }
    }
}
bool check_visited_spot(int i,int j)
{
    if(visited[i][j]==0)
    {
        visited[i][j]=1;
        return true;
    }
    else
    {
        return false;
    }
}
bool check_valid(int i, int j)
{
    if (i >= 0 && i < Size && j >= 0 && j < Size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool check_connect(int x,int y,node*curr)
{
    for(int k=0; k<curr->v.size(); k++)
    {

        if (curr->v[k]==grid[x][y] && curr->data==grid[x][y]->data &&check_visited_spot(x,y))
        {
            return true;
        }
        if (curr->v[k]==grid[x][y] && curr->data*2==grid[x][y]->data && counter > 0&&check_visited_spot(x,y))
        {
            return true;
        }

    }

    return false;
}

int found(int x)
{
    int k = 1 ;

    while (x >= pow(2,k))
    {
        k++;
    }
    return pow(2,k-1);


}
int merge_connect ()
{
    int c = 0;

    for ( int i=0 ; i < path.size() ; i++ )
    {
        if (path [i] == path [0])
        {
            c += 1 ;
        }

        else
        {
            c += path[i]/path[0];
        }
    }

    int result = found(path[0] * c);
    return result;

}
void move_spots()
{
    int k;
    srand(time(0));
    for(int i=Size; i>=0; i--)
    {
        k=i;
        for(int j=0; j<Size; j++)
        {
            if(visited[i][j]==1)
            {
                while(visited[k][j]==1 && k>=0)
                {
                    k--;
                }
                if(k==-1)
                {

                    grid[i][j]->data=nums[rand()%3];
                    visited[i][j]=0;

                }
                else
                {
                    grid[i][j]->data=grid[k][j]->data;
                    visited[i][j]=0;
                    visited[k][j]=1;
                    k=i;
                }
            }
        }
    }
    print_grid();
}
void print_path()
{
    cout<<"Your path is:";
    for ( int i=0 ; i < path.size() ; i++ )
    {
        cout<<path[i]<<"  ";
    }
    cout<<endl;
}
int play_game()
{
    adjacency_matrix();
    node *curr=new node();
    int x,y;
    cout<<"Enter index of spot:";
    cin>>x>>y;
    while(!check_valid(x,y))
    {
        cout<<"invalid input"<<endl;
        cout<<"Enter index of spot or -1 to end path:";
        cin>>x>>y;
    }
    curr=grid[x][y];
    check_visited_spot(x,y);
    path.push_back(curr->data);
    print_path();
    int m,n;
    int a1,a2;
    int s=0;
    while(true)
    {
        cout<<"Enter index of spot or -1 to end path:";
        cin>>m>>n;
        if (m==-1 && n== -1)
        {
            counter = 0;
            break ;
        }
        else
        {
            a1=m;
            a2=n;
        }
        while(!check_valid(m,n))
        {
            cout<<"invalid input"<<endl;
            cout<<"Enter index of spot or -1 to end path:";
            cin>>m>>n;
        }
        while(!check_connect(m,n,curr))
        {
            cout<<"invalid connection"<<endl;
            cout<<"Enter index of spot or -1 to end path:";
            cin>>m>>n;
        }
        path.push_back(grid[m][n]->data);
        curr=grid[m][n];
        counter += 1;
        print_path();
    }
    grid[a1][a2]->data= merge_connect();
    s+=merge_connect();
    visited[a1][a2]=0;
    return s;
}
int main()
{
    cout<<"-----------------------------2248 Game ------------------------------------------"<<endl;
    intialize_grid();
    add_edge();
    int moves=0;
    int score=0;
    while(moves<10)
    {
        score+=play_game();
        move_spots();
        cout<<"your score:"<<score<<endl;
        path.clear();
        moves++;
    }
    cout<<"your limit of moves reached";
    return 0;
}


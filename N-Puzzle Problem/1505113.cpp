#include<bits/stdc++.h>

using namespace std;

class Node
{
public:
    int size;
    int board [3][3];

    Node()
    {

    }

    //assigning the values
    void fillupboard(Node temp)
    {
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
                board[i][j]=temp.board[i][j];
            }
        }
    }

    //operator overloading

    bool operator==(const Node &other) const
    {
        for (int i=0; i<size; i++)
        {
            for (int j=0; j<size; j++)
            {
                if (board[i][j] != other.board[i][j])
                    return false;
            }
        }

        return true;
    }


    bool operator<(const Node &other) const
    {
        for (int i=0; i<size; i++)
        {
            for (int j=0; j<size; j++)
            {
                if (board[i][j] < other.board[i][j])
                    return true;
                else if (board[i][j] == other.board[i][j])
                    continue;
                else
                    return false;
            }
        }

        return false;
    }


    //print the board
    void print()
    {
        for(int i=0;i<size;i++)
        {

            for(int j=0;j<size;j++)
            {

                cout<< board[i][j] << " ";
            }
            cout<< "\n";
        }

        cout<< "\n";

    }


};


int HammingDistance(Node curr, Node goal)
{
    int size=curr.size;
    int counter=0;

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {

            if(curr.board[i][j]!=0 && curr.board[i][j] != goal.board[i][j])
                counter++;
        }
    }

    return counter;

}

int ManhattanDistance(Node curr, Node goal)
{
    int size=curr.size;
    int xval[17];
    int yval[17];
    int counter=0;
    int tempx,tempy;

    for(int i=0;i<size;i++)
    {

        for(int j=0;j<size;j++)
        {
            xval[curr.board[i][j]]=i;
            yval[curr.board[i][j]]=j;
        }
    }


    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(goal.board[i][j]==0)
                continue;
            tempx=abs(xval[goal.board[i][j]]-i);
            tempy=abs(yval[goal.board[i][j]]-j);
            counter+=tempx+tempy;

        }

    }

    return counter;

}


int main()
{
   Node startnode;
   Node goalnode;

   int size=3;

   int arr[3][3]={{7,2,4},{6,0,5},{8,3,1}};
   int goal[3][3]={{1,2,3},{4,5,6},{7,8,9}};


   startnode.size=size;
   for(int i=0;i<size;i++)
   {
       for(int j=0;j<size;j++)
       {

           startnode.board[i][j]=arr[i][j];
       }

   }


   goalnode.size=size;
   for(int i=0;i<size;i++)
   {
       for(int j=0;j<size;j++)
       {

           goalnode.board[i][j]=goal[i][j];
       }

   }

   goalnode.board[size-1][size-1]=0;

   startnode.print();

   int temp=ManhattanDistance(startnode,goalnode);
   cout<<temp;

    return 0;
}

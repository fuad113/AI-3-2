#include<bits/stdc++.h>
using namespace std;

class Node
{
public:
    int size;
    int board [4][4];

    Node()
    {

    }
    Node (int sz)
    {
        size=sz;
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

    bool operator==(const Node &temp) const
    {
        for (int i=0; i<size; i++)
        {
            for (int j=0; j<size; j++)
            {
                if (board[i][j] != temp.board[i][j])
                    return false;
            }
        }

        return true;
    }


    bool operator<(const Node &temp) const
    {
        for (int i=0; i<size; i++)
        {
            for (int j=0; j<size; j++)
            {
                if (board[i][j] < temp.board[i][j])
                    return true;
                else if (board[i][j] == temp.board[i][j])
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
        cout<< "\n-------------------\n";
        for(int i=0; i<size; i++)
        {

            for(int j=0; j<size; j++)
            {

                cout<< board[i][j] << " ";
            }
            cout<< "\n";
        }

        cout<< "\n-------------------\n";


    }


};



int HammingDistance(Node curr, Node goal)
{
    int size=curr.size;
    int counter=0;

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
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
    int xval[size*size];
    int yval[size*size];
    int counter=0;
    int tempx,tempy;

    for(int i=0; i<size; i++)
    {

        for(int j=0; j<size; j++)
        {
            xval[curr.board[i][j]]=i;
            yval[curr.board[i][j]]=j;
        }
    }


    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
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




int LinearConflict(Node curr,Node goal)
{

    int size=curr.size;
    int xval[size*size];
    int yval[size*size];
    int tempx,tempy,counter=0;


    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            xval[goal.board[i][j]]=i;
            yval[goal.board[i][j]]=j;
        }
    }

    //counting linear conflict in row

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-1; j++)
        {
            tempx=curr.board[i][j];
            for(int k=j+1; k<size; k++)
            {
                tempy=curr.board[i][k];

                if(xval[tempx]==i && xval[tempy]==i && yval[tempx] > yval[tempy] )
                    counter++;

            }
        }

    }


    //counting linear conflict in column

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-1; j++)
        {
            tempx=curr.board[j][i];
            for(int k=j+1; k<size; k++)
            {
                tempy=curr.board[k][i];

                if(yval[tempx]==i && yval[tempy]==i && xval[tempx] > xval[tempy] )
                    counter++;

            }
        }

    }


    return counter;



}




int CalculateHeuristicvalue(int choice,Node curr,Node goal)
{
    if(choice==1)
        return HammingDistance(curr,goal);
    else if(choice==2)
        return ManhattanDistance(curr,goal);
    else if(choice==3)
    {
        int mdist=ManhattanDistance(curr,goal);
        int lcon=LinearConflict(curr,goal);
        int temp=mdist+(2*lcon);
        return temp;
    }

}



bool Isvalid(int x,int y,int size)
{
    if(x>=0 && y>=0 && x<size && y<size)
        return true;
    else
        return false;

}



map <Node,bool> closedList;
map <Node,int> cost;
map <Node,Node> parent;
int node_explored=0;
int node_expanded=0;


int movex[4]= {0,0,1,-1};
int movey[4]= {1,-1,0,0};


void AStar(Node start, Node goal, int hchoice)
{
    int heuristic_cost,pathcost;
    priority_queue < pair<int,Node> > OpenList;

    OpenList.push({0,start});
    Node temp(0);
    parent[start]=temp;
    cost[start]=0;

    while(OpenList.empty()!=true)
    {

        //getting the top node of the priority queue
        Node curr=OpenList.top().second;

        //pop from the priority queue
        OpenList.pop();
        closedList[curr]=true;
        int currcost=cost[curr];
        node_expanded++;

        //goal checking
        if(curr == goal)
            break;

        int zerox;
        int zeroy;
        int currsize=curr.size;

        //getting the position of zero
        for(int i=0; i<currsize; i++)
        {
            for(int j=0; j<currsize; j++)
            {
                if(curr.board[i][j]==0)
                {
                    zerox=i;
                    zeroy=j;
                }
            }
        }


        //moving to the neighbours using 4 possible moves

        for(int i=0; i<4; i++)
        {

            int dx=zerox+movex[i];
            int dy=zeroy+movey[i];

            if(Isvalid(dx,dy,currsize))
            {

                Node newnode(currsize);
                newnode.fillupboard(curr);

                swap(newnode.board[zerox][zeroy],newnode.board[dx][dy]);

                if(closedList[newnode]==true)
                    continue;

                heuristic_cost=CalculateHeuristicvalue(hchoice,newnode,goal);
                pathcost=currcost+1+heuristic_cost;

                if(cost[newnode]==0 || cost[newnode]> currcost+1)
                {
                    parent[newnode]=curr;
                    cost[newnode]=currcost+1;
                    OpenList.push({-pathcost,newnode});
                    node_explored++;
                }

            }

        }

    }

    while(OpenList.size())
    {
        OpenList.pop();
    }

}



bool ISsolvable(Node node)
{
    int size=node.size;
    int arraysize=size*size;
    int arr[arraysize];
    int inversioncounter=0;

    int k=0;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            arr[k]=node.board[i][j];
            k++;
        }
    }



    for(int i=0; i<arraysize-1; i++)
    {
        for(int j=i+1; j<arraysize; j++)
        {
            if( arr[i]!=0 && arr[j]!=0 && arr[i]>arr[j])
            {
                inversioncounter++;
            }
        }

    }


    //if n/size is odd
    if(size%2 != 0)
    {
        if(inversioncounter%2 != 0)
            return false;
        else
            return true;
    }

    //if n is even
    else
    {
        int xrow;

        //measure the row number of zero
        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
                if(node.board[i][j]==0)
                {
                    xrow=i;
                }
            }
        }


        if( (inversioncounter+xrow)%2 == 0)
        {
            return false;
        }
        else
        {
            return true;
        }

    }

}



int main()
{
    Node startnode;
    Node goalnode;

    int size=3;
    int hchoice;

    ///for n=3
    //int arr[3][3]= {{1,2,3},{4,5,6},{8,7,0}}; //this is for non-solvable testing
    int arr[3][3]= {{8,1,3},{4,0,2},{7,6,5}};
    int goal[3][3]= {{1,2,3},{4,5,6},{7,8,0}};

    ///for n=4
    //int arr[4][4]={{1,2,3,4},{5,6,7,8},{9,10,0,11},{13,14,15,12}};
    //int goal[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};


    //making the start node and the goal node
    startnode.size=size;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {

            startnode.board[i][j]=arr[i][j];
        }

    }


    goalnode.size=size;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            goalnode.board[i][j]=goal[i][j];
        }

    }

    goalnode.board[size-1][size-1]=0;

    bool solvablecheck= ISsolvable(startnode);

    if(solvablecheck)
    {
        cout<< "The puzzle is solvable\n\n";
        cout<< "Choose the Heuristic Type: \n\n";
        cout<< "1.Hamming distance \n2.Manhattan distance \n3.Linear Conflict\n\n";
        cout<< "Heuristic choice: ";
        cin>> hchoice;

        AStar(startnode,goalnode,hchoice);

        //printing the path/solve steps
        vector<Node> path;
        Node current=goalnode;
        while(current.size!=0)
        {
            path.push_back(current);
            current=parent[current];

        }

        reverse(path.begin(),path.end());



        for(int i=0; i<path.size(); i++)
        {
            path[i].print();
        }

        cout << "Number of Nodes Explored: "<< node_explored << "\n";
        cout << "Number of Nodes Expanded: "<< node_expanded << "\n";

        cout << "Optimal cost to reach the goal state: " << cost[goalnode] << "\n";

        parent.clear();
        cost.clear();
        closedList.clear();
    }

    else
    {
        cout<< "Sorry... The puzzle is not solvable\n";
    }


    return 0;
}

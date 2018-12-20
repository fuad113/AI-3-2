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
                if(board[i][j]==0)
                {
                    cout<< "  ";
                }
                else
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

    int sz=curr.size;
    int xval[sz*sz];
    int yval[sz*sz];
    int tempx,tempy,counter=0;


    for(int i=0; i<sz; i++)
    {
        for(int j=0; j<sz; j++)
        {
            xval[goal.board[i][j]]=i;
            yval[goal.board[i][j]]=j;
        }
    }

    //counting linear conflict in row

    for(int i=0; i<sz; i++)
    {
        for(int j=0; j<sz-1; j++)
        {
            tempx=curr.board[i][j];
            for(int k=j+1; k<sz; k++)
            {
                tempy=curr.board[i][k];

                if( (xval[tempx]==i && xval[tempy]==i) && yval[tempx] > yval[tempy] )
                    {
                        counter++;
                    }

            }
        }

    }


    //counting linear conflict in column

    for(int i=0; i<sz; i++)
    {
        for(int j=0; j<sz-1; j++)
        {
            tempx=curr.board[j][i];
            for(int k=j+1; k<sz; k++)
            {
                tempy=curr.board[k][i];

                if((yval[tempx]==i && yval[tempy]==i) && xval[tempx] > xval[tempy] )
                    {
                        counter++;
                    }

            }
        }

    }


    return counter;



}




int CalculateHeuristicvalue(int choice,Node curr,Node goal)
{
    if(choice == 1)
        return HammingDistance(curr,goal);
    else if(choice == 2)
        return ManhattanDistance(curr,goal);
    else if(choice == 3)
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
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    Node startnode;
    Node goalnode;

    int size;
    cin>> size;

    //making the start node and the goal node
    startnode.size=size;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            cin >> startnode.board[i][j];

        }

    }


    goalnode.size=size;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            cin>>goalnode.board[i][j];
        }

    }


    bool solvablecheck= ISsolvable(startnode);

    if(solvablecheck)
    {
        cout<< "The puzzle is solvable\n\n";

        for(int k=1; k<=3; k++)
        {
            if(k==1)
                cout<< "----------------Hamming Distance as heuristic----------------\n\n";
            else if(k==2)
                cout<< "----------------Manhattan Distance as heuristic----------------\n\n";
            else
                cout<< "----------------Linear Conflict as heuristic----------------\n\n";


            AStar(startnode,goalnode,k);

            cout << "Number of Nodes Explored: "<< node_explored << "\n";
            cout << "Number of Nodes Expanded: "<< node_expanded << "\n";
            cout << "Optimal cost to reach the goal state: " << cost[goalnode] << "\n\n";
            cout << "Solving steps:\n\n";

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


            parent.clear();
            cost.clear();
            closedList.clear();
            path.clear();
            node_expanded=0;
            node_explored=0;
        }

    }

    else
    {
        cout<< "Sorry... The puzzle is not solvable\n";
    }


    return 0;
}

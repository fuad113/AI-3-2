#include <bits/stdc++.h>
#define maxcity 100


using namespace std;


struct City
{
    int x,y;

    City()
    {

    }
    City (int x1, int y1)
    {
        x=x1;
        y=y1;
    }
};


int n;
City cities[maxcity];
bool visited[maxcity];
vector<int> path;

int CalculateDistanceTwoNodes(City f,City s)
{
    int tempx= f.x - s.x ;
    int tempy= f.y - s.y ;

    int ret = tempx*tempx+tempy*tempy ;
    return ret;

}



/// Nearest Neighbour Heuristic implementation

int FindClosestUnvisitedNode(int node)
{
    int mindistance=100000;
    int index=-1;

    for(int i=0;i<n;i++)
    {
        if(visited[i]==true)
            continue;

        if(CalculateDistanceTwoNodes(cities[i],cities[node]) < mindistance)
        {
            mindistance=CalculateDistanceTwoNodes(cities[i],cities[node]);
            index=i;
        }

    }

    return index;

}



void NearestNeighbour(int startnodeindex)
{

   path.clear();

   memset(visited,0,sizeof(visited));

   int temp;
   int lastvisited=startnodeindex;
   visited[startnodeindex]=true;
   path.push_back(startnodeindex);


   while(path.size()<n)
   {
    temp=FindClosestUnvisitedNode(lastvisited);
    visited[temp]=true;
    path.push_back(temp);
    lastvisited=temp;
   }

   path.push_back(startnodeindex);

}


void PrintPath()
{
    for(int i=0;i<path.size();i++)
    {
        if(i==path.size()-1)
            cout<< path[i] << endl;
        else
            cout<< path[i] << " -> " ;
    }


}

float CalculateCost()
{
   float ans=0;

   for(int i=0;i<path.size()-1;i++)
   {
       int temp=CalculateDistanceTwoNodes(cities[path[i]],cities[path[i+1]]);

       ans+= sqrt(temp*1.0);
   }

    return ans;

}





int main()
{
    cin>> n;

    for(int i=0;i<n;i++)
    {
        cin>> cities[i].x >> cities[i].y ;
    }

    int startnode=0;

    cout<< "Start Node is at index : " << startnode << endl;

    NearestNeighbour(startnode);
    PrintPath();

    cout<< "cost : " << CalculateCost() << endl;


    return 0;
}
/*
10
1 2
5 3
4 5
2 7
3 9
8 3
1 9
5 8
6 7
9 2
*/

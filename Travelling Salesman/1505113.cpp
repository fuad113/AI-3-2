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

int FindClosestUnvisitedNode(int node)
{
    int mindistance=100000;
    int index=-1;

    for(int i=0; i<n; i++)
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


int FindNearestTotalGraph()
{
    int mindistance=100000;
    int index=-1;
    int temp;

    for(int i=0; i<n; i++)
    {
        if(visited[i]== false)
            continue;

        temp=FindClosestUnvisitedNode(i);

        if(CalculateDistanceTwoNodes(cities[i],cities[temp]) < mindistance)
        {
            mindistance=CalculateDistanceTwoNodes(cities[i],cities[temp]);
            index=temp;
        }

    }

    return index;
}


///calculate minimized Cir+Crj-Cij for Nearest Insertion
int FindMinimizedEdge(int r)
{
    int mindistance=10000000.00;
    int index=-1;

    int s=path.size();

    int i,j;
    double temp;

    for(int k=0; k<s; k++)
    {
        i=path[k];
        j=path[(k+1)%s];
        temp=CalculateDistanceTwoNodes(cities[i],cities[r])+CalculateDistanceTwoNodes(cities[r],cities[j])- CalculateDistanceTwoNodes(cities[i],cities[j]);

        if(temp < mindistance)
        {
            mindistance=temp;
            index=i;
        }

    }

    return index;

}

///calculate minimized Cir+Crj-Cij for Cheapest Insertion
int FindMinimizedEdge2()
{
    int mindistance=10000000.00;
    int index=-1;

    int s=path.size();

    int i,j,city;
    double temp;

    for(int k=0; k<s; k++)
    {
        i=path[k];
        j=path[(k+1)%s];

        for(int r=0;r<n;r++)
        {

          if(visited[r]==true)
                continue;

          temp=CalculateDistanceTwoNodes(cities[i],cities[r])+CalculateDistanceTwoNodes(cities[r],cities[j])- CalculateDistanceTwoNodes(cities[i],cities[j]);

          if(temp < mindistance)
          {
            mindistance=temp;
            index=i;
            city=r;
          }

        }

    }

    visited[city]=true;
    path.push_back(city);
    return index;

}

/// Nearest Neighbour Heuristic implementation

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

///Nearest Insertion Heuristic Implementation

void NearestInsertion(int startindex)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    visited[startindex]=true;
    path.push_back(startindex);
    int temp= FindClosestUnvisitedNode(startindex);
    visited[temp]=true;
    path.push_back(temp);


    int r,s;

    while(path.size() < n)
    {
        s=path.size();
        r=FindNearestTotalGraph();
        visited[r]=true;
        temp=FindMinimizedEdge(r);

        //adding r between i and j
        path.push_back(r);
        for(int i=s-1; i>=0; i--)
        {
            if(path[i]==temp)
                break;
            swap(path[i],path[i+1]);
        }

    }

    path.push_back(startindex);


}

///Cheapest Insertion Heuristic Implementation

void CheapestInsertion(int startindex)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    visited[startindex]=true;
    path.push_back(startindex);
    int temp= FindClosestUnvisitedNode(startindex);
    visited[temp]=true;
    path.push_back(temp);

    int s;
    while(path.size() < n)
    {
        s=path.size();
        temp=FindMinimizedEdge2();

        for(int i=s-1; i>=0; i--)
        {
            if(path[i]==temp)
                break;
            swap(path[i],path[i+1]);
        }

    }

    path.push_back(startindex);

}


void PrintPath()
{
    for(int i=0; i<path.size(); i++)
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

    for(int i=0; i<path.size()-1; i++)
    {
        int temp=CalculateDistanceTwoNodes(cities[path[i]],cities[path[i+1]]);

        ans+= sqrt(temp*1.0);
    }

    return ans;

}





int main()
{
    cin>> n;

    for(int i=0; i<n; i++)
    {
        cin>> cities[i].x >> cities[i].y ;
    }


    int startnode=6;

    cout<< "Start Node is at index : " << startnode << endl;

    NearestInsertion(startnode);
    PrintPath();
    cout<< "cost : " << CalculateCost() << endl;

    CheapestInsertion(startnode);
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

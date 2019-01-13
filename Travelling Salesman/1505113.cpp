#include <bits/stdc++.h>
#define maxcity 100
#define inf 9999999


using namespace std;


struct City
{
    float x,y;

    City()
    {

    }
    City (float x1, float y1)
    {
        x=x1;
        y=y1;
    }
};


int n;
City cities[maxcity];
bool visited[maxcity];
vector<int> path;

float CalculateDistanceTwoNodes(City f,City s)
{
    float tempx= f.x - s.x ;
    float tempy= f.y - s.y ;

    float ret = tempx*tempx+tempy*tempy ;
    return ret;
}

int FindClosestUnvisitedNode(int node)
{
    float mindistance=100000;
    int index=-1;

    for(int i=1; i<=n; i++)
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
    float mindistance=100000;
    int index=-1;
    int temp;

    for(int i=1; i<=n; i++)
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
    float mindistance=10000000.00;
    int index=-1;

    int s=path.size();

    int i,j;
    float temp;

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
    float mindistance=10000000.00;
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
        float temp=CalculateDistanceTwoNodes(cities[path[i]],cities[path[i+1]]);

        ans+= sqrt(temp*1.0);
    }

    return ans;

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

///savings Heuristic Implementation

void Savings(int startIndex)
{
   path.clear();
   memset(visited,0,sizeof(visited));

   deque<int> dq;

   visited[startIndex]=true;

   float savings[n+1][n+1];
   memset(savings,0,sizeof(savings));

   for(int i=1;i<=n;i++)
   {
       for(int j=i+1;j<=n;j++)
       {
           if(i!= startIndex && j!= startIndex)
           {
           savings[i][j]=CalculateDistanceTwoNodes(cities[startIndex],cities[i])+
           CalculateDistanceTwoNodes(cities[startIndex],cities[j])-
           CalculateDistanceTwoNodes(cities[i],cities[j]);

           savings[j][i]=CalculateDistanceTwoNodes(cities[startIndex],cities[i])+
           CalculateDistanceTwoNodes(cities[startIndex],cities[j])-
           CalculateDistanceTwoNodes(cities[i],cities[j]);
           }

       }
   }

   float maximum=0.0;
   int indexi=-1;
   int indexj=-1;

   for(int i=1;i<=n;i++)
   {
       for(int j=1;j<=n;j++)
       {
           if(savings[i][j]>maximum)
           {
               maximum=savings[i][j];
               indexi=i;
               indexj=j;
           }

       }
   }

   //cout<< indexi <<  " " << indexj << endl;


    dq.push_back(indexj);
    dq.push_front(indexi);
    visited[indexi]=true;
    visited[indexj]=true;



/*
    for(int i=0;i<dq.size();i++)
    {
        cout<< dq[i] << " ";
    }
*/

    int temp1,temp2,tempx,tempy;

    while(dq.size()< (n-1))
    {
        tempx=-1;
        tempy=-1;
        temp1=dq.front();
        temp2=dq.back();

        float maximum=0.0;
        for(int i=1;i<=n;i++)
        {
            if(visited[i]==false)
            {
                if(savings[temp1][i]>maximum)
                {
                    maximum=savings[temp1][i];
                    tempx=i;
                }
            }
        }


        float maximum2=0.0;
        for(int i=1;i<=n;i++)
        {
            if(visited[i]==false)
            {
                if(savings[temp2][i]>maximum2)
                {
                    maximum2=savings[temp2][i];
                    tempy=i;
                }
            }
        }


        if(tempx!=tempy)
        {
           visited[tempx]=true;
           visited[tempy]=true;

           dq.push_front(tempx);
           dq.push_back(tempy);

        }
        else
        {

           if(maximum>maximum2)
           {
               visited[tempx]=true;
               dq.push_front(tempx);
           }
           else
           {
               visited[tempy]=true;
               dq.push_front(tempy);
           }
        }

    }



 dq.push_front(startIndex);
 dq.push_back(startIndex);





 for(int i=0;i<dq.size();i++)
 {
     path.push_back(dq[i]);
 }

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

///2-opt Heuristic implementation

void TwoOpt(int startindex)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    NearestNeighbour(startindex);

    float best=CalculateCost();
    float temp_cost;
    bool flag;


    while(true)
    {
        flag=false;
        for(int i=1;i<path.size()-2;i++)
        {
            for(int k=i+1;k<path.size()-1;k++)
            {
                reverse(path.begin()+i,path.begin()+k+1);
                temp_cost=CalculateCost();

                if(temp_cost < best)
                {
                    best=temp_cost;
                    flag=true;
                    break;
                }
                reverse(path.begin()+i,path.begin()+k+1);
            }
            if(flag==true)
                break;
        }

        if(flag==false)
            break;

    }

}



int main()
{


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

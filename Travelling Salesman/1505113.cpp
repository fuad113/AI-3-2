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
    float mindistance=100000000.00;
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

int FindClosestUnvisitedNodeRandomly(int node)
{
    float mindistance=100000000.00;
    int index=-1;
    vector<pair<float,int>> v;

    for(int i=1; i<=n; i++)
    {
        if(visited[i]==true)
            continue;

        if(CalculateDistanceTwoNodes(cities[i],cities[node]) < mindistance)
        {
            mindistance=CalculateDistanceTwoNodes(cities[i],cities[node]);
            v.push_back({mindistance,i});
        }

    }

    ///we have to choose 5 best nodes
    ///we choose this by sorting

    sort(v.begin(),v.end());

    int k=5;

    if(v.size()<= k)
        k=v.size();

    int temp= rand()%k;


    return v[temp].second;
}


int FindNearestTotalGraph()
{
    float mindistance=100000000.00;
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
    float mindistance=100000000.00;
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

        for(int r=0; r<n; r++)
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


///Nearest Neighbour Heuristic Implementation (Randomized)
void NearestNeighbourRandomized(int startnodeindex)
{

    path.clear();
    memset(visited,0,sizeof(visited));

    int temp;
    int lastvisited=startnodeindex;
    visited[startnodeindex]=true;
    path.push_back(startnodeindex);

    while(path.size()<n)
    {
        temp=FindClosestUnvisitedNodeRandomly(lastvisited);
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

    for(int i=1; i<=n; i++)
    {
        for(int j=i+1; j<=n; j++)
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

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(savings[i][j]>maximum)
            {
                maximum=savings[i][j];
                indexi=i;
                indexj=j;
            }

        }
    }

    dq.push_back(indexj);
    dq.push_front(indexi);
    visited[indexi]=true;
    visited[indexj]=true;


    int temp1,temp2,tempx,tempy;

    while(dq.size()< (n-1))
    {
        tempx=-1;
        tempy=-1;
        temp1=dq.front();
        temp2=dq.back();

        float maximum=0.0;
        for(int i=1; i<=n; i++)
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
        for(int i=1; i<=n; i++)
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
                dq.push_back(tempy);
            }
        }

    }


    dq.push_front(startIndex);
    dq.push_back(startIndex);

    for(int i=0; i<dq.size(); i++)
    {
        path.push_back(dq[i]);
    }

}


///Randomized savings Heuristic Implementation

void SavingsRandomized(int startIndex)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    deque<int> dq;

    vector<pair<float,int>>v1;
    vector<pair<float,int>>v2;

    visited[startIndex]=true;

    float savings[n+1][n+1];
    memset(savings,0,sizeof(savings));

    for(int i=1; i<=n; i++)
    {
        for(int j=i+1; j<=n; j++)
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

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(savings[i][j]>maximum)
            {
                maximum=savings[i][j];
                indexi=i;
                indexj=j;
            }

        }
    }

    dq.push_back(indexj);
    dq.push_front(indexi);
    visited[indexi]=true;
    visited[indexj]=true;


    int temp1,temp2,tempx,tempy;

    while(dq.size()< (n-1))
    {
        tempx=-1;
        tempy=-1;
        temp1=dq.front();
        temp2=dq.back();

        for(int i=1; i<=n; i++)
        {
            if(visited[i]==false)
            {
                v1.push_back({savings[temp1][i],i});
            }
        }


        for(int i=1; i<=n; i++)
        {
            if(visited[i]==false)
            {
                v2.push_back({savings[temp2][i],i});
            }
        }


        sort(v1.begin(),v1.end());
        sort(v2.begin(),v2.end());

        int k1=5;
        int k2=5;

        if(k1>=v1.size())
            k1=v1.size();

        if(k2>=v2.size())
            k2=v2.size();

        int tempindex1=rand()%k1;
        int tempindex2=rand()%k2;




        if(v1[tempindex1].second!=v2[tempindex2].second)
        {
            visited[v1[tempindex1].second]=true;
            visited[v2[tempindex2].second]=true;

            dq.push_front(v1[tempindex1].second);
            dq.push_back(v2[tempindex2].second);

        }

        else
        {
            if(v1[tempindex1].first > v2[tempindex2].first)
            {
                visited[v1[tempindex1].second]=true;
                dq.push_front(v1[tempindex1].second);
            }
            else
            {
                visited[v2[tempindex2].second]=true;
                dq.push_front(v2[tempindex2].second);
            }
        }

        v1.clear();
        v2.clear();

    }

    dq.push_front(startIndex);
    dq.push_back(startIndex);



    for(int i=0; i<dq.size(); i++)
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

void TwoOpt(vector<int>path2)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    //NearestNeighbour(startindex);

    for(int i=0; i<path2.size(); i++)
    {
        path.push_back(path2[i]);
    }

    float best=CalculateCost();
    float temp_cost;
    bool flag;



    while(true)
    {
        flag=false;
        for(int i=1; i<path.size()-2; i++)
        {
            for(int k=i+1; k<path.size()-1; k++)
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


///2-opt Heuristic implementation

void TwoOptfirst(vector<int>path2)
{
    path.clear();
    memset(visited,0,sizeof(visited));

    //NearestNeighbour(startindex);

    for(int i=0; i<path2.size(); i++)
    {
        path.push_back(path2[i]);
    }

    float best=CalculateCost();
    float best2=CalculateCost();
    float temp_cost;
    bool flag;


    while(true)
    {
        flag=false;
        for(int i=1; i<path.size()-2; i++)
        {
            for(int k=i+1; k<path.size()-1; k++)
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
            if(flag==true || best2!= best)
                break;
        }

        if(flag==false)
            break;

    }

}



int main()
{
    //freopen("burma14.tsp", "r", stdin);
    //freopen("berlin52.tsp", "r", stdin);
    freopen("st70.tsp", "r", stdin);

    cin>> n;

    int idx;
    float x;
    float y;
    for(int i=1; i<=n; i++)
    {
        cin>>idx>>x>>y;
        cities[idx].x=x;
        cities[idx].y=y;
    }


    ///task 1

    ///calculation for nearest neighbour

    int nearestneighbourstrt[5];
    float nearestneighbourcosts[5];
    int k;
    float cost;

    for(int i=0; i<5; i++)
    {
        k= rand()%n;

        if(k==0)
        {
            k=n;
        }


        nearestneighbourstrt[i]=k;

        NearestNeighbour(k);

        nearestneighbourcosts[i]=CalculateCost();

    }


    /*for(int i=0;i<5;i++)
    {
        cout<< nearestneighbourstrt[i] << "-> " << nearestneighbourcosts[i] << endl;
    }*/

    float best=inf;
    float worst=0;
    int bestcoststrtnode;

    for(int i=0; i<5; i++)
    {
        if(nearestneighbourcosts[i]<best)
        {
            best=nearestneighbourcosts[i];
            bestcoststrtnode=nearestneighbourstrt[i];
        }
        if(nearestneighbourcosts[i]>worst)
        {
            worst=nearestneighbourcosts[i];
        }
    }


    cout<< "*****Nearest Neighbour Heuristic*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;


    ///calculation for Savings Heuristic

    int savingsstrt[5];
    float savingscosts[5];

    for(int i=0; i<5; i++)
    {
        k= rand()%n;

        if(k==0)
        {
            k=n;
        }


        savingsstrt[i]=k;

        Savings(k);

        savingscosts[i]=CalculateCost();

    }

   /*
    for(int i=0;i<5;i++)
    {
        cout<< savingsstrt[i] << "-> " << savingscosts[i] << endl;
    }*/

    best=inf;
    worst=0;
    int bestcoststrtnode2;

    for(int i=0; i<5; i++)
    {
        if(savingscosts[i]<best)
        {
            best=savingscosts[i];
            bestcoststrtnode2=savingsstrt[i];
        }
        if(savingscosts[i]>worst)
        {
            worst=savingscosts[i];
        }
    }


    cout<< "*****Savings Heuristic*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;



    ///task 2

    ///Randomized Nearest Neighbour

    float randnearestneighbourcosts[10];
    vector<pair<float,vector<int>>> rtemp;

    for(int i=0; i<10; i++)
    {

        NearestNeighbourRandomized(bestcoststrtnode);

        randnearestneighbourcosts[i]=CalculateCost();

        rtemp.push_back({CalculateCost(),path});


    }
    /*
    cout<< "Starting Index:" << bestcoststrtnode <<  endl;
    for(int i=0;i<10;i++)
    {
        cout<< randnearestneighbourcosts[i] << endl;
    }*/

    best=inf;
    worst=0;

    for(int i=0; i<10; i++)
    {
        if(randnearestneighbourcosts[i]<best)
        {
            best=randnearestneighbourcosts[i];

        }
        if(randnearestneighbourcosts[i]>worst)
        {
            worst=randnearestneighbourcosts[i];
        }
    }


    cout<< "*****Random Nearest Neighbour Heuristic*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;

    sort(rtemp.begin(),rtemp.end());


/// Randomized Savings

    float randsavingscosts[10];

    vector<pair<float,vector<int>>> rtemp2;


    for(int i=0; i<10; i++)
    {

        SavingsRandomized(bestcoststrtnode2);

        randsavingscosts[i]=CalculateCost();

        rtemp2.push_back({CalculateCost(),path});

    }

    /*
    cout<< "Starting Index:" << bestcoststrtnode2 <<  endl;
    for(int i=0;i<10;i++)
    {
        cout<< randsavingscosts[i] << endl;
    }*/

    best=inf;
    worst=0;

    for(int i=0; i<10; i++)
    {
        if(randsavingscosts[i]<best)
        {
            best=randsavingscosts[i];

        }
        if(randsavingscosts[i]>worst)
        {
            worst=randsavingscosts[i];
        }
    }


    cout<< "*****Random Savings Heuristic*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;

    sort(rtemp2.begin(),rtemp2.end());


    ///task 3
    ///Running the 2-OPT heuristic(best)

    ///2opt for Nearest Neighbour

    float nnhopt[3];

    for(int i=0;i<3;i++)
    {

     TwoOpt(rtemp[i].second);

     nnhopt[i]=CalculateCost();

    }


    best=inf;
    worst=0;

    for(int i=0; i<3; i++)
    {
        if(nnhopt[i]<best)
        {
            best=nnhopt[i];

        }
        if(nnhopt[i]>worst)
        {
            worst=nnhopt[i];
        }
    }


    cout<< "*****2-OPT(Best) Heuristic on NNH*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;



    ///2opt for Savings

    float sopt[3];

    for(int i=0;i<3;i++)
    {

     TwoOpt(rtemp2[i].second);

     sopt[i]=CalculateCost();

    }


    best=inf;
    worst=0;

    for(int i=0; i<3; i++)
    {
        if(sopt[i]<best)
        {
            best=sopt[i];

        }
        if(sopt[i]>worst)
        {
            worst=sopt[i];
        }
    }


    cout<< "*****2-OPT(Best) Heuristic on SH*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;




    ///Running the 2-OPT heuristic(first)

    ///2opt(first) for Nearest Neighbour

    float nnhfopt[3];

    for(int i=0;i<3;i++)
    {

     TwoOptfirst(rtemp[i].second);

     nnhfopt[i]=CalculateCost();

    }


    best=inf;
    worst=0;

    for(int i=0; i<3; i++)
    {
        if(nnhfopt[i]<best)
        {
            best=nnhfopt[i];

        }
        if(nnhfopt[i]>worst)
        {
            worst=nnhfopt[i];
        }
    }


    cout<< "*****2-OPT(First) Heuristic on NNH*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;



    ///2opt(first) for Savings

    float soptf[3];

    for(int i=0;i<3;i++)
    {

     TwoOptfirst(rtemp2[i].second);

     soptf[i]=CalculateCost();

    }


    best=inf;
    worst=0;

    for(int i=0; i<3; i++)
    {
        if(soptf[i]<best)
        {
            best=soptf[i];

        }
        if(soptf[i]>worst)
        {
            worst=soptf[i];
        }
    }


    cout<< "*****2-OPT(First) Heuristic on SH*****"<< endl ;
    cout<< "Best case: " << best << endl;
    cout<< "Worst case: "<< worst << endl;
    cout<< endl << endl;


    return 0;
}

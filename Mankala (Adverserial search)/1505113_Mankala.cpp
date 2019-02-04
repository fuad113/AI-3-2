#include <bits/stdc++.h>
#define INF 100000000
#define _INF -100000000

#define dbg printf("in\n")

using namespace std;

class Board
{

public :

    int player1board[6];
    int player2board[6];
    int container[2];

    Board()
    {
        for(int i=0; i<6; i++)
        {
            player1board[i]=4;
            player2board[i]=4;
        }

        for(int i=0; i<2; i++)
        {
            container[i]=0;
        }

    }


    int UpdateBoard(int player,int startposition)
    {
        int nextturn;
        if(player==1)
            nextturn=2;
        else
            nextturn=1;


        if(player==1)
        {
            int temp=player1board[startposition];
            player1board[startposition]=0;

            int temp2=temp/13;
            int temp3=temp%13;

            for(int i=0; i<6; i++)
            {
                player1board[i]+=temp2;
                player2board[i]+=temp2;
            }
            container[0]+=temp2;


            int i=startposition+1;

            while(i<6 && temp3!=0)
            {
                player1board[i]+=1;
                temp3--;
                if(temp3==0)
                {

                    if(player2board[6-i-1]!=0 && player1board[i]==1)
                    {
                        int sum=player1board[i]+player2board[6-i-1];
                        player1board[i]=0;
                        player2board[6-i-1]=0;
                        container[0]+=sum;
                    }
                }

                i++;
            }

            if(temp3 != 0)
            {
                container[0]+=1;
                temp3--;
                if(temp3==0)
                {
                    nextturn=1;

                }
            }

            i=0;
            while(i<6 && temp3!=0)
            {
                player2board[i]+=1;
                temp3--;
                i++;
            }


            i=0;
            while(i<startposition-1 && temp3!=0)
            {
                player1board[i]+=1;
                temp3--;
                i++;
            }

            return nextturn;
        }





        else if(player==2)
        {
            int temp=player2board[startposition];
            player2board[startposition]=0;

            int temp2=temp/13;
            int temp3=temp%13;

            for(int i=0; i<6; i++)
            {
                player2board[i]+=temp2;
                player1board[i]+=temp2;
            }
            container[1]+=temp2;


            int i=startposition+1;

            while(i<6 && temp3!=0)
            {
                player2board[i]+=1;
                temp3--;
                if(temp3==0)
                {

                    if(player1board[6-i-1]!=0 && player2board[i]==1)
                    {

                        int sum=player1board[6-i-1]+player2board[i];
                        player1board[6-i-1]=0;
                        player2board[i]=0;
                        container[1]+=sum;
                    }
                }

                i++;
            }

            if(temp3 != 0)
            {
                container[1]+=1;
                temp3--;
                if(temp3==0)
                {
                    nextturn=2;
                }
            }

            i=0;
            while(i<6 && temp3!=0)
            {
                player1board[i]+=1;
                temp3--;
                i++;
            }


            i=0;
            while(i<startposition-1 && temp3!=0)
            {
                player2board[i]+=1;
                temp3--;
                i++;
            }

            return nextturn;
        }


    }


    bool Endgame()
    {
        int sum1=0;

        for(int i=0; i<6; i++)
        {
            sum1+=player1board[i];
        }

        int sum2=0;
        for(int i=0; i<6; i++)
        {
            sum2+=player2board[i];
        }

        if(sum1==0 && sum2!=0)
        {
            container[1]+=sum2;
            for(int i=0; i<6; i++)
                player2board[i]=0;
            return true;
        }

        else if(sum2==0 && sum1!=0)
        {
            container[0]+=sum1;
            for(int i=0; i<6; i++)
                player1board[i]=0;

            return true;
        }


        return false;

    }


    void Winner()
    {
        if(container[0]> container[1])
        {
            cout<< "Player 1 is winner\n";
            return;
        }
        else if(container[0] < container[1])
        {
            cout<< "Player 2 is winner\n";
            return;
        }
        else
        {
            cout << "Match Draw\n";
            return;
        }
    }


    int Whoiswinner()
    {
        if(container[0]> container[1])
        {
            return 1;
        }
        else if(container[0] < container[1])
        {
            return 2;
        }
        else
        {
            return 3;
        }

    }



    void PrintBoard()
    {
        cout<< "\n";
        for(int i=5; i>=0; i--)
            cout<< "  " <<player2board[i] << "  " ;

        cout<< "\n";

        cout<< container[1] << "                            " << container[0];

        cout<< "\n";
        for(int i=0; i<6; i++)
            cout<< "  " <<player1board[i] << "  " ;


        cout<< "\n";


    }

};



class Player
{

    int heuristic,depth,playernum,w1,w2,w3,w4,otherplayer, addition,initialstorage;
    bool ishuman;

public:

    Player(int playernum,int heuristic,bool ishuman,int depth,int w1,int w2,int w3, int w4)
    {
        this->heuristic=heuristic;
        this->ishuman=ishuman;
        this->depth=depth;
        this->w1=w1;
        this->w2=w2;
        this->w3=w3;
        this->w4=w4;
        this->playernum=playernum;



        if(playernum==1)
            otherplayer=2;
        else
            otherplayer=1;
    }


    int Getstartindex(Board b)
    {
        int idx;
        if(ishuman==true)
        {
            cout<< "Human turn\n";
            cout<< "Select Index: \n";
            cin>> idx;
            return idx;
        }
        else
        {
            addition = 0;

            if(playernum==1)
                initialstorage=b.container[0];
            else
                initialstorage=b.container[1];

            idx=MiniMaxalgo(b,depth,true,_INF,INF);
            return idx;
        }

    }


    int Evaluationfunction(Board temp)
    {
        int x1=temp.container[0];
        int x2=temp.container[1];

        if(heuristic==1)
        {
            if(playernum==1)
            {
                return temp.container[0]-temp.container[1];
            }
            else
            {
                return temp.container[1]-temp.container[0];
            }
        }


        else if(heuristic==2)
        {
            int sum1,sum2;

            for(int i=0; i<6; i++)
            {
                sum1+=temp.player1board[i];
                sum2+=temp.player2board[i];
            }


            if(playernum==1)
            {

                int storagedif= temp.container[0]-temp.container[1];
                int h= (w1*storagedif) + (w2*(sum1-sum2)) ;
                return h;
            }
            else
            {
                int storagedif= temp.container[1]-temp.container[0];
                int h= (w1*storagedif) + (w2*(sum2-sum1)) ;
                return h;
            }

        }

        else if(heuristic==3)
        {
            int sum1,sum2;

            for(int i=0; i<6; i++)
            {
                sum1+=temp.player1board[i];
                sum2+=temp.player2board[i];
            }


            if(playernum==1)
            {
                int storagedif= temp.container[0]-temp.container[1];
                int h= (w1*storagedif) + (w2*(sum1-sum2)) +w3*addition;
                return h;

            }

            else
            {
                int storagedif= temp.container[1]-temp.container[0];
                int h= (w1*storagedif) + (w2*(sum2-sum1)) + w3*addition ;
                return h;

            }

        }


        else if(heuristic==4)
        {

            int sum1,sum2;

            for(int i=0; i<6; i++)
            {
                sum1+=temp.player1board[i];
                sum2+=temp.player2board[i];
            }


            if(playernum==1)
            {
                int storagedif= temp.container[0]-temp.container[1];

                int h= (w1*storagedif) + (w2*(sum1-sum2)) +w3*addition + w4*(temp.container[0]-initialstorage);
                return h;

            }

            else
            {
                int storagedif= temp.container[1]-temp.container[0];
                int h= (w1*storagedif) + (w2*(sum2-sum1)) + w3*addition + w4*(temp.container[1]-initialstorage);
                return h;

            }



        }

    }


    int MiniMaxalgo(Board b,int dep,bool isMaximizing,int alpha,int beta)
    {

        int bestval,value;

        if(b.Endgame()==true)
        {
            if(b.Whoiswinner()==playernum)
                return 100000;
            else if(b.Whoiswinner() ==otherplayer)
                return -100000;
            else
                return Evaluationfunction(b);
        }


        if(dep==0)
            return Evaluationfunction(b);

        Board temp;

        for(int i=0; i<6; i++)
        {
            temp.player1board[i]=b.player1board[i];
            temp.player2board[i]=b.player2board[i];
        }

        for(int i=0; i<2; i++)
        {
            temp.container[i]=b.container[i];
        }


        if(isMaximizing==true)
        {
            int index=-1;
            bestval=_INF;


            for(int i=0; i<6; i++)
            {
                if(playernum==1)
                {

                    if(b.player1board[i]==0)
                    {
                        continue;
                    }
                }

                else if(playernum==2)
                {

                    if(b.player2board[i]==0)
                    {
                        continue;
                    }
                }

                //update board
                int x = b.UpdateBoard(playernum, i);

                if(x==playernum)
                {
                    addition++;
                    value=MiniMaxalgo(b,dep-1,true,alpha,beta);
                    addition--;
                }

                else
                    value=MiniMaxalgo(b,dep-1,false,alpha,beta);


                if(value > bestval)
                {
                    bestval = value;
                    index = i;
                }


                alpha=max(alpha,bestval);

                //restore board
                for(int i=0; i<6; i++)
                {
                    b.player1board[i]=temp.player1board[i];
                    b.player2board[i]=temp.player2board[i];
                }

                for(int i=0; i<2; i++)
                {
                    b.container[i]=temp.container[i];
                }



                if(beta <= alpha)
                    break;
            }

            if(dep==depth)
                return index;
            else
                return bestval;


        }

        else
        {

            bestval=INF;


            for(int i=0; i<6; i++)
            {
                if(playernum==1)
                {
                    if(b.player2board[i]==0)
                        continue;
                }

                else if(playernum==2)
                {
                    if(b.player1board[i]==0)
                        continue;
                }

                //update board
                int x = b.UpdateBoard(otherplayer, i);


                if(x==otherplayer)
                    value=MiniMaxalgo(b,dep-1,false,alpha,beta);
                else
                    value = MiniMaxalgo(b,dep-1,true,alpha,beta);

                bestval=min(bestval,value);
                beta=min(beta,bestval);

                //restore board
                for(int i=0; i<6; i++)
                {
                    b.player1board[i]=temp.player1board[i];
                    b.player2board[i]=temp.player2board[i];
                }

                for(int i=0; i<2; i++)
                {
                    b.container[i]=temp.container[i];
                }


                if(beta <= alpha)
                    break;

            }

            return bestval;
        }

    }





};





int main()
{

    int counter1=0;
    int counter2=0;

    for(int i=0; i<100; i++)
    {
        int h=4;

        int w1=100;
        int w2=90;
        int w3=95;
        int w4=91;

        Player p1=Player(1,h,false,3,w1,w2,w3,w4);
        Player p2=Player(2,h,false,3,w1,w2,w3,w4);

        Board b;

        int player=(rand()%2)+1;
        int idx,nxturn;
        bool endg;


        while(true)
        {
            endg=b.Endgame();
            if(endg==true)
                break;

            if(player==1)
            {
                idx=p1.Getstartindex(b);
                nxturn=b.UpdateBoard(1,idx);
            }

            else if(player==2)
            {
                idx=p2.Getstartindex(b);
                nxturn=b.UpdateBoard(2,idx);
            }

            player=nxturn;
        }

        if(b.Whoiswinner() == 1)
            counter1++;
        else if(b.Whoiswinner()==2)
            counter2++;


    }

    cout<< "player 1 has won " << counter1 << "times" << endl;
    cout<< "player 2 has won " << counter2 << "times" << endl;

    return 0;
}

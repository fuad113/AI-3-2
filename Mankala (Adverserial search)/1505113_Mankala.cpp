#include <bits/stdc++.h>


using namespace std;

class Board
{
    int player1board[6];
    int player2board[6];
    int container[2];

public :

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


    void PrintBoard()
    {
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

    int heuristic,depth,playernum,w1,w2,w3,w4;
    bool ishuman;

public:

    Player(int heuristic,bool ishuman,int playernum,int depth,int w1,int w2,int w3, int w4)
    {
        this.heuristic=heuristic;
        this.ishuman=ishuman;
        this.depth=depth;
        this.w1=w1;
        this.w2=w2;
        this.w3=w3;
        this.w4=w4;
    }


    int Getstartindex()
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
            idx=MinMax();
            return idx;
        }

    }


    int Evaluationfunction(Board temp)
    {

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


        }
        else if(heuristic==4)
        {


        }

    }




};







int main()
{


    Board b;

    int player=1;
    int idx,nxturn;
    bool endg;

    cout<< "Initial Board\n";

    b.PrintBoard();



    while(true)
    {

        endg=b.Endgame();
        if(endg==true)
            break;

        if(player==1)
        {
            cout<< "Player 1 turn\n";
            cout<< "Choose index: ";
            cin>> idx;

            nxturn=b.UpdateBoard(1,idx-1);
        }

        else if(player==2)
        {
            cout<< "Player 2 turn\n";
            cout<< "Choose index: ";
            cin>> idx;

            nxturn=b.UpdateBoard(2,idx-1);
        }


        b.PrintBoard();
        player=nxturn;
        continue;

    }


    b.Winner();

    return 0;
}

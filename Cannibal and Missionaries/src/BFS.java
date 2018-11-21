import java.lang.reflect.Array;
import java.util.*;

public class BFS {

    public void bfs(State startstate)
    {
        long excecstart=System.currentTimeMillis();
        long bfsstarttime=System.currentTimeMillis();

        State target=null;

        Queue<State> queue =new LinkedList<State>();

        queue.add(startstate);


        while(queue.size()>0)
        {

            State tempstate=queue.remove();
            Main.visitedstatelist.add(tempstate);

            boolean goal=tempstate.Isgoal();
            if(goal==true){
                target=tempstate;
                break;
            }


            if(tempstate.getboatpos()==0)
            {
                for (int i = 0; i < Main.missionariesmove.size(); i++) {
                    int m = Main.missionariesmove.get(i);
                    int c = Main.cannibalmoves.get(i);

                    if (tempstate.getmissionariesleft() >= m && tempstate.getcanniballeft() >= c ) {
                        State temp2 = new State(tempstate.getmissionariesleft() - m, tempstate.getcanniballeft() - c, tempstate.getmissionariesright() + m, tempstate.getcannibalright() + c, 1);
                        if (temp2.valid()&& Main.checkvisited(temp2) == false)
                        {
                            queue.add(temp2);
                            temp2.setparentstate(tempstate);
                        }
                    }
                }
            }

            else
            {
                for (int i = 0; i < Main.missionariesmove.size(); i++) {
                    int m = Main.missionariesmove.get(i);
                    int c = Main.cannibalmoves.get(i);

                    if (tempstate.getmissionariesright() >= m && tempstate.getcannibalright() >= c ) {
                        State temp2 = new State(tempstate.getmissionariesleft() + m, tempstate.getcanniballeft() + c, tempstate.getmissionariesright() - m, tempstate.getcannibalright() - c, 0);
                        if (temp2.valid() && Main.checkvisited(temp2) == false)
                        {
                            queue.add(temp2);
                            temp2.setparentstate(tempstate);
                        }
                    }

                }
            }
            long bfsendtime=System.currentTimeMillis();
            long timeelapsed=(bfsendtime-bfsstarttime)/1000;
            if(timeelapsed > Main.timeout)
            {
                System.out.println("Timeout!!!!!!!!!!!");
                break;
            }


        }

        long execend=System.currentTimeMillis();
        long exectime=(long)((execend-excecstart)/1000);



        if(target==null){
            System.out.println("no solution");
        }

        else
        {
            ArrayList<State> path=new ArrayList<State>();

            while (target!=null)
            {
                path.add(target);
                target=target.getparent();
            }
            boolean check=false;
            for(int i=path.size()-1;i>0;i--)
            {
                if(!check)
                {
                    System.out.println("(" + path.get(i).getmissionariesleft()+","+path.get(i).getcanniballeft()+
                            ","+path.get(i).getmissionariesright()+","+path.get(i).getcannibalright()+")" +
                            "->" + "("+path.get(i-1).getmissionariesleft()+","+path.get(i-1).getcanniballeft()+
                            ","+path.get(i-1).getmissionariesright()+","+path.get(i-1).getcannibalright()+")" );
                }
                else
                {
                    System.out.println("(" + path.get(i).getmissionariesleft()+","+path.get(i).getcanniballeft()+
                            ","+path.get(i).getmissionariesright()+","+path.get(i).getcannibalright()+")" +
                            "<-" + "("+path.get(i-1).getmissionariesleft()+","+path.get(i-1).getcanniballeft()+
                            ","+path.get(i-1).getmissionariesright()+","+path.get(i-1).getcannibalright()+")" );
                }

                check=!check;

            }
        }

        System.out.println();
        System.out.println("BFS execution time: "+(long)exectime+"s");

    }

}

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    //how many missionaries and cannibals can move
    public static List<Integer> missionariesmove = new ArrayList<Integer>();
    public static List<Integer> cannibalmoves = new ArrayList<Integer>();
    public static List<State> visitedstatelist = new ArrayList<State>();
    public static long timeout=600000;

    public static boolean checkvisited(State state) {

        for (int i = 0; i < visitedstatelist.size(); i++) {
            State temp = visitedstatelist.get(i);
            if (temp.getcanniballeft() == state.getcanniballeft()
                    && temp.getcannibalright() == state.getcannibalright()
                    && temp.getmissionariesleft() == state.getmissionariesleft()
                    && temp.getmissionariesright() == state.getmissionariesright()
                    && temp.getboatpos() == state.getboatpos()) {
                return true;
            }
        }

        return false;

    }


    public static void main(String[] args) {

        int m, c, k;

        Scanner sc = new Scanner(System.in);
        m = sc.nextInt();
        c = sc.nextInt();
        k = sc.nextInt();


        for (int i = 1; i <= k; i++) {
            for (int j = 0; j <= i; j++) {
                missionariesmove.add(j);
                cannibalmoves.add(i - j);
            }
        }

        //creating the starting state
        State state = new State(m, c, 0, 0, 0);

        //bfs

        System.out.println("BFS solution:");
        System.out.println();
        BFS bfs=new BFS();

        bfs.bfs(state);
        System.out.println();
        System.out.println("Total nodes visited for BFS: "+visitedstatelist.size());


        //clearing list for DFS
        visitedstatelist.clear();

        //dfs
        System.out.println();
        System.out.println("DFS solution:");
        System.out.println();


        DFS dfs = new DFS();

        long execstart=System.currentTimeMillis();
        dfs.dfs(state);
        long execend=System.currentTimeMillis();

        long exectime=(long)(execend-execstart);
        float time=exectime/1000.0f;


        //printing the path
        State tar= dfs.target;

        if(tar==null){
            System.out.println("no solution");
        }

        else
        {
            ArrayList<State> path=new ArrayList<State>();


            while (tar!=null)
            {
                path.add(tar);
                tar=tar.getparent();
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
                    System.out.println("(" + path.get(i-1).getmissionariesleft()+","+path.get(i-1).getcanniballeft()+
                            ","+path.get(i-1).getmissionariesright()+","+path.get(i-1).getcannibalright()+")" +
                            "<-" + "("+path.get(i).getmissionariesleft()+","+path.get(i).getcanniballeft()+
                            ","+path.get(i).getmissionariesright()+","+path.get(i).getcannibalright()+")" );
                }

                check=!check;

            }
        }

        System.out.println();
        System.out.print("DFS execution time: ");
        System.out.format("%.3f s",time);



        System.out.println();
        System.out.println("Total nodes visited for DFS: "+visitedstatelist.size());

    }

}



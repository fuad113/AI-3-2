
public class DFS {

    public static State target = null;
    public static boolean stackOverflown = false;

    public void dfs(State currentState) {

        long starttime=System.currentTimeMillis();
        boolean goal = currentState.Isgoal();

        if (goal == true) {
            target = currentState;
            return;
        }

        if (stackOverflown)
            return;

        Main.visitedstatelist.add(currentState);

        if (currentState.getboatpos() == 0) {
            for (int i = 0; i < Main.missionariesmove.size(); i++) {
                int m = Main.missionariesmove.get(i);
                int c = Main.cannibalmoves.get(i);

                if (currentState.getmissionariesleft() >= m && currentState.getcanniballeft() >= c) {
                    State temp2 = new State(currentState.getmissionariesleft() - m, currentState.getcanniballeft() - c, currentState.getmissionariesright() + m, currentState.getcannibalright() + c, 1);
                    if (temp2.valid() && Main.checkvisited(temp2) == false)
                    {
                        temp2.setparentstate(currentState);

                        try {
                            long endtime=System.currentTimeMillis();
                            long elapsedtime=(endtime-starttime)/1000;
                            if(elapsedtime > Main.timeout)
                            {
                                System.out.println("Timeout!!!!!");
                                return;
                            }
                            dfs(temp2);
                        } catch (Exception e) {
                            stackOverflown=true;
                            e.printStackTrace();
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < Main.missionariesmove.size(); i++) {
                int m = Main.missionariesmove.get(i);
                int c = Main.cannibalmoves.get(i);

                if (currentState.getmissionariesright() >= m && currentState.getcannibalright() >= c) {
                    State temp2 = new State(currentState.getmissionariesleft() + m, currentState.getcanniballeft() + c, currentState.getmissionariesright() - m, currentState.getcannibalright() - c, 0);
                    if (temp2.valid() && Main.checkvisited(temp2) == false)
                    {
                        temp2.setparentstate(currentState);
                        try {
                            long endtime=System.currentTimeMillis();
                            long elapsedtime=(endtime-starttime)/1000;
                            if(elapsedtime > Main.timeout)
                            {
                                System.out.println("Timeout!!!!!");
                                return;
                            }
                            dfs(temp2);
                        } catch (Exception e) {
                            stackOverflown=true;
                            e.printStackTrace();
                        }
                    }
                }

            }
        }
    }

}

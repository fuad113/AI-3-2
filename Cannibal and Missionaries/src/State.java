import java.util.*;

public class State {

    //in starting there is C cannibals and m missionaries

    private int cleft;
    private int mleft;
    private int cright;
    private int mright;
    private int boatpos;

    private State parentstate=null;

    public State(int mleft,int cleft,int mright,int cright,int boatpos)
    {
        this.cleft=cleft;
        this.mleft=mleft;
        this.cright=cright;
        this.mright=mright;
        this.boatpos=boatpos; //boat position 0 means left and 1 means right

    }

    public boolean valid()
    {
        if(cleft >= 0 && mleft >= 0 && cright >= 0 && mright >=0 && (mleft==0 || mleft>=cleft) && (mright==0 || mright>=cright ))
            return true;
        else
            return false;
    }

    public boolean Isgoal()
    {
        if(cleft==0 && mleft==0)
            return true;
        return false;
    }


    public void setparentstate(State parentstate)
    {
        this.parentstate=parentstate;
    }

    public int getmissionariesleft()
    {
        return mleft;
    }

    public int getcanniballeft()
    {
        return cleft;
    }

    public int getmissionariesright()
    {
        return mright;
    }

    public int getcannibalright()
    {
        return cright;
    }

    public int getboatpos()
    {
        return boatpos;
    }

    public State getparent()
    {
        return parentstate;
    }


    public void setmissionariesleft(int mleft)
    {
        this.mleft=mleft;
    }

    public void setcannibalsleft(int cleft)
    {
        this.cleft=cleft;
    }
    public void setmissionariesright(int mright)
    {
        this.mright=mright;
    }

    public void setcannibalsright(int cright)
    {
        this.cright=cright;
    }

    public void setboatpos(int boatpos)
    {
        this.boatpos=boatpos;
    }

    public void print()
    {
        System.out.println(mleft+" "+cleft+" "+mright+" "+cright+" "+boatpos);
    }

}

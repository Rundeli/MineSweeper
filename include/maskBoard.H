
#ifndef maskBoard_H
#define maskBoard_H

#include "gameBoard.H"
#include "backGroundBoard.H"

class maskBoard : public GameBoard
{
private:
    int m_play_x,m_play_y;
    char playSign = '+';

    bool** isPlayed;

    struct bound
    {
        int row_lower,row_higher;
        int col_lower,col_higher;
    };

public:

    bool isOver=0;
    
    maskBoard(std::string& diffculty)
    :GameBoard(diffculty)
    {boolInit();}

    void setValue(const int& row,const int& col,const backGoundBoard& bgb)
    {
        m_play_x=row-1;
        m_play_y=col-1;

        this->getBoard()[m_play_x][m_play_y]=playSign;
        this->isPlayed[m_play_x][m_play_y]=1;

        bound bound_outer = setBound(m_play_x,m_play_y);

        for(int r=bound_outer.row_lower;r<bound_outer.row_higher;r++){
            for(int c=bound_outer.col_lower;c<bound_outer.col_higher;c++){
                if( ((r==0)&&(c==0)) || isPlayed[m_play_x+r][m_play_y+c]){continue;}
                    else{
                            this->getBoard()[m_play_x+r][m_play_y+c]='0' + surroundingMine(m_play_x+r,m_play_y+c,bgb);
                        }
                    }
                }                 
    }
    
    void endGame(const backGoundBoard& bgb)
    {
        isOver=1;
        std::cout<<"Game Over!"<<std::endl;
        bgb.PrintBoard();
    }

    void boolInit()
    {
        for(int i=0;i<this->Getx();i++)
        {   
            isPlayed[i] = new bool[this->Gety()];
            for(int j=0;j<this->Gety();j++)
            {
                isPlayed[i][j]=0;
            }
        }
    }

    int surroundingMine(const int& x,const int& y,const backGoundBoard& bgb)
    {   
        int m,n;
        int counter=0;

        bound bound_inner = setBound(x,y);

        for(m=bound_inner.row_lower;m<bound_inner.row_higher;m++){
            for(n=bound_inner.col_lower;n<bound_inner.col_higher;n++){
                    if(bgb.getBoard()[x+m][y+n]=='x'){
                    counter+=1;
                    }
                    else 
                    {continue;}
            }
        }

        return counter;
    }

    void playDecide(const int& row,const int& col,const backGoundBoard& bgb)
    {
        if(this->isPlayed[row-1][col-1])
        {
            std::cout<<"This place is already played,try a differant place."<<std::endl;
        }
        else
        {
            if(bgb.getBoard()[row-1][col-1]=='o')
            {
                this->setValue(row,col,bgb);
            }
            else if(bgb.getBoard()[row-1][col-1]=='x')
            {
                endGame(bgb);
            }
        }
    }

    bound setBound(const int& x,const int& y)
    {
        bound b;

        b.row_lower = (x > 0) ? -1 : 0;
        b.row_higher = (x < Getx() - 1) ? 2 : 1;
 
        b.col_lower = (y > 0) ? -1 : 0;
        b.col_higher = (y < Gety() - 1) ? 2 : 1;

        return b;
    }

    ~maskBoard()
    {
        for(int row=0;row<this->Getx();row++)
        {
            delete[] isPlayed[row];
            delete[] this->getBoard()[row];
        }
    }
};

#endif

#ifndef maskBoard_H
#define maskBoard_H

#include <queue>
#include <utility>

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

        setPlayed(m_play_x,m_play_y);

        if(this->surroundingMine(m_play_x,m_play_y,bgb))
        {
            normalHit(m_play_x,m_play_y,bgb);
        }
        else
        {
            blankSpotHit(m_play_x,m_play_y,bgb);
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
                    if(bgb.getBoard()[x+m][y+n]=='X'){
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
            if(bgb.getBoard()[row-1][col-1]=='O')
            {
                this->setValue(row,col,bgb);
            }
            else if(bgb.getBoard()[row-1][col-1]=='X')
            {
                endGame(bgb);
            }
        }
    }

    void setPlayed(const int& row,const int& col)
    {
        this->getBoard()[row][col]=playSign;
        this->isPlayed[row][col]=1;
    }

    void blankSpotHit(const int& row,const int& col,const backGoundBoard& bgb)
    {

        std::queue<std::pair<int,int>> blankspotPos;
    
        blankspotPos.push({row,col});

        while(!blankspotPos.empty())
        {
            auto [x,y] = blankspotPos.front();
            blankspotPos.pop();
            bound bound_ = setBound(x,y);

            for(int r=bound_.row_lower;r<bound_.row_higher;r++){
                for(int c=bound_.col_lower;c<bound_.col_higher;c++){
                    if( ((r==0)&&(c==0)) || isPlayed[x+r][y+c]){continue;}
                        else{
                                if(this->surroundingMine(x+r,y+c,bgb)==0)
                                {
                                    setPlayed(x+r,y+c);
                                    blankspotPos.push({x+r,y+c});
                                }
                                else
                                {
                                    getBoard()[x+r][y+c]='0' + surroundingMine(x+r,y+c,bgb);
                                }
                    }
                }
            }
        }
    }

    void normalHit(const int& row,const int& col,const backGoundBoard& bgb)
    {
        bound bound_outer = setBound(row,col);

        for(int r=bound_outer.row_lower;r<bound_outer.row_higher;r++){
            for(int c=bound_outer.col_lower;c<bound_outer.col_higher;c++){
                if( ((r==0)&&(c==0)) || isPlayed[row+r][col+c]){continue;}
                    else{
                            if(surroundingMine(row+r,col+c,bgb))
                            this->getBoard()[row+r][col+c]='0' + surroundingMine(row+r,col+c,bgb);
                            else
                            {
                                blankSpotHit(row+r,col+c,bgb);
                            }
                        }
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

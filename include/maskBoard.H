
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

    bool isOver=1;
    
    maskBoard(std::string& diffculty)
    :GameBoard(diffculty)
    {};

    void setValue(const int& row,const int& col,const backGoundBoard& bgb)
    {
        m_play_x=row-1;
        m_play_y=col-1;

        boolInit();
        if(bgb.getValue(m_play_x,m_play_y)=='o')
        {
            if(!isPlayed[m_play_x][m_play_y])
            {
                this->gameBoard_[m_play_x][m_play_y]=playSign;
                this->isPlayed[m_play_x][m_play_y]=1;

                bound bound_outer = setBound(m_play_x,m_play_y);

                for(int r=bound_outer.row_lower;r<bound_outer.row_higher;r++){
                    for(int c=bound_outer.col_lower;c<bound_outer.col_higher;c++){
                        if( ((r==0)&&(c==0)) || isPlayed[m_play_x+r][m_play_y+c]){continue;}
                        else{
                            this->gameBoard_[m_play_x+r][m_play_y+c]='0' + surroundingMine(m_play_x+r,m_play_y+c,bgb);
                        }
                    }
                }
            }
            else
            {
                std::cout<<"This place is already played!"<<std::endl;
            }
        }
        else
        {
            endGame(bgb);
        }
    }
    
    void endGame(const backGoundBoard& bgb)
    {
        isOver=0;
        this->gameBoard_=bgb.gameBoard_;
        std::cout<<"Game Over!"<<std::endl;
        this->PrintBoard();
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
                    if(bgb.gameBoard_[x+m][y+n]=='x'){
                    counter+=1;
                    }
                    else 
                    {continue;}
            }
        }

        return counter;
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

    void PrintBoard()
    {
        for(int row=0;row<this->Getx();row++){
            std::cout<<std::endl;
            for(int col=0;col<this->Gety();col++)
                std::cout<<this->gameBoard_[row][col]<<' ';
        }
        std::cout<<std::endl;
    }

    ~maskBoard()
    {
        for(int row=0;row<this->Getx();row++)
        {
            delete[] isPlayed[row];
            delete[] this->gameBoard_[row];
        }
    }
};

#endif

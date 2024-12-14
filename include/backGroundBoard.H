#ifndef backGoundBoard_H
#define backGoundBoard_H

#include <cstdlib>
#include <ctime>
#include "gameBoard.H"

class backGoundBoard : public GameBoard
{

private:

    int m_mine_x,m_mine_y;

public:

    backGoundBoard(std::string& diffculty)
    :GameBoard(diffculty){}

    void setMine()
    {
        srand(time(0));

        int i;

        for(i=0;i<getMineNum();i++)
        { 
            m_mine_x =(rand()%(Getx()));
            m_mine_y =(rand()%(Gety()));

            if(!(gameBoard_[m_mine_x][m_mine_y]=='x'))
                gameBoard_[m_mine_x][m_mine_y]='x';
            else
                i-=1;
        }
    }

    ~backGoundBoard()
    {
        for(int row=0;row<this->Getx();row++)
        {
            delete[] this->gameBoard_[row];
        }
    }
};

#endif

#ifndef gameBoard_H
#define gameBoard_H

#include <string>
#include <iostream>
#include <ostream>

class GameBoard
{
    private:
    int m_size_x,m_size_y,m_mineNum;
    std::string m_diffculty;

    public:

    char** gameBoard_;

    GameBoard(const std::string& diffculty)
    :m_diffculty(diffculty)
    {
        setSize();
        setBoard();
        setInitalValue(gameBoard_);
        setMine();     
    }

    GameBoard(const GameBoard& gambo)
    {
        this->m_size_x=gambo.Getx();
        this->m_size_y=gambo.Gety();

        char** gameboard = new char* [m_size_x];
        for(int row=0;row<m_size_x;row++)
            gameboard[row] = new char[m_size_y];

        for(int i=0;i<m_size_x;i++)
            for(int j=0;j<m_size_y;j++)
            gameBoard_[i][j]=gambo.getValue(i,j);
    }

    int Getx() const
    {return m_size_x;}

    int Gety() const
    {return m_size_y;}

    void setSize() 
    {
        if (m_diffculty=="EASY")
        {
            m_size_x=10;m_size_y=10;m_mineNum=40;
        }
        else if(m_diffculty=="MEDIUM")
        {
            m_size_x=15;m_size_y=15;m_mineNum=70;
        }
        else //m_diffculty=="HARD"
        {
            m_size_x=20;m_size_y=20;m_mineNum=100;
        }
    }

    void setBoard()
    {
        char** gameboard = new char* [m_size_x];
        for(int row=0;row<m_size_x;row++)
            gameboard[row] = new char[m_size_y];
        gameBoard_=gameboard;
    }

    void setInitalValue(char** gmb)
    {
        for(int i=0;i<m_size_x;i++)
            for(int j=0;j<m_size_y;j++)
            gmb[i][j]='o';
    }

    char getValue(int& row,int& col) const
    {
        return gameBoard_[row][col];
    }

    int getMineNum() const
    {
        return m_mineNum;
    }

    virtual void setValue(const int& row,const int& col,const GameBoard& gb){}; //play on maskBoard
    
    virtual void setMine(){};  //set mine for backgoundBoard

    virtual void PrintBoard(){};

    virtual ~GameBoard()=default;
  

    GameBoard& operator=(const GameBoard&) = delete;
};

#endif
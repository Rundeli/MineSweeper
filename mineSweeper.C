#include "backGroundBoard.H"
#include "maskBoard.H"


void setDiffculty(std::string& diff_)
{
    std::cout<<"Select your gameplay diffculty,options are EASY,MEDIUM or HARD"<<std::endl;
    while (true)
    {
        std::cin>>diff_;

        if(diff_ !="EASY" && diff_!="MEDIUM" && diff_!="HARD")
        {
            std::cout<<"Enter EASY,MEDIUM or HARD"<<std::endl;
        }
        else
        {
            std::cout<<"You have chosen "<<diff_<<",enjoy your game!"<<std::endl;
            break;
        }
    }
}

void play(const int& m_round_,int& m_play_x,int& m_play_y,const backGoundBoard& m_bgb,maskBoard& m_msb)
{
    std::cout<<std::endl;
    std::cout<<"Enter your move,ROUND"<<m_round_<<std::endl;
    std::cout<<"row:";
    std::cin>>m_play_x;
    std::cout<<"col:";
    std::cin>>m_play_y;

    m_msb.playDecide(m_play_x,m_play_y,m_bgb);
}

int main()
{
    std::string diffculty;
    setDiffculty(diffculty);

    backGoundBoard bgb(diffculty);
    bgb.setMine();
    maskBoard msb(diffculty);

    msb.PrintBoard();

    int play_x,play_y;
    int round_=1;

    while (round_<bgb.getMineNum())
    {
        play(round_,play_x,play_y,bgb,msb);

        if(msb.isOver)
        {break;}
        msb.PrintBoard();
        round_++;
    }

    if(!msb.isOver){std::cout<<"Congraulation! You win!"<<std::endl;}

    return 0;
}


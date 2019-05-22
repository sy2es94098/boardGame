#include "mainwindow.h"
#include<QDebug>

mainwindow::mainwindow(QWidget *parent): QWidget(parent)
{
    srand(time(nullptr));

    this->setFixedSize(1300,1000);
    this->setWindowTitle("Chinese Chess");

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/chessimg/chessBoard.jpg")));
    this->setPalette(palette);

    bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/chessimg/back.jpg"));
    bg->setGeometry(0,0,1300,1000);
    bg->show();

    card = new QLabel(this);
    card->setPixmap(QPixmap(":/chessimg/JOJO/cardBack.png"));
    card->setGeometry(0,0,1300,1000);
    card->hide();

    edit = false;
    kingCrimsonR = false;
    kingCrimsonB = false;
    zawarudo = false;
    star = false;
    run = false;

    player1Time=new QLabel("步時: 00:00:00",this);
    player1Time->setGeometry(1120,180,150,40);
    player2Time=new QLabel("步時: 00:00:00",this);
    player2Time->setGeometry(1120,780,150,40);
    sumTime=new QLabel("局時: 00:00:00",this);
    sumTime->setGeometry(1120,250,150,40);
    player1Time->hide();
    player2Time->hide();
    sumTime->hide();

    Timer =new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(timeOutSlots()));

    stepTime=0;
    sumTimeRecord=0;
    gameOver=true;

    startGame=new QPushButton("遊戲開始",this);
    startGame->setGeometry(1130,400,100,40);

    regretGame=new QPushButton("悔棋",this);
    regretGame->setGeometry(1130,450,100,40);
    regretGame->hide();

    exitGame=new QPushButton("離開遊戲",this);
    exitGame->setGeometry(1130,550,100,40);

    editGame = new QPushButton("自訂遊戲", this);
    editGame -> setGeometry(1130, 500, 100, 40);
    editGame->hide();

    editEnd = new QPushButton("結束編輯", this);
    editEnd -> setGeometry(1130, 500, 100, 40);
    editEnd->hide();

    timing = new QPushButton("顯示時間", this);
    timing -> setGeometry(1130, 600, 100, 40);
    timing->hide();

    RSkill = new QPushButton("技能卡",this);
    RSkill->setGeometry(1130,700,100,40);
    RSkill->hide();

    BSkill = new QPushButton("技能卡",this);
    BSkill->setGeometry(1130,300,100,40);
    BSkill->hide();

    cancel = new QPushButton("取消",this);
    cancel->setGeometry(1130,200,100,40);
    cancel->hide();

    Gio = new QPushButton(this);
    Gio->setGeometry(80,20,293,419);
    Gio -> setIcon(QIcon(":/chessimg/JOJO/Gio.jpg"));
    Gio -> setIconSize(Gio -> size());
    Gio->hide();

    Boss = new QPushButton(this);
    Boss->setGeometry(448,20,290,420);
    Boss -> setIcon(QIcon(":/chessimg/JOJO/Diavolo.png"));
    Boss -> setIconSize(Boss -> size());
    Boss->hide();

    Dio = new QPushButton(this);
    Dio->setGeometry(833,20,285,411);
    Dio -> setIcon(QIcon(":/chessimg/JOJO/Dio.jpg"));
    Dio -> setIconSize(Dio -> size());
    Dio->hide();

    Jotaro = new QPushButton(this);
    Jotaro->setGeometry(20,470,339,512);
    Jotaro -> setIcon(QIcon(":/chessimg/JOJO/Jotaro.jpg"));
    Jotaro -> setIconSize(Jotaro -> size());
    Jotaro->hide();

    Joseph = new QPushButton(this);
    Joseph->setGeometry(379,470,402,505);
    Joseph -> setIcon(QIcon(":/chessimg/JOJO/Joseph.jpg"));
    Joseph -> setIconSize(Joseph -> size());
    Joseph->hide();

    Kira = new QPushButton(this);
    Kira->setGeometry(801,460,406,522);
    Kira -> setIcon(QIcon(":/chessimg/JOJO/Kira.png"));
    Kira -> setIconSize(Kira -> size());
    Kira->hide();

    connect(startGame,SIGNAL(clicked(bool)),this,SLOT(startGameSlots()));
    connect(regretGame,SIGNAL(clicked(bool)),this,SLOT(regretGameSlots()));
    connect(exitGame,SIGNAL(clicked(bool)),this,SLOT(exitGameSlots()));
    connect(editGame,SIGNAL(clicked(bool)),this,SLOT(editGameSlots()));
    connect(editEnd,SIGNAL(clicked(bool)),this,SLOT(editEndSlots()));
    connect(timing,SIGNAL(clicked(bool)),this,SLOT(timingSlots()));
    connect(RSkill,SIGNAL(clicked(bool)),this,SLOT(RSkillSlots()));
    connect(BSkill,SIGNAL(clicked(bool)),this,SLOT(BSkillSlots()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(cancelSlots()));
    connect(Gio,SIGNAL(clicked(bool)),this,SLOT(GioSlots()));
    connect(Boss,SIGNAL(clicked(bool)),this,SLOT(BossSlots()));
    connect(Dio,SIGNAL(clicked(bool)),this,SLOT(DioSlots()));
    connect(Jotaro,SIGNAL(clicked(bool)),this,SLOT(JotaroSlots()));
    connect(Joseph,SIGNAL(clicked(bool)),this,SLOT(JosephSlots()));
    connect(Kira,SIGNAL(clicked(bool)),this,SLOT(KiraSlots()));

}

mainwindow::~mainwindow()
{
    delete this;
}

void mainwindow::initializeCoordinate()
{
    memset(coordinate,0,90*sizeof(int));
    memset(regretRecord,0,36*sizeof(int));
    coordinate[4][0]=1;//BlackKing
    coordinate[3][0]=2;//BlackGuard
    coordinate[5][0]=2;
    coordinate[2][0]=3;//BlackElephant
    coordinate[6][0]=3;
    coordinate[1][0]=4;//BlackHorse
    coordinate[7][0]=4;
    coordinate[0][0]=5;//BlackChariot
    coordinate[8][0]=5;
    coordinate[1][2]=6;//BlackCannon
    coordinate[7][2]=6;
    for(int i=0;i<5;i++)//BlackSoldier
    {
        coordinate[2*i][3]=7;
    }
    coordinate[4][9]=-1;//Red
    coordinate[3][9]=-2;
    coordinate[5][9]=-2;
    coordinate[2][9]=-3;
    coordinate[6][9]=-3;
    coordinate[1][9]=-4;
    coordinate[7][9]=-4;
    coordinate[0][9]=-5;
    coordinate[8][9]=-5;
    coordinate[1][7]=-6;
    coordinate[7][7]=-6;
    for(int i=0;i<5;i++)
    {
        coordinate[2*i][6]=-7;
    }
    initializeMove();
}

void mainwindow::initializeMove()//清理殘留move
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<10;j++)
        {
            move[i][j]=coordinate[i][j];
        }
    }
}
void mainwindow::mousePressEvent(QMouseEvent *event)
{
    if(10<event->pos().x() && event->pos().x()<=1190 && 10<event->pos().y() && event->pos().y()<=990 && !gameOver)
    {
        for(int i=0;i<9;i++)//點擊區域轉座標
        {
            for(int j=0;j<10;j++)
            {
                if(30+119*i<=event->pos().x() && event->pos().x()<30+119*(i+1) && 10+100*j<=event->pos().y()&&event->pos().y()<10+100*(j+1))
                {

                    if(edit == true)//使用編輯
                    {
                        if(move[i][j]==10)
                        {
                            coordinate[i][j] = type;
                            move[i][j] = type;
                        }
                    }
                    else if(star == true)
                    {
                        if(coordinate[i][j] != 1 && coordinate[i][j] != -1)
                        {
                            eat(0,0,0,i,j,coordinate[i][j]);
                            star = false;
                        }
                    }
                    else if(move[i][j]==10)//10表示該位置可以移動
                    {
                        eat(Clicked_X,Clicked_Y,coordinate[Clicked_X][Clicked_Y],i,j,coordinate[i][j]);
                        run = false;
                    }
                    else  if(coordinate[i][j]==0)//0表示該位置空白且不可移動
                    {
                        initializeMove();
                        return;
                    }
                    else if(run == true)
                    {
                        if((coordinate[i][j] > 3 && coordinate[i][j] <= 7 && stepNumber%2 == 0) || (coordinate[i][j] < -3 && coordinate[i][j] >= -7 && stepNumber%2==1))
                        {
                            for(int m = 0 ; m < 9; ++m)
                            {
                                for(int n = 0; n < 10 ; ++n)
                                {
                                    if(coordinate[m][n] == 0)
                                    {
                                        move[m][n] = 10;
                                    }
                                }
                            }
                        }
                        else {
                            initializeMove();
                            return;
                        }

                    }
                    else if(stepNumber%2==0 && coordinate[i][j]>0)//黑棋回合且點擊黑棋
                    {
                         initializeMove();
                         moveChess(i,j,coordinate[i][j]);//找出該子可移動位置
                    }
                    else if(stepNumber%2==1&&coordinate[i][j]<0)//紅棋回合且點擊紅棋
                    {
                         initializeMove();
                         moveChess(i,j,coordinate[i][j]);
                    }
                    else
                    {
                        initializeMove();
                        return;
                    }
                    Clicked_X=i;//用於吃子,悔棋
                    Clicked_Y=j;
                    this->repaint();
                    if(zawarudo == true)
                    {
                        ++stepNumber;
                        zawarudo = false;
                    }
                }
            }
        }
    }
}

void mainwindow::moveChess(int i,int j,int value)//將棋子可移動之座標設為10
{
    bool Is_Skip=false;//砲是否跳過
    switch (value) {
    case 1://BlackKing
        if(i-1>=3&&coordinate[i-1][j]<=0)
            move[i-1][j]=10;
        if(i+1<=5&&coordinate[i+1][j]<=0)
            move[i+1][j]=10;
        if(j-1>=0&&coordinate[i][j+1]<=0)
            move[i][j-1]=10;
        if(j+1<=2&&coordinate[i][j+1]<=0)
            move[i][j+1]=10;
        break;
    case 2://BlackGuard
        if(i-1>=3&&j-1>=0&&coordinate[i-1][j-1]<=0)
            move[i-1][j-1]=10;
        if(i-1>=3&&j+1<=2&&coordinate[i-1][j+1]<=0)
            move[i-1][j+1]=10;
        if(i+1<=5&&j-1>=0&&coordinate[i+1][j-1]<=0)
            move[i+1][j-1]=10;
        if(i+1<=5&&j+1<=2&&coordinate[i+1][j+1]<=0)
            move[i+1][j+1]=10;
        break;
    case 3://BlackElephant
        if(i-2>=0&&j-2>=0&&coordinate[i-1][j-1]==0&&coordinate[i-2][j-2]<=0)
            move[i-2][j-2]=10;
        if(i-2>=0&&j+2<=4&&coordinate[i-1][j+1]==0&&coordinate[i-2][j+2]<=0)
            move[i-2][j+2]=10;
        if(i+2<=8&&j-2>=0&&coordinate[i+1][j-1]==0&&coordinate[i+2][j-2]<=0)
            move[i+2][j-2]=10;
        if(i+2<=8&&j+2<=4&&coordinate[i+1][j+1]==0&&coordinate[i+2][j+2]<=0)
            move[i+2][j+2]=10;
        break;
    case 4://BlackHorse
        if(i-2>=0&&j-1>=0&&coordinate[i-1][j]==0&&coordinate[i-2][j-1]<=0)
            move[i-2][j-1]=10;
        if(i-1>=0&&j-2>=0&&coordinate[i][j-1]==0&&coordinate[i-1][j-2]<=0)
            move[i-1][j-2]=10;
        if(i-2>=0&&j+1<=9&&coordinate[i-1][j]==0&&coordinate[i-2][j+1]<=0)
            move[i-2][j+1]=10;
        if(i-1>=0&&j+2<=9&&coordinate[i][j+1]==0&&coordinate[i-1][j+2]<=0)
            move[i-1][j+2]=10;
        if(i+2<=8&&j-1>=0&&coordinate[i+1][j]==0&&coordinate[i+2][j-1]<=0)
            move[i+2][j-1]=10;
        if(i+1<=8&&j-2>=0&&coordinate[i][j-1]==0&&coordinate[i+1][j-2]<=0)
            move[i+1][j-2]=10;
        if(i+2<=8&&j+1<=9&&coordinate[i+1][j]==0&&coordinate[i+2][j+1]<=0)
            move[i+2][j+1]=10;
        if(i+1<=8&&j+2<=9&&coordinate[i][j+1]==0&&coordinate[i+1][j+2]<=0)
            move[i+1][j+2]=10;
        break;
    case 5://BlackChariot
        for(int x=1;x<=8;x++)
        {
            if(i+x<=8&&coordinate[i+x][j]==0)
                move[i+x][j]=10;
            else  if(i+x<=8&&coordinate[i+x][j]<0)
            {
                move[i+x][j]=10;
                break;
            }
            else  break;
        }
        for(int x=1;x<=8;x++)
        {
            if(i-x>=0&&coordinate[i-x][j]==0)
                move[i-x][j]=10;
            else  if(i-x>=0&&coordinate[i-x][j]<0)
            {
                move[i-x][j]=10;
                break;
            }
            else  break;
        }
        for(int x=1;x<=9;x++)
        {
            if(j+x<=9&&coordinate[i][j+x]==0)
                move[i][j+x]=10;
            else  if(j+x<=9&&coordinate[i][j+x]<0)
            {
                move[i][j+x]=10;
                break;
            }
            else  break;
        }
        for(int x=1;x<=9;x++)
        {
            if(j-x>=0&&coordinate[i][j-x]==0)
                move[i][j-x]=10;
            else  if(j-x>=0&&coordinate[i][j-x]<0)
            {
                move[i][j-x]=10;
                break;
            }
            else  break;
        }

        break;
    case 6://BlackCannon
        Is_Skip=false;
        for(int x=1;x<=8;x++)
        {
            if(i+x<=8&&coordinate[i+x][j]==0&&!Is_Skip)
                move[i+x][j]=10;
            else  if(i+x<=8&&coordinate[i+x][j]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(i+x<=8&&coordinate[i+x][j]<0&&Is_Skip)
            {
                move[i+x][j]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=8;x++)
        {
            if(i-x>=0&&coordinate[i-x][j]==0&&!Is_Skip)
                move[i-x][j]=10;
            else  if(i-x>=0&&coordinate[i-x][j]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(i-x>=0&&coordinate[i-x][j]<0&&Is_Skip)
            {
                move[i-x][j]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=9;x++)
        {
            if(j+x<=9&&coordinate[i][j+x]==0&&!Is_Skip)
                move[i][j+x]=10;
            else  if(j+x<=9&&coordinate[i][j+x]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(j+x<=9&&coordinate[i][j+x]<0&&Is_Skip)
            {
                move[i][j+x]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=9;x++)
        {
            if(j-x>=0&&coordinate[i][j-x]==0&&!Is_Skip)
                move[i][j-x]=10;
            else  if(j-x>=0&&coordinate[i][j-x]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(j-x>=0&&coordinate[i][j-x]<0&&Is_Skip)
            {
                move[i][j-x]=10;
                break;
            }
        }
        break;
    case 7://BlackSoldier
        if(j<5)
        {
            if(coordinate[i][j+1]<=0)
            move[i][j+1]=10;
        }
        else
        {
            if(i-1>=0&&coordinate[i-1][j]<=0)
                move[i-1][j]=10;
            if(i+1<=8&&coordinate[i+1][j]<=0)
                move[i+1][j]=10;
            if(j+1<=9&&coordinate[i][j+1]<=0)
                move[i][j+1]=10;
        }
        break;
    case -1:
        if(i-1>=3&&coordinate[i-1][j]>=0)
            move[i-1][j]=10;
        if(i+1<=5&&coordinate[i+1][j]>=0)
            move[i+1][j]=10;
        if(j-1>=7&&coordinate[i][j-1]>=0)
            move[i][j-1]=10;
        if(j+1<=9&&coordinate[i][j+1]>=0)
            move[i][j+1]=10;
        break;
    case -2:
        if(i-1>=3&&j-1>=7&&coordinate[i-1][j-1]>=0)
            move[i-1][j-1]=10;
        if(i-1>=3&&j+1<=9&&coordinate[i-1][j+1]>=0)
            move[i-1][j+1]=10;
        if(i+1<=5&&j-1>=7&&coordinate[i+1][j-1]>=0)
            move[i+1][j-1]=10;
        if(i+1<=5&&j+1<=9&&coordinate[i+1][j+1]>=0)
            move[i+1][j+1]=10;
        break;
    case -3:
        if(i-2>=0&&j-2>=5&&coordinate[i-1][j-1]==0&&coordinate[i-2][j-2]>=0)
            move[i-2][j-2]=10;
        if(i-2>=0&&j+2<=9&&coordinate[i-1][j+1]==0&&coordinate[i-2][j+2]>=0)
            move[i-2][j+2]=10;
        if(i+2<=8&&j-2>=5&&coordinate[i+1][j-1]==0&&coordinate[i+2][j-2]>=0)
            move[i+2][j-2]=10;
        if(i+2<=8&&j+2<=9&&coordinate[i+1][j+1]==0&&coordinate[i+2][j+2]>=0)
            move[i+2][j+2]=10;
        break;
    case -4:
        if(i-2>=0&&j-1>=0&&coordinate[i-1][j]==0&&coordinate[i-2][j-1]>=0)
            move[i-2][j-1]=10;
        if(i-1>=0&&j-2>=0&&coordinate[i][j-1]==0&&coordinate[i-1][j-2]>=0)
            move[i-1][j-2]=10;
        if(i-2>=0&&j+1<=9&&coordinate[i-1][j]==0&&coordinate[i-2][j+1]>=0)
            move[i-2][j+1]=10;
        if(i-1>=0&&j+2<=9&&coordinate[i][j+1]==0&&coordinate[i-1][j+2]>=0)
            move[i-1][j+2]=10;
        if(i+2<=8&&j-1>=0&&coordinate[i+1][j]==0&&coordinate[i+2][j-1]>=0)
            move[i+2][j-1]=10;
        if(i+1<=8&&j-2>=0&&coordinate[i][j-1]==0&&coordinate[i+1][j-2]>=0)
            move[i+1][j-2]=10;
        if(i+2<=8&&j+1<=9&&coordinate[i+1][j]==0&&coordinate[i+2][j+1]>=0)
            move[i+2][j+1]=10;
        if(i+1<=8&&j+2<=9&&coordinate[i][j+1]==0&&coordinate[i+1][j+2]>=0)
            move[i+1][j+2]=10;
        break;
    case -5:
        for(int x=1;x<=8;x++)
        {
            if(i+x<=8&&coordinate[i+x][j]==0)
                move[i+x][j]=10;
            else  if(i+x<=8&&coordinate[i+x][j]>0)
            {
                move[i+x][j]=10;
                break;
            }
            else break;
        }
        for(int x=1;x<=8;x++)
        {
            if(i-x>=0&&coordinate[i-x][j]==0)
                move[i-x][j]=10;
            else  if(i-x>=0&&coordinate[i-x][j]>0)
            {
                move[i-x][j]=10;
                break;
            }
            else break;
        }
        for(int x=1;x<=9;x++)
        {
            if(j+x<=9&&coordinate[i][j+x]==0)
                move[i][j+x]=10;
            else  if(j+x<=9&&coordinate[i][j+x]>0)
            {
                move[i][j+x]=10;
                break;
            }
            else break;
        }
        for(int x=1;x<=9;x++)
        {
            if(j-x>=0&&coordinate[i][j-x]==0)
                move[i][j-x]=10;
            else  if(j-x>=0&&coordinate[i][j-x]>0)
            {
                move[i][j-x]=10;
                break;
            }
            else break;
        }
        break;
    case -6:
        Is_Skip=false;
        for(int x=1;x<=8;x++)
        {
            if(i+x<=8&&coordinate[i+x][j]==0&&!Is_Skip)
                move[i+x][j]=10;
            else  if(i+x<=8&&coordinate[i+x][j]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(i+x<=8&&coordinate[i+x][j]>0&&Is_Skip)
            {
                move[i+x][j]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=8;x++)
        {
            if(i-x>=0&&coordinate[i-x][j]==0&&!Is_Skip)
                move[i-x][j]=10;
            else  if(i-x>=0&&coordinate[i-x][j]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(i-x>=0&&coordinate[i-x][j]>0&&Is_Skip)
            {
                move[i-x][j]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=9;x++)
        {
            if(j+x<=9&&coordinate[i][j+x]==0&&!Is_Skip) move[i][j+x]=10;
            else  if(j+x<=9&&coordinate[i][j+x]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(j+x<=9&&coordinate[i][j+x]>0&&Is_Skip)
            {
                move[i][j+x]=10;
                break;
            }
        }
        Is_Skip=false;
        for(int x=1;x<=9;x++)
        {
            if(j-x>=0&&coordinate[i][j-x]==0&&!Is_Skip)
                move[i][j-x]=10;
            else  if(j-x>=0&&coordinate[i][j-x]!=0&&!Is_Skip)
            {
                Is_Skip=true;
            }
            else if(j-x>=0&&coordinate[i][j-x]>0&&Is_Skip)
            {
                move[i][j-x]=10;
                break;
            }
        }
        break;
    case -7:
        if(j>4)
        {
            if(coordinate[i][j-1]>=0)
            move[i][j-1]=10;
        }
        else
        {
            if(i-1>=0&&coordinate[i-1][j]>=0)
                move[i-1][j]=10;
            if(i+1<=8&&coordinate[i+1][j]>=0)
                move[i+1][j]=10;
            if(j-1>=0&&coordinate[i][j-1]>=0)
                move[i][j-1]=10;
        }
        break;
    default:  break;
    }

}

void mainwindow::eat(int Eat_x, int Eat_y , int Eat_value, int Eaten_x, int Eaten_y, int Eaten_value)//移動與吃子
{
    stepTime=0;//移動後,步時歸0
    stepNumber++;//移動後,回合+1
    regretTimes=0;//移動後,悔棋數歸0
    regretRecord[stepNumber%6][0]=Eat_x;//保存悔棋座標
    regretRecord[stepNumber%6][1]=Eat_y;
    regretRecord[stepNumber%6][2]=Eat_value;
    regretRecord[stepNumber%6][3]=Eaten_x;
    regretRecord[stepNumber%6][4]=Eaten_y;
    regretRecord[stepNumber%6][5]=Eaten_value;

    coordinate[Eat_x][Eat_y]=0;
    coordinate[Eaten_x][Eaten_y]=Eat_value;

    initializeMove();
    isWin();

    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }

    if(Eaten_value != 0 && stepNumber%2 == 1)
    {
        getCard = rand()%6;
        switch(getCard){
        case 0 : count = deckB[0];
                 count +=1;
                 deckB[0] = count;
                 QMessageBox::information(this,"Get Card","Giorno",QMessageBox::Yes);
            break;
        case 1 : count = deckB[1];
                 count +=1;
                 deckB[1] = count;
                 QMessageBox::information(this,"Get Card","Diavolo",QMessageBox::Yes);
            break;
        case 2 : count = deckB[2];
                 count +=1;
                 deckB[2] = count;
                 QMessageBox::information(this,"Get Card","Dio",QMessageBox::Yes);
            break;
        case 3 : count = deckB[3];
                 count +=1;
                 deckB[3] = count;
                 QMessageBox::information(this,"Get Card","Jotaro",QMessageBox::Yes);
            break;
        case 4 : count = deckB[4];
                 count +=1;
                 deckB[4] = count;
                 QMessageBox::information(this,"Get Card","Joseph",QMessageBox::Yes);
            break;
        case 5 : count = deckB[5];
                 count +=1;
                 deckB[5] = count;
                 QMessageBox::information(this,"Get Card","Kira",QMessageBox::Yes);
            break;
        }

    }

    if(Eaten_value != 0 && stepNumber%2 == 0)
    {
        getCard = rand()%6;
        switch(getCard){
        case 0 : count = deckR[0];
                 count +=1;
                 deckR[0] = count;
                 QMessageBox::information(this,"Get Card","Giorno",QMessageBox::Yes);
            break;
        case 1 : count = deckR[1];
                 count +=1;
                 deckR[1] = count;
                 QMessageBox::information(this,"Get Card","Diavolo",QMessageBox::Yes);
            break;
        case 2 : count = deckR[2];
                 count +=1;
                 deckR[2] = count;
                 QMessageBox::information(this,"Get Card","Dio",QMessageBox::Yes);
            break;
        case 3 : count = deckR[3];
                 count +=1;
                 deckR[3] = count;
                 QMessageBox::information(this,"Get Card","Jotaro",QMessageBox::Yes);
            break;
        case 4 : count = deckR[4];
                 count +=1;
                 deckR[4] = count;
                 QMessageBox::information(this,"Get Card","Joseph",QMessageBox::Yes);
            break;
        case 5 : count = deckR[5];
                 count +=1;
                 deckR[5] = count;
                 QMessageBox::information(this,"Get Card","Kira",QMessageBox::Yes);
            break;
        default:    break;
        }
    }
}

void mainwindow::isWin()
{
    gameOver=true;
    int Boss_Is_Meet[4]={0,0,0,0};
    for(int i=1;i<2;i++)
    {
        for(int i=3;i<=5;i++)//判斷將是否存在
        {
            for(int j=0;j<=2;j++)
            {
                if(coordinate[i][j]==1)
                {
                    gameOver=false;
                    Boss_Is_Meet[0]=i;
                    Boss_Is_Meet[1]=j;
                }
            }
        }
        if(gameOver) break;

        gameOver=true;
        for(int i=3;i<=5;i++)//判斷帥是否存在
        {
            for(int j=7;j<=9;j++)
            {
                if(coordinate[i][j]==-1)
                {
                    gameOver=false;
                    Boss_Is_Meet[2]=i;
                    Boss_Is_Meet[3]=j;
                }
            }
        }
        if(gameOver) break;

        if(Boss_Is_Meet[0]==Boss_Is_Meet[2])//判斷王見王
        {
            gameOver=true;
            for(int i=Boss_Is_Meet[1]+1;i<Boss_Is_Meet[3];i++)
            {
                if(coordinate[Boss_Is_Meet[0]][i]!=0)
                {
                    gameOver=false;
                    break;
                }
            }
            if(gameOver==true)
            {
                stepNumber++;
            }
        }
    }
    if(gameOver==true)
    {
        QString Winer=(stepNumber%2==0? "红棋":"黑棋");
        Timer->stop();
        stepNumber=0;
        QMessageBox::information(this,"棋局勝負：",Winer+"取得勝利！",QMessageBox::Yes);
    }
}

void mainwindow::buttonClean()//清除殘留Move
{
    for(int i = 0 ; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <=9 ; ++j)
        {
            if(coordinate[i][j]==10)
            {
                coordinate[i][j] = 0;
            }
        }
    }
    initializeMove();
}
void mainwindow::timeOutSlots()
{
    stepTime++;
    sumTimeRecord++;
    QString step_time="步時："+QString("%1").arg(stepTime/3600%60, 2, 10,QChar('0'))
            +":"+QString("%2").arg(stepTime/60%60, 2, 10, QChar('0'))
            +":"+QString("%3").arg(stepTime%60, 2, 10, QChar('0'));
    (stepNumber%2==0? player1Time:player2Time)->setText(step_time);
    QString sum_time="局時："+QString("%1").arg(sumTimeRecord/3600%60, 2, 10,QChar('0'))
            +":"+QString("%2").arg(sumTimeRecord/60%60, 2, 10, QChar('0'))
            +":"+QString("%3").arg(sumTimeRecord%60, 2, 10, QChar('0'));
    sumTime->setText(sum_time);

}

void mainwindow::startGameSlots()
{
    for(int i = 0 ; i < 6 ; ++i)
    {
        deckR[i] = 0;
        deckB[i] = 0;
    }
    bg->hide();
    editGame->show();
    timing->show();
    BSkill->show();

    regretTimes=0;
    Clicked_X=0;
    Clicked_Y=0;
    stepNumber=0;
    stepTime=0;
    sumTimeRecord=0;
    gameOver=false;
    kingCrimsonB=false;
    kingCrimsonR=false;
    startGame->setText("新的一局");
    initializeCoordinate();
    this->repaint();
    Timer->start(1000);
    player1Time->setText("步時: 00:00:00");
    player2Time->setText("步時: 00:00:00");

    if(stepNumber%2 == 0)	//判斷悔棋技能，有發動者在它的回合顯示悔棋鈕
    {
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
              }
        }
    if(stepNumber%2 == 1)
    {
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }

}

void mainwindow::regretGameSlots()
{
    if(stepNumber<=0||regretTimes>1)
        return;

    int Eat_x=regretRecord[stepNumber%6][0];
    int Eat_y=regretRecord[stepNumber%6][1];
    coordinate[Eat_x][Eat_y]=regretRecord[stepNumber%6][2];
    int Eaten_x=regretRecord[stepNumber%6][3];
    int Eaten_y=regretRecord[stepNumber%6][4];
    coordinate[Eaten_x][Eaten_y]=regretRecord[stepNumber%6][5];
    initializeMove();
    Clicked_X=regretRecord[stepNumber%6][0];
    Clicked_Y=regretRecord[stepNumber%6][1];
    stepNumber--;
    regretTimes++;

    this->repaint();
}

void mainwindow::editGameSlots()
{
    for(int i = 0 ; i < 6 ; ++i)
    {
        deckR[i] = 0;
        deckB[i] = 0;
    }
    edit = true;
    startGame -> hide();
    regretGame -> hide();
    RSkill->hide();
    BSkill->hide();

    editGame->hide();
    editEnd->show();
    sumTime -> hide();
    timing -> hide();
    blackKing = new QPushButton(this);
    blackKing -> setIcon(QIcon(":/chessimg/kingB.png"));
    blackKing -> setGeometry(1160,20,80,80);
    blackKing -> setIconSize(blackKing -> size());
    blackKing -> show();
    blackGuard = new QPushButton(this);
    blackGuard -> setIcon(QIcon(":/chessimg/guardB.png"));
    blackGuard -> setGeometry(1110,110,80,80);
    blackGuard -> setIconSize(blackKing -> size());
    blackGuard -> show();
    blackElephant = new QPushButton(this);
    blackElephant -> setIcon(QIcon(":/chessimg/elephantB.png"));
    blackElephant -> setGeometry(1210,110,80,80);
    blackElephant -> setIconSize(blackKing -> size());
    blackElephant -> show();
    blackHorse = new QPushButton(this);
    blackHorse -> setIcon(QIcon(":/chessimg/horseB.png"));
    blackHorse -> setGeometry(1110,200,80,80);
    blackHorse -> setIconSize(blackKing -> size());
    blackHorse -> show();
    blackChariot = new QPushButton(this);
    blackChariot -> setIcon(QIcon(":/chessimg/chariotB.png"));
    blackChariot -> setGeometry(1210,200,80,80);
    blackChariot -> setIconSize(blackKing -> size());
    blackChariot -> show();
    blackCannon = new QPushButton(this);
    blackCannon -> setIcon(QIcon(":/chessimg/cannonB.png"));
    blackCannon -> setGeometry(1110,290,80,80);
    blackCannon -> setIconSize(blackKing -> size());
    blackCannon -> show();
    blackSoldier = new QPushButton(this);
    blackSoldier -> setIcon(QIcon(":/chessimg/soldierB.png"));
    blackSoldier -> setGeometry(1210,290,80,80);
    blackSoldier -> setIconSize(blackKing -> size());
    blackSoldier -> show();
    connect(blackKing,SIGNAL(clicked(bool)),this,SLOT(blackKingSlot()));
    connect(blackGuard,SIGNAL(clicked(bool)),this,SLOT(blackGuardSlot()));
    connect(blackElephant,SIGNAL(clicked(bool)),this,SLOT(blackElephantSlot()));
    connect(blackHorse,SIGNAL(clicked(bool)),this,SLOT(blackHorseSlot()));
    connect(blackChariot,SIGNAL(clicked(bool)),this,SLOT(blackChariotSlot()));
    connect(blackCannon,SIGNAL(clicked(bool)),this,SLOT(blackCannonSlot()));
    connect(blackSoldier,SIGNAL(clicked(bool)),this,SLOT(blackSoldierSlot()));

    redKing = new QPushButton(this);
    redKing -> setIcon(QIcon(":/chessimg/kingR.png"));
    redKing -> setGeometry(1160,880,80,80);
    redKing -> setIconSize(redKing -> size());
    redKing -> show();
    redGuard = new QPushButton(this);
    redGuard -> setIcon(QIcon(":/chessimg/guardR.png"));
    redGuard -> setGeometry(1110,790,80,80);
    redGuard -> setIconSize(redKing -> size());
    redGuard -> show();
    redElephant = new QPushButton(this);
    redElephant -> setIcon(QIcon(":/chessimg/elephantR.png"));
    redElephant -> setGeometry(1210,790,80,80);
    redElephant -> setIconSize(redKing -> size());
    redElephant -> show();
    redHorse = new QPushButton(this);
    redHorse -> setIcon(QIcon(":/chessimg/horseR.png"));
    redHorse -> setGeometry(1110,700,80,80);
    redHorse -> setIconSize(redKing -> size());
    redHorse -> show();
    redChariot = new QPushButton(this);
    redChariot -> setIcon(QIcon(":/chessimg/chariotR.png"));
    redChariot -> setGeometry(1210,700,80,80);
    redChariot -> setIconSize(redKing -> size());
    redChariot -> show();
    redCannon = new QPushButton(this);
    redCannon -> setIcon(QIcon(":/chessimg/cannonR.png"));
    redCannon -> setGeometry(1110,610,80,80);
    redCannon -> setIconSize(redKing -> size());
    redCannon -> show();
    redSoldier = new QPushButton(this);
    redSoldier -> setIcon(QIcon(":/chessimg/soldierR.png"));
    redSoldier -> setGeometry(1210,610,80,80);
    redSoldier -> setIconSize(redKing -> size());
    redSoldier -> show();
    connect(redKing,SIGNAL(clicked(bool)),this,SLOT(redKingSlot()));
    connect(redGuard,SIGNAL(clicked(bool)),this,SLOT(redGuardSlot()));
    connect(redElephant,SIGNAL(clicked(bool)),this,SLOT(redElephantSlot()));
    connect(redHorse,SIGNAL(clicked(bool)),this,SLOT(redHorseSlot()));
    connect(redChariot,SIGNAL(clicked(bool)),this,SLOT(redChariotSlot()));
    connect(redCannon,SIGNAL(clicked(bool)),this,SLOT(redCannonSlot()));
    connect(redSoldier,SIGNAL(clicked(bool)),this,SLOT(redSoldierSlot()));

    memset(coordinate,0,90*sizeof(int));
    this->repaint();
    initializeMove();

    regretGame->hide();
    kingCrimsonB = false;
    if(stepNumber%2 == 0)	//判斷悔棋技能，有發動者在它的回合顯示悔棋鈕
    {
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
              }
        }
        if(stepNumber%2 == 1)
        {
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }

}

void mainwindow::editEndSlots()
{
    edit = false;
    buttonClean();
    startGame -> show();
    regretGame -> show();
    editGame->show();
    editEnd->hide();
    timing -> show();
    blackKing->hide();
    blackGuard->hide();
    blackElephant->hide();
    blackHorse->hide();
    blackChariot->hide();
    blackCannon->hide();
    blackSoldier->hide();
    redKing->hide();
    redGuard->hide();
    redElephant->hide();
    redHorse->hide();
    redChariot->hide();
    redCannon->hide();
    redSoldier->hide();
    this->repaint();

    regretGame->hide();
    kingCrimsonB = false;
    if(stepNumber%2 == 0)	//判斷悔棋技能，有發動者在它的回合顯示悔棋鈕
    {
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
              }
        }
        if(stepNumber%2 == 1)
        {
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
}

void mainwindow::timingSlots()
{
    player1Time->show();
    player2Time->show();
    sumTime->show();
}
void mainwindow::exitGameSlots()
{
    if(QMessageBox::Yes==QMessageBox::question(this,"提示：","確定要離開遊戲?",QMessageBox::Yes|QMessageBox::No))
    {
        exit(0);
    }
}

void mainwindow::blackKingSlot()
{
    buttonClean();
    type = 1;
    for(int i = 3; i <= 5 ; ++i)
    {
        for(int j = 0 ; j <= 2 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::redKingSlot()
{
    buttonClean();
    type = -1;
    for(int i = 3; i <= 5 ; ++i)
    {
        for(int j = 7 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::blackGuardSlot()
{
    buttonClean();
    type = 2;
    if(coordinate[3][0] == 0)
    coordinate[3][0] = 10;
    if(coordinate[5][0] == 0)
    coordinate[5][0] = 10;
    if(coordinate[4][1] == 0)
    coordinate[4][1] = 10;
    if(coordinate[3][2] == 0)
    coordinate[3][2] = 10;
    if(coordinate[5][2] == 0)
    coordinate[5][2] = 10;
    initializeMove();
    this -> repaint();
}

void mainwindow::redGuardSlot()
{
    buttonClean();
    type = -2;
    if(coordinate[3][9] == 0)
    coordinate[3][9] = 10;
    if(coordinate[5][9] == 0)
    coordinate[5][9] = 10;
    if(coordinate[4][8] == 0)
    coordinate[4][8] = 10;
    if(coordinate[3][7] == 0)
    coordinate[3][7] = 10;
    if(coordinate[5][7] == 0)
    coordinate[5][7] = 10;
    initializeMove();
    this -> repaint();
}

void mainwindow::blackElephantSlot()
{
    buttonClean();
    type = 3;
    if(coordinate[2][0] == 0)
    coordinate[2][0] = 10;
    if(coordinate[6][0] == 0)
    coordinate[6][0] = 10;
    if(coordinate[0][2] == 0)
    coordinate[0][2] = 10;
    if(coordinate[4][2] == 0)
    coordinate[4][2] = 10;
    if(coordinate[8][2] == 0)
    coordinate[8][2] = 10;
    if(coordinate[2][4] == 0)
    coordinate[2][4] = 10;
    if(coordinate[6][4] == 0)
    coordinate[6][4] = 10;
    initializeMove();
    this -> repaint();
}

void mainwindow::redElephantSlot()
{
    buttonClean();
    type = -3;
    if(coordinate[2][9] == 0)
    coordinate[2][9] = 10;
    if(coordinate[6][9] == 0)
    coordinate[6][9] = 10;
    if(coordinate[0][7] == 0)
    coordinate[0][7] = 10;
    if(coordinate[4][7] == 0)
    coordinate[4][7] = 10;
    if(coordinate[8][7] == 0)
    coordinate[8][7] = 10;
    if(coordinate[2][5] == 0)
    coordinate[2][5] = 10;
    if(coordinate[6][5] == 0)
    coordinate[6][5] = 10;
    initializeMove();
    this -> repaint();
}

void mainwindow::blackHorseSlot()
{
    type = 4;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::redHorseSlot()
{
    type = -4;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::blackChariotSlot()
{
    type = 5;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::redChariotSlot()
{
    type = -5;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::blackCannonSlot()
{
    type = 6;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::redCannonSlot()
{
    type = -6;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::blackSoldierSlot()
{
    type = 7;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::redSoldierSlot()
{
    type = -7;
    for(int i = 0; i <= 8 ; ++i)
    {
        for(int j = 0 ; j <= 9 ; ++j)
        {
            if(coordinate[i][j] == 0)
            coordinate[i][j] = 10;
        }
    }
    initializeMove();
    this -> repaint();
}

void mainwindow::RSkillSlots()
{
    RSkill->hide();
    card->show();
    startGame->hide();
    regretGame->hide();
    timing->hide();
    player1Time->hide();
    player2Time->hide();
    sumTime->hide();
    editGame->hide();
    exitGame->hide();
    cancel->show();

    if(deckR[0] > 0)
    Gio->show();
    if(deckR[1] > 0)
    Boss->show();
    if(deckR[2] > 0)
    Dio->show();
    if(deckR[3] > 0)
    Jotaro->show();
    if(deckR[4] > 0)
    Joseph->show();
    if(deckR[5] > 0)
    Kira->show();
}

void mainwindow::BSkillSlots()
{
    BSkill->hide();
    card->show();
    startGame->hide();
    regretGame->hide();
    timing->hide();
    player1Time->hide();
    player2Time->hide();
    sumTime->hide();
    editGame->hide();
    exitGame->hide();
    cancel->show();

    if(deckB[0] > 0)
    Gio->show();
    if(deckB[1] > 0)
    Boss->show();
    if(deckB[2] > 0)
    Dio->show();
    if(deckB[3] > 0)
    Jotaro->show();
    if(deckB[4] > 0)
    Joseph->show();
    if(deckB[5] > 0)
    Kira->show();
}

void mainwindow::cancelSlots()
{
    exitGame->show();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();

        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();

        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
}

void mainwindow::GioSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        count = deckB[0];
        --count;
        deckB[0] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    for(int i = rand()%9, j = rand()%10; ; i = rand()%9, j = rand()%10)
    {
        if(coordinate[i][j] == 0)
        {
            coordinate[i][j] = rand()%4 + 4;
            break;
        }
    }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        count = deckR[0];
        --count;
        deckR[0] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
        for(int i = rand()%9, j = rand()%10; ; i = rand()%9, j = rand()%10)
        {
            if(coordinate[i][j] == 0)
            {
                coordinate[i][j] =-(rand()%4 + 4);
                break;
            }
        }
    }
    this->repaint();

}

void mainwindow::BossSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        kingCrimsonB = true;
        BSkill->show();
        RSkill->hide();
        count = deckB[1];
        --count;
        deckB[1] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        kingCrimsonR = true;
        RSkill->show();
        BSkill->hide();
        count = deckR[1];
        --count;
        deckR[1] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }

}

void mainwindow::DioSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        count = deckB[2];
        --count;
        deckB[2] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        count = deckR[2];
        --count;
        deckR[2] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    zawarudo = true;
}

void mainwindow::JotaroSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        count = deckB[3];
        --count;
        deckB[3] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        count = deckR[3];
        --count;
        deckR[3] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    star = true;
}

void mainwindow::JosephSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        count = deckB[4];
        --count;
        deckB[4] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        count = deckR[4];
        --count;
        deckR[4] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    run = true;
}

void mainwindow::KiraSlots()
{
    Dio->hide();
    Gio->hide();
    Boss->hide();
    Jotaro->hide();
    Joseph->hide();
    Kira->hide();
    card->hide();
    startGame->show();
    regretGame->show();
    timing->show();
    editGame->show();
    cancel->hide();
    if(stepNumber%2 == 0)
    {
        BSkill->show();
        RSkill->hide();
        count = deckB[5];
        --count;
        deckB[5] = count;
        if(kingCrimsonB == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber%2 == 1)
    {
        RSkill->show();
        BSkill->hide();
        count = deckR[5];
        --count;
        deckR[5] = count;
        if(kingCrimsonR == true)
            regretGame->show();
        else {
            regretGame->hide();
        }
    }
    if(stepNumber<=6)
        return;

    for(int i = 0 ; i < 6 ; ++i)
    {
        int Eat_x=regretRecord[stepNumber%6][0];
        int Eat_y=regretRecord[stepNumber%6][1];
        coordinate[Eat_x][Eat_y]=regretRecord[stepNumber%6][2];
        int Eaten_x=regretRecord[stepNumber%6][3];
        int Eaten_y=regretRecord[stepNumber%6][4];
        coordinate[Eaten_x][Eaten_y]=regretRecord[stepNumber%6][5];
        initializeMove();
        Clicked_X=regretRecord[stepNumber%6][0];
        Clicked_Y=regretRecord[stepNumber%6][1];
        stepNumber--;
        regretTimes++;
    }
    this->repaint();
}

void mainwindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for(int i=0;i<9;i++)//畫出棋子位置
    {
        for(int j=0;j<10;j++)
        {
            switch (coordinate[i][j])
            {
            case 1:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/kingB.png"));  break;
            case 2:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/guardB.png"));  break;
            case 3:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/elephantB.png"));  break;
            case 4:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/horseB.png"));  break;
            case 5:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/chariotB.png"));  break;
            case 6:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/cannonB.png"));  break;
            case 7:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/soldierB.png"));  break;
            case -1:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/kingR.png"));  break;
            case -2:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/guardR.png"));  break;
            case -3:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/elephantR.png"));  break;
            case -4:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/horseR.png"));  break;
            case -5:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/chariotR.png"));  break;
            case -6:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/cannonR.png"));  break;
            case -7:painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/soldierR.png"));  break;
            default:       break;
            }
            if(move[i][j]==10)//畫出可移動位置
            {
                painter.drawImage(QRect(30+119*i,10+100*j,80,80),QImage(":/chessimg/move.png"));
            }
        }
    }
    painter.drawImage(QRect(30+119*Clicked_X,10+100*Clicked_Y,80,80),QImage(":/chessimg/choose.png"));//畫出上次移動位置
}


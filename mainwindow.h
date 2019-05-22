#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QPalette>
#include<QMouseEvent>
#include<QLabel>
#include<QTimer>
#include<string>
#include<QPushButton>
#include<QMessageBox>
#include<time.h>
#include<stdlib.h>


namespace Ui {
class MainWindow;
}

class mainwindow : public  QWidget
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    int coordinate[9][10];
    int move[9][10];
    int regretRecord[6][6];
    int deckR[6] = {0};
    int deckB[6] = {0};
    int Clicked_X;
    int Clicked_Y;
    int regretTimes;
    int stepNumber;
    int stepTime;
    int sumTimeRecord;
    int type;
    int getCard;
    int count;
    bool gameOver;
    bool edit;
    bool kingCrimsonR;
    bool kingCrimsonB;
    bool zawarudo;
    bool star;
    bool run;
    QLabel *player1Time;
    QLabel *player2Time;
    QLabel *sumTime;
    QLabel *bg;
    QLabel *card;
    QTimer *Timer; //一秒更新一次
    QPushButton *startGame;
    QPushButton *regretGame;
    QPushButton *exitGame;
    QPushButton *timing;
    QPushButton *editGame;
    QPushButton *editEnd;
    QPushButton *blackKing;
    QPushButton *blackGuard;
    QPushButton *blackElephant;
    QPushButton *blackHorse;
    QPushButton *blackChariot;
    QPushButton *blackCannon;
    QPushButton *blackSoldier;
    QPushButton *redKing;
    QPushButton *redGuard;
    QPushButton *redElephant;
    QPushButton *redHorse;
    QPushButton *redChariot;
    QPushButton *redCannon;
    QPushButton *redSoldier;
    QPushButton *RSkill;
    QPushButton *BSkill;
    QPushButton *cancel;
    QPushButton *Dio;
    QPushButton *Gio;
    QPushButton *Jotaro;
    QPushButton *Joseph;
    QPushButton *Boss;
    QPushButton *Kira;
    QPixmap *back;
public:
    mainwindow (QWidget *parent = nullptr );
    ~mainwindow();
    void initializeCoordinate ();
    void initializeMove ();
    void paintEvent (QPaintEvent *);
    void mousePressEvent (QMouseEvent *event);
    void moveChess ( int i, int j, int value);
    void eat ( int Eat_x, int Eat_y, int Eat_value, int Eaten_x, int Eaten_y, int Eaten_value);
    void isWin ();
    void buttonClean();

public slots:
    void timeOutSlots();
    void startGameSlots();
    void regretGameSlots();
    void exitGameSlots();
    void editEndSlots();
    void editGameSlots();
    void timingSlots();
    void blackKingSlot();
    void blackGuardSlot();
    void blackElephantSlot();
    void blackHorseSlot();
    void blackChariotSlot();
    void blackCannonSlot();
    void blackSoldierSlot();
    void redKingSlot();
    void redGuardSlot();
    void redElephantSlot();
    void redHorseSlot();
    void redChariotSlot();
    void redCannonSlot();
    void redSoldierSlot();
    void RSkillSlots();
    void BSkillSlots();
    void cancelSlots();
    void DioSlots();
    void GioSlots();
    void BossSlots();
    void JotaroSlots();
    void KiraSlots();
    void JosephSlots();
};

#endif // MAINWINDOW_H

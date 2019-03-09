#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "Stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:

    ~Board(){}

    explicit Board(QWidget *parent = nullptr);

    Stone _s[32];
    int d;
    int _selectid;
    bool _bRedTurn;

    QPoint center(int row, int col);

    bool getRowCol(QPoint pt, int& row,int& col);

    void paintEvent(QPaintEvent *);
    void drawStone(QPainter& painter,int id);
    void mouseReleaseEvent(QMouseEvent *);
    //void mousePressEvent(QMouseEvent *);

    bool canMove(int moveid, int row, int col, int killid);
    bool canMove1(int moveid, int row, int col, int killid);
    bool canMove2(int moveid, int row, int col, int killid);
    bool canMove3(int moveid, int row, int col, int killid);
    bool canMove4(int moveid, int row, int col, int killid);
    bool canMove5(int moveid, int row, int col, int killid);
    bool canMove6(int moveid, int row, int col, int killid);
    bool canMove7(int moveid, int row, int col, int killid);

signals:

public slots:
    void returnClick();
};

#endif // BOARD_H

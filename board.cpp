#include "Board.h"
#include<QPainter>
#include<QMouseEvent>

Board::Board(QWidget *parent) :
    QWidget(parent)
{
    for(int i=0; i<32; i++)
    {
        _s[i].init(i);
    }
    _selectid=-1;
    _bRedTurn=true;
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //paint line
    d=40;
    for(int i=1;i<=10;++i)
    {
        painter.drawLine(QPoint(d, i*d),QPoint(9*d, i*d));
    }

    for(int i=1;i<=9;++i)
    {
        if(i==1 || i==9)
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d, 10*d));
        }
        else
        {
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d, 10*d));
        }
    }
    painter.drawLine(QPoint(4*d, 1*d), QPoint(6*d, 3*d));
    painter.drawLine(QPoint(6*d, 1*d), QPoint(4*d, 3*d));

    painter.drawLine(QPoint(4*d, 8*d), QPoint(6*d, 10*d));
    painter.drawLine(QPoint(6*d, 8*d), QPoint(4*d, 10*d));

    for(int i=0;i<32;++i)
    {
      drawStone(painter, i);
    }
}

QPoint Board::center(int row, int col){
    QPoint rex;
    rex.rx()=(col+1)*d;
    rex.ry()=(row+1)*d;
    return rex;
}

void Board::drawStone(QPainter& painter, int id)
{
    if(_s[id]._dead){
        return;
    }
    QPoint c=center(_s[id]._row, _s[id]._col);
    QRect rect=QRect(c.rx()-d/2,c.ry()-d/2,d,d);

    if(id == _selectid)
    {
        painter.setBrush(QBrush(Qt::gray));
    }
    else
    {
    painter.setBrush(QBrush(QColor(255, 255, 0)));
    }
    painter.setPen(Qt::black);

    painter.drawEllipse(c, d/2, d/2);

    if(_s[id]._red)
    {
        painter.setPen(Qt::red);
    }else{
        painter.setPen(Qt::black);
    }

    painter.setFont(QFont("system",d/2,700));

    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));

}

bool Board::getRowCol(QPoint pt, int& row,int& col)
{
    for(row=0;row<=9;row++)
    {
        for(col=0;col<=8;col++)
        {
            QPoint c=center(row, col);
            int dx = c.x()-pt.x();
            int dy = c.y()-pt.y();
            int dist=dx*dx+dy*dy;
            if(dist<(d*d/4))
            {
                return true;
            }

        }
    }
    return false;
}

bool Board::canMove1(int moveid, int row, int col, int killid)
{
    if(_s[moveid]._red)
    {
        if(row>2)
        {
            return false;
        }
    }
    else
    {
       if(row<7)
       {
           return false;
       }
    }

    if(col<3)
    {
        return false;
    }
    if(col>5)
    {
        return false;
    }

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);

    if(d !=1 && d!=10)
    {
        return false;
    }

    return true;
}

bool Board::canMove2(int moveid, int row, int col, int killid)
{
    if(_s[moveid]._red)
    {
        if(row>2)
        {
            return false;
        }
    }
    else
    {
       if(row<7)
       {
           return false;
       }
    }

    if(col<3)
    {
        return false;
    }
    if(col>5)
    {
        return false;
    }

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);

    if(d !=11)
    {
        return false;
    }

    return true;
}

bool Board::canMove3(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMove4(int moveid, int row, int col, int killid)
{
   return true;
}
bool Board::canMove5(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMove6(int moveid, int row, int col, int killid)
{
    return true;
}
bool Board::canMove7(int moveid, int row, int col, int killid)
{
    return true;
}


bool Board::canMove(int moveid, int row, int col, int killid)
{
    if(killid>0){
        if(_s[moveid]._red == _s[killid]._red)
        {
            _selectid = killid;
            update();

            return false;
        }
    }

    switch (_s[moveid]._type) {
    case Stone::JIANG:
        return canMove1(moveid, row, col, killid);
        break;
    case Stone::SHI:
        return canMove2(moveid, row, col, killid);
        break;
    case Stone::XIANG:
        return canMove3(moveid, row, col, killid);
        break;
    case Stone::CHE:
        return canMove4(moveid, row, col, killid);
        break;
    case Stone::MA:
        return canMove5(moveid, row, col, killid);
        break;
    case Stone::PAO:
        return canMove6(moveid, row, col, killid);
        break;
    case Stone::BING:
        return canMove7(moveid, row, col, killid);
        break;
    }

    return true;
}


void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt = ev->pos();

    int row,col;
    bool bRet=getRowCol(pt, row, col);
    if(bRet==false)
    {
        return;
    }

    int i;
    int clickid=-1;
    for(i=0;i<32;++i)
    {
        if(_s[i]._row ==row && _s[i]._col==col && _s[i]._dead ==false)
        {
            break;
        }
    }

    if(i<32)
    {
        clickid=i;
    }

    if(_selectid == -1)
    {
        if(clickid != -1)
        {
            if(_bRedTurn == _s[clickid]._red)
            {
                _selectid=clickid;
                update();
            }
        }
    }
    else
    {
        if(canMove(_selectid, row, col, clickid))
        {
            _s[_selectid]._row=row;
            _s[_selectid]._col=col;
            if(clickid != -1)
            {
                _s[clickid]._dead = true;
            }
            _selectid = -1;
            _bRedTurn = !_bRedTurn;
            update();
        }
    }
}
void Board::returnClick()
{
    _s[0]._dead = true;
    update();
}

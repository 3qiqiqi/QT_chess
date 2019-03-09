#include<QApplication>
#include"Board.h"
#include<QMessageBox>
#include<QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMessageBox::StandardButton ret;

    ret=QMessageBox::question(NULL, "open or close", "莫昭奇是不是比你帅");




    if(ret==QMessageBox::Yes){
    Board board;
    board.show();

    QPushButton button;
    button.setText("饶你一字");
    button.setGeometry(400,200,70,35);
    button.setParent(&board);
    QObject::connect(&button, SIGNAL(clicked()), &board, SLOT(returnClick()));
    button.show();

    return app.exec();
    }
    else{
        return 0;
    }

}

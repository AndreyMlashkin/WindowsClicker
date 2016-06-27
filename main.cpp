#include "mainwindow.h"
#include <QApplication>
#include <QPoint>

#include <w32api.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QPoint pos(100, 130);
    POINT cp;
    GetCursorPos(&cp);

//    SetCursorPos(pos.x(), pos.y());
//    Sleep(1);
//    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
//    Sleep(1);
//    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
//    Sleep(1);
//    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, GetMessageExtraInfo());

    return a.exec();
}

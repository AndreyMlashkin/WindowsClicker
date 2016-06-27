#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <w32api.h>
#include <windows.h>

int keyPressed(int key)
{
    return (GetAsyncKeyState(key) & 0x8000 != 0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->record, &QPushButton::toggled, this, &MainWindow::recordClicked);
    connect(ui->replay, &QPushButton::toggled, this, &MainWindow::replayClicked);
    ui->listView->setModel(&m_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recordClicked(bool _toggle)
{
    if(_toggle)
        startRecorting();
    else
        stopRecorting();
}

void MainWindow::replayClicked(bool _toggle)
{
    if(_toggle)
        startReplay();
    else
        stopReplay();
}

void MainWindow::startRecorting()
{
    m_timer.setInterval(500);
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::saveState);
}

void MainWindow::stopRecorting()
{
    m_timer.stop();
}

void MainWindow::startReplay()
{

}

void MainWindow::stopReplay()
{

}

void MainWindow::click(const QPoint &_point) const
{
    SetCursorPos(_point.x(), _point.y());
    Sleep(1);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
}

void MainWindow::saveState()
{
    POINT cp;
    GetCursorPos(&cp);
    QPoint pos(cp.x, cp.y);

    bool click = false;
    if(keyPressed(VK_LBUTTON))
        click = true;
//    if(keyPressed(VK_RBUTTON))
//    {
//        button |= Qt::RightButton;
//    }

    Event event;
    event.pos = pos;
    event.click = click;

    m_events << event;
    QStandardItem* item = new QStandardItem(QString("(%1, %2) btn:%3")
                                            .arg(event.pos.x())
                                            .arg(event.pos.y())
                                            .arg(click)
                                            );
    m_model.appendRow(item);
    ui->listView->scrollToBottom();
}

#include <QDebug>
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
    ui(new Ui::MainWindow),
    m_frequenz(100),
    m_replayingEventCount(0)
{
    ui->setupUi(this);

    connect(ui->record, &QPushButton::toggled, this, &MainWindow::recordClicked);
    connect(ui->replay, &QPushButton::toggled, this, &MainWindow::replayClicked);
    connect(ui->clear,  &QPushButton::clicked, this, &MainWindow::clear);
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
    m_recordingTimer.setInterval(m_frequenz);
    m_recordingTimer.start();
    connect(&m_recordingTimer, &QTimer::timeout, this, &MainWindow::saveState);
}

void MainWindow::stopRecorting()
{
    m_recordingTimer.stop();
}

void MainWindow::startReplay()
{
    stopRecorting();

//    m_replayTimer.setInterval(500);
//    m_replayTimer.start();
//    connect(&m_replayTimer, &QTimer::timeout, this, &MainWindow::replayEvent);

    for(int i = 0; i < m_events.count(); ++i)
    {
        Sleep(m_frequenz);
        Event event = m_events[i];
        setPos(event.pos);
        Sleep(1);
        if(event.click)
            click();

        auto index = m_model.index(i, 0);
        ui->listView->setCurrentIndex(index);
    }
}

void MainWindow::stopReplay()
{
    m_replayTimer.stop();
}

void MainWindow::setPos(const QPoint &_point) const
{
    qDebug() << Q_FUNC_INFO << " " << _point;
    SetCursorPos(_point.x(), _point.y());
}

void MainWindow::click() const
{
    qDebug() << Q_FUNC_INFO;
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP,   0, 0, 0, 0);
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

void MainWindow::replayEvent()
{
    m_replayingEventCount = (m_replayingEventCount++) % m_events.count();
    Event event = m_events[m_replayingEventCount];

    setPos(event.pos);
    Sleep(1);
    if(event.click)
        click();

    auto index = m_model.index(m_replayingEventCount, 0);
    ui->listView->setCurrentIndex(index);
}

void MainWindow::clear()
{
    m_events.clear();
    m_model.clear();
}

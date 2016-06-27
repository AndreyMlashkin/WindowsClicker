#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void recordClicked(bool _toggle);
    void replayClicked(bool _toggle);

    void saveState();
    void replayEvent();

    void clear();

private:
    void startRecorting();
    void stopRecorting();

    void startReplay();
    void stopReplay();

    void setPos(const QPoint& _point) const;
    void click() const;


struct Event
{
    QPoint pos;
    bool click;
};

private:
    Ui::MainWindow *ui;
    int m_frequenz;

    QTimer m_recordingTimer;
    QTimer m_replayTimer;

    QStandardItemModel m_model;
    QVector<Event> m_events;
    int m_replayingEventCount;
};

#endif // MAINWINDOW_H

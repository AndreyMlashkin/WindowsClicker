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

    void click(const QPoint& _point) const;
    void saveState();

private:
    void startRecorting();
    void stopRecorting();

    void startReplay();
    void stopReplay();

struct Event
{
    QPoint pos;
    bool click;
};

private:
    Ui::MainWindow *ui;
    QTimer m_timer;

    QStandardItemModel m_model;
    QVector<Event> m_events;
};

#endif // MAINWINDOW_H

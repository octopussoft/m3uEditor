#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "m3u.h"

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
    void on_btnLoadM3U_clicked();
    void loadM3U(QString filename);
    void createTableItem(int row, QString chanelName, QString chanelStreamUrl, QString chanelImage);
    void setCurrentStatus(QString status, int percent);

    void on_btnUpdateM3U_clicked();

    void on_btnSaveM3U_clicked();

    void updateTableview();

    void on_btnUp_clicked();

    void on_btnDown_clicked();

    void on_btnDelete_clicked();

    void on_btnNew_clicked();

    void moveRows(bool up);


private:
    Ui::MainWindow *ui;

    m3u mPlaylist;
    int mLastSelectedRow;
};

#endif // MAINWINDOW_H

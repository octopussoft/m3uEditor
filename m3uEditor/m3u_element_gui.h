#ifndef M3U_ELEMENT_GUI_H
#define M3U_ELEMENT_GUI_H

#include <QWidget>

namespace Ui {
class m3u_element_gui;
}

class m3u_element_gui : public QWidget
{
    Q_OBJECT

public:
    explicit m3u_element_gui(QWidget *parent = 0);
    ~m3u_element_gui();

private slots:
    void on_btnPlay_clicked();

    void on_btnStreamURL_clicked();

private:
    Ui::m3u_element_gui *ui;
};

#endif // M3U_ELEMENT_GUI_H

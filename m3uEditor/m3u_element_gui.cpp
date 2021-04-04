#include "m3u_element_gui.h"
#include "ui_m3u_element_gui.h"
#include <QInputDialog>

m3u_element_gui::m3u_element_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::m3u_element_gui)
{
    ui->setupUi(this);
}

m3u_element_gui::~m3u_element_gui()
{
    delete ui;
}

void m3u_element_gui::on_btnPlay_clicked()
{

}

void m3u_element_gui::on_btnStreamURL_clicked()
{
    QInputDialog* inputDialog = new QInputDialog();
    bool ok;
    inputDialog->getText(this, tr("User Input"), tr("STREAM_URL"), QLineEdit::Normal, "", &ok);
}

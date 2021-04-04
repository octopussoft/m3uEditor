#include <global_settings.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "input_output.h"
#include <QFileDialog>
#include "channel.h"
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QImageReader>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    /* initialize class variables */
    mLastSelectedRow = 0;

    /* initialize gui */
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_btnLoadM3U_clicked(){

//    QString filename = QFileDialog::getOpenFileName(this,
//        tr("Open M3U Playlist"), "/", tr("m3u playlist (*.m3u)"));
//    loadM3U(filename);
    loadM3U("E:/tv.m3u");

}

void MainWindow::loadM3U(QString filename) {

#ifdef PRINT_DEBUG_INFO
    qDebug() << "open " + filename;
#endif /* PRINT_DEBUG_INFO */

    /* create input/output instance */
    input_output io;

    /* open m3u file */
    if (io.read_m3u(filename) == true) {

        /* read file row by row */
        QStringList fileRows = io.getfileRows();

        /* count rows  */
        int size = fileRows.count();
        if (size > 0) {
            /* get channels from file rows */
            mPlaylist.createChannelObjects(fileRows);

            updateTableview();
        } else {
            /* error get file rows */
        }
    }
}

void MainWindow::on_btnUpdateM3U_clicked(){

}

void MainWindow::on_btnSaveM3U_clicked(){

    /* create input/output instance */
    input_output io;

    /* write m3u file */
    if (io.write_m3u("C:/Users/MHilz/Desktop/test.m3u", mPlaylist.mChannels) != true) {

        /* write failed */

    }

    /* write success */
}


void MainWindow::setCurrentStatus(QString status, int percent) {

    /* set progress in percent */
    ui->barStatus->setValue(percent);

    /* set status if different */
    if (status != ui->lblStatus->text()) {
        ui->lblStatus->setText(status);
    }
}

void MainWindow::updateTableview(){
    int row = 0;

    // clear table view
    ui->tblPlaylist->setRowCount(0);

    /* set current status */
    setCurrentStatus("Add Items to table", 0);

    /* disable table view while importing */
    ui->tblPlaylist->setDisabled(true);

    /* update channel groups view */
    foreach (QString group , mPlaylist.mChannelGroups) {
        ui->tblChannelGroups->insertRow(0);
        QTableWidgetItem *channelGroup = new QTableWidgetItem();
        channelGroup->setText(group);
        ui->tblChannelGroups->setItem(0, 0, channelGroup);
    }

    /* prepare import */
    double percent = 0;
    int count = mPlaylist.mChannels.count();
    ui->tblPlaylist->setRowCount(count);

    /* import channels */
    foreach (channel chan, mPlaylist.mChannels) {

        /* add channel to table */
        createTableItem(row, chan.name.toLatin1(), chan.url.toLatin1(), chan.tvgLogo.toLatin1());

        /* set current status */
        percent = (row / static_cast<double>(count)) * 100;
        setCurrentStatus("Add Items to table", static_cast<int>(percent));

        /* keep gui responsivenes */
        QCoreApplication::processEvents();

        row++;
    }

    /* set current status */
    setCurrentStatus("Idle", 100);

    /* re enable table view after import */
    ui->tblPlaylist->setDisabled(false);

    /* resize table */
    ui->tblPlaylist->resizeColumnsToContents();
    //ui->tblPlaylist->horizontalHeader()->setStretchLastSection(true);
    //ui->tblPlaylist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* select row */
    ui->tblPlaylist->selectRow(mLastSelectedRow);
}


void MainWindow::createTableItem(int row, QString chanelName, QString chanelStreamUrl, QString chanelImage)
{
    /* setup stream name */
    QTableWidgetItem *chanelNameItem = new QTableWidgetItem();
    chanelNameItem->setText(chanelName);

    /* setup stream URL */
    QTableWidgetItem *chanelStreamUrlItem = new QTableWidgetItem();
    chanelStreamUrlItem->setText(chanelStreamUrl);

    /* setup channel logo URL */
    QTableWidgetItem *chanelLogoUrlItem = new QTableWidgetItem();
    chanelLogoUrlItem->setText(chanelImage);

    /* setup channel logo preview */
    QTableWidgetItem *chanelImageItem = new QTableWidgetItem();


    /* setup channel groups box */
    QComboBox *chanelGroups = new QComboBox;
    foreach (QString group , mPlaylist.mChannelGroups) {
        QTableWidgetItem *channelGroup = new QTableWidgetItem();
        channelGroup->setText(group);
    }
    chanelGroups->addItems(mPlaylist.mChannelGroups);

    /* insert items into row */
    ui->tblPlaylist->setItem(row,0,chanelNameItem);
    ui->tblPlaylist->setItem(row,1,chanelStreamUrlItem);
    ui->tblPlaylist->setItem(row,2,chanelImageItem);
    ui->tblPlaylist->setItem(row,3,chanelLogoUrlItem);
    ui->tblPlaylist->setCellWidget(row,4,chanelGroups);
}

void MainWindow::moveRows(bool up)
{
    int newRow;

    /* get selected items */
    QList<QTableWidgetItem*> list = ui->tblPlaylist->selectedItems();
    QList<QTableWidgetItem*> moveItems;

    /* moved rows */
    QList<int> rows;

    /* set row(s) to move */
    if (list.length() > 0) {

        /* get 1 item of each row to move */
        foreach (QTableWidgetItem* item , list) {
            if (rows.contains(item->row())) {
                continue;
            } else {
                rows.append(item->row());
                moveItems.append(item);
            }
        }

#ifdef PRINT_DEBUG_INFO
    qDebug() << "move " << moveItems.count() << " row(s)";
#endif /* PRINT_DEBUG_INFO */

        //foreach (QTableWidgetItem* item , moveItems) {

        for (int i = 0; i < moveItems.count(); i++) {

            /* save current item row */
            int oldRow = moveItems[i]->row();

            if (up) {
                newRow = oldRow - 1;
            } else {
                newRow = rows[0] + moveItems.count();
            }

            /* check if future row is out of range (direction up) */
            if (    up == true &&
                    !(newRow >= 0)) {
#ifdef PRINT_DEBUG_INFO
    qDebug() << "future row is out of range (direction up) " << newRow;
#endif /* PRINT_DEBUG_INFO */
                return;
            }

            /* check if future row is out of range (direction down) */
            if (    up == false &&
                    !(newRow <= (ui->tblPlaylist->rowCount() - 1))) {
#ifdef PRINT_DEBUG_INFO
    qDebug() << "future row is out of range (direction down) " << newRow;
#endif /* PRINT_DEBUG_INFO */
                return;
            }

#ifdef PRINT_DEBUG_INFO
    qDebug() << "move row " << moveItems[i]->row() << "to row " << newRow;
#endif /* PRINT_DEBUG_INFO */

            /* move row */
            for (int column = 0; column < ui->tblPlaylist->columnCount(); column++) {

                /* take items of row to move */
                QTableWidgetItem* itemToMove = ui->tblPlaylist->takeItem(oldRow, column);

                /* take items of row to swap */
                QTableWidgetItem* itemToSwap = ui->tblPlaylist->takeItem(newRow, column);

                /* move item */
                ui->tblPlaylist->setItem(newRow, column, itemToMove);

                /* swap item */
                ui->tblPlaylist->setItem(oldRow, column, itemToSwap);

                /* select new row */
                ui->tblPlaylist->selectRow(newRow);
            }
        }
    }
}

void MainWindow::on_btnUp_clicked()
{
    moveRows(true);
}

void MainWindow::on_btnDown_clicked()
{
    moveRows(false);
}

void MainWindow::on_btnDelete_clicked()
{
#ifdef PRINT_DEBUG_INFO
    qDebug() << "delete row(s)";
#endif /* PRINT_DEBUG_INFO */

    /* get selected items */
    QList<QTableWidgetItem*> list = ui->tblPlaylist->selectedItems();

    /* set row(s) to delete */
    if (list.length() > 0) {
        /* delete all selected rows */
        foreach (QTableWidgetItem* item , list) {
            mLastSelectedRow = item->row();
            ui->tblPlaylist->removeRow(mLastSelectedRow);
        }
    } else {

        /* set row to delete to last row
         * if last selected row is out of range */
        if(mLastSelectedRow >= ui->tblPlaylist->rowCount()) {
            mLastSelectedRow = ui->tblPlaylist->rowCount() - 1;
        }

        /* delete row */
        ui->tblPlaylist->removeRow(mLastSelectedRow);
    }

    if (mLastSelectedRow < 0) {
        mLastSelectedRow = 0;
#ifdef PRINT_DEBUG_INFO
qDebug() << "mLastSelectedRow was below 0";
#endif /* PRINT_DEBUG_INFO */
    }

    /* select row */
    ui->tblPlaylist->selectRow(mLastSelectedRow);

#ifdef PRINT_DEBUG_INFO
    qDebug() << "mLastSelectedRow = " + QString::number(mLastSelectedRow);
#endif /* PRINT_DEBUG_INFO */
}

void MainWindow::on_btnNew_clicked()
{
#ifdef PRINT_DEBUG_INFO
    qDebug() << "create row";
#endif /* PRINT_DEBUG_INFO */

    /* get selected items */
    QList<QTableWidgetItem*> list = ui->tblPlaylist->selectedItems();

    /* set row for new line */
    if (list.length() > 0) {
        /* row for new line is on top of selected line */
            mLastSelectedRow = list[0]->row();

        if (mLastSelectedRow < 0) {
            mLastSelectedRow = 0;
#ifdef PRINT_DEBUG_INFO
    qDebug() << "mLastSelectedRow was below 0";
#endif /* PRINT_DEBUG_INFO */
        }
    }

    /* insert new row */
    createTableItem(mLastSelectedRow, "", "", "");

    /* select row */
    ui->tblPlaylist->selectRow(mLastSelectedRow);

#ifdef PRINT_DEBUG_INFO
    qDebug() << "mLastSelectedRow = " + QString::number(mLastSelectedRow);
#endif /* PRINT_DEBUG_INFO */
}

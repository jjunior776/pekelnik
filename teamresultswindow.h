#ifndef TEAMRESULTSWINDOW_H
#define TEAMRESULTSWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include "csvreader.h"

namespace Ui {
class TeamResultsWindow;
}

class TeamResultsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeamResultsWindow(QWidget *parent = 0);
    ~TeamResultsWindow();

private slots:
    void on_loadFromCSV_clicked();

    void on_generateHtmlBtn_clicked();

private:
    Ui::TeamResultsWindow *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
};

#endif // TEAMRESULTSWINDOW_H

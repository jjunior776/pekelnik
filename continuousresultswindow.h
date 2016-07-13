#ifndef CONTINUOUSRESULTSWINDOW_H
#define CONTINUOUSRESULTSWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include "csvreader.h"

namespace Ui {
class ContinuousResultsWindow;
}

class ContinuousResultsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ContinuousResultsWindow(QWidget *parent = 0);
    ~ContinuousResultsWindow();

private slots:
    void on_loadFromCSV_clicked();

    void on_generateHtmlBtn_clicked();

private:
    Ui::ContinuousResultsWindow *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
};

#endif // CONTINUOUSRESULTSWINDOW_H

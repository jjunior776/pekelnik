#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include "csvreader.h"

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent = 0);
    ~ResultsWindow();

private slots:
    void on_loadFromCSV_clicked();
    void on_generateHtmlBtn_clicked();

private:
    Ui::ResultsWindow *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
};

#endif // RESULTSWINDOW_H

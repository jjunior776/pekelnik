#ifndef OVERALLRESULTSWINDOW_H
#define OVERALLRESULTSWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include "csvreader.h"

namespace Ui {
class OverallResultsWindow;
}

class OverallResultsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OverallResultsWindow(QWidget *parent = 0);
    ~OverallResultsWindow();

private:
    Ui::OverallResultsWindow *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
};

#endif // OVERALLRESULTSWINDOW_H

#ifndef PROPOSITIONSDIALOG_H
#define PROPOSITIONSDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTextStream>

namespace Ui {
class PropositionsDialog;
}

class PropositionsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PropositionsDialog(QWidget *parent = 0);
    ~PropositionsDialog();

private slots:
    void on_loadFromCSV_clicked();
    void checkString(QString &temp, QChar character = 0);

    void on_generateHtmlBtn_clicked();

private:
    Ui::PropositionsDialog *ui;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
};

#endif // PROPOSITIONSDIALOG_H

#ifndef PROPOSITIONSWINDOW_H
#define PROPOSITIONSWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QPainter>

namespace Ui {
class PropositionsWindow;
}

class PropositionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PropositionsWindow(QWidget *parent = 0);
    ~PropositionsWindow();

private slots:
    void on_pdfBtn_clicked();

    void on_logoBtn_clicked();

private:
    Ui::PropositionsWindow *ui;
    QString logo;
    QPrinter *printer;
    QPainter *painter;
};

#endif // PROPOSITIONSWINDOW_H

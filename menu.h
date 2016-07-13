#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "resultswindow.h"
#include "continuousresultswindow.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_resultsBtn_clicked();

    void on_continuousResultBtn_clicked();

private:
    Ui::Menu *ui;
    ResultsWindow *resultsWindow;
    ContinuousResultsWindow *continuousResultsWindow;
};

#endif // MENU_H

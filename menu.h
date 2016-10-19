#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "resultswindow.h"
#include "continuousresultswindow.h"
#include "teamresultswindow.h"
#include "propositionswindow.h"

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

    void on_teamResiltsBtn_clicked();

    void on_propositionsBtn_clicked();

private:
    Ui::Menu *ui;
    ResultsWindow *resultsWindow;
    ContinuousResultsWindow *continuousResultsWindow;
    TeamResultsWindow *teamResultsWindow;
    PropositionsWindow *propositionsWindow;
};

#endif // MENU_H

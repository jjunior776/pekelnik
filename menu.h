#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "propositionsdialog.h"

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

private:
    Ui::Menu *ui;
    PropositionsDialog *propositions;
};

#endif // MENU_H

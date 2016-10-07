#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resultsWindow = new ResultsWindow;
    continuousResultsWindow = new ContinuousResultsWindow;
    teamResultsWindow = new TeamResultsWindow;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_resultsBtn_clicked()
{
    resultsWindow->show();

}

void Menu::on_continuousResultBtn_clicked()
{
    continuousResultsWindow->show();
}

void Menu::on_teamResiltsBtn_clicked()
{
    teamResultsWindow->show();
}

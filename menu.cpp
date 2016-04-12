#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    propositions = new PropositionsDialog;

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_resultsBtn_clicked()
{
    propositions->show();

}

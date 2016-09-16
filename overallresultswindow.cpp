#include "overallresultswindow.h"
#include "ui_overallresultswindow.h"

OverallResultsWindow::OverallResultsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverallResultsWindow)
{
    ui->setupUi(this);
}

OverallResultsWindow::~OverallResultsWindow()
{
    delete ui;
}

#ifndef OVERALLRESULTSWINDOW_H
#define OVERALLRESULTSWINDOW_H

#include <QWidget>

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
};

#endif // OVERALLRESULTSWINDOW_H

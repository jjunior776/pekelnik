#include "teamresultswindow.h"
#include "ui_teamresultswindow.h"
#include <qdebug.h>
#include <QList>

TeamResultsWindow::TeamResultsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamResultsWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->resultsTableV->setModel(model);
    ui->resultsTableV->horizontalHeader()->setStretchLastSection(true);
}

TeamResultsWindow::~TeamResultsWindow()
{
    delete ui;
}

void TeamResultsWindow::on_loadFromCSV_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Otevři CSV", QDir::currentPath(), "CSV (*.csv)");
    QFile file (filename);
    model->clear();
    if (file.open(QIODevice::ReadOnly)){
        //QString data = file.readAll(); //qDebug() << data; //data.remove( QRegExp("\r"));;
        QTextStream stream(file.readAll());
        stream.setCodec("ANSI");

        CSVReader *csv = new CSVReader();
        csv->loadFromCSV(stream,model);
        ui->generateHtmlBtn->setEnabled(true);
    }
}

void TeamResultsWindow::on_generateHtmlBtn_clicked()
{
    QString html = "";
    QString headHtml = "";
    QString teamHeaderHtml = "";
    QString finalHtml = "";
    QString input;
    QString styleNaStred = " class=\"naStred\" style=\"width: 5% !important;\" ";
    QString styleNaStredM = " class=\"naStred\" style=\"width: 20% !important;\" ";
    QString style = "";
    QString inputLink;
    QStringList races;
    QList<int> *teamSpan = new QList<int>;
    QStringList teams;
    bool racesDone = false;
    bool table = false;
    bool head = false;
    int teamIndex = 0;
    int z = 0;

    headHtml = "<h2 class=\"vysledky_hlavni_nadpis\">"+ui->highlightEdit->text()+"</h2><br>\n";
    headHtml += "<small><a class=\"button\" href=\""+ui->pdfUrlEdit->text()+"\" download>PDF ke stažení</a></small><br>\n";
    headHtml += "<table style=\"border: 0px\"><tr style=\"border: 0px\">\n";
    int rowSpanCount = 0;
    for(int i=0;i<model->rowCount();i++){
        input = model->data(model->index(i,1)).toString();
        if(!input.isEmpty()){
            if(!teams.isEmpty())
                teamSpan->append(rowSpanCount);
            rowSpanCount = 0;
            teams.append(input);
        }
        rowSpanCount++;
    }
    teamSpan->append(rowSpanCount);

    teamHeaderHtml += "<table class=\"vysledky\">\n<tr>\n<th"+styleNaStred+">Pořadí</th>";
    style = " style=\"width: 20% !important;\" ";
    teamHeaderHtml += "<th"+styleNaStredM+">Tým</th>";
    teamHeaderHtml += "<th"+styleNaStredM+">Závodník</th>";
    for(int i=3;i<model->columnCount()-1;i++){
        input = model->data(model->index(0,i)).toString();
        races.append(input);
        //qDebug() << input;
        teamHeaderHtml += "<th"+styleNaStred+">Z"+QString::number(races.count())+"</th>";
    }
    teamHeaderHtml += "<th"+styleNaStred+">Body celkem</th></tr>\n";

    for(int i=2;i<model->rowCount();i++){
        if(!model->data(model->index(i,1)).toString().isEmpty()){
            html+= "\n</table>";
            html+= teamHeaderHtml;
            html+= "<tr><td rowspan=\""+QString::number(teamSpan->at(teamIndex))+"\">"+QString::number(teamIndex+1)+".</td>";
            html+= "<td rowspan=\""+QString::number(teamSpan->at(teamIndex))+"\">"+teams.at(teamIndex)+"</td>";
            teamIndex++;
        }
        else{
            html+= "<tr>";
        }
        style = "";
        for(int j=2;j<model->columnCount();j++){
            input = model->data(model->index(i,j)).toString();
            if(input=="body celkem")
                style = " style=\"background-color: #CCCCCC\"";
            html+= "<td"+style+">"+input+"</td>";
        }
        html += "</tr>";
    }
    html += "</table>";
    headHtml += "<td style=\"border: 0px\">";
    foreach (QString race, races) {
        z++;
        headHtml+= "Z"+QString::number(z)+" = " + race + "<br>";
    }
    headHtml+= "</td></tr></table>";
    finalHtml = headHtml+html;
    ui->htmlPText->setPlainText(finalHtml);
}


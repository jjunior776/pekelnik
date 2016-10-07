#include "continuousresultswindow.h"
#include "ui_continuousresultswindow.h"

ContinuousResultsWindow::ContinuousResultsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContinuousResultsWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    ui->resultsTableV->setModel(model);
    ui->resultsTableV->horizontalHeader()->setStretchLastSection(true);
}

ContinuousResultsWindow::~ContinuousResultsWindow()
{
    delete ui;
}

void ContinuousResultsWindow::on_loadFromCSV_clicked()
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

void ContinuousResultsWindow::on_generateHtmlBtn_clicked()
{
    QString html = "";
    QString headHtml = "";
    QString finalHtml = "";
    QString input;
    QString style = "";
    QString inputLink;
    QStringList races;
    bool racesDone = false;
    bool table = false;
    bool head = false;
    int category = 999;
    int empty = 0;
    int z = 0;
    bool finalResults = ui->finalResultsChB->isChecked();

    headHtml = "<h2 class=\"vysledky_hlavni_nadpis\">"+ui->highlightEdit->text()+"</h2><br>\n";
    headHtml += "<small><a class=\"button\" href=\""+ui->pdfUrlEdit->text()+"\" download>PDF ke stažení</a></small><br>\n";
    headHtml += "<table style=\"border: 0px\"><tr style=\"border: 0px\"><td style=\"border: 0px\"><ul class=\"osnova_zavody\">\n";
    for(int i=0;i<model->rowCount();i++){
        if(table)
            html+= "<tr>";
        for(int j=0;j<model->columnCount();j++){
            input = model->data(model->index(i,j)).toString();
            if((j==0)||(j>2))
                style = " class=\"naStred\" style=\"width: 5% !important;\" ";
            else
                style = " style=\"width: 20% !important;\" ";
            if(table){
                if (head){
                    //if(j>0){
                        if(j==model->columnCount()-1)
                            input = input.mid(0,input.size()-1);
                        if((j>2)&&(j<10)){                          //TODO: udelat na libovolnej pocet zavodu!
                            z++;
                            if(!racesDone)
                                    races.append(input);
                            input = "Z"+QString::number(z);
                        }
                        if(finalResults){
                            if(j!=2)
                                html += "<th"+style+">"+input+"</th>";
                        }
                        else{
                            if((j!=11)&&(j!=12)&&(j!=2))
                                html += "<th"+style+">"+input+"</th>";
                        }

                    //}
                }
                else {
                    if(((j==0)&&(input==""))||((j==1)&&(input==""))||((j==2)&&(input=="")))
                        empty++;
                    if(j==model->columnCount()-1)
                        input = input.mid(0,input.size()-1);
                    if(finalResults){
                        if(j!=2)
                            html += "<td"+style+">"+input+"</td>";
                    }
                    else{
                        if((j!=11)&&(j!=12)&&(j!=2))
                            html += "<td"+style+">"+input+"</td>";
                    }
                }
            }
            else if((!table)&&(input!="")&&(j==1)&&(category>2)){                 //pokud si narazil na tabulku -> vytvor ji
                //html +=  + "<br>";  //nadpis
                inputLink = input;
                html += "<h3 id=\"K"+input.replace(' ','_')+"\" class=\"vysledky_nadpis\">"+inputLink+"</h3>\n";
                headHtml += "<li><a href=\"#K"+input.replace(' ','_')+"\">"+inputLink+"</a></li>\n";
                category = 2;

            }
        }
        category--;
        z=0;
        if(category==1){
            table = true;
            head = true;
            html += "<table class=\"vysledky\">\n";
        }
        else if(category==0){
            head = false;
            html += "</tr>\n";
        }
        else if(table){
            html += "</tr>\n";
        }
        if(empty==3){
            racesDone = true;
            html += "</table>\n";
            table = false;
            empty = 0;
            category = 99999;
        }
        else{
            empty = 0;
        }



    }
    html+="</table>";
    headHtml += "</ul></td><td style=\"border: 0px\">";
    foreach (QString zavod, races) {
        z++;
        headHtml+= "Z"+QString::number(z)+" = " + zavod + "<br>";
    }
    headHtml+= "</td></tr></table>";
    finalHtml = headHtml+html;
    ui->htmlPText->setPlainText(finalHtml);
}


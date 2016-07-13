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
        //ui->generateHtmlBtn->setEnabled(true);
    }
}

void ContinuousResultsWindow::on_generateHtmlBtn_clicked()
{
    QString html = "";
    QString headHtml = "";
    QString finalHtml = "";
    QString input;
    QString style = "";
    QString pStyle = "";
    QString temp;
    bool table = false;
    bool head = false;
    int category = 999;
    int empty = 0;
    int z = 0;

    //headHtml = "<h3 class=\"vysledky_hlavni_nadpis\">"+ui->highlightEdit->text()+"</h3><br>\n";
    //headHtml += "<small><a href=\""+ui->pdfUrlEdit->text()+"\" download>PDF ke stažení</a></small><br>\n";
    //DODELAT OSNOVU!!!!
    for(int i=0;i<model->rowCount();i++){
        if(table)
            html+= "<tr>";
        for(int j=0;j<model->columnCount();j++){
            input = model->data(model->index(i,j)).toString();
            if(table){
                if (head){
                    //if(j>0){
                        if(j==model->columnCount()-1)
                            input = input.mid(0,input.size()-1);
                        if((j>2)&&(j<10)){
                            z++;
                            input = "Z"+QString::number(z);
                        }
                        if(j!=11)
                            html += "<th"+style+">"+input+"</th>";
                    //}
                }
                else {
                    if(((j==0)&&(input==""))||((j==1)&&(input==""))||((j==2)&&(input=="")))
                        empty++;
                    if(j==model->columnCount()-1)
                        input = input.mid(0,input.size()-1);
                    if(j!=11)
                        html += "<td"+style+">"+input+"</td>";
                }
            }
            else if((!table)&&(input!="")&&(j==1)&&(category>2)){                 //pokud si narazil na tabulku -> vytvor ji
                html += input + "<br>";  //nadpis
                category = 2;

            }
        }
        category--;
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
    finalHtml = headHtml+html;
    ui->htmlPText->setPlainText(finalHtml);
}

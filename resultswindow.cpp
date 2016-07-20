#include "resultswindow.h"
#include "ui_resultswindow.h"
#include "QDebug"

ResultsWindow::ResultsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultsWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->resultsTableV->setModel(model);
    ui->resultsTableV->horizontalHeader()->setStretchLastSection(true);
}

ResultsWindow::~ResultsWindow()
{
    delete ui;
}

void ResultsWindow::on_loadFromCSV_clicked()
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

void ResultsWindow::on_generateHtmlBtn_clicked()
{
    QString html = "";
    QString headHtml = "";
    QString finalHtml = "";
    QString input;
    QString style = "";
    QString temp;
    bool table = false;
    bool head = false;
    int category = 999;
    headHtml = "<h3 class=\"vysledky_hlavni_nadpis\">"+ui->highlightEdit->text()+"</h3><br>\n";
    headHtml += "<small><a href=\""+ui->pdfUrlEdit->text()+"\" download>PDF ke stažení</a></small><br>\n";
    headHtml += "<ul class=\"osnova_zavody\">\n";
    for(int i=0;i<model->rowCount();i++){

        if((table)&&(category<=0)){
            if(i==model->rowCount()-1){
                html += "<tr>";
            } else if(model->data(model->index(i,0)).toString()!=""){
                html += "<tr>";
            }
        }
        for(int j=0;j<model->columnCount();j++){
                input = model->data(model->index(i,j)).toString();
                if((j==0)||(j==1)||(j==4)||(j==5)||(j==6))
                    style = " class=\"naStred\" style=\"width: 10%;\" ";
                else
                    style = " style=\"width: 25%;\" ";
                if(table){
                    if(head){
                        if(j==model->columnCount()-1)
                            input = input.mid(0,input.size()-1);
                        html += "<th"+style+">"+input+"</th>";
                    }
                    else if((j==0)&&(input=="")){
                        html += "</table>\n";
                        table = false;
                        category = 9;
                    }
                    else{
                        if(j==model->columnCount()-1)
                            input = input.mid(0,input.size()-1);
                        html += "<td"+style+">"+input+"</td>";
                    }

                }
                else if((input.left(9)=="Kategorie")||(input.left(9)=="kategorie")){
                    html += "<h3 id=\"K"+input.mid(12, input.size()-12).replace(' ','_')+"\" class=\"vysledky_nadpis\">"+input+"</h3>\n";
                    headHtml += "<li><a href=\"#K"+input.mid(12, input.size()-12).replace(' ','_')+"\">"+input.mid(12, input.size()-12)+"</a></li>\n";
                    category = 2;
                }
        }
        category--;
        if(table)
            html += "</tr>\n";
        if(category<1){
            table = true;
            head = false;
            if(category==0){
                head = true;
                html += "<table class=\"vysledky\">\n";
            }
        }
    }
    if(table)
        html += "</table>";
    headHtml += "</ul>";
    finalHtml = headHtml+html;
    ui->htmlPText->setPlainText(finalHtml);


}



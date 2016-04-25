#include "propositionsdialog.h"
#include "ui_propositionsdialog.h"
#include "QDebug"

PropositionsDialog::PropositionsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropositionsDialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->resultsTableV->setModel(model);
    ui->resultsTableV->horizontalHeader()->setStretchLastSection(true);
}

PropositionsDialog::~PropositionsDialog()
{
    delete ui;
}

void PropositionsDialog::on_loadFromCSV_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Otevři CSV", QDir::currentPath(), "CSV (*.csv)");
    QFile file (filename);
    model->clear();
    if (file.open(QIODevice::ReadOnly)){
        //QString data = file.readAll();
        //qDebug() << data;
        //data.remove( QRegExp("\r"));
        QString temp;
        QChar character;
        QTextStream textStream(file.readAll());
        textStream.setCodec("ANSI");
        while(!textStream.atEnd()){
            textStream >> character;
            if(character == ';'){
                checkString(temp, character);
            } else if (character == '\n'){
                checkString(temp, character);
            } else if (textStream.atEnd()){
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
        ui->generateHtmlBtn->setEnabled(true);
    }
}

void PropositionsDialog::checkString(QString &temp, QChar character){
    if(temp.count("\"")%2 == 0) {
        if(temp.startsWith(QChar('\"')) && temp.endsWith(QChar('\"'))){
            temp.remove( QRegExp("^\""));
            temp.remove( QRegExp("\"$"));
        }
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if(character != QChar(';')){
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    }
    else{
            temp.append(character);

    }
}

void PropositionsDialog::on_generateHtmlBtn_clicked()
{
    QString html = "";
    QString input;
    QString style = "";
    bool table = false;
    bool head = false;
    int category = false;
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
                    html += "<h3 class=\"vysledky_nadpis\">"+input+"</h3>\n";
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
    ui->htmlPText->setPlainText(html);


}



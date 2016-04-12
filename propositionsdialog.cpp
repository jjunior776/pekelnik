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
    QString html;
    QString input;
    html = "<table class=\"vysledky\">\n<tr><th>#</th>\n<th>Jméno</th>\n<th>Příjmení</th>\n<th>Čas</th></tr>\n\n";
    for(int i=1;i<model->rowCount();i++){
        html += "<tr>\n";
        for(int j=0;j<model->columnCount();j++){
                input = model->data(model->index(i,j)).toString();
                if(j==model->columnCount()-1)
                    input = input.mid(0,input.size()-1);
                html += "<td>"+input+"</td>";

        }
        html +="\n</tr>\n";
    }
    html += "</table>";

    ui->htmlPText->setPlainText(html);


}

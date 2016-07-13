#include "csvreader.h"

CSVReader::CSVReader()
{

}

void CSVReader::loadFromCSV(QTextStream &textStream, QStandardItemModel *model){
    QString temp;
    QChar character;
    while(!textStream.atEnd()){
        textStream >> character;
        if(character == ';'){
            checkString(temp, model, character);
        } else if (character == '\n'){
            checkString(temp, model, character);
        } else if (textStream.atEnd()){
            temp.append(character);
            checkString(temp, model);
        } else {
            temp.append(character);
        }
    }
}

void CSVReader::checkString(QString &temp, QStandardItemModel *model, QChar character){
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

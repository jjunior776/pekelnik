#ifndef CSVREADER_H
#define CSVREADER_H

#include <QString>
#include <QChar>
#include <QTextStream>
#include <QRegExp>
#include <QStandardItem>
#include <QStandardItemModel>

class CSVReader
{
public:
    CSVReader();
public slots:
    void loadFromCSV(QTextStream &textStream, QStandardItemModel *model);
private slots:
    void checkString(QString &temp, QStandardItemModel *model, QChar character = 0);
private:
    QList<QStandardItem*> standardItemList;
};


#endif // CSVREADER_H

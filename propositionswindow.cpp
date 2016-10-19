#include "propositionswindow.h"
#include "ui_propositionswindow.h"

PropositionsWindow::PropositionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropositionsWindow)
{
    ui->setupUi(this);
}

PropositionsWindow::~PropositionsWindow()
{
    delete ui;
}

void PropositionsWindow::on_pdfBtn_clicked()
{
    QString html;

    html = "<div align=center><img src=\""+ui->logoText->text()+"\"></div><br>";

    html += "<div align=center>"+ui->h1Text->text()+"</div>";
    html += "<h2 align=center>"+ui->h2Text->text()+"</h2>";
    html += "<h4 align=center>"+ui->h3Text->text()+"</h4>";

    html += "<table style=\"width: 100%; border:1\" align=center>";
    html += "<tr><td>Termín:</td><td>"+ui->dateText->text()+"</td></tr>";
    html += "<tr><td>Pořadatel:</td><td>"+ui->organizerText->text()+"</td></tr>";
    html += "<tr><td>Místo:</td><td>"+ui->placeText->text()+"</td></tr>";
    html += "<tr><td>Ředitel závodu:</td><td>"+ui->directorText->text()+"</td></tr>";
    html += "<tr><td>Prezentace:</td><td>"+ui->presentationText->text()+"</td></tr>";
    html += "</table><br>";
    html += "Startují:<br>";

    html =
    "<div align=right>"
       "City, 11/11/2015"
    "</div>"
    "<div align=left>"
       "Sender Name<br>"
       "street 34/56A<br>"
       "121-43 city"
    "</div>"
    "<h1 align=center>DOCUMENT TITLE</h1>"
    "<p align=justify>"
       "document content document content document content document content document content document content document content document content document content document content "
       "document content document content document content document content document content document content document content document content document content document content "
    "</p>"
    "<div align=right>sincerly</div>";

    QTextDocument *doc = new QTextDocument();
    doc->setHtml(html);

    QPrinter *printer = new QPrinter();

    printer->setOutputFileName("test.pdf");
    printer->setOutputFormat(QPrinter::PdfFormat);

    QPainter *painter = new QPainter();
    painter->begin( printer );
    doc->drawContents(painter, printer->pageRect().translated( -printer->pageRect().x(), -    printer->pageRect().y() ));
    doc->print(printer);

    painter->end();
}

void PropositionsWindow::on_logoBtn_clicked()
{
    QString logo = QFileDialog::getOpenFileUrl(this, "Zvol Logo", QDir::currentPath(), "Images (*.png *.jpg *.bmp *.gif)").toString();
    ui->logoText->setText(logo);
}

#include "eisagogi_lexis.h"
#include "ui_eisagogi_lexis.h"

eisagogi_lexis::eisagogi_lexis(QWidget *parent) : QDialog(parent), ui(new Ui::eisagogi_lexis)
{
    ui->setupUi(this);
    setWindowTitle(tr("Εισαγωγή Λέξης"));
    ok=false;
}

eisagogi_lexis::~eisagogi_lexis()
{
    delete ui;
}

void eisagogi_lexis::on_pushButton_kataxor_clicked()
{
    gb = ui->lineEdit_gb->text();
    gr = ui->lineEdit_gr->text();
    if(!(gb.isEmpty()||gr.isEmpty()))
    {
        ok=true;
        close();
    }
}

void eisagogi_lexis::on_pushButton_akuro_clicked()
{
    ok=false;
    close();
}

void eisagogi_lexis::arxiki__probalomeni_lexi(QString el, QString gb)
{
    ui->lineEdit_gr->setText(el);
    ui->lineEdit_gb->setText(gb);
}

#include "diagrafi_lexis.h"
#include "ui_diagrafi_lexis.h"
#include <QMessageBox>

diagrafi_lexis::diagrafi_lexis(QWidget *parent) : QDialog(parent), ui(new Ui::diagrafi_lexis)
{
    ui->setupUi(this);
    thesi=-1;
}

void diagrafi_lexis::dedomena_listas(arxeio trexon_arxeio)
{
    data=trexon_arxeio;
    long ar_lex = data.arithmos_lexeon_arith();
    QString grami;
    QString kena;
    long arithSirasStiLista;
    for(long arithSirasStoArxeio=0;arithSirasStoArxeio<ar_lex;arithSirasStoArxeio++)
    {
        arithSirasStiLista = arithSirasStoArxeio+1;
        if(arithSirasStiLista<10)
            kena = "        ";
        else if(arithSirasStiLista>=10&&arithSirasStiLista<100)
            kena = "      ";
        else if(arithSirasStiLista>=100&&arithSirasStiLista<1000)
            kena = "    ";
        else if(arithSirasStiLista>=1000&&arithSirasStiLista<10000)
            kena = "   ";

        grami = QString::number(arithSirasStiLista,10) + kena + data.epistrofi_egrafis(arithSirasStoArxeio,GB)+" = "+data.epistrofi_egrafis(arithSirasStoArxeio,EL);
        if(!data.EinaiExetasimi(arithSirasStoArxeio))
        {
            ui->listWidget->addItem(grami);
            ui->listWidget->item(arithSirasStiLista-1)->setForeground(Qt::gray);
        }
        else
            ui->listWidget->addItem(grami);
    }
}

diagrafi_lexis::~diagrafi_lexis()
{
    delete ui;
}

void diagrafi_lexis::on_pushButton_diag_clicked()
{
    //QMessageBox::about(this,tr("Πληροφορίες"),QString::number(ui->listWidget->currentRow(),10));
    thesi=euretirio.epistrofiAntistixisiThesisPinakaThesiArxiou(ui->listWidget->currentRow());

    if(thesi<0)
    {
        //QMessageBox::about(this,tr("Πληροφορίες"),QString::number(thesi,10));
        thesi=ui->listWidget->currentRow();
        if(thesi==-1)   //Αν δεν επιλέχθηκε γραμμή από την λίστα τότε μύνημα
            QMessageBox::about(this,tr("Πληροφορίες"),tr("Επιλέξτε γραμμή"));
        else
            close();
    }
    else
        close();
}

void diagrafi_lexis::on_pushButton_akuro_clicked()
{
    close();
}

void diagrafi_lexis::allagi_onom_pliktrou(QString onoma)
{
    ui->pushButton_diag->setText(onoma);
}

void diagrafi_lexis::diagrafi_pliktrou()
{
    ui->pushButton_diag->setVisible(false);
}

void diagrafi_lexis::on_lineEditEuresiGb_textChanged(QString textEditQString)
{
    if(textEditQString.length()>0)
        ui->lineEditEuresiGr->setReadOnly(true);    //Αν έχω γράψει κάτι στο αγγλικό πεδίο απενεργοποιείται το ελληνικό πεδίο
    else
        ui->lineEditEuresiGr->setReadOnly(false);

    long ar_lex = data.arithmos_lexeon_arith();
    QString grami;
    QString kena;
    long arithSirasStiLista=0;
    ui->listWidget->clear();
    euretirio.reset();
    thesi=-1;

    for(long arithSirasStoArxeio=0;arithSirasStoArxeio<ar_lex;arithSirasStoArxeio++)
    {
        if(data.lexiArxizeiApo(textEditQString, data.epistrofi_egrafis(arithSirasStoArxeio,GB)))
        {
            euretirio.eisagogiGrammis(arithSirasStoArxeio);
            arithSirasStiLista += 1;
            if(arithSirasStiLista<10)
                kena = "        ";
            else if(arithSirasStiLista>=10&&arithSirasStiLista<100)
                kena = "      ";
            else if(arithSirasStiLista>=100&&arithSirasStiLista<1000)
                kena = "    ";
            else if(arithSirasStiLista>=1000&&arithSirasStiLista<10000)
                kena = "   ";

            grami = QString::number(arithSirasStiLista,10) + kena + data.epistrofi_egrafis(arithSirasStoArxeio,GB)+" = "+data.epistrofi_egrafis(arithSirasStoArxeio,EL);
            if(!data.EinaiExetasimi(arithSirasStoArxeio))
            {
                ui->listWidget->addItem(grami);
                ui->listWidget->item(arithSirasStiLista-1)->setForeground(Qt::gray);
            }
            else
                ui->listWidget->addItem(grami);
        }
    }
}

void diagrafi_lexis::on_lineEditEuresiGr_textChanged(QString textEditQString)
{
    if(textEditQString.length()>0)
        ui->lineEditEuresiGb->setReadOnly(true);
    else
        ui->lineEditEuresiGb->setReadOnly(false);

    long ar_lex = data.arithmos_lexeon_arith();
    QString grami;
    QString kena;
    long int arithSirasStiLista=0;
    ui->listWidget->clear();
    euretirio.reset();
    thesi=-1;

    for(long arithSirasStoArxeio=0;arithSirasStoArxeio<ar_lex;arithSirasStoArxeio++)
    {
        if(data.lexiArxizeiApo(textEditQString, data.epistrofi_egrafis(arithSirasStoArxeio,EL)))
        {
            euretirio.eisagogiGrammis(arithSirasStoArxeio);
            arithSirasStiLista += 1;
            if(arithSirasStiLista<10)
                kena = "        ";
            else if(arithSirasStiLista>=10&&arithSirasStiLista<100)
                kena = "      ";
            else if(arithSirasStiLista>=100&&arithSirasStiLista<1000)
                kena = "    ";
            else if(arithSirasStiLista>=1000&&arithSirasStiLista<10000)
                kena = "   ";

            grami = QString::number(arithSirasStiLista,10) + kena + data.epistrofi_egrafis(arithSirasStoArxeio,GB)+" = "+data.epistrofi_egrafis(arithSirasStoArxeio,EL);
            if(!data.EinaiExetasimi(arithSirasStoArxeio))
            {
                ui->listWidget->addItem(grami);
                ui->listWidget->item(arithSirasStiLista-1)->setForeground(Qt::gray);
            }
            else
                ui->listWidget->addItem(grami);
        }
    }
}

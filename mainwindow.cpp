#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eisagogi_lexis.h"
#include "diagrafi_lexis.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDateTime>
#include <QRandomGenerator>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    thesi_trexousas_lexis=-1;
    ar_lexeon_pou_exet = 0;

    ui->setupUi(this);
    ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
    ui->label_ar_ex_lex->setText(QString::number(ar_lexeon_pou_exet,10));
    ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
    ui->lineEdit_el->setDisabled(true);
    ui->lineEdit_gb->setDisabled(true);
    ui->pushButton_elenxos->setDisabled(true);
    setWindowTitle(tr("%1[*] - %2").arg(tr("Ανώνυμο")).arg(tr("Λεξιλόγιο")));


    for (int i = 0; i < arith_prosfaton_arxeion; ++i) 
    {
        prosfata_arxeia_Actions[i] = new QAction(this);
        prosfata_arxeia_Actions[i]->setVisible(false);
        connect(prosfata_arxeia_Actions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    ui->arxeio->removeAction(ui->m_a_exodos);
    separatorAction = ui->arxeio->addSeparator();
    for (int i = 0; i < arith_prosfaton_arxeion; ++i)
        ui->arxeio->addAction(prosfata_arxeia_Actions[i]);
    ui->arxeio->addSeparator();
    ui->arxeio->addAction(ui->m_a_exodos);
    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
}

void MainWindow::openRecentFile()
{
    if (Egrisi_Sinexias())
    {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
        {
            if(trexon_arxeio.anagnosi_arxeiou_disko(action->data().toString()))
            {
                setWindowModified(false);

                ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
                arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
                ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
                ui->label_ar_ex_lex->setText("0");

                QString fileName = trexon_arxeio.epistrofi_onomatos_arxeiou();
                QString onoma = QFileInfo(fileName).fileName();

                prosfata_arxeia.removeAll(fileName);
                prosfata_arxeia.prepend(fileName);
                ananeosi_prosfaton_arxeion_Action();


                setWindowTitle(tr("%1[*] - %2").arg(onoma).arg(tr("Λεξιλόγιο")));
                ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
                arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
                thesi_trexousas_lexis=-1;
                ar_lexeon_pou_exet = 0;
                statusBar()->showMessage(tr("Το αρχείο φορτώθηκε"), 2000);
            }
            else
                statusBar()->showMessage(tr("Το αρχείο δεν φορτώθηκε"), 2000);
        }
    }
}

void MainWindow::ananeosi_prosfaton_arxeion_Action()
{
    QMutableStringListIterator i(prosfata_arxeia);
    while (i.hasNext())
    {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < arith_prosfaton_arxeion; ++j)
    {
        if (j < prosfata_arxeia.count())
        {
            QString onoma = tr("&%1 %2").arg(j + 1).arg(QFileInfo(prosfata_arxeia[j]).fileName());
            prosfata_arxeia_Actions[j]->setText(onoma);
            prosfata_arxeia_Actions[j]->setData(prosfata_arxeia[j]);
            prosfata_arxeia_Actions[j]->setVisible(true);
        }
        else
        {
            prosfata_arxeia_Actions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!prosfata_arxeia.isEmpty());
}

MainWindow::~MainWindow()
{
    delete ui;
}


////////////////////////////////////////////////////////////////////////////////
//***Γενικές Συναρτήσεις******Γενικές Συναρτήσεις***Γενικές Συναρτήσεις******

bool MainWindow::Egrisi_Sinexias()  //Ελέγχει αν το αρχείο είναι σωμένο ή δεν θέλω να σωθεί και επιτρέπεται να συνεχίσω χωρις από λάθως απόλεια δεδομένων
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Λεξιλόγιο"), tr("Το άρχείο έχει αλλαγές\n" "Αποθήκευση Αλλαγών;"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
        {
            return Apothikeusi_Arxeiou();
        }
        else if (r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

//***Τέλος Γενικων Συναρτήσεων******Τέλος Γενικων Συναρτήσεων***Τέλος Γενικων Συναρτήσεων******
///////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//***Αρχή συναρτήσεων κυνηγών Μενού******Αρχή συναρτήσεων κυνηγών Μενού***

void MainWindow::Neo_Arxeio()
{
    if (Egrisi_Sinexias())
    {
        setWindowModified(false);
        trexon_arxeio.katharismos_mnimis();
        arxeio_exetasis.katharismos_mnimis();
        ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
        ui->label_arith_lex_pros_exet->setText("0");
        ui->label_ar_ex_lex->setText("0");
        setWindowTitle(tr("%1[*] - %2").arg(tr("Ανώνυμο")).arg(tr("Λεξιλόγιο")));
    }
}

void MainWindow::Anoigma_Arxeiou()
{
    if (Egrisi_Sinexias())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Άνοιγμα Λεξιλογίου"), ".",tr("Αρχείο Λεξιλογίου (*.lxg *.lxe)"));

        if (!fileName.isEmpty())
        {
            if (!trexon_arxeio.anagnosi_arxeiou_disko(fileName))
            {
                statusBar()->showMessage(tr("Ακυρώθηκε η φόρτωση του αρχείου"), 2000);
            }
            else
            {
                setWindowModified(false);

                ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
                ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
                ui->label_ar_ex_lex->setText("0");

                prosfata_arxeia.removeAll(fileName);
                prosfata_arxeia.prepend(fileName);
                ananeosi_prosfaton_arxeion_Action();

                QString onoma = QFileInfo(trexon_arxeio.epistrofi_onomatos_arxeiou()).fileName();
                setWindowTitle(tr("%1[*] - %2").arg(onoma).arg(tr("Λεξιλόγιο")));
                ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
                arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
                thesi_trexousas_lexis=-1;
                ar_lexeon_pou_exet = 0;
                statusBar()->showMessage(tr("Το αρχείο φορτώθηκε"), 2000);
            }
        }
    }
}

bool MainWindow::Apothikeusi_Arxeiou()
{
    QString onoma_tr_arx = trexon_arxeio.epistrofi_onomatos_arxeiou();
    if (onoma_tr_arx.isEmpty())
    {
        return Apothik_Os();
    }
    else
    {
        if(trexon_arxeio.egrafi_arxeiou_disko(trexon_arxeio.epistrofi_onomatos_arxeiou()))
        {
            setWindowModified(false);

            QString fileName = trexon_arxeio.epistrofi_onomatos_arxeiou();
//            QString onoma = QFileInfo(fileName).fileName();
            prosfata_arxeia.removeAll(fileName);
            prosfata_arxeia.prepend(fileName);
            ananeosi_prosfaton_arxeion_Action();

            statusBar()->showMessage(tr("Το αρχείο σώθηκε"), 2000);
            return true;
        }
        else
        {
            statusBar()->showMessage(tr("Το αρχείο δεν σώθηκε"), 2000);
            return false;
        }
    }
    return false;
}

bool MainWindow::Apothik_Os()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Αποθήκευση Λεξιλογίου"), ".",
                               tr("Αρχείο Λεξιλογίου (*.lxg)"));
    if (!fileName.isEmpty())
    {

        if(trexon_arxeio.egrafi_arxeiou_disko(fileName))
        {
            setWindowModified(false);

            prosfata_arxeia.removeAll(fileName);
            prosfata_arxeia.prepend(fileName);
            ananeosi_prosfaton_arxeion_Action();

            QString onoma = QFileInfo(fileName).fileName();
            setWindowTitle(tr("%1[*] - %2").arg(onoma).arg(tr("Λεξιλόγειο")));
            trexon_arxeio.orismos_onomatos_arxeiou(fileName);
            statusBar()->showMessage(tr("Το αρχείο σώθηκε"), 2000);
            return true;
        }
        else
        {
            statusBar()->showMessage(tr("Το αρχείο δεν σώθηκε"), 2000);
            return false;
        }
    }
    return false;
}

void MainWindow::Diagrafi_Lexis()
{
    diagrafi_lexis parathiro(this);
    parathiro.dedomena_listas(trexon_arxeio);
    parathiro.exec();
    if(parathiro.thesi>=0)
    {
        QString elin = trexon_arxeio.epistrofi_egrafis(parathiro.thesi,EL);
        QString aglk = trexon_arxeio.epistrofi_egrafis(parathiro.thesi,GB);
        trexon_arxeio.diagrafi_lexis(parathiro.thesi);

        int x = arxeio_exetasis.ThesiUparxousas_Lexis(aglk,elin);
        if(x>=0)
            arxeio_exetasis.diagrafi_lexis(x);

        ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
        ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
        setWindowModified(true);
    }
}

void MainWindow::Eisagogi_Lexis()
{
    eisagogi_lexis parathiro(this);
    parathiro.exec();

    if(parathiro.ok==true)
    {
        if(trexon_arxeio.uparxi_lexi(parathiro.gb,parathiro.gr))
            QMessageBox::about(this,tr("Μήνυμα"),tr("Το ζεύγος των λέξεων υπάρχει!"));
        else
        {
            trexon_arxeio.eisagogi_lexis(parathiro.gb,parathiro.gr);
            arxeio_exetasis.eisagogi_lexis(parathiro.gb,parathiro.gr);
            ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
            ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
            setWindowModified(true);
        }
    }
}

void MainWindow::Diorthosi_Lexis()
{
    diagrafi_lexis par_alag(this);
    par_alag.dedomena_listas(trexon_arxeio);
    par_alag.allagi_onom_pliktrou(tr("Αλλαγή"));
    par_alag.exec();

    if(par_alag.thesi>=0)
    {
        eisagogi_lexis par_eis(this);
        par_eis.arxiki__probalomeni_lexi(trexon_arxeio.epistrofi_egrafis(par_alag.thesi,EL),trexon_arxeio.epistrofi_egrafis(par_alag.thesi,GB));
        par_eis.exec();

        if(par_eis.ok==true)
        {
            if(trexon_arxeio.uparxi_lexi(par_eis.gb,par_eis.gr))
                QMessageBox::about(this,tr("Μήνυμα"),tr("Η λέξη υπάρχει!"));
            else
            {
                int x = arxeio_exetasis.ThesiUparxousas_Lexis(trexon_arxeio.epistrofi_egrafis(par_alag.thesi,GB),trexon_arxeio.epistrofi_egrafis(par_alag.thesi,EL));
                if(x>=0)
                {
                    arxeio_exetasis.diagrafi_lexis(x);
                    arxeio_exetasis.eisagogi_lexis(par_eis.gb,par_eis.gr);
                }
                trexon_arxeio.diagrafi_lexis(par_alag.thesi);
                trexon_arxeio.eisagogi_lexis(par_eis.gb,par_eis.gr);
                ui->label_ar_lexeon->setText(trexon_arxeio.arithmos_lexeon_QStr());
                ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
                setWindowModified(true);
            }
        }
    }
}

void MainWindow::ExetaseApo()
{
    diagrafi_lexis parathiro_ExApo(this);
    parathiro_ExApo.dedomena_listas(trexon_arxeio);
    parathiro_ExApo.allagi_onom_pliktrou(tr("Εξέτασε Από Εδώ"));
    parathiro_ExApo.exec();

    if(parathiro_ExApo.thesi>=0)
    {
        arxeio_exetasis = trexon_arxeio;
        for(long x=0;x<parathiro_ExApo.thesi;x++)
            arxeio_exetasis.diagrafi_lexis(0);

        arxeio_exetasis.AferesiMiExetasimon();

        thesi_trexousas_lexis=-1;
        ar_lexeon_pou_exet=0;

        QString thesi;
        thesi.setNum(parathiro_ExApo.thesi,10);
        ui->label_ar_ex_lex->setText("0");
        ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
    }
}

void MainWindow::MinExetazeisTo()
{
    diagrafi_lexis parathiroMinExetasisTo(this);
    parathiroMinExetasisTo.dedomena_listas(trexon_arxeio);
    parathiroMinExetasisTo.allagi_onom_pliktrou(tr("Αλλαγή Εξέτασης Εδώ"));
    parathiroMinExetasisTo.exec();
    if(parathiroMinExetasisTo.thesi>=0)
    {
        if(trexon_arxeio.EinaiExetasimi(parathiroMinExetasisTo.thesi))
            trexon_arxeio.lexi_eksetasimi(false,parathiroMinExetasisTo.thesi);
        else
            trexon_arxeio.lexi_eksetasimi(true,parathiroMinExetasisTo.thesi);

        arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
        ui->label_ar_ex_lex->setText("0");
        ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());

        setWindowModified(true);
    }
}

void MainWindow::on_m_e_Proboli_Mitroo_triggered()
{
        diagrafi_lexis parathiro(this);
        parathiro.dedomena_listas(mitroo_ektuposis);
        parathiro.diagrafi_pliktrou();
        parathiro.exec();
}

void MainWindow::on_m_e_ektuposi_mitroo_triggered()
{
    long ar_lex = mitroo_ektuposis.arithmos_lexeon_arith();
    if(ar_lex>0)
    {
        QString lexi_GR,lexi_GB;
        QString html = tr("<table border =1 cellspacing=0><tr><td><h2>ΑΓΓΛΙΚΑ<td><h2>_____<td><h2>ΕΛΛΗΝΙΚΑ<tr>");
        for(long x=0;x<ar_lex;x++)
        {
            lexi_GB = mitroo_ektuposis.epistrofi_egrafis(x,GB);
            lexi_GR = mitroo_ektuposis.epistrofi_egrafis(x,EL);
            html = html + "<tr><td>" + lexi_GB + "<td> <td>" + lexi_GR;
        }
        html+="</table>";

        QPrinter printer(QPrinter::HighResolution);

        QPrintDialog printDialog(&printer,this);
        printDialog.setWindowTitle("Ektuposis");
        printDialog.exec();

        QTextDocument textdoc;
        textdoc.setHtml(html);
        textdoc.print(&printer);
    }
    else
        statusBar()->showMessage(tr("Δεν υπάρχουν λέξεις στο μητρώο"), 2000);
}

void MainWindow::on_m_e_ExagMitrooPDF_triggered()
{
    long ar_lex = mitroo_ektuposis.arithmos_lexeon_arith();
    if(ar_lex>0)
    {

    //Ρυθμίσεις
        QString lexi_GR,lexi_GB;
        QString html = tr("<table border =1 cellspacing=0><tr><td><h2>ΑΓΓΛΙΚΑ<td><h2>_____<td><h2>ΕΛΛΗΝΙΚΑ<tr>");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        QString OnomaArxeiou = QFileDialog::getSaveFileName(this,
                                   tr("Εξαγωγή Λεξιλογίου Σε PDF"), ".",
                                   tr("Αρχείο PDF (*.pdf)"));
        if (!OnomaArxeiou.isEmpty())
        {
            //QString OnomaArxeiou = tr("C:\\Documents and Settings\\TASOS\\Επιφάνεια εργασίας\\print.pdf");
            printer.setOutputFileName(OnomaArxeiou);
            //Τέλος Ρυθμίσεις

            for(long x=0;x<ar_lex;x++)
            {
                lexi_GB = mitroo_ektuposis.epistrofi_egrafis(x,GB);
                lexi_GR = mitroo_ektuposis.epistrofi_egrafis(x,EL);
                html = html + "<tr><td>" + lexi_GB + "<td> <td>" + lexi_GR;
            }
            html+="</table>";

            QTextDocument textdoc;
            textdoc.setHtml(html);
            textdoc.print(&printer);
        }
    }
    else
        statusBar()->showMessage(tr("Δεν υπάρχουν λέξεις στο μητρώο"), 2000);
}

void MainWindow::on_m_e_ektuposi_triggered()
{
    long ar_lex = trexon_arxeio.arithmos_lexeon_arith();
    if(ar_lex>0)
    {
        QPrinter printer(QPrinter::HighResolution);

        QPrintDialog printDialog(&printer,this);
        printDialog.setWindowTitle("Ektuposis");
        bool ektuposi_OK = printDialog.exec();

        if(ektuposi_OK)
        {
            QString lexi_GR,lexi_GB;
            QString html = tr("<table border =1 cellspacing=0><tr><td><h2>ΑΓΓΛΙΚΑ<td><h2>_____<td><h2>ΕΛΛΗΝΙΚΑ<tr>");
            for(long x=0;x<ar_lex;x++)
            {
                lexi_GB = trexon_arxeio.epistrofi_egrafis(x,GB);
                lexi_GR = trexon_arxeio.epistrofi_egrafis(x,EL);
                html = html + "<tr><td>" + lexi_GB + "<td> <td>" + lexi_GR;
            }
            html+="</table>";

            QTextDocument textdoc;
            textdoc.setHtml(html);
            textdoc.print(&printer);
        }
    }
    else
        statusBar()->showMessage(tr("Δεν υπάρχουν λέξεις στο μητρώο"), 2000);
}

void MainWindow::on_m_e_ExagArxeioPDF_triggered()
{
    long ar_lex = trexon_arxeio.arithmos_lexeon_arith();
    if(ar_lex>0)
    {

    //Ρυθμίσεις
        QString lexi_GR,lexi_GB;
        QString html = tr("<table border =1 cellspacing=0><tr><td><h2>ΑΓΓΛΙΚΑ<td><h2>_____<td><h2>ΕΛΛΗΝΙΚΑ<tr>");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QString OnomaArxeiou = QFileDialog::getSaveFileName(this,
                                   tr("Εξαγωγή Λεξιλογίου Σε PDF"), ".",
                                   tr("Αρχείο PDF (*.pdf)"));
        if (!OnomaArxeiou.isEmpty())
        {
            //QString OnomaArxeiou = tr("C:\\Documents and Settings\\TASOS\\Επιφάνεια εργασίας\\print.pdf");
            printer.setOutputFileName(OnomaArxeiou);
            //Τέλος Ρυθμίσεις

            for(long x=0;x<ar_lex;x++)
            {
                lexi_GB = trexon_arxeio.epistrofi_egrafis(x,GB);
                lexi_GR = trexon_arxeio.epistrofi_egrafis(x,EL);
                html = html + "<tr><td>" + lexi_GB + "<td> <td>" + lexi_GR;
            }
            html+="</table>";

            QTextDocument textdoc;
            textdoc.setHtml(html);
            textdoc.print(&printer);
        }
    }
    else
        statusBar()->showMessage(tr("Δεν υπάρχουν λέξεις στο μητρώο"), 2000);
}

bool MainWindow::on_m_e_ApothMitroou_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Αποθήκευση Λεξιλογίου"), ".",
                               tr("Αρχείο Λεξιλογίου (*.lxe)"));
    if (!fileName.isEmpty())
    {

        if(mitroo_ektuposis.egrafi_arxeiou_disko(fileName))
        {
            QString onoma = QFileInfo(fileName).fileName();
            mitroo_ektuposis.orismos_onomatos_arxeiou(fileName);
            statusBar()->showMessage(tr("Το αρχείο σώθηκε"), 2000);
            return true;
        }
        else
        {
            statusBar()->showMessage(tr("Το αρχείο δεν σώθηκε"), 2000);
            return false;
        }
    }
    return false;
}

void MainWindow::Sxetika()
{
    QMessageBox::about(this,tr("Πληροφορίες"),tr("Τάσος Γεωργίου"));
}

//***Τέλος συναρτήσεων κυνηγών Μενού******Τέλος συναρτήσεων κυνηγών Μενού***
//////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//***Αρχή συναρτήσεων κυνηγών Πλήκτρων******Αρχή συναρτήσεων κυνηγών Πλήκτρων***


void MainWindow::on_pushButton_el_clicked()
{
    if((trexon_arxeio.arithmos_lexeon_arith()>1&&1<arxeio_exetasis.arithmos_lexeon_arith())||
       (trexon_arxeio.arithmos_lexeon_arith()==1&&0<arxeio_exetasis.arithmos_lexeon_arith()&&thesi_trexousas_lexis==-1))
    {
        if(thesi_trexousas_lexis>=0)
        {
            arxeio_exetasis.diagrafi_lexis(thesi_trexousas_lexis);
        }
        if(ui->checkBox_el->isChecked())
        {
            int kikloi = QDateTime::currentDateTime().time().second()+1;
            for(int x=0;x<kikloi;x++)
            {
               do
               {
                   //thesi_trexousas_lexis = arxeio_exetasis.arithmos_lexeon_arith()*qrand()/32768;
                   thesi_trexousas_lexis = (long) (arxeio_exetasis.arithmos_lexeon_arith()* (double) QRandomGenerator::global()->bounded(32768)/32768);
               }while(thesi_trexousas_lexis>=arxeio_exetasis.arithmos_lexeon_arith());
             }
        }
        else
            thesi_trexousas_lexis=0;
        ar_lexeon_pou_exet++;
        ui->lineEdit_el->setText(arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,EL));
        ui->lineEdit_el->setDisabled(true);
        ui->lineEdit_gb->setEnabled(true);
        ui->lineEdit_gb->clear();
        ui->pushButton_elenxos->setEnabled(true);
    }
    else
    {
        thesi_trexousas_lexis=-1;
        ar_lexeon_pou_exet=0;
        ui->pushButton_elenxos->setDisabled(true);
        if(trexon_arxeio.arithmos_lexeon_arith()>0)
        {
            ui->lineEdit_el->clear();
            ui->lineEdit_gb->clear();
            arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
            ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
            QMessageBox::about(this,tr("Μήνυμα"),tr("Τέλος Αρχείου.\nΕκίνηση από αρχή"));
        }
    }
     ui->label_ar_ex_lex->setText(QString::number(ar_lexeon_pou_exet,10));
}

void MainWindow::on_pushButton_gb_clicked()
{
    if((trexon_arxeio.arithmos_lexeon_arith()>1&&1<arxeio_exetasis.arithmos_lexeon_arith())||
       (trexon_arxeio.arithmos_lexeon_arith()==1&&0<arxeio_exetasis.arithmos_lexeon_arith()&&thesi_trexousas_lexis==-1))
    {
        if(thesi_trexousas_lexis>=0)
        {
            arxeio_exetasis.diagrafi_lexis(thesi_trexousas_lexis);
        }
        if(ui->checkBox_gb->isChecked())
        {
            int kikloi = QDateTime::currentDateTime().time().second()+1;
            for(int x=0;x<kikloi;x++)
            {
                do
                {
                    //thesi_trexousas_lexis = arxeio_exetasis.arithmos_lexeon_arith()*qrand()/32768;
                    thesi_trexousas_lexis = (long) (arxeio_exetasis.arithmos_lexeon_arith()* (double) QRandomGenerator::global()->bounded(32768)/32768);
                }while(thesi_trexousas_lexis>=arxeio_exetasis.arithmos_lexeon_arith());
            }
        }
        else
            thesi_trexousas_lexis=0;
        ar_lexeon_pou_exet++;
        ui->lineEdit_gb->setText(arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,GB));
        ui->lineEdit_gb->setDisabled(true);
        ui->lineEdit_el->setEnabled(true);
        ui->lineEdit_el->clear();
        ui->pushButton_elenxos->setEnabled(true);
    }
    else    //Ξεκινάει από την αρχή
    {
        thesi_trexousas_lexis=-1;
        ar_lexeon_pou_exet=0;
        ui->lineEdit_el->clear();
        ui->pushButton_elenxos->setDisabled(true);
        if(trexon_arxeio.arithmos_lexeon_arith()>0)
        {
            ui->lineEdit_el->clear();
            ui->lineEdit_gb->clear();
            arxeio_exetasis.AntigrafiExetasimon(trexon_arxeio);
            ui->label_arith_lex_pros_exet->setText(arxeio_exetasis.arithmos_lexeon_QStr());
            QMessageBox::about(this,tr("Μήνυμα"),tr("Τέλος Αρχείου.\nΕκίνηση από αρχή"));
        }
    }
     ui->label_ar_ex_lex->setText(QString::number(ar_lexeon_pou_exet,10));
}

void MainWindow::on_pushButton_lisi_clicked()
{
    if(thesi_trexousas_lexis == -1)
        QMessageBox::about(this,tr("Μήνυμα"),tr("Επιλέξτε Λέξη"));
    else
    {
        QString aglika = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,GB);
        QString elinika = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,EL);
        if(ui->lineEdit_el->isEnabled())
            QMessageBox::about(this,tr("Μήνυμα"),aglika + " = " + elinika);
        else
            QMessageBox::about(this,tr("Μήνυμα"),elinika + " = " + aglika);
    }
    ui->pushButton_elenxos->setDisabled(true);
}


void MainWindow::on_pushButton_elenxos_clicked()
{
    QString egrafi_EL;
    QString egrafi_GB;
    egrafi_EL = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,EL);
    egrafi_GB = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,GB);

    if(ui->lineEdit_el->isEnabled())
    {
        QString elinika = ui->lineEdit_el->text();
        if(egrafi_EL==elinika)
            QMessageBox::about(this,tr("Μήνυμα"),tr("ΣΩΣΤΟ"));
        else
            QMessageBox::about(this,tr("Μήνυμα"),tr("ΛΑΘΟΣ"));
    }
    else
    {
        QString aglika = ui->lineEdit_gb->text();
        if(egrafi_GB==aglika)
            QMessageBox::about(this,tr("Μήνυμα"),tr("ΣΩΣΤΟ"));
        else
            QMessageBox::about(this,tr("Μήνυμα"),tr("ΛΑΘΟΣ"));
    }
}


void MainWindow::on_pushButton_printlist_clicked()
{//Αποθηκεύη την τρέχουσα λέξη στο μητρώο εκτύπωσης
    if(thesi_trexousas_lexis>=0)
    {
        QString egrafi_EL;
        QString egrafi_GB;

        egrafi_EL = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,EL);
        egrafi_GB = arxeio_exetasis.epistrofi_egrafis(thesi_trexousas_lexis,GB);

        if(!mitroo_ektuposis.uparxi_lexi(egrafi_GB,egrafi_EL))
        {//Αν δεν υπάρχει τότε καταχωρείται
            mitroo_ektuposis.eisagogi_lexis(egrafi_GB,egrafi_EL);
            statusBar()->showMessage(tr("Καταχωρήθηκε Στο Μητρώο Εκτύπωσης"), 2000);
        }
        else
        {
            long thesi_mitroo = mitroo_ektuposis.ThesiUparxousas_Lexis(egrafi_GB,egrafi_EL);
            mitroo_ektuposis.diagrafi_lexis(thesi_mitroo);
            statusBar()->showMessage(tr("Διαγράφηκε Από Το Μητρώο Εκτύπωσης"), 2000);
        }
    }
    else
        statusBar()->showMessage(tr("Επιλέξτε Λέξη"), 2000);
}

//***Τέλος συναρτήσεων κυνηγών Πλήκτρων******Τέλος συναρτήσεων κυνηγών Πλήκτρων***
//////////////////////////////////////////////////////////////////////////////////


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Egrisi_Sinexias())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Lexis");

    restoreGeometry(settings.value("geometry").toByteArray());

    prosfata_arxeia = settings.value("prosfata_arxeia").toStringList();

    ananeosi_prosfaton_arxeion_Action();
}

void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "Lexis");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("prosfata_arxeia", prosfata_arxeia);
}



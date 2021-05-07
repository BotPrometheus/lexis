#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "arxeio.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintDialog>

//commit
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readSettings();
    void writeSettings();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    bool Egrisi_Sinexias();                         //Ελέγχει αν το αρχείο είναι σωμένο ή δεν θέλω να σωθεί και επιτρέπεται να συνεχίσω χωρις από λάθως απόλεια δεδομένων
    void ananeosi_prosfaton_arxeion_Action();       //Ανανεώνει τη λίστα των πρόσφατων αρχείων στην λίστα αρχείο και αντιστοιχεί με τις λειτουργείες τους
    arxeio trexon_arxeio;
    arxeio arxeio_exetasis;                         //Εδώ αποθηκεύονται οι λέξεις που θα εξεταστούν και κάθε λέξη που εξετάστηκε αφαιρείται για να εξεταστούν οι υπόλοιπες
    arxeio mitroo_ektuposis;                        //Εδώ αποθηκεύονται οι λέξεις που θα εκτυπωθούν. Ο πίνακας αυτός δεν αποθηκεύεται και χάνεται μετά την λήξη του προγράμματος
    long thesi_trexousas_lexis;                     //Η λέξη που εξετάζεται για την γνώση τους
    long ar_lexeon_pou_exet;                        //Οι λέξεις που έχουν εξεταστεί
    enum { arith_prosfaton_arxeion = 4 };           //Ο αριθμός πρόσφατων αρχείων που θα εμφανίζονται στο μενού Αρχείο
    QAction *prosfata_arxeia_Actions[arith_prosfaton_arxeion];
    QStringList prosfata_arxeia;
    QAction *separatorAction;

private slots:
    void on_pushButton_elenxos_clicked();
    void on_pushButton_lisi_clicked();
    void on_pushButton_gb_clicked();
    void on_pushButton_el_clicked();
    void on_pushButton_printlist_clicked();
    void on_m_e_Proboli_Mitroo_triggered();
    void on_m_e_ektuposi_mitroo_triggered();

    void Neo_Arxeio();
    void Anoigma_Arxeiou();
    bool Apothikeusi_Arxeiou();
    bool Apothik_Os();
    void Diagrafi_Lexis();
    void Eisagogi_Lexis();
    void openRecentFile();
    void Sxetika();
    void Diorthosi_Lexis();
    void ExetaseApo();
    void MinExetazeisTo();

    void on_m_e_ExagMitrooPDF_triggered();
    void on_m_e_ektuposi_triggered();
    void on_m_e_ExagArxeioPDF_triggered();
    bool on_m_e_ApothMitroou_triggered();
};

#endif // MAINWINDOW_H

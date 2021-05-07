#ifndef DIAGRAFI_LEXIS_H
#define DIAGRAFI_LEXIS_H

#include <QDialog>
#include "arxeio.h"

namespace Ui {
    class diagrafi_lexis;
}

class diagrafi_lexis : public QDialog
{
    Q_OBJECT

public:
    explicit diagrafi_lexis(QWidget *parent = 0);
    ~diagrafi_lexis();
    void dedomena_listas(arxeio data);  //Βάζει στην λίστα τα δεδομένα του αρχείου
    int thesi;  //Επιστρέφει τη θέση από την λίστα διαγραφής. Αν δεν επιλεχθεί κατι thesi == -1
    arxeio data; //Τα δεδομένα στην RAM
    void allagi_onom_pliktrou(QString onoma);
    void diagrafi_pliktrou();

private:
    Ui::diagrafi_lexis *ui;

    class KlasiEuretiriouAnazitisis
    {
    private:


    public:
        long int* grammiEgrafisArxeiou;
        long int plithosEgrafon;

        KlasiEuretiriouAnazitisis()
        {
            grammiEgrafisArxeiou=NULL;
            plithosEgrafon=0;
        }

        ~KlasiEuretiriouAnazitisis()
        {
            plithosEgrafon=0;
            if(grammiEgrafisArxeiou!=NULL)
                delete[]grammiEgrafisArxeiou;
        }

        void reset()
        {
            plithosEgrafon=0;
        }

        void eisagogiGrammis(long int eisagArithSirasStoArxeio)
        {
            if(plithosEgrafon>0)
            {
                long int* grammiEgrafisArxeiouCopy;
                grammiEgrafisArxeiouCopy=new long int[plithosEgrafon];
                for(int x=0;x<plithosEgrafon;x++)
                {
                    grammiEgrafisArxeiouCopy[x]=grammiEgrafisArxeiou[x];
                }
                grammiEgrafisArxeiou = new long int [plithosEgrafon+1];
                for(int x=0;x<plithosEgrafon;x++)
                {
                    grammiEgrafisArxeiou[x]=grammiEgrafisArxeiouCopy[x];
                }
                grammiEgrafisArxeiou[plithosEgrafon]=eisagArithSirasStoArxeio;
                plithosEgrafon++;
                delete [] grammiEgrafisArxeiouCopy;
            }
            else if(plithosEgrafon==0)
            {
                grammiEgrafisArxeiou = new long int [1];
                grammiEgrafisArxeiou[0]=eisagArithSirasStoArxeio;
                plithosEgrafon=1;
            }
        }

        long int epistrofiAntistixisiThesisPinakaThesiArxiou(long int thesiEgrafisPinaka)
        {
            if(thesiEgrafisPinaka>=0 && thesiEgrafisPinaka<=plithosEgrafon && plithosEgrafon>0)    //Η συνθήκη αυτή είναι αληθής όταν έχει γίνει αναζήτηση στα πεδία εύρεσης στο κύριο παράθυρο και έχει επιλεχθεί με το ποντίκι μία σειρά της λίστας
                return grammiEgrafisArxeiou[thesiEgrafisPinaka];
            else
                return -1;
        }
    };

    KlasiEuretiriouAnazitisis euretirio;

private slots:
    void on_lineEditEuresiGr_textChanged(QString textEditQString);
    void on_lineEditEuresiGb_textChanged(QString textEditQString);
    void on_pushButton_akuro_clicked();
    void on_pushButton_diag_clicked();
};

#endif // DIAGRAFI_LEXIS_H

#ifndef ARXEIO_H
#define ARXEIO_H

#define EL 1
#define GB 2

#include <QString>

class arxeio
{
public:
    arxeio();
    arxeio(const arxeio &copy);
    ~arxeio();
    arxeio operator = (arxeio data);

    void eisagogi_lexis(QString aglika,QString elinika);     //Αποθήκευση νέας λέξης στο λεξιλόγιο
    void diagrafi_lexis(long thesi);                         //Διαγραφή λέξης στο λεξιλόγιο
    void katharismos_mnimis();                              //Καθαρίζει την μνήμη που αποθηκεύεται το αρχείο για νέο αρχείο
    bool uparxi_lexi(QString aglika,QString elinika);       //Έρευνα άν έχει καταχωριθεί η λέξη στο παρελθόν
    long ThesiUparxousas_Lexis(QString aglikaN,QString elinikaN);

    bool anagnosi_arxeiou_disko(const QString &fileName);                 //Διαβάζει ένα αρχείο από τον δίσκο και το αποθηκεύει στην μνήμη arxeio_ram
    bool egrafi_arxeiou_disko(const QString &fileName);                //Γράφει ένα αρχείο από τη μνήμη arxeio_ram και το αποθηκεύει στον δίσκο

    QString arithmos_lexeon_QStr();                              //Επιστρέφει σε μορφή γραμματοσειράς τον αριθμό αποθηκευμένων λέξεων
    long arithmos_lexeon_arith();                                //Επιστρέφει σε αριθμό long τον αριθμό αποθηκευμένων λέξεων
    QString epistrofi_onomatos_arxeiou();
    void orismos_onomatos_arxeiou(QString neo_onoma_arxeiou);
    QString epistrofi_egrafis(long thesi_egrafis, int glosa);
    void lexi_eksetasimi(bool katastasi, long thesi);
    bool EinaiExetasimi(long thesi);
    void AntigrafiExetasimon(arxeio data);
    void AferesiMiExetasimon();
    bool lexiArxizeiApo(QString arxizeiApo, QString lexi);

private:
    QString* aglika;
    QString* elinika;
    QString onoma_arxeiou;
    bool* exetasimi; //Αν αληθεύει η λέξη είναι δεκτή για εξέταση
    long ar_lex;                 //Τα δεδομένα στην RAM
};

#endif // ARXEIO_H

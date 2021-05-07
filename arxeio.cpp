#include "arxeio.h"
#include <QFile>
#include <QMessageBox>
#include <QApplication>
arxeio::arxeio()
{
    aglika=elinika=NULL;
    exetasimi=NULL;
    ar_lex=0;
    onoma_arxeiou.clear();
}

arxeio::arxeio(const arxeio &copy)
{
    onoma_arxeiou=copy.onoma_arxeiou;
    ar_lex = copy.ar_lex;
    aglika  = new QString [ar_lex];
    elinika = new QString [ar_lex];
    exetasimi = new bool  [ar_lex];
    for(int x=0;x<ar_lex;x++)
    {
        aglika [x] = copy.aglika [x];
        elinika[x] = copy.elinika[x];
        exetasimi[x] = copy.exetasimi[x];
    }
}

arxeio::~arxeio()
{
    if(aglika!=NULL)
        delete[]aglika;
    if(elinika!=NULL)
        delete[]elinika;
    if(exetasimi!=NULL)
        delete[]exetasimi;
}

arxeio arxeio::operator = (arxeio data)
{
    onoma_arxeiou=data.onoma_arxeiou;
    ar_lex = data.ar_lex;
    if(aglika!=NULL)
        delete [] aglika;
    if(elinika!=NULL)
        delete [] elinika;
    if(exetasimi!=NULL)
        delete [] exetasimi;

    aglika  = new QString [ar_lex];
    elinika = new QString [ar_lex];
    exetasimi = new bool  [ar_lex];
    for(int x=0;x<ar_lex;x++)
    {
        aglika [x] = data.aglika [x];
        elinika[x] = data.elinika[x];
        exetasimi[x] = data.exetasimi[x];
    }

    return *this;
}

QString arxeio::arithmos_lexeon_QStr()
{
    return QString::number(ar_lex,10);
}

long arxeio::arithmos_lexeon_arith()
{
    return ar_lex;
}

void arxeio::orismos_onomatos_arxeiou(QString neo_onoma_arxeiou)
{
    onoma_arxeiou = neo_onoma_arxeiou;
}

QString arxeio::epistrofi_onomatos_arxeiou()
{
    return onoma_arxeiou;
}

void arxeio::katharismos_mnimis()
{
    ar_lex=0;
    onoma_arxeiou.clear();
    if(aglika!=NULL)
    {
        delete [] aglika;
        aglika=NULL;
    }
    if(elinika!=NULL)
    {
        delete [] elinika;
        elinika=NULL;
    }
    if(exetasimi!=NULL)
    {
        delete [] exetasimi;
        exetasimi=NULL;
    }
}

void arxeio::eisagogi_lexis(QString aglikaN,QString elinikaN)	//ΑΛΦΑΒΗΤΙΚΗ ΛΑΤΙΝΙΚΗ Αποθήκευση νέας λέξης στο λεξιλόγιο
{
    QString* aglika_temp  = new QString[ar_lex];
    QString* elinika_temp = new QString[ar_lex];
    bool* exetasimi_temp = new bool [ar_lex];

    for(int x=0;x<ar_lex;x++)
    {
        aglika_temp[x]=aglika[x];
        elinika_temp[x]=elinika[x];
        exetasimi_temp[x]=exetasimi[x];
    }
    if(aglika!=NULL)
    {
        delete [] aglika;
        aglika = NULL;
    }
    if(elinika!=NULL)
    {
        delete [] elinika;
        elinika = NULL;
    }
    if(exetasimi!=NULL)
    {
        delete [] exetasimi;
        exetasimi = NULL;
    }

    ar_lex++;
    aglika  = new QString[ar_lex];	//Νέα θέση
    elinika = new QString[ar_lex];	//Νέα θέση
    exetasimi = new bool [ar_lex];	//Νέα θέση

    if(ar_lex == 1)       //Αν είναι η πρώτη λέξη που έβαλα στο λεξιλόγιο
    {
        aglika [0]  = aglikaN;    //Μπαίνει στην αρχή
        elinika[0]  = elinikaN;
        exetasimi[0] = true;
    }
    else if(aglika_temp[0]>aglikaN) //Αν είναι μικρότερη από την πρώτη λέξη της λίστας
    {
        aglika [0]  = aglikaN;  //Μπαίνει στην αρχή
        elinika[0]  = elinikaN;
        exetasimi[0] = true;

        for(long x=1;x<ar_lex;x++)
        {
            aglika [x] = aglika_temp [x-1];
            elinika[x] = elinika_temp[x-1];
            exetasimi[x] = exetasimi_temp[x-1];
        }
    }
    else if(aglika_temp[ar_lex-2]<=aglikaN) //Αν είναι μεγαλύτερη από την τελευταία λέξη της λίστας
    {
        for(long x=0;x<ar_lex-1;x++)
        {
            aglika[x]  = aglika_temp[x];
            elinika[x] = elinika_temp[x];
            exetasimi[x] = exetasimi_temp[x];
        }
        aglika [ar_lex-1]  = aglikaN;  //Μπαίνει στο τέλος
        elinika[ar_lex-1]  = elinikaN;
        exetasimi[ar_lex-1] = true;
    }
    else
    {
        bool exei_kataxor = false;    //Αν exei_kataxor=false δεν έχει μπει η νέα λέξη Αν exei_kataxor=true έχει μπεί
        for(long x=0;x<ar_lex-1;x++) //Το arxeio_ram.ar_lex-1 είναι η θέση της προ τελευταίας λέξης του aglika_temp
        {
            if(exei_kataxor == false && (aglika_temp[x]<=aglikaN && aglikaN<aglika_temp[x+1]))    //Αν είναι κάπου στο ενδιάμεσο
            {
                aglika[x]  = aglika_temp[x];
                elinika[x] = elinika_temp[x];
                exetasimi[x] = exetasimi_temp[x];

                aglika [x+1]  = aglikaN;
                elinika[x+1]  = elinikaN;
                exetasimi[x+1] = true;

                exei_kataxor = true;
            }
            else    //Αλλιώς αποθηκεύω τη λίστα
            {
                if(exei_kataxor == false)    //Δεν έχει καταχωριθεί η νέα λέξη
                {
                    aglika [x] = aglika_temp [x];
                    elinika[x] = elinika_temp[x];
                    exetasimi[x] = exetasimi_temp[x];
                }
                else            //Έχει καταχωριθεί η νέα λέξη
                {
                    aglika [x+1] = aglika_temp [x];
                    elinika[x+1] = elinika_temp[x];
                    exetasimi[x+1] = exetasimi_temp[x];
                }
            }
        }
    }

    delete [] aglika_temp;      aglika_temp=NULL;
    delete [] elinika_temp;     elinika_temp=NULL;
    delete [] exetasimi_temp;   exetasimi_temp=NULL;
}

void arxeio::diagrafi_lexis(long thesi)	//Διαγραφή λέξης στο λεξιλόγιο
{
    QString* aglika_temp  = new QString[ar_lex-1];
    QString* elinika_temp = new QString[ar_lex-1];
    bool* exetasimi_temp = new bool [ar_lex-1];

    for(int x=0;x<thesi;x++)
    {
        aglika_temp[x]=aglika[x];
        elinika_temp[x]=elinika[x];
        exetasimi_temp[x] = exetasimi[x];
    }

    if((thesi+1)<ar_lex)    //Δηλαδή άν δεν έχω επιλέξει την τελευταία λέξη της λίστας, Άν το έχω κάνει η δουλειά έχει γίνει παραπάνω
    {
        for(int x=(thesi+1);x<ar_lex;x++)
        {
            aglika_temp[x-1]  = aglika[x];
            elinika_temp[x-1] = elinika[x];
            exetasimi_temp[x-1] = exetasimi[x];
        }
    }

    aglika  = new QString[ar_lex-1];  //Αφαίρεση Θέσης
    elinika = new QString[ar_lex-1];  //
    exetasimi = new bool [ar_lex-1];  //

    for(int x=0;x<(ar_lex-1);x++)
    {
        aglika [x] = aglika_temp[x];
        elinika[x] = elinika_temp[x];
        exetasimi[x] = exetasimi_temp[x];
    }

    ar_lex--;
    delete [] aglika_temp;
    delete [] elinika_temp;
    delete [] exetasimi_temp;
}

bool arxeio::uparxi_lexi(QString aglikaN,QString elinikaN)	//Έρευνα άν έχει καταχωριθεί η λέξη στο παρελθόν
{
    for(long x=0;x<ar_lex;x++)
    {
        if((aglika[x] == aglikaN)&&elinika[x] == elinikaN)
        {
            return true;
        }
    }
    return false;
}

long arxeio::ThesiUparxousas_Lexis(QString aglikaN,QString elinikaN)	//Έρευνα άν έχει καταχωριθεί η λέξη στο παρελθόν και επιστρέφει την θέση της
{
    for(long x=0;x<ar_lex;x++)
    {
        if((aglika[x] == aglikaN)&&elinika[x] == elinikaN)
        {
            return x;
        }
    }
    return -1;
}

bool arxeio::anagnosi_arxeiou_disko(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
    //        QMessageBox::warning(this, "Spreadsheet",
    //        "Cannot read file.".arg(file.fileName()).arg(file.errorString()));
            return false;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_3);

        quint32 magic;
        in >> magic;
        if (magic != quint32(847))
        {
    //      QMessageBox::about(this, "Spreadsheet","The file is not a Lexilogio file.");
            return false;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);
        long x=0;int a;
        in>>a;ar_lex=a;
        aglika = new QString  [ar_lex];
        elinika = new QString [ar_lex];
        exetasimi = new bool  [ar_lex];
        while (!in.atEnd())
        {
            in >> aglika[x] >> elinika[x] >> exetasimi[x];
            x++;
        }
        onoma_arxeiou = fileName;
        QApplication::restoreOverrideCursor();
        return true;
    }
    else
        return false;
}

bool arxeio::egrafi_arxeiou_disko(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
//        QMessageBox::warning(this, tr("Spreadsheet"),tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint32(847);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<int (ar_lex);
    for (int x = 0; x < ar_lex; ++x)
    {
        out << aglika[x] << elinika[x] << exetasimi[x];
    }
    QApplication::restoreOverrideCursor();
    return true;
}

QString arxeio::epistrofi_egrafis(long thesi_egrafis, int glosa)
{
    if(glosa==GB)
        return aglika[thesi_egrafis];

    if(glosa==EL)
        return elinika[thesi_egrafis];

    return "";
}

void arxeio::lexi_eksetasimi(bool katastasi, long thesi)
{
    if(thesi<ar_lex)
    {
        if(katastasi==true)
            exetasimi[thesi]=true;
        else
            exetasimi[thesi]=false;
    }
}

bool arxeio::EinaiExetasimi(long thesi)
{
    if(thesi>=0)
        return exetasimi[thesi];

    return false;
}

void arxeio::AntigrafiExetasimon(arxeio data)
{
    onoma_arxeiou=data.onoma_arxeiou;
    ar_lex=0;
    for(long x=0;x<data.ar_lex;x++) //Εύρεση πλήθος εξετάσιμων λέξεων
    {
       if(data.EinaiExetasimi(x))
           ar_lex++;
    }

    if(aglika!=NULL)
        delete [] aglika;
    if(elinika!=NULL)
        delete [] elinika;
    if(exetasimi!=NULL)
        delete [] exetasimi;

    aglika  = new QString [ar_lex];
    elinika = new QString [ar_lex];
    exetasimi = new bool  [ar_lex];
    long thesi=0;
    for(long x=0;x<data.ar_lex;x++)
    {
        if(data.exetasimi[x])
        {
            aglika [thesi] = data.aglika [x];
            elinika[thesi] = data.elinika[x];
            exetasimi[thesi] = data.exetasimi[x];
            thesi++;
        }
    }
}

void arxeio::AferesiMiExetasimon()
{
    long ar_dieg_lex = 0;

    for(long x=0;x<ar_lex;x++)
    {
        if(!exetasimi[x-ar_dieg_lex])
        {
            diagrafi_lexis(x-ar_dieg_lex);
            ar_dieg_lex++;
        }
    }
}

bool arxeio::lexiArxizeiApo(QString arxizeiApo, QString lexi)
{
    if(arxizeiApo == lexi.left(arxizeiApo.length()))
        return true;

    return false;
}

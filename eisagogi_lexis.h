#ifndef EISAGOGI_LEXIS_H
#define EISAGOGI_LEXIS_H

#include <QDialog>

namespace Ui {
    class eisagogi_lexis;
}

class eisagogi_lexis : public QDialog
{
    Q_OBJECT

public:
    explicit eisagogi_lexis(QWidget *parent = 0);
    ~eisagogi_lexis();
    QString gr,gb;
    bool ok;
    void arxiki__probalomeni_lexi(QString el, QString gb); //Θέτει στην φόρμα ένα αρχικό ζεύγος λέξεων

private:
    Ui::eisagogi_lexis *ui;

private slots:
    void on_pushButton_akuro_clicked();
    void on_pushButton_kataxor_clicked();
};

#endif // EISAGOGI_LEXIS_H

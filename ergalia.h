#ifndef ERGALIA_H
#define ERGALIA_H

#include "mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QMessageBox>

void loadFile(QString fileName)
{
//    if (okToContinue())
//    {
//        QString fileName = QFileDialog::getOpenFileName(this,
//                                   tr("Anoigma Lexilogiou"), ".",
//                                   tr("Arxeio Lexilogiou (*.lxg)"));
//        if (!fileName.isEmpty())
//        {
//            loadFile(fileName);
//        }
//    }
}

bool okToContinue()
{
    if (isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadsheet"), tr("Το αρχείο έχει αλλαχθεί\n" "Θέλετε να αποθηκευτούν οι αλλαγές;"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
        {
            return true;//save();
        }
        else if (r == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

#endif // ERGALIA_H

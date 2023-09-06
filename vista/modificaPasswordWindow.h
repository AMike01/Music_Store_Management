#ifndef MODIFICAPASSWORDWINDOW_H
#define MODIFICAPASSWORDWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMessageBox>
#include "../modello/utente.h"

class modificaPasswordWindow : public QDialog
{
private:
    Q_OBJECT

    QGridLayout * gridLayout;
    QVBoxLayout * modPassLayout;
    Utente* u;

    QLabel* vecchiaPasswordlabel;
    QLineEdit* vecchiaPassword;
    QLabel* nuovaPasswordlabel;
    QLineEdit* nuovaPassword;
    QLabel* nuovaPasswordRipetilabel;
    QLineEdit* nuovaPasswordRipeti;
    QPushButton* bCambia;

public:
    modificaPasswordWindow(Utente*);
    void clearF();

private slots:
    void tryCambiaPassword();

signals:
    void CambiaPassword(QString,QString);
};

#endif // MODIFICAPASSWORDWINDOW_H

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include <QFont>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QRegularExpressionValidator>
#include<QString>
#include <QPixmap>
#include<QMessageBox>
#include "registrazioneWindow.h"

class loginwindow : public QDialog
{
private:
    Q_OBJECT

    QLabel * lMain;
    QLabel * lImmagine;
    QLabel * lUsername;
    QLabel * lPassword;
    QLabel * lOppure;
    QLineEdit * tUsername;
    QLineEdit * tPassword;
    QPushButton * bLogin;
    QPushButton * bRegister;
    QGridLayout * gridLogin;
    QHBoxLayout * layoutLogin;

public:
    loginwindow();
    void clearF();
    void errorLogin();

private slots:
    void emitlogin();
    void launchRegistrazione();
    void UsernameDaReg(QString);

signals:
    void trylogin(const QString&, const QString&);
    void tryRegister(const QString&, const QString&);
    void regRiuscita();
    void regNonRiuscita();
};

#endif // LOGINWINDOW_H

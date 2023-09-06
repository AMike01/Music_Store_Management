#ifndef REGISTRAZIONEWINDOW_H
#define REGISTRAZIONEWINDOW_H

#include<QDialog>
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QRegularExpressionValidator>
#include<QString>
#include<QMessageBox>

class registrazionewindow : public QDialog {
private:
    Q_OBJECT

    QLabel* rUsername;
    QLabel* rPassword;
    QLabel* rPassword_repeat;
    QLineEdit* UsernameRegister;
    QLineEdit* PasswordRegister;
    QLineEdit* Password_repeatRegister;
    QPushButton* bRegister;
    QGridLayout * gridRegister;
    QVBoxLayout * layoutRegister;

    void clearPasswords();

public:
    registrazionewindow();
    void clearF();

public slots:
    void regRiuscita();
    void regNonRiuscita();

private slots:
    void slRegister();
signals:
    void tryRegistrazione(const QString&, const QString&);
    void UsernamePerLogin(QString);
};

#endif // REGISTRAZIONEWINDOW_H

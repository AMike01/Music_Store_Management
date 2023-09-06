#ifndef CONFERMAWINDOW_H
#define CONFERMAWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class confermaWindow : public QDialog {
private:
    Q_OBJECT

    QGridLayout * gridConferma;
    QVBoxLayout * layoutConferma;
    QLabel *label;
    QPushButton *conferma;
    QPushButton *annulla;

public:
    confermaWindow();

signals:
    void confermaElimina();
    void annullaElimina();

private slots:
    void slConferma();
    void slAnnulla();
};

#endif // CONFERMAWINDOW_H

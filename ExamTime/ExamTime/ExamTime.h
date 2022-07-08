#pragma once

#include <QtWidgets/QWidget>
#include <QTableWidget>
#include "ui_ExamTime.h"
#include "ServiceJoc.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QGridLayout>

/*
class ExamTime : public QWidget
{
    Q_OBJECT

public:
    ExamTime(QWidget *parent = Q_NULLPTR);

private:
    Ui::ExamTimeClass ui;
};
*/

class ExamTime: public QWidget
{
private:
    ServiceJoc& serviceJoc;

    QTableWidget* tabelJocuri;
    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;
    QWidget* rightSide;
    QWidget* properForm;
    QFormLayout* inputForm;

    QLineEdit* editDim;
    QLineEdit* editTabla;
    QLineEdit* editNextPlayer;
    QLineEdit* editStare;

    QPushButton* tabela[5][5];

    QWidget* tabla;
    QGridLayout* tablaLayout;

    QPushButton* addJoc;
    QPushButton* editJoc;

    //Manages the initialization of the GUI.
    void initGUI();

    void connectSignalsSlots();
    void reloadTable(const vector<Joc>);
    void AddJoc();
    void EditJoc();
public:
    
    ExamTime(ServiceJoc& srv): serviceJoc{srv}
    {
        initGUI();
        connectSignalsSlots();
        reloadTable(serviceJoc.srvGetAllSortedByState());
    }
    ExamTime(const ServiceJoc&) = delete;


};
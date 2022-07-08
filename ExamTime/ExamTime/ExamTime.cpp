#include "ExamTime.h"
#include <QMessageBox>
/*
ExamTime::ExamTime(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}
*/

void ExamTime::initGUI()
{
    mainLayout = new QHBoxLayout();
    this->setLayout(mainLayout);

    tabelJocuri = new QTableWidget();
    rightSide = new QWidget();
    rightLayout = new QVBoxLayout();
    rightSide->setLayout(rightLayout);

    properForm = new QWidget();
    inputForm = new QFormLayout();
    properForm->setLayout(inputForm);

    mainLayout->addWidget(tabelJocuri);
    mainLayout->addWidget(rightSide);

    editDim = new QLineEdit();
    editTabla = new QLineEdit();
    editNextPlayer = new QLineEdit();
    editStare = new QLineEdit();

    addJoc = new QPushButton("Adauga Joc");
    editJoc = new QPushButton("Edit Joc");



    rightLayout->addWidget(properForm);
    inputForm->addRow("Dimensiune: ", editDim);
    inputForm->addRow("Tabla: ", editTabla);
    inputForm->addRow("Urmatorul Jucator: ", editNextPlayer);
    inputForm->addRow("Stare (doar pentru edit): ", editStare);
    rightLayout->addWidget(addJoc);
    rightLayout->addWidget(editJoc);

    //tabla = new QWidget();

    //tabla->setLayout(tablaLayout);


    /*
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            QLayoutItem item = new QLayoutItem();
            tablaLayout->addItem(, i, j);
        }
    }*/
    

}

//Makes the connection between the UI and the logic behind
void ExamTime::connectSignalsSlots()
{
    QObject::connect(addJoc, &QPushButton::clicked, this, &ExamTime::AddJoc);
    QObject::connect(editJoc, &QPushButton::clicked, this, &ExamTime::EditJoc);
    QObject::connect(tabelJocuri, &QTableWidget::itemSelectionChanged, [&]() {
        if (tabelJocuri->selectedItems().size() < 1)
        {
            return;
        }

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                tabela[i][j]->setVisible(false);
            }
        }

        auto item = tabelJocuri->selectedItems().at(0);
        int id = stoi(item->data(Qt::UserRole).toString().toStdString());

        vector<Joc> allOfThem = serviceJoc.srvGetAll();
        int dim = 0;
        string tabel;
        for (Joc j : allOfThem)
        {
            if (j.getId() == id)
            {
                dim = id;
                tabel = j.getTabla();
            }
        }
        int index = 0;

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                tabela[i][j]->setVisible(false);
                tabela[i][j]->setText(QString(tabel[index]));

                index++;
            }
        }
    });

}

//Updates the data in the table when changes occur
void ExamTime::reloadTable(const vector<Joc> vect)
{
    tabelJocuri->setRowCount(vect.size());
    tabelJocuri->setColumnCount(5);

    for (int i = 0; i < vect.size(); i++)
    {
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(vect[i].getId()));
        item1->setData(Qt::UserRole, vect[i].getId());

        QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(vect[i].getDim()));
        item2->setData(Qt::UserRole, vect[i].getId());
        
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(vect[i].getTabla()));
        item3->setData(Qt::UserRole, vect[i].getId());
        
        QTableWidgetItem* item4 = new QTableWidgetItem(QString::fromStdString(vect[i].getNextPlayer()));
        item4->setData(Qt::UserRole, vect[i].getId());
        
        QTableWidgetItem* item5 = new QTableWidgetItem(QString::fromStdString(vect[i].getStare()));
        item5->setData(Qt::UserRole, vect[i].getId());
        
        tabelJocuri->setItem(i, 0, item1);
        tabelJocuri->setItem(i, 1, item2);
        tabelJocuri->setItem(i, 2, item3);
        tabelJocuri->setItem(i, 3, item4);
        tabelJocuri->setItem(i, 4, item5);
    }
}

//Manages the process of adding games to the program's internal storage.
void ExamTime::AddJoc()
{
    int dim = stoi(editDim->text().toStdString());
    string tabla = editTabla->text().toStdString();
    string nextPlayer = editNextPlayer->text().toStdString();
    qDebug() << "fdfd";
    try {
        serviceJoc.srvAddJoc(dim, tabla, nextPlayer);
        reloadTable(serviceJoc.srvGetAllSortedByState());
    }
    catch (CustomException e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.getMessage()));
    }
}


//Manages the process of editing games from the program's internal storage.
void ExamTime::EditJoc()
{
    if (tabelJocuri->selectedItems().size() < 1)
    {
        QMessageBox::warning(this, "Avertizare", "Nu este niciun joc selectat in tabel!");
        return;
    }

    qDebug() << "dfdf";
    string stringID = (tabelJocuri->selectedItems().at(0)->text()).toStdString();
    int id = stoi(stringID);

    int dim = stoi(editDim->text().toStdString());
    string tabla = editTabla->text().toStdString();
    string nextPlayer = editNextPlayer->text().toStdString();
    string stare = editStare->text().toStdString();

    try
    {
        serviceJoc.srvEditJoc(id, dim, tabla, nextPlayer, stare);
        reloadTable(serviceJoc.srvGetAllSortedByState());
    }
    catch (CustomException e)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.getMessage()));
    }
}
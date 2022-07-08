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

    tabla = new QWidget();
    tablaLayout = new QGridLayout();

    tabla->setLayout(tablaLayout);


    rightLayout->addWidget(tabla);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tabela[i][j] = new QPushButton();
            tablaLayout->addWidget(tabela[i][j], i, j);
        }
    }
    

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
                dim = j.getDim();
                tabel = j.getTabla();
            }
        }
        int index = 0;

        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                tabela[i][j]->setVisible(true);
                if(QString(tabel[index]) != "-")
                    tabela[i][j]->setText(QString(tabel[index]));
                else
                    tabela[i][j]->setText(" ");
                index++;
            }
        }
    });
    //This is what's broken now
    /*
    for (int l = 0; l < 5; l++) {
        for (int k = 0; k < 5; k++) {
            QPushButton* temp = tabela[l][k];
            QObject::connect(temp, &QPushButton::clicked, [&]() {
                if (tabelJocuri->selectedItems().size() < 1)
                {
                    return;
                }
                
                vector<Joc> allOfThem = serviceJoc.srvGetAll();

                auto item = tabelJocuri->selectedItems().at(0);
                int id = stoi(item->data(Qt::UserRole).toString().toStdString());

                string nextPlayer;
                int dim;

                for (Joc j : allOfThem)
                {
                    if (j.getId() == id)
                    {
                        nextPlayer = j.getNextPlayer();
                        dim = j.getDim();
                    }
                }



                if (temp->text() == " ")
                {
                    temp->setText(QString::fromStdString(nextPlayer));

                    if (nextPlayer == "X")
                        nextPlayer = "O";
                    else
                        nextPlayer = "X";

                    string newTabela = "";


                    string stare = "Terminat";

                    for (int i = 0; i < dim; i++)
                    {
                        for (int j = 0; j < dim; j++)
                        {
                            if ((tabela[i][j]->text()).toStdString() == " ")
                                stare = "In derulare";
                            newTabela += (tabela[i][j]->text()).toStdString();
                        }
                    }


                    serviceJoc.srvEditJoc(id, dim, newTabela, nextPlayer, stare);
                }
            });
        }
    }*/
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
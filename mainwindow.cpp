#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDebug>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(1000, 700);

    /*ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidgetLeft->setCurrentIndex(0);
    ui->stackedWidgetRight->setCurrentIndex(0);*/

    ui->listWidgetReserv->setAcceptDrops(false);
    ui->listWidgetReserv->setDragEnabled(false);
    //ui->listWidgetDrop->setDragEnabled(false);

    /*ui->listWidgetDrag->insertItem(1, new QListWidgetItem(QIcon(":user-max.png"), "Jean-Louis Dureuille"));
    ui->listWidgetDrag->insertItem(2, new QListWidgetItem(QIcon(":user-max.png"), "Marc Lendo"));
    ui->listWidgetDrag->insertItem(3, new QListWidgetItem(QIcon(":user-max.png"), "Sophie Marteno"));
    ui->listWidgetDrag->insertItem(4, new QListWidgetItem(QIcon(":user-max.png"), "Damien Prébau"));
    ui->listWidgetDrag->insertItem(5, new QListWidgetItem(QIcon(":user-max.png"), "Alick Mouriesse"));*/

    updateListClients();

    ui->listWidgetReserv->insertItem(1, this->createItem((char*) "Chambres"));
    ui->listWidgetReserv->insertItem(2, this->createItem((char*) "Repas"));
    ui->listWidgetReserv->insertItem(3, this->createItem((char*) "SPA"));
    ui->listWidgetReserv->insertItem(4, this->createItem((char*) "Room Services"));
    ui->listWidgetReserv->insertItem(5, this->createItem((char*) "Taxis"));
    ui->listWidgetReserv->insertItem(6, this->createItem((char*) "Avions"));
    ui->listWidgetReserv->insertItem(7, this->createItem((char*) "Golf"));
    ui->listWidgetReserv->insertItem(8, this->createItem((char*) "Tennis"));
    ui->listWidgetReserv->insertItem(9, this->createItem((char*) "Massages"));
    ui->listWidgetReserv->insertItem(10, this->createItem((char*) "Bateaux"));
    ui->listWidgetReserv->insertItem(11, this->createItem((char*) "Spectacles"));
    ui->listWidgetReserv->insertItem(12, this->createItem((char*) "EXIT"));

    ui->comboBoxAddGenre->addItem("Monsieur");
    ui->comboBoxAddGenre->addItem("Madame");
    ui->comboBoxAddGenre->addItem("Mademoiselle");
    ui->comboBoxInfoGenre->addItem("Monsieur");
    ui->comboBoxInfoGenre->addItem("Madame");
    ui->comboBoxInfoGenre->addItem("Mademoiselle");

    ui->comboBoxAddPay->addItem("CB");
    ui->comboBoxAddPay->addItem("Chèque");
    ui->comboBoxAddPay->addItem("Virement");
    ui->comboBoxAddPay->addItem("Liquide");
    ui->comboBoxInfoPay->addItem("CB");
    ui->comboBoxInfoPay->addItem("Chèque");
    ui->comboBoxInfoPay->addItem("Virement");
    ui->comboBoxInfoPay->addItem("Liquide");

}

MainWindow::~MainWindow()
{
    delete ui;
}

QListWidgetItem* MainWindow::createItem(char* name)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(name);
    if (name[0] != 'E') {
        item->setIcon(QIcon(":" + item->text() + ".png"));
    } else {
        item->setIcon(QIcon(":exit.png"));
    }
    return item;
}

void MainWindow::changeMenuData(QString name)
{
    ui->labelTitleFocus->setText(name);
}

void MainWindow::updateListClients()
{
    ui->listWidgetDrag->clear();
    for (size_t i = 0; i < clients.size(); i++) {
        QListWidgetItem *itemClient = new QListWidgetItem;

        itemClient->setText(QString::fromStdString(clients[i].getFirstName() + " " + clients[i].getLastName()));
        if (clients[i].getGenre() == 0) {
            itemClient->setIcon(QIcon(":user-max.png"));
        } else {
            itemClient->setIcon(QIcon(":user-girl-max.png"));
        }
        itemClient->setData(Qt::UserRole, clients[i].getId());

        ui->listWidgetDrag->insertItem(1, itemClient);
    }
    ui->labelClientCount->setText(QString::fromStdString("Clients total : " + std::to_string(clients.size())));
    ui->listWidgetDrag->repaint();
}

void MainWindow::on_pushButtonLogin_clicked()
{
    ui->stackedWidgetLeft->setCurrentIndex(0);
    ui->stackedWidgetRight->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_listWidgetReserv_itemDoubleClicked(QListWidgetItem *item)
{
    this->changeMenuData("Réservation " + item->text());

    if (item->data(0).toString().contains("EXIT")) {
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        ui->stackedWidgetRight->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButtonBackHome_clicked()
{
    ui->stackedWidgetRight->setCurrentIndex(0);
}

void MainWindow::on_listWidgetDrag_itemDoubleClicked(QListWidgetItem *item)
{
    Client clientInfo;

    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].getId() == item->data(Qt::UserRole).toInt()) {
            clientInfo = clients[i];
        }
    }

    if (clientInfo.getGenre() == 0) {
        ui->labelLogoClientInfo->setPixmap(QPixmap(":user-max.png"));
    } else {
        ui->labelLogoClientInfo->setPixmap(QPixmap(":user-girl-max.png"));
    }

    ui->lineEditInfoFirstName->setText(QString::fromStdString(clientInfo.getFirstName()));
    ui->lineEditInfoLastName->setText(QString::fromStdString(clientInfo.getLastName()));
    ui->labelInfoID->setText(QString::fromStdString("#" + std::to_string(clientInfo.getId())));
    ui->comboBoxInfoGenre->setCurrentIndex(clientInfo.getGenre());
    ui->lineEditInfoPhone->setText(QString::fromStdString(clientInfo.getPhoneNumber()));
    ui->lineEditInfoMail->setText(QString::fromStdString(clientInfo.getEmail()));
    ui->lineEditInfoAddress->setText(QString::fromStdString(clientInfo.getAddress()));
    ui->lineEditInfoCity->setText(QString::fromStdString(clientInfo.getCity()));
    ui->lineEditInfoCP->setText(QString::fromStdString(clientInfo.getCP()));
    ui->comboBoxInfoPay->setCurrentIndex(clientInfo.getGenre());
    ui->spinBoxInfoAssoc->setValue(clientInfo.getAssociateMembers());
    ui->textEditInfoInfo->setText(QString::fromStdString(clientInfo.getInfo()));

    ui->stackedWidgetLeft->setCurrentIndex(1);
}

void MainWindow::on_pushButtonAddClient_clicked()
{
    ui->stackedWidgetLeft->setCurrentIndex(2);
}

void MainWindow::on_pushButtonDelClient_clicked()
{
    if (ui->listWidgetDrag->selectedItems().size() != 0) {
        if (QMessageBox::question(
                    this,
                    tr("Supprimer un client"),
                    tr("Étes vous sûr de vouloir supprimer le client ") + ui->listWidgetDrag->currentItem()->text(),
                    QMessageBox::Yes | QMessageBox::Cancel
                ) == QMessageBox::Yes) {

            for (size_t i = 0; i < clients.size(); i++) {
                if (clients[i].getId() == ui->listWidgetDrag->currentItem()->data(Qt::UserRole).toInt()) {
                    clients.erase(clients.begin() + i);
                }
            }

            updateListClients();
        }
    } else {
        QMessageBox::warning(
            this,
            tr("Supprimer un client"),
            tr("Vous devez sélectionner un client avant de le supprimer !")
        );
    }
}

void MainWindow::clearAddClient()
{
    ui->comboBoxAddGenre->setCurrentIndex(0);
    ui->lineEditAddLastName->setText("");
    ui->lineEditAddFirstName->setText("");
    ui->lineEditAddPhone->setText("");
    ui->lineEditAddEmail->setText("");
    ui->lineEditAddAddress->setText("");
    ui->lineEditAddCity->setText("");
    ui->lineEditAddCP->setText("");
    ui->comboBoxAddPay->setCurrentIndex(0);
    ui->spinBoxAddAssoc->setValue(0);
}

void MainWindow::on_pushButtonInfoBack_clicked()
{
    ui->stackedWidgetLeft->setCurrentIndex(0);
}

void MainWindow::on_pushButtonAddCancel_clicked()
{
    clearAddClient();
    ui->stackedWidgetLeft->setCurrentIndex(0);
}

void MainWindow::on_pushButtonAddValide_clicked()
{
    // Create client

    if (ui->lineEditAddLastName->text().isEmpty() == true || ui->lineEditAddFirstName->text().isEmpty() == true) {
        QMessageBox::warning(
            this,
            tr("Ajouter un client"),
            tr("Vous devez donner un Nom et un Prénom pour créer un client !")
        );
    } else {
        Client newClient{
            ui->comboBoxAddGenre->currentIndex(),
            ui->comboBoxAddPay->currentIndex(),
            ui->spinBoxAddAssoc->value(),
            ui->lineEditAddFirstName->text().toUtf8().constData(),
            ui->lineEditAddLastName->text().toUtf8().constData(),
            ui->lineEditAddPhone->text().toUtf8().constData(),
            ui->lineEditAddEmail->text().toUtf8().constData(),
            ui->lineEditAddAddress->text().toUtf8().constData(),
            ui->lineEditAddCity->text().toUtf8().constData(),
            ui->lineEditAddCP->text().toUtf8().constData(),
            ""
        };

        clients.push_back(newClient);

        updateListClients();

        ui->stackedWidgetLeft->setCurrentIndex(0);

        QMessageBox::information(
            this,
            tr("Ajouter un client"),
            tr("Le client a bien été ajouté !")
        );

        clearAddClient();
    }
}

void MainWindow::on_comboBoxAddGenre_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->labelLogoClientAdd->setPixmap(QPixmap(":user-max.png"));
    } else {
        ui->labelLogoClientAdd->setPixmap(QPixmap(":user-girl-max.png"));
    }
}

void MainWindow::on_comboBoxInfoGenre_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->labelLogoClientInfo->setPixmap(QPixmap(":user-max.png"));
    } else {
        ui->labelLogoClientInfo->setPixmap(QPixmap(":user-girl-max.png"));
    }
}

void MainWindow::on_pushButtonInfoUpdate_clicked()
{
    int indexClient = 0;

    for (size_t i = 0; i < clients.size(); i++) {
        std::string formatId = ui->labelInfoID->text().toStdString();
        if (clients[i].getId() == std::stoi(ui->labelInfoID->text().replace(0, 1, "").toStdString())) {
            indexClient = i;
        }
    }

    clients[indexClient].setFirstName(ui->lineEditInfoFirstName->text().toStdString());
    clients[indexClient].setLastName(ui->lineEditInfoLastName->text().toStdString());
    clients[indexClient].setGenre(ui->comboBoxInfoGenre->currentIndex());
    clients[indexClient].setPhoneNumber(ui->lineEditInfoPhone->text().toStdString());
    clients[indexClient].setEmail(ui->lineEditInfoMail->text().toStdString());
    clients[indexClient].setAddress(ui->lineEditInfoAddress->text().toStdString());
    clients[indexClient].setCity(ui->lineEditInfoCity->text().toStdString());
    clients[indexClient].setCP(ui->lineEditInfoCP->text().toStdString());
    clients[indexClient].setPayment(ui->comboBoxInfoPay->currentIndex());
    clients[indexClient].setAssociateMembers(ui->spinBoxInfoAssoc->value());
    clients[indexClient].setInfo(ui->textEditInfoInfo->toPlainText().toStdString());

    updateListClients();

    QMessageBox::information(
        this,
        tr("Mise à jour client"),
        tr("Le client a bien été mis à jour !")
    );
}


void MainWindow::on_lineEditSearch_textChanged(const QString &arg1)
{
    for (int i = 0; i < ui->listWidgetDrag->count(); i++) {
        if (ui->listWidgetDrag->item(i)->text().contains(arg1)) {
            ui->listWidgetDrag->item(i)->setHidden(false);
        } else {
            ui->listWidgetDrag->item(i)->setHidden(true);
        }
    }
}

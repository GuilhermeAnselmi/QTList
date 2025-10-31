#include "list.h"
#include "./ui_list.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include "nlohmann/json.hpp"
#include <fstream>
#include "../config/config.h"
#include "manageList/manageList.h"

List::List(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::List)
{
    ui->setupUi(this);

    _model = new QStringListModel(this);
    ui->listView->setModel(_model);

    connect(ui->btnAddList, &QPushButton::clicked, this, &List::OnAddList);
    connect(ui->btnRemoveList, &QPushButton::clicked, this, &List::OnRemoveList);
    connect(ui->btnSaveList, &QPushButton::clicked, this, &List::OnSaveList);
    connect(ui->actionConfiguration, &QAction::triggered, this, &List::OnOpenConfig);

    _manage = new ManageList(this);

    OnLoad();
}

List::~List()
{
    delete ui;
}

QString List::GetAppDataPath() {
    QCoreApplication::setOrganizationName("Code137");
    QCoreApplication::setApplicationName("CodeList");

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataPath);

    return appDataPath;
}

void List::OnLoad() {
    QStringList list = _manage->GetList();

    _model->setStringList(list);
}

void List::OnAddList() {
    if (ui->txtAddItem->text().isEmpty()) {
        QMessageBox::information(this, "Text Empty", "Value is not empty");

        return;
    }

    QStringList list = _model->stringList();

    list.append(ui->txtAddItem->text());

    _model->setStringList(list);

    ui->txtAddItem->setText("");
}

void List::OnRemoveList() {
    QModelIndex index = ui->listView->currentIndex();

    if (!index.isValid()) {
        QMessageBox::critical(this, "Error", QObject::tr("Select item"));

        return;
    }

    QStringList list = _model->stringList();

    list.remove(index.row());

    _model->setStringList(list);
}

void List::OnSaveList() {
    QStringList listView = _model->stringList();

    _manage->SaveList(listView);
}

void List::OnOpenConfig() {
    Config *config = new Config();
    config->show();
}

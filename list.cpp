#include "list.h"
#include "./ui_list.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include "nlohmann/json.hpp"
#include <fstream>

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
    using json = nlohmann::json;

    try {
        QString appDataPath = GetAppDataPath();
        QString savePath = appDataPath + QDir::separator() + "savefile.json";

        std::ifstream file(savePath.toStdString());
        std::string jsonString = "{ \"list\": [\"test 1\"] }";

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            jsonString = buffer.str();

            file.close();
        }else {
            return;
        }

        json save = json::parse(jsonString);

        std::vector<std::string> list = save["list"].get<std::vector<std::string>>();

        QStringList listView;

        for (const std::string item : list) {
            listView.append(QString::fromStdString(item));
        }

        _model->setStringList(listView);
    } catch (json::parse_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    } catch (std::exception ex) {
        QMessageBox::critical(this, "Error", ex.what());
    }
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
    using json = nlohmann::json;

    try {
        QStringList listView = _model->stringList();
        std::vector<std::string> list;

        for (const QString item : listView) {
            list.push_back(item.toStdString());
        }

        json save;

        save["list"] = list;

        std::string jsonString = save.dump(4);

        QString appDataPath = GetAppDataPath();
        QString savePath = appDataPath + QDir::separator() + "savefile.json";

        std::ofstream file(savePath.toStdString());

        if (file.is_open()) {
            file << jsonString;

            file.close();
        }else {
            QMessageBox::critical(this, "Error", QObject::tr("Error Save"));
        }

        QMessageBox::information(this, "Success", "Saved list");
    } catch (json::parse_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    } catch (std::exception ex) {
        QMessageBox::critical(this, "Error", ex.what());
    }
}

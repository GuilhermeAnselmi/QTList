#include "manageList.h"
#include <QDir>
#include <QMessageBox>
#include <qstring.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include "common/common.h"

ManageList::ManageList(QWidget *parent) {
    _parent = parent;
}

QStringList ManageList::GetList() const {
    using json = nlohmann::json;

    try {
        QString appDataPath = Common::GetAppDataPath();
        QString savePath = appDataPath + QDir::separator() + "savefile.json";

        std::ifstream file(savePath.toStdString());
        std::string jsonString;

        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            jsonString = buffer.str();

            file.close();
        }else {
            return QStringList();
        }

        json save = json::parse(jsonString);

        std::vector<std::string> list = save["list"].get<std::vector<std::string>>();

        QStringList listView;

        for (const std::string item : list) {
            listView.append(QString::fromStdString(item));
        }

        return listView;
    } catch (json::parse_error& e) {
        QMessageBox::critical(_parent, "Error", e.what());
    } catch (std::exception ex) {
        QMessageBox::critical(_parent, "Error", ex.what());
    }

    return QStringList();
}

void ManageList::SaveList(QStringList listView) const {
    using json = nlohmann::json;

    try {
        std::vector<std::string> list;

        for (const QString item : listView) {
            list.push_back(item.toStdString());
        }

        json save;

        save["list"] = list;

        std::string jsonString = save.dump(4);

        QString appDataPath = Common::GetAppDataPath();
        QString savePath = appDataPath + QDir::separator() + "savefile.json";

        std::ofstream file(savePath.toStdString());

        if (file.is_open()) {
            file << jsonString;

            file.close();
        }else {
            QMessageBox::critical(_parent, "Error", QObject::tr("Error Save"));
        }

        QMessageBox::information(_parent, "Success", "Saved list");
    } catch (json::parse_error& e) {
        QMessageBox::critical(_parent, "Error", e.what());
    } catch (std::exception ex) {
        QMessageBox::critical(_parent, "Error", ex.what());
    }
}

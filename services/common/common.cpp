#include "common.h"

#include <qcoreapplication.h>
#include <QDir>
#include <QStandardPaths>

QString Common::GetAppDataPath() {
    QCoreApplication::setOrganizationName("Code137");
    QCoreApplication::setApplicationName("CodeList");

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(appDataPath);

    return appDataPath;
}

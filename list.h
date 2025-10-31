#ifndef LIST_H
#define LIST_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class List;
}
QT_END_NAMESPACE

class List : public QMainWindow
{
    Q_OBJECT

public:
    List(QWidget *parent = nullptr);
    ~List();

private:
    QStringListModel *_model;

    Ui::List *ui;
    QString GetAppDataPath();
    void OnLoad();
    void OnAddList();
    void OnRemoveList();
    void OnSaveList();
    void OnOpenConfig();
};
#endif // LIST_H

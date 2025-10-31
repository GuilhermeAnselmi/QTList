#ifndef QTLIST_MANAGELIST_H
#define QTLIST_MANAGELIST_H
#include <QWidget>


class ManageList {
public:
    ManageList(QWidget *parent);

    QStringList GetList() const;
    void SaveList(QStringList list) const;

private:
    QWidget *_parent;
};


#endif //QTLIST_MANAGELIST_H
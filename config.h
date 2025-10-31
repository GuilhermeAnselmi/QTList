#ifndef QTLIST_CONFIG_H
#define QTLIST_CONFIG_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class Config;
}

QT_END_NAMESPACE

class Config : public QWidget {
    Q_OBJECT

public:
    explicit Config(QWidget *parent = nullptr);

    ~Config() override;

private:
    Ui::Config *ui;
};


#endif //QTLIST_CONFIG_H
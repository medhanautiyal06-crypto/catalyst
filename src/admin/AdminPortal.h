
#ifndef ADMIN_PORTAL_H
#define ADMIN_PORTAL_H

#include <QWidget>

class AdminPortal : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPortal(QWidget *parent = nullptr);

signals:
    void backRequested();
};

#endif

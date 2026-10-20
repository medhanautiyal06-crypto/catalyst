#ifndef FACULTY_PORTAL_H
#define FACULTY_PORTAL_H

#include <QWidget>

class FacultyPortal : public QWidget
{
    Q_OBJECT

public:
    explicit FacultyPortal(QWidget *parent = nullptr);

signals:
    void backRequested();
};

#endif

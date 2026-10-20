#include "AdminPortal.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QPalette>
#include <QFont>
#include <QStringList>

AdminPortal::AdminPortal(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Catalyst - Admin Portal");
    resize(1100, 700);

    QPalette pagePalette = palette();
    pagePalette.setColor(QPalette::Window, QColor("#F5F7FB"));
    pagePalette.setColor(QPalette::WindowText, QColor("#172B4D"));
    setPalette(pagePalette);
    setAutoFillBackground(true);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(28, 24, 28, 24);
    mainLayout->setSpacing(20);

    auto *header = new QFrame(this);
    header->setMinimumHeight(80);
    QPalette headerPalette = header->palette();
    headerPalette.setColor(QPalette::Window, QColor("#142B52"));
    header->setPalette(headerPalette);
    header->setAutoFillBackground(true);

    auto *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(20, 12, 20, 12);

    auto *brand = new QLabel("CATALYST | ADMIN PORTAL", header);
    QFont brandFont = brand->font();
    brandFont.setPointSize(16);
    brandFont.setBold(true);
    brand->setFont(brandFont);
    QPalette brandPalette = brand->palette();
    brandPalette.setColor(QPalette::WindowText, Qt::white);
    brand->setPalette(brandPalette);

    auto *backButton = new QPushButton("Back to Welcome", header);
    connect(backButton, &QPushButton::clicked, this, &AdminPortal::backRequested);
    headerLayout->addWidget(brand);
    headerLayout->addStretch();
    headerLayout->addWidget(backButton);
    mainLayout->addWidget(header);

    auto *heading = new QLabel("Admin Dashboard", this);
    QFont headingFont = heading->font();
    headingFont.setPointSize(23);
    headingFont.setBold(true);
    heading->setFont(headingFont);
    mainLayout->addWidget(heading);

    auto *description = new QLabel("Manage college timetables, faculty, rooms and scheduling conflicts.", this);
    mainLayout->addWidget(description);

    auto *statsLayout = new QHBoxLayout;
    statsLayout->setSpacing(16);
    const QStringList statTitles = {"Faculty Members", "Scheduled Classes", "Available Rooms", "Clashes"};
    const QStringList statValues = {"24", "42", "18", "0"};

    for (int i = 0; i < statTitles.size(); ++i) {
        auto *card = new QFrame(this);
        card->setFrameShape(QFrame::StyledPanel);
        card->setMinimumHeight(125);
        QPalette cardPalette = card->palette();
        cardPalette.setColor(QPalette::Window, Qt::white);
        card->setPalette(cardPalette);
        card->setAutoFillBackground(true);
        auto *cardLayout = new QVBoxLayout(card);
        auto *value = new QLabel(statValues[i], card);
        QFont valueFont = value->font();
        valueFont.setPointSize(25);
        valueFont.setBold(true);
        value->setFont(valueFont);
        auto *title = new QLabel(statTitles[i], card);
        cardLayout->addWidget(value);
        cardLayout->addWidget(title);
        cardLayout->addStretch();
        statsLayout->addWidget(card);
    }
    mainLayout->addLayout(statsLayout);

    auto *actionsTitle = new QLabel("Quick Actions", this);
    QFont actionsFont = actionsTitle->font();
    actionsFont.setPointSize(17);
    actionsFont.setBold(true);
    actionsTitle->setFont(actionsFont);
    mainLayout->addWidget(actionsTitle);

    auto *actionsLayout = new QHBoxLayout;
    actionsLayout->addWidget(new QPushButton("Generate Timetable", this));
    actionsLayout->addWidget(new QPushButton("Check for Clashes", this));
    actionsLayout->addWidget(new QPushButton("Manage Faculty", this));
    actionsLayout->addWidget(new QPushButton("Manage Rooms", this));
    mainLayout->addLayout(actionsLayout);

    auto *note = new QLabel("Prototype dashboard: timetable generation and data management will be connected in later stages.", this);
    note->setWordWrap(true);
    mainLayout->addWidget(note);
    mainLayout->addStretch();
}

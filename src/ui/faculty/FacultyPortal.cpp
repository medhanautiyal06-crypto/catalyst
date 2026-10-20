
#include "FacultyPortal.h"

#include <QAbstractItemView>
#include <QColor>
#include <QFont>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

FacultyPortal::FacultyPortal(QWidget *parent) : QWidget(parent) {
  setWindowTitle("Catalyst - Faculty Portal");
  resize(1150, 760);

  // Main window colors
  QPalette pagePalette = palette();
  pagePalette.setColor(QPalette::Window, QColor("#F4F6FA"));
  pagePalette.setColor(QPalette::WindowText, QColor("#1E293B"));
  setPalette(pagePalette);
  setAutoFillBackground(true);

  auto *root = new QVBoxLayout(this);
  root->setContentsMargins(22, 20, 22, 20);
  root->setSpacing(18);

  // Header
  auto *header = new QFrame(this);
  header->setMinimumHeight(76);

  QPalette headerPalette = header->palette();
  headerPalette.setColor(QPalette::Window, QColor("#142B52"));
  header->setPalette(headerPalette);
  header->setAutoFillBackground(true);

  auto *headerLayout = new QHBoxLayout(header);
  headerLayout->setContentsMargins(22, 12, 22, 12);

  auto *brand = new QLabel("CATALYST | FACULTY PORTAL", header);
  QFont brandFont = brand->font();
  brandFont.setPointSize(16);
  brandFont.setBold(true);
  brand->setFont(brandFont);

  QPalette brandPalette = brand->palette();
  brandPalette.setColor(QPalette::WindowText, Qt::white);
  brand->setPalette(brandPalette);

  auto *backButton = new QPushButton("Back", header);
  connect(backButton, &QPushButton::clicked, this,
          &FacultyPortal::backRequested);

  headerLayout->addWidget(brand);
  headerLayout->addStretch();
  headerLayout->addWidget(backButton);
  root->addWidget(header);

  // Welcome heading
  auto *welcomeTitle = new QLabel("Faculty Dashboard", this);
  QFont welcomeFont = welcomeTitle->font();
  welcomeFont.setPointSize(25);
  welcomeFont.setBold(true);
  welcomeTitle->setFont(welcomeFont);
  root->addWidget(welcomeTitle);

  auto *welcomeText =
      new QLabel("View your teaching schedule and timetable updates.", this);
  root->addWidget(welcomeText);

  // Summary cards
  auto *cardsLayout = new QHBoxLayout;
  cardsLayout->setSpacing(16);

  const QStringList cardTitles = {"Classes Today", "Next Class",
                                  "Schedule Status"};

  const QStringList cardValues = {"5", "10:00 AM", "Up to date"};

  for (int i = 0; i < cardTitles.size(); ++i) {
    auto *card = new QFrame(this);
    card->setMinimumHeight(110);
    card->setFrameShape(QFrame::StyledPanel);

    QPalette cardPalette = card->palette();
    cardPalette.setColor(QPalette::Window, Qt::white);
    card->setPalette(cardPalette);
    card->setAutoFillBackground(true);

    auto *cardLayout = new QVBoxLayout(card);

    auto *value = new QLabel(cardValues[i], card);
    QFont valueFont = value->font();
    valueFont.setPointSize(19);
    valueFont.setBold(true);
    value->setFont(valueFont);

    auto *label = new QLabel(cardTitles[i], card);

    cardLayout->addWidget(value);
    cardLayout->addWidget(label);
    cardLayout->addStretch();

    cardsLayout->addWidget(card);
  }

  root->addLayout(cardsLayout);

  // Today's timetable
  auto *tableTitle = new QLabel("Today's Timetable", this);
  QFont tableTitleFont = tableTitle->font();
  tableTitleFont.setPointSize(18);
  tableTitleFont.setBold(true);
  tableTitle->setFont(tableTitleFont);
  root->addWidget(tableTitle);

  auto *table = new QTableWidget(5, 4, this);
  table->setHorizontalHeaderLabels({"Time", "Subject", "Batch", "Room"});

  const QString timetable[5][4] = {
      {"09:00 - 10:00", "Data Structures", "CSE - 3A", "Room 204"},
      {"10:00 - 11:00", "OOP", "CSE - 3B", "Lab 3"},
      {"11:00 - 12:00", "Free Period", "-", "-"},
      {"12:00 - 01:00", "Database Systems", "CSE - 3A", "Room 105"},
      {"02:00 - 03:00", "Practical Session", "CSE - 3B", "Lab 2"}};

  for (int row = 0; row < 5; ++row) {
    for (int col = 0; col < 4; ++col) {
      table->setItem(row, col, new QTableWidgetItem(timetable[row][col]));
    }
  }

  table->setMinimumHeight(240);
  table->setAlternatingRowColors(true);
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table->setSelectionBehavior(QAbstractItemView::SelectRows);
  table->setSelectionMode(QAbstractItemView::SingleSelection);
  table->verticalHeader()->setVisible(false);
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table->horizontalHeader()->setMinimumHeight(36);
  table->verticalHeader()->setDefaultSectionSize(35);

  root->addWidget(table, 1);

  // Timetable update notice
  auto *announcement = new QFrame(this);
  announcement->setFrameShape(QFrame::StyledPanel);

  QPalette announcementPalette = announcement->palette();
  announcementPalette.setColor(QPalette::Window, Qt::white);
  announcement->setPalette(announcementPalette);
  announcement->setAutoFillBackground(true);

  auto *announcementLayout = new QVBoxLayout(announcement);

  auto *announcementTitle = new QLabel("Timetable Updates", announcement);
  QFont announcementFont = announcementTitle->font();
  announcementFont.setPointSize(15);
  announcementFont.setBold(true);
  announcementTitle->setFont(announcementFont);

  auto *announcementText =
      new QLabel("Schedule change notifications will appear here when "
                 "live timetable synchronization is implemented.",
                 announcement);
  announcementText->setWordWrap(true);

  announcementLayout->addWidget(announcementTitle);
  announcementLayout->addWidget(announcementText);

  root->addWidget(announcement);
}
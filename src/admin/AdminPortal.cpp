
#include "AdminPortal.h"

#include <QColor>
#include <QFont>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>

// Helper function to set a widget's background color.
static void setBackground(QWidget *widget, const QColor &color) {
  QPalette widgetPalette = widget->palette();
  widgetPalette.setColor(QPalette::Window, color);
  widget->setPalette(widgetPalette);
  widget->setAutoFillBackground(true);
}

// Helper function to set a label's text color.
static void setTextColor(QLabel *label, const QColor &color) {
  QPalette labelPalette = label->palette();
  labelPalette.setColor(QPalette::WindowText, color);
  label->setPalette(labelPalette);
}

AdminPortal::AdminPortal(QWidget *parent) : QWidget(parent) {
  const QColor navy("#142B4A");
  const QColor white("#FFFFFF");
  const QColor lightGray("#F3F5F8");
  const QColor darkText("#243247");

  setWindowTitle("Catalyst - Administrator Dashboard");
  setBackground(this, white);

  // Main page layout
  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(32, 28, 32, 28);
  mainLayout->setSpacing(20);

  // ---------------- HEADER ----------------
  auto *header = new QFrame(this);
  setBackground(header, navy);
  header->setMinimumHeight(100);

  auto *headerLayout = new QVBoxLayout(header);
  headerLayout->setContentsMargins(24, 16, 24, 16);
  headerLayout->setSpacing(5);

  auto *brandLabel = new QLabel("CATALYST", header);

  QFont brandFont;
  brandFont.setPointSize(21);
  brandFont.setBold(true);
  brandLabel->setFont(brandFont);
  setTextColor(brandLabel, white);

  auto *subtitleLabel =
      new QLabel("Smart College Timetable Management System", header);
  setTextColor(subtitleLabel, white);

  headerLayout->addWidget(brandLabel);
  headerLayout->addWidget(subtitleLabel);

  mainLayout->addWidget(header);

  // ---------------- PAGE TITLE ----------------
  auto *pageTitle = new QLabel("Administrator Dashboard", this);

  QFont titleFont;
  titleFont.setPointSize(22);
  titleFont.setBold(true);
  pageTitle->setFont(titleFont);
  setTextColor(pageTitle, darkText);

  auto *pageDescription = new QLabel(
      "Manage timetables, faculty, rooms, and scheduling conflicts.", this);
  pageDescription->setWordWrap(true);
  setTextColor(pageDescription, darkText);

  mainLayout->addWidget(pageTitle);
  mainLayout->addWidget(pageDescription);

  // ---------------- STATISTICS ----------------
  auto *statsLayout = new QHBoxLayout();
  statsLayout->setSpacing(16);

  const QStringList statNames = {"Faculty Members", "Classes", "Rooms",
                                 "Timetable Clashes"};

  const QStringList statValues = {"24", "42", "18", "0"};

  for (int i = 0; i < statNames.size(); ++i) {
    auto *card = new QFrame(this);
    card->setFrameShape(QFrame::StyledPanel);
    card->setMinimumHeight(105);
    setBackground(card, lightGray);

    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(16, 14, 16, 14);
    cardLayout->setSpacing(8);

    auto *valueLabel = new QLabel(statValues[i], card);

    QFont valueFont;
    valueFont.setPointSize(23);
    valueFont.setBold(true);
    valueLabel->setFont(valueFont);
    setTextColor(valueLabel, navy);

    auto *nameLabel = new QLabel(statNames[i], card);
    nameLabel->setWordWrap(true);
    setTextColor(nameLabel, darkText);

    cardLayout->addWidget(valueLabel);
    cardLayout->addWidget(nameLabel);

    statsLayout->addWidget(card);
  }

  mainLayout->addLayout(statsLayout);

  // ---------------- QUICK ACTIONS ----------------
  auto *actionsTitle = new QLabel("Quick Actions", this);

  QFont actionsFont;
  actionsFont.setPointSize(17);
  actionsFont.setBold(true);
  actionsTitle->setFont(actionsFont);
  setTextColor(actionsTitle, darkText);

  auto *generateButton = new QPushButton("Generate Timetable", this);

  auto *checkButton = new QPushButton("Check Timetable Clashes", this);

  auto *actionsLayout = new QHBoxLayout();
  actionsLayout->setSpacing(12);
  actionsLayout->addWidget(generateButton);
  actionsLayout->addWidget(checkButton);
  actionsLayout->addStretch();

  mainLayout->addWidget(actionsTitle);
  mainLayout->addLayout(actionsLayout);

  // ---------------- STATUS MESSAGE ----------------
  auto *statusLabel =
      new QLabel("Welcome! Select a quick action to get started.", this);
  statusLabel->setWordWrap(true);
  setTextColor(statusLabel, darkText);

  mainLayout->addWidget(statusLabel);

  // These buttons are placeholders until the scheduling
  // and conflict-detection engine is implemented.
  connect(generateButton, &QPushButton::clicked, this, [statusLabel]() {
    statusLabel->setText(
        "Timetable generation is not connected yet. "
        "The scheduling engine will be added in a later phase.");
  });

  connect(checkButton, &QPushButton::clicked, this, [statusLabel]() {
    statusLabel->setText(
        "Clash detection is not connected yet. "
        "The timetable validation engine will be added in a later phase.");
  });

  // ---------------- FOOTER / BACK BUTTON ----------------
  auto *footerLayout = new QHBoxLayout();
  footerLayout->addStretch();

  auto *backButton = new QPushButton("Back to Login", this);
  footerLayout->addWidget(backButton);

  mainLayout->addStretch();
  mainLayout->addLayout(footerLayout);

  connect(backButton, &QPushButton::clicked, this, &AdminPortal::backRequested);
}

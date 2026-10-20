
#include <QApplication>
#include <QStackedWidget>
#include <QMessageBox>
#include <QPalette>
#include <QStyleFactory>
#include "ui/WelcomePage.h"
#include "ui/AuthWindow.h"
#include "ui/admin/AdminPortal.h"
#include "ui/faculty/FacultyPortal.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Force Fusion style so Windows dark mode doesn't override our colors
    app.setStyle(QStyleFactory::create("Fusion"));

    // Set a light base palette
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor("#F4F6FA"));
    lightPalette.setColor(QPalette::WindowText, QColor("#1E293B"));
    lightPalette.setColor(QPalette::Base, QColor("#FFFFFF"));
    lightPalette.setColor(QPalette::AlternateBase, QColor("#EEF2F7"));
    lightPalette.setColor(QPalette::Text, QColor("#1E293B"));
    lightPalette.setColor(QPalette::Button, QColor("#E2E8F0"));
    lightPalette.setColor(QPalette::ButtonText, QColor("#1E293B"));
    lightPalette.setColor(QPalette::Highlight, QColor("#2563EB"));
    lightPalette.setColor(QPalette::HighlightedText, QColor("#FFFFFF"));
    app.setPalette(lightPalette);

    QStackedWidget stack;
    stack.setWindowTitle("Catalyst - Smart Timetable Management");
    stack.resize(1200, 800);
    stack.setMinimumSize(1000, 680);

    auto *welcome = new WelcomePage;
    auto *auth = new AuthWindow;
    auto *admin = new AdminPortal;
    auto *faculty = new FacultyPortal;

    stack.addWidget(welcome);
    stack.addWidget(auth);
    stack.addWidget(admin);
    stack.addWidget(faculty);

    // Welcome page -> Login
    QObject::connect(
        welcome, &WelcomePage::loginRequested,
        &stack, [&stack, auth]()
    {
        auth->openLogin();
        stack.setCurrentWidget(auth);
    });

    // Welcome page -> Sign Up
    QObject::connect(
        welcome, &WelcomePage::signUpRequested,
        &stack, [&stack, auth]()
    {
        auth->openSignUp();
        stack.setCurrentWidget(auth);
    });

    // Login page -> Welcome page
    QObject::connect(
        auth, &AuthWindow::backRequested,
        &stack, [&stack, welcome]()
    {
        stack.setCurrentWidget(welcome);
    });

    // Validated form -> Navigate to the appropriate portal
    QObject::connect(
        auth, &AuthWindow::authenticationRequested,
        &stack, [&stack, admin, faculty](
            const QString &role, bool isSignUp)
    {
        if (role.contains("Administrator", Qt::CaseInsensitive))
        {
            stack.setCurrentWidget(admin);
        }
        else if (role.contains("Faculty", Qt::CaseInsensitive))
        {
            stack.setCurrentWidget(faculty);
        }
    });

    // Admin portal -> Login
    QObject::connect(
        admin, &AdminPortal::backRequested,
        &stack, [&stack, auth]()
    {
        auth->openLogin();
        stack.setCurrentWidget(auth);
    });

    // Faculty portal -> Login
    QObject::connect(
        faculty, &FacultyPortal::backRequested,
        &stack, [&stack, auth]()
    {
        auth->openLogin();
        stack.setCurrentWidget(auth);
    });

    // Welcome page -> Explore More
    QObject::connect(
        welcome, &WelcomePage::exploreRequested,
        &stack, [&stack]()
    {
        QMessageBox::information(
            &stack,
            "Explore Catalyst",
            "Catalyst is designed to manage college timetables, "
            "detect scheduling conflicts, and coordinate updates.");
    });

    stack.setCurrentWidget(welcome);
    stack.show();

    return app.exec();
}

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSqlError>
#include "Controllers/MainWindow.hpp"
#include "Logics/Config.hpp"
#include "App.hpp"
#include "appinfo.hpp"
#include "version.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(app::info::COMPANY);
    QCoreApplication::setApplicationName(app::info::PRODUCT);
    QCoreApplication::setApplicationVersion(app::version::FULL);
    Config::initialise();

    QApplication app(argc, argv);

    if (!App::getInstance()->intitaliseDataSource())
    {
        QMessageBox::critical(nullptr, QObject::tr("Critical DataSource Error"),
                              QObject::tr("Error initialising the applicaiton data source.\n") +
                              "\"" + App::getInstance()->getDataSource()->getConnection()->lastError().text() + "\"\n\n" +
                              QObject::tr("The application may not have the correct access privilege to the database file or the file does not exist at path [") +
                              Config::getDatabasePath() +"].");
//        App::destroyInstance();
//        return EXIT_FAILURE;
    }

    qApp->setStyleSheet(Config::getGlobalStylesheet());

    qDebug() << "Creating main window";
    MainWindow window;
    qDebug() << "Showing main window";
    window.show();

    auto resultCode = app.exec();
    App::destroyInstance();
    return resultCode;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wrestler.h"

#include <QMainWindow>
#include <QSqlDatabase>  // Include this for database connection
#include <QSqlQuery>     // Include this for running queries
#include <QSqlError>     // Include this for error handling
#include <QDebug>        // For debugging output
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>


#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

#include <random>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QVector<Wrestler> getPlayerRoster() const { return m_playerRoster; }
    QVector<int> getMoneyHistory() const { return m_moneyHistory; }
    QVector<int> getFanHistory() const { return m_fanHistory; }
    int getCurrentWeek() const { return m_currentWeek; }


private slots:
    void on_RosterTab_clicked();
    void on_DashboardTab_clicked();
    void on_PromotionTab_clicked();
    void on_SettingsTab_clicked();
    void on_CardTab_clicked();
    void on_StartNew_clicked();
    void on_LoadGame_clicked();
    void on_userSave_clicked();
    void on_finalizeBooking_clicked();
    void on_pushButton_clicked();

    void on_defaultRoster_clicked();

    void on_customRoster_clicked();

    void on_randomRoster_clicked();

    void on_backToLanding_clicked();

    void on_RosterDisplayTab_clicked();

private:
    Ui::MainWindow *ui;

    // Method to set up the database connection
    void connectToDatabase();
    // Method to load wrestler attributes from the text file
    void loadWrestlerAttributes(const QString &filePath);
    // Method to save wrestker attributes to text file
    void saveWrestlerAttributes(const QString &filePath, const QList<Wrestler> &wrestlers);
    // Load data from a text file
    void loadFromText(const QString &filePath);

    // function to display a line graph
    void makeCharts(const QList<int>& values, QWidget* chartWidget);

    // update labels in the GUI
    void updateLabels();

    // sets all values to what they would be for creating a new save file
    void newGameSetup();

    void showWrestlerDetails(const Wrestler &wrestler);
    void populateWrestlerList(const QList<Wrestler> &wrestlers);
    void updateWrestlerDetails(const Wrestler &wrestler);

    QList<Wrestler> m_playerRoster;
    int m_money;
    int m_fans;
    int m_year;
    int m_currentWeek;

    // Tracks money over the past n weeks
    QList<int> m_moneyHistory;
    QList<int> m_fanHistory;
};

#endif // MAINWINDOW_H

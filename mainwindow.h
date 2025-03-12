#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wrestler.h"
#include "match.h"
#include "show.h"
#include "team.h"
#include "championship.h"

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
#include <QComboBox>



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
    void on_addToMatch_clicked();
    void on_addMatchButton_clicked();
    void on_removeFromMatch_clicked();
    void updateWinnerComboBox(); // Updates the choices the user has to select the winner of a match
    void on_saveMatchDetails_clicked();
    void on_ChampionTab_clicked();  // shows championships
    void on_teamNameRadio_toggled(bool checked);     // on champ page, whether to select tag champ by team name
    void on_individualRadioButton_toggled(bool checked);    // on champ page, whether to select tag champ by individuals
    void on_addToTeamButton_clicked();  //adds wrestler to team
    void on_newTeamButton_clicked();    // creates new team
    void on_saveTeamButton_clicked();   // saves team attributes

    void on_TeamsTab_clicked();

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
    void updateDashboardLabels();

    // sets all values to what they would be for creating a new save file
    void newGameSetup();

    // for debugging
    void showWrestlerDetails(const Wrestler &wrestler);

    // Displays all wrestlers that can be used
    void populateWrestlerList(const QList<Wrestler> &wrestlers);

    // Shows all info to player about a wrestler
    void updateWrestlerDetails(const Wrestler &wrestler);

    // Shows matches that have been added to show
    void populateMatchList( );
    // Adds a generic match to show
    void addMatchToCard();

    // Edit match
    void openEditMatchPage(match &m, int index);
    // Shows menu to edit match
    void populateEditMatchPage(match &m);

    // Sets up combo boxes for championship page
    void setUpChampionSelection();

    // Select and update tag champs by selecting a team
    void onTagChampSelected(int index);
    // select and update tag champs by selecting individuals
    void onManualTagChampsSelected();

    // Select and update world champ
    void onWorldChampSelected(int index);
    // Select and update women's champ
    void onWomenChampSelected(int index);

    // Shows all teams
    void populateTeamList();
    // opens page to show specific team
    void openEditTeamPage(team& team);
    // Deletes team at index in m_teams
    void removeTeam(int index);
    // Removes individual wrestler from a team
    void removeWrestlerFromTeam(QComboBox* wrestlerComboBox);
    // Allows team attributes to be saved if there are 2 or more comboboxes with wrestlers
    void updateSaveButton();


    QList<Wrestler> m_playerRoster;
    QList<team> m_teams;

    championship m_world;
    championship m_tag;
    championship m_women;

    team* m_currentTeam;
    int m_currentTeamIndex;

    int m_money;
    int m_fans;
    int m_year;
    int m_currentWeek;

    class show m_currentShow;

    match* m_currentMatch = nullptr;  // Match that is currently being edited
    int m_currentMatchIndex = -1; // Store the index of the match being edited

    // Tracks money over the past n weeks
    QList<int> m_moneyHistory;
    QList<int> m_fanHistory;
};

#endif // MAINWINDOW_H

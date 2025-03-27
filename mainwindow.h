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
#include <QSpacerItem>



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
    void on_finalizeBooking_clicked();      // goes to next week, performs weekly calculations
    void on_pushButton_clicked();           // skips 26 weeks.!!!!!!!!!! FOR DEBUGGING!!! DO NOT KEEP THIS IN FINAL PROJECT!!!!!!!!!!!!
    void on_defaultRoster_clicked();        // loads default roster
    void on_customRoster_clicked();         // user selects custom roster
    void on_randomRoster_clicked();         // user selects random roster
    void on_backToLanding_clicked();        // goes back to landing page
    void on_RosterDisplayTab_clicked();     // displays members of roster
    void on_addToMatch_clicked();           // adds wrestler to match
    void on_addMatchButton_clicked();       // adds match to show
    void on_saveMatchDetails_clicked();     // saves match details
    void on_ChampionTab_clicked();          // shows championships
    void on_teamNameRadio_toggled(bool checked);            // on champ page, whether to select tag champ by team name
    void on_individualRadioButton_toggled(bool checked);    // on champ page, whether to select tag champ by individuals
    void on_addToTeamButton_clicked();      //adds wrestler to team
    void on_newTeamButton_clicked();        // creates new team
    void on_saveTeamButton_clicked();       // saves team attributes

    void on_TeamsTab_clicked();

    void on_nextWeekButton_clicked();

    void on_teamCheckBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    void connectToDatabase();                                                           // Method to set up the database connection
    void loadWrestlerAttributes(const QString &filePath);                               // Method to load wrestler attributes from the text file
    void saveWrestlerAttributes(const QString &filePath,
                                const QList<Wrestler> &wrestlers);     // Method to save wrestker attributes to text file
    void loadFromText(const QString &filePath);                                 // Load data from a text file
    void makeCharts(const QList<int>& values, QWidget* chartWidget);            // function to display a line graph
    void newGameSetup();                                // sets all values to what they would be for creating a new save file

    void populateResultsList();                     // Displays matches, the winners, and the ratings

    void updateDashboardLabels();                   // update dashboard labels in the GUI


    void populateWrestlerList(const QList<Wrestler> &wrestlers);        // Adds wrestlers and important info to scoll widget
    void updateWrestlerDetails(const Wrestler &wrestler);               // Shows all info to player about a wrestler

    void populateMatchList( );                          // Shows matches that have been added to show
    void openEditMatchPage(match &m, int index);        // Edit match
    void populateEditMatchPage(match &m);               // Shows menu to edit match
    void removeWrestlerFromMatch(QComboBox* WrestlerComboBox);   // Removes specific wrestler from match
    void updateSaveMatchButton();                       // Allows player to save match
    void updateMatchWrestlerSelection();                // Updates wrestlers that can be in a match
    void updateTeamMatchLayout(bool isTeamMatch);       // Changes layout when editing a tag match, or unselecting tag team check box


    void setUpChampionSelection();                  // Sets up combo boxes for championship page
    void onTagChampSelected(int index);             // Select and update tag champs by selecting a team
    void onManualTagChampsSelected();               // select and update tag champs by selecting individuals
    void onWorldChampSelected(int index);           // Select and update world champ
    void onWomenChampSelected(int index);           // Select and update women's champ

    void populateTeamList();                        // Shows all teams
    void openEditTeamPage(team& team);              // opens page to show specific team
    void removeTeam(int index);                     // Deletes team at index in m_teams
    void removeWrestlerFromTeam(QComboBox* wrestlerComboBox);   // Removes individual wrestler from a team
    void updateSaveTeamButton();        // Allows team attributes to be saved if there are 2 or more comboboxes with wrestlers
    void updateWrestlerTeamSelection();             // Updates wrestlers able to be chosen for a team

    QList<Wrestler> m_playerRoster;

    championship m_world;
    championship m_tag;
    championship m_women;

    QList<team> m_teams;
    team* m_currentTeam;
    int m_currentTeamIndex;

    int m_money;
    int m_fans;
    int m_year;
    int m_currentWeek;

    class show m_currentShow;
    match* m_currentMatch = nullptr;            // Match that is currently being edited
    int m_currentMatchIndex = -1;               // Store the index of the match being edited
    QSpacerItem* m_spacerItem = nullptr;        // Spacer on match edit page for uneven teams

    // Tracks money over the past n weeks
    QList<int> m_moneyHistory;
    QList<int> m_fanHistory;
};

#endif // MAINWINDOW_H

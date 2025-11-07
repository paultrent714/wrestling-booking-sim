#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wrestler.h"
#include "match.h"
#include "show.h"
#include "team.h"
#include "championship.h"
#include "gamedatamanager.h"
#include "rivalry.h"

#include <QMainWindow>
#include <QSqlDatabase>  // Include this for database connection
#include <QSqlQuery>     // Include this for running queries
#include <QSqlError>     // Include this for error handling
#include <QDebug>        // For debugging output
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QFontDatabase>    // for symbols and icons on buttons
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QSpacerItem>

#include <QWebEngineView>   // For faces.js
#include <QWebEnginePage>


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


    QVector<Wrestler*> getPlayerRoster() const { return m_playerRoster; }
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

    void on_defaultRoster_clicked();        // loads default roster
    void on_customRoster_clicked();         // user selects custom roster
    void on_randomRoster_clicked();         // user selects random roster
    void on_backToLanding_clicked();        // goes back to landing page
    void on_RosterDisplayTab_clicked();     // displays members of roster
    void on_addToMatch_clicked();           // adds wrestler to match
    void on_addMatchButton_clicked();       // adds match to show
    void on_backFromEditMatch_clicked();     // for when user is done editing match
    void on_ChampionTab_clicked();          // shows championships
    void on_teamNameRadio_toggled(bool checked);            // on champ page, whether to select tag champ by team name
    void on_individualRadioButton_toggled(bool checked);    // on champ page, whether to select tag champ by individuals
    void on_addToTeamButton_clicked();      //adds wrestler to team
    void on_newTeamButton_clicked();        // creates new team
    void on_saveTeamButton_clicked();       // saves team attributes
    void on_TeamsTab_clicked();
    void on_nextWeekButton_clicked();       // finishes week after player views show results
    void on_teamCheckBox_toggled(bool checked);     // toggles whether a match is a tag match
    void on_InjuredTab_clicked();      // goes to page to see injured list
    void on_darkModeCheckBox_stateChanged(int arg1);    // changes dark mode when game loads/user checks it
    void on_homeButton_clicked();
    void on_editNameButton_clicked();
    void on_RosterDescendingSort_toggled(bool checked);
    void on_sortByAttributesCB_currentTextChanged(const QString &arg1);
    void on_InjuredBackButton_clicked();
    void on_champBackButton_clicked();
    void on_teamsBackButton_clicked();
    void on_rosterBackButton_clicked();
    void on_backFromWrestler_clicked();
    void on_ScoutTalentButton_clicked();
    void on_FeudsTab_clicked();
    void on_createFeudButton_clicked();
    void on_startFeudButton_clicked();
    void on_rivalryBackButton_clicked();
    void on_saveNameButton_clicked();

    void on_RivalPromotionTab_clicked();

    void on_FreeAgentTab_clicked();

private:
    Ui::MainWindow *ui;

    void loadMaterialFont();

    void newGameSetup();                            // sets all values to what they would be for creating a new save file
    void setRosters(QList<Wrestler*>);                              // sorts wrestlers into their respective promotion

    void makeCharts(const QList<int>& values, QWidget* chartWidget);            // function to display a line graph

    void finalizeBooking();                         // Calculates results of matches
    void populateResultsList();                     // Displays matches, the winners, and the ratings

    void updateDashboardLabels();                   // update dashboard labels in the GUI


    void populateWrestlerList( QList<Wrestler*> &wrestlers);        // Adds wrestlers and important info to scoll widget
    void updateRosterLabel();       // updates text in the label at the top of the widget that marks which promotion the wrestlers are signed to
    void updateWrestlerDetails( Wrestler* wrestler);               // Shows all info to player about a wrestler
    QStringList loadFaceFiles(bool isFemale);          // creates list of face paths from one of faces subdirectories
    //QString randomFace(const QStringList &faces, bool isFemale);
    QString randomFace(const QStringList &faces);

    void populateInjuredWrestlersList( QList<Wrestler*> &wrestlers);    // Shows wrestlers who are injured and for how long

    void populateMatchList( );                          // Shows matches that have been added to show
    void openEditMatchPage(match &m, int index);        // Edit match
    void populateEditMatchPage(match &m);               // Shows menu to edit match
    void removeWrestlerFromMatch(QComboBox* WrestlerComboBox);   // Removes specific wrestler from match
    void updateSaveMatchButton();                       // Allows player to save match
    void updateMatchWrestlerSelection();                // Updates wrestlers that can be in a match
    void updateTeamMatchLayout(bool isTeamMatch);       // Changes layout when editing a tag match, or unselecting tag team check box
    void clearTeamMatchSpacer();                        // Removes the spacer and sets the spacer pointer to null when finished editing match

    void setUpChampionSelection();                  // Sets up combo boxes for championship page
    void onTagChampSelected(int index);             // Select and update tag champs by selecting a team
    void onManualTagChampsSelected();               // select and update tag champs by selecting individuals
    void onWorldChampSelected(int index);           // Select and update world champ
    void onWomenChampSelected(int index);           // Select and update women's champ
    bool isChampion( Wrestler* w);       // Returns whether given wrestler is a champion

    void populateTeamList();                        // Shows all teams
    void openEditTeamPage(team& team);              // opens page to show specific team
    void removeTeam(int index);                     // Deletes team at index in m_teams
    void removeWrestlerFromTeam(QComboBox* wrestlerComboBox);   // Removes individual wrestler from a team
    void updateSaveTeamButton();        // Allows team attributes to be saved if there are 2 or more comboboxes with wrestlers
    void updateWrestlerTeamSelection();             // Updates wrestlers able to be chosen for a team

    void applyTheme();          // changes labels and widgets created in .ui file to dark/light mode
    void applyScrollBarStyle(); // ensures the scroll bars do not change their appearance
    void clearData();           // for clearing game data and going to landing page

    void sortWrestlers();

    void scoutNewRecruit();     // used for viewing info about m_scoutedWrestler
    void signNewRecruit();      // signs scouted wrestler
    void declineSign();         // deletes new recruit wrestler object

    int evaluateWrestlerForCpu(Wrestler* w);    // calculates whether cpu should sign a wrestler
    bool shouldCpuResign(Wrestler* w);          // decides whether the cpu's wrestler score is worth resiging
    void processCpuContracts();                 // decrements contract length and resigns wrestler if needed (currently 20 week extensions)
    void cpuSignFreeAgents(int minRosterSize);  // if cpu roster is too small, signs the best (or sometimes one of the best) free agents
    void updateCpuRosterWeekly();               // calls functions to process cpu contracts and sign free agents

    void populateRivalryList(); // displays current rivalries
    void saveNewRivalry();      // saves rivalry created by user
    void populateRivalryComboBoxes();   // updates combo boxes for creating a new rivalry with available wrestlers
    QList<Wrestler*> getAvailableWrestlersForRivalry() const;   // returns list of wrestlers not part of active rivalry
    bool isDuplicateRivalry(Wrestler* a, Wrestler* b);      // checks whether the rivalry already exists


    void resizeEvent(QResizeEvent *event);
    void updateWrestlerImage();
    bool eventFilter(QObject *obj, QEvent *event);



    GameDataManager* dataManager;

    QList<Wrestler*> m_playerRoster;
    QList<Wrestler*> m_cpuRoster;
    QList<Wrestler*> m_freeAgents;
    int m_lastUsedID;           // Last created wrestler ID

    QList<Wrestler*>* m_currentRoster = nullptr;    // whether player is seeing free agents, player roster, cpu roster
    int m_currentAffiliation = 0; // 0 = Free Agent, 1 = Player, 2 = CPU


    Wrestler* m_scoutedWrestler = nullptr;
    Wrestler* m_currentWrestler = nullptr;
    QPixmap m_currentFace;

    championship m_world;
    championship m_tag;
    championship m_women;

    QList<team> m_teams;
    team* m_currentTeam;
    int m_currentTeamIndex;

    QList<rivalry*> m_rivalries;
    QList<Wrestler*> m_availableRivalryWrestlers;   // list of wrestlers not part of an active rivalry

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

    bool m_darkMode = false;    // Whether user is using dark mode
    QColor m_textColor;         // Default color of text
    QColor m_backgroundColor;   // Default color of background

    QFont m_materialFont;       // Where the symbols are being retrieved from

    //Default style for combo boxes
    QString m_comboBoxStyle =
        "QComboBox { background: #f0f0f0; border: 1px solid #888; padding: 4px; border-radius: 4px; color: black; }"
        "QComboBox::drop-down { width: 20px; border-left: 1px solid #888; background: #d3d3d3; }"
        "QComboBox::down-arrow { image: url(:/icons/down-arrow.png); width: 12px; height: 12px; }"
        "QComboBox QAbstractItemView { background: #f0f0f0; selection-background-color: #0078D7; color: black; border: 1px solid #888; }"
        "QComboBox QAbstractItemView::item { background-color: #f0f0f0; color: black; }";  // Ensure the item background color is consistent
    ;


    // QChars for icons used in program
    const QChar saveIcon = QChar(0xe161);
    const QChar injuredIcon = QChar(0xe3f3);
    // QIcons for icons used for buttons, because buttons can't have different fonts
    const QIcon injuredIconRed =  QIcon("icons/healing_red.png");
};

#endif // MAINWINDOW_H

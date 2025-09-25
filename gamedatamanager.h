#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H

#include <QList>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <qcoreapplication.h>

#include "wrestler.h"
#include "championship.h"
#include "team.h"
#include "show.h"
#include "rivalry.h"

class GameDataManager {
public:
    GameDataManager();
    ~GameDataManager();

    // Initialize the database
    void initializeDatabase();

    bool openDatabase();  // Open the database connection
    void closeDatabase(); // Close the database connection

    // Save data
    void saveWrestlers( const QList<Wrestler*>& player,
                        const QList<Wrestler*>& cpu,
                        const QList<Wrestler*>& freeAgents);

    void saveChampionships( championship& world,  championship& tag,  championship& women);
    void saveTeams( QList<team>& teams);
    void saveRivalries( QList<rivalry*>& rivalries);
    void saveGameInfo(int money, int fans, int year, int currentWeek,
                      QList<int> &moneyHistory, QList<int> &fanHistory,
                      bool darkMode);
    void saveShow( show& currentShow);
    void saveMatches(show &currentShow);
    // Load data
    QList<Wrestler*> loadWrestlers();
    void loadChampionships(QList<championship*>& championshipList,
                           const QMap<int, Wrestler*>& wrestlerMap);
    void loadTeams(QList<team> &teams,
                   const QMap<int, Wrestler*>& wrestlerMap);
    void loadRivalries(QList<rivalry*>& rivalries,
                       const QMap<int, Wrestler*>& wrestlerMap);
    void loadGameInfo(int& money, int& fans, int& year, int& currentWeek,
                      QList<int> &moneyHistory, QList<int> &fanHistory,
                      bool &darkMode);
    void loadShow(show &currentShow,
                  const QMap<int, Wrestler*>& wrestlerMap);

    void clearDatabase();

    QList<Wrestler*> loadDefaultRoster();

    void loadDefaultRoster( const QString& defaultDbPath);   // retrieves default roster
    void loadDefaultWrestlers(QSqlDatabase& db );

    QList<Wrestler*> getWrestlers() { return m_wrestlers;}
    QList<championship> getChampionships() const { return m_championships; }

private:
    QSqlDatabase db;

    QList<Wrestler*> m_wrestlers;
    QList<championship> m_championships;


    Wrestler* findWrestlerById(int wrestlerId);
};

#endif // GAMEDATAMANAGER_H

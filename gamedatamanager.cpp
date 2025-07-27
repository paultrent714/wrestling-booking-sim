#include "gamedatamanager.h"

GameDataManager::GameDataManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Create or reference the "saveFiles" directory relative to the executable
    QString saveFolder = QDir::currentPath() + "/saveFiles";
    QDir().mkpath(saveFolder);  // Ensure the directory exists

    QString dbPath = saveFolder + "/game_data.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database -" << db.lastError().text();
    } else {
        qDebug() << "Database opened successfully.";
    }
    initializeDatabase();
}

GameDataManager::~GameDataManager() {
    if (db.isOpen()) {
        db.close();
    }
}

void GameDataManager::initializeDatabase() {
    QSqlQuery query;

    // Wrestler Table
    query.exec("CREATE TABLE IF NOT EXISTS Wrestlers ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, gender INTEGER, popularity INTEGER, age INTEGER, "
               "potential INTEGER, powerhouse INTEGER, brawler INTEGER, "
               "highFlyer INTEGER, technician INTEGER, mma INTEGER, "
               "charisma INTEGER, stamina INTEGER, salary INTEGER, role INTEGER, "
               "health INTEGER, injury INTEGER, weeksOnContract INTEGER);");

    // ContractSegments Table (for wrestler contracts)
    query.exec("CREATE TABLE IF NOT EXISTS Contracts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "wrestler_id INTEGER, "
               "matchesRemaining INTEGER, "
               "salaryPerMatch INTEGER, "
               "FOREIGN KEY(wrestler_id) REFERENCES Wrestlers(id) ON DELETE CASCADE);");

    // Championship Table
    query.exec("CREATE TABLE IF NOT EXISTS Championships ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "titleName TEXT, isTagTitle BOOLEAN, isWomensTitle BOOLEAN, "
               "champion1_id INTEGER, champion2_id INTEGER, "
               "FOREIGN KEY(champion1_id) REFERENCES Wrestlers(id), "
               "FOREIGN KEY(champion2_id) REFERENCES Wrestlers(id));");

    // Team Table
    query.exec("CREATE TABLE IF NOT EXISTS Teams ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, team_name TEXT);");

    // Team Members Table (to associate wrestlers with teams)
    query.exec("CREATE TABLE IF NOT EXISTS TeamMembers ("
               "team_id INTEGER, "
               "wrestler_id INTEGER, "
               "FOREIGN KEY(team_id) REFERENCES Teams(id) ON DELETE CASCADE, "
               "FOREIGN KEY(wrestler_id) REFERENCES Wrestlers(id) ON DELETE CASCADE);");

    // Rivalry Table ( table for rivalries)
    query.exec("CREATE TABLE IF NOT EXISTS Rivalries ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "wrestler1_id INTEGER, wrestler2_id INTEGER, "
               "bonusWeeks INTEGER, penaltyWeeks INTEGER, "
               "status INTEGER,"
               "FOREIGN KEY(wrestler1_id) REFERENCES Wrestlers(id), "
               "FOREIGN KEY(wrestler2_id) REFERENCES Wrestlers(id));");

    // Game Info Table
    query.exec("CREATE TABLE IF NOT EXISTS GameInfo ("
               "id INTEGER PRIMARY KEY, money INTEGER, fans INTEGER, year INTEGER, currentWeek INTEGER, "
               "moneyHistory TEXT, fanHistory TEXT, darkMode BOOLEAN DEFAULT 0);");

    // Show Table
    query.exec("CREATE TABLE IF NOT EXISTS Show ("
               "id INTEGER PRIMARY KEY, showRating INTEGER, totalRevenue INTEGER, "
               "totalCosts INTEGER, showProfit INTEGER, fanImpact INTEGER, showType INTEGER);");

    // Matches Table
    query.exec("CREATE TABLE IF NOT EXISTS Matches ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, show_id INTEGER, matchType TEXT, "
               "participants TEXT, teams BOOLEAN, rating FLOAT, winner_id INTEGER, "
               "championship BOOLEAN, finances INTEGER, "
               "FOREIGN KEY(show_id) REFERENCES Show(id), "
               "FOREIGN KEY(winner_id) REFERENCES Wrestlers(id));");

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
    }

}

bool GameDataManager::openDatabase()
{
    if (!db.isOpen()) {
        if (db.open()) {
            qDebug() << "Database opened successfully.";
            return true;
        } else {
            qDebug() << "Error opening database: " << db.lastError().text();
            return false;
        }
    }
    return true;  // If already open, return true
}

void GameDataManager::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database closed.";
    }
}

// Save Wrestlers
void GameDataManager::saveWrestlers(QList<Wrestler*> &wrestlers) {
    QSqlQuery query;

    // Clear Wrestlers and Contracts tables
    query.exec("DELETE FROM Wrestlers");
    query.exec("DELETE FROM Contracts");

    // Reset auto-increment counters
    query.exec("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE name = 'Wrestlers'");
    query.exec("UPDATE SQLITE_SEQUENCE SET seq = 0 WHERE name = 'Contracts'");

    for (Wrestler* wrestler : wrestlers) {
        query.prepare("INSERT INTO Wrestlers (id, name, gender, popularity, age, potential, powerhouse, brawler, "
                      "highFlyer, technician, mma, charisma, stamina, role, health, injury) "
                      "VALUES (:id, :name, :gender, :popularity, :age, :potential, :powerhouse, :brawler, "
                      ":highFlyer, :technician, :mma, :charisma, :stamina, :role, :health, :injury)");

        query.bindValue(":id", wrestler->getID());  // Preserve ID
        query.bindValue(":name", wrestler->getName());
        query.bindValue(":gender", wrestler->getGender());
        query.bindValue(":popularity", wrestler->getPopularity());
        query.bindValue(":age", wrestler->getAge());
        query.bindValue(":potential", wrestler->getPotential());
        query.bindValue(":powerhouse", wrestler->getPowerhouse());
        query.bindValue(":brawler", wrestler->getBrawler());
        query.bindValue(":highFlyer", wrestler->getHighFlyer());
        query.bindValue(":technician", wrestler->getTechnician());
        query.bindValue(":mma", wrestler->getMMA());
        query.bindValue(":charisma", wrestler->getCharisma());
        query.bindValue(":stamina", wrestler->getStamina());
        query.bindValue(":role", wrestler->getRole());
        query.bindValue(":health", wrestler->getHealth());
        query.bindValue(":injury", wrestler->getInjury());
        query.exec();

        int wrestlerId = wrestler->getID();
        if (wrestlerId <= 0)
            wrestlerId = query.lastInsertId().toInt();  // fallback if new wrestler

        // Now insert contract segments for this wrestler
        for (const ContractSegment& segment : wrestler->getContractSegments()) {
            QSqlQuery contractQuery;
            contractQuery.prepare("INSERT INTO Contracts (wrestler_id, matchesRemaining, salaryPerMatch) "
                                  "VALUES (:wrestler_id, :matchesRemaining, :salaryPerMatch)");
            contractQuery.bindValue(":wrestler_id", wrestlerId);
            contractQuery.bindValue(":matchesRemaining", segment.matchesRemaining);
            contractQuery.bindValue(":salaryPerMatch", segment.salaryPerMatch);
            contractQuery.exec();
        }
    }
}

// Save Championships
void GameDataManager::saveChampionships( championship &world,  championship &tag,  championship &women) {
    QSqlQuery query;

    // delete old entries
    query.exec("DELETE FROM Championships");

    // Save each championship
    query.prepare("INSERT INTO Championships (titleName, isTagTitle, isWomensTitle, champion1_id, champion2_id) "
                  "VALUES (:titleName, :isTagTitle, :isWomensTitle, :champion1_id, :champion2_id)");

    // Save World Championship
    query.bindValue(":titleName", world.getTitleName());
    query.bindValue(":isTagTitle", world.isTagTitle());
    query.bindValue(":isWomensTitle", world.isWomensTitle());
    query.bindValue(":champion1_id", world.getChampions().size() > 0 ? world.getChampions().at(0)->getID() : QVariant());
    query.bindValue(":champion2_id", world.getChampions().size() > 1 ? world.getChampions().at(1)->getID() : QVariant());
    query.exec();

    // Save Tag Championship
    query.bindValue(":titleName", tag.getTitleName());
    query.bindValue(":isTagTitle", tag.isTagTitle());
    query.bindValue(":isWomensTitle", tag.isWomensTitle());
    query.bindValue(":champion1_id", tag.getChampions().size() > 0 ? tag.getChampions().at(0)->getID() : QVariant());
    query.bindValue(":champion2_id", tag.getChampions().size() > 1 ? tag.getChampions().at(1)->getID() : QVariant());
    query.exec();

    // Save Women's Championship
    query.bindValue(":titleName", women.getTitleName());
    query.bindValue(":isTagTitle", women.isTagTitle());
    query.bindValue(":isWomensTitle", women.isWomensTitle());
    query.bindValue(":champion1_id", women.getChampions().size() > 0 ? women.getChampions().at(0)->getID() : QVariant());
    query.bindValue(":champion2_id", women.getChampions().size() > 1 ? women.getChampions().at(1)->getID() : QVariant());
    query.exec();

}

// Save Teams
void GameDataManager::saveTeams(QList<team>& teams) {
    if (teams.isEmpty()) {
        qDebug() << "No teams to save.";
        return;
    }

    QSqlQuery query;

    // Start a transaction
    if (!query.exec("BEGIN TRANSACTION")) {
        qDebug() << "Error starting transaction: " << query.lastError().text();
        return;
    }

    // Clear existing teams and members (if necessary)
    query.exec("DELETE FROM TeamMembers");  // Remove existing relationships
    query.exec("DELETE FROM Teams");

    // Insert teams
    for (const team& t : teams) {
        query.prepare("INSERT INTO Teams (team_name) VALUES (:team_name)");
        query.bindValue(":team_name", t.getTeamName());

        if (!query.exec()) {
            qDebug() << "Error inserting team: " << query.lastError().text();
            query.exec("ROLLBACK");  // Rollback if the team insert fails
            return;
        }

        int teamId = query.lastInsertId().toInt();

        // Insert team-member relationships
        for (Wrestler* wrestler : t.getMembers()) {
            query.prepare("INSERT INTO TeamMembers (team_id, wrestler_id) VALUES (:team_id, :wrestler_id)");
            query.bindValue(":team_id", teamId);
            query.bindValue(":wrestler_id", wrestler->getID());

            if (!query.exec()) {
                qDebug() << "Error inserting team member: " << query.lastError().text();
                query.exec("ROLLBACK");  // Rollback if a member insert fails
                return;
            }
        }
    }

    // Commit the transaction after all operations succeed
    if (!query.exec("COMMIT")) {
        qDebug() << "Error committing transaction: " << query.lastError().text();
        query.exec("ROLLBACK");  // Rollback if the commit fails
        return;
    }

    qDebug() << "Teams and team members saved successfully.";
}

// Save Rivalries
void GameDataManager::saveRivalries(QList<rivalry*>& rivalries) {
    if (rivalries.isEmpty()) {
        qDebug() << "No rivalries to save.";
        return;
    }

    QSqlQuery query;

    // Start a transaction
    if (!query.exec("BEGIN TRANSACTION")) {
        qDebug() << "Error starting transaction: " << query.lastError().text();
        return;
    }

    // Clear existing rivalries
    query.exec("DELETE FROM Rivalries");

    // Insert rivalries
    for (rivalry* rivalry : rivalries) {
        query.prepare("INSERT INTO Rivalries (wrestler1_id, wrestler2_id, bonusWeeks, penaltyWeeks, status) "
                      "VALUES (:wrestler1_id, :wrestler2_id, :bonusWeeks, :penaltyWeeks, :status)");
        query.bindValue(":wrestler1_id", rivalry->getWrestler1()->getID());  // Get wrestler ID using getId()
        query.bindValue(":wrestler2_id", rivalry->getWrestler2()->getID());  // Get wrestler ID using getId()
        query.bindValue(":bonusWeeks", rivalry->getWeeksLeft());  // The bonus weeks for the rivalry
        query.bindValue(":penaltyWeeks", rivalry->getPenaltyWeeksLeft());  // The penalty weeks for the rivalry
        query.bindValue(":status", rivalry->getStatus());  // Status of the rivalry

        if (!query.exec()) {
            qDebug() << "Error inserting rivalry: " << query.lastError().text();
            query.exec("ROLLBACK");
            return;
        }
    }

    // Commit the transaction
    if (!query.exec("COMMIT")) {
        qDebug() << "Error committing transaction: " << query.lastError().text();
        query.exec("ROLLBACK");
        return;
    }

    qDebug() << "Rivalries saved successfully.";
}

// Save Game Info
void GameDataManager::saveGameInfo(int money, int fans, int year, int currentWeek,
                                   QList<int> &moneyHistory, QList<int> &fanHistory, bool darkMode) {

    // Ensure database connection is open
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    // Delete any existing game info
    QSqlQuery query;
    if (!query.exec("DELETE FROM GameInfo")) {
        qDebug() << "Error deleting previous game info: " << query.lastError().text();
        return;  // Exit if delete fails
    }

    // Convert the QList<int> to a QStringList
    QStringList moneyHistStrList;
    for (int i : moneyHistory) {
        moneyHistStrList.append(QString::number(i));
    }
    QString moneyHistStr = moneyHistStrList.join(",");
    if (moneyHistStr.isEmpty()) {
        moneyHistStr = "0";  // Set default if history is empty
    }

    QStringList fanHistStrList;
    for (int i : fanHistory) {
        fanHistStrList.append(QString::number(i));
    }
    QString fanHistStr = fanHistStrList.join(",");
    if (fanHistStr.isEmpty()) {
        fanHistStr = "0";  // Set default if history is empty
    }

    // Prepare and execute the insert query
    query.prepare("INSERT INTO GameInfo (money, fans, year, currentWeek, moneyHistory, fanHistory, darkMode) "
                  "VALUES (:money, :fans, :year, :currentWeek, :moneyHistory, :fanHistory, :darkMode)");
    query.bindValue(":money", money);
    query.bindValue(":fans", fans);
    query.bindValue(":year", year);
    query.bindValue(":currentWeek", currentWeek);
    query.bindValue(":moneyHistory", moneyHistStr);
    query.bindValue(":fanHistory", fanHistStr);
    query.bindValue(":darkMode", darkMode);
    if (!query.exec()) {
        qDebug() << "Error executing insert query: " << query.lastError().text();
        return;  // Exit if insert fails
    }
}


// Save Show
void GameDataManager::saveShow(show &currentShow) {
    // Start a transaction to ensure data consistency (if your DB supports transactions)
    QSqlDatabase::database().transaction();

    // Save the show data to the "Shows" table
    QSqlQuery query;

    // Clear data already in the tables
    query.exec("DELETE FROM Show");
    query.exec("DELETE FROM Matches");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Show'");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Matches'");

    query.prepare("INSERT INTO Show (showRating, totalRevenue, totalCosts, showProfit, fanImpact, showType) "
                  "VALUES (:showRating, :totalRevenue, :totalCosts, :showProfit, :fanImpact, :showType)");

    query.bindValue(":showRating", currentShow.getShowRating());
    query.bindValue(":totalRevenue", currentShow.getTotalRevenue());
    query.bindValue(":totalCosts", currentShow.getTotalCosts());
    query.bindValue(":showProfit", currentShow.getShowProfit());
    query.bindValue(":fanImpact", currentShow.getFanImpact());
    query.bindValue(":showType", currentShow.getShowType());

    if (!query.exec()) {
        qDebug() << "Error saving show data: " << query.lastError().text();
        QSqlDatabase::database().rollback(); // Rollback if there is an error
        return;
    }

    // Get the last inserted show ID (auto-incremented)
    int showId = query.lastInsertId().toInt();

    // Save the matches data for the show
    for (const match &match : currentShow.getMatches()) {
        // Serialize the participants list into a comma-separated string
        QString matchParticipantsString;
        for (Wrestler* wrestler : match.getParticipants()) {
            matchParticipantsString.append(QString::number(wrestler->getID()) + ",");
        }
        if (!matchParticipantsString.isEmpty()) {
            matchParticipantsString.chop(1);  // Remove trailing comma
        }

        // Save each match to the "Matches" table
        query.prepare("INSERT INTO Matches (show_id, matchType, participants, teams, rating, winner_id, championship, finances) "
                      "VALUES (:show_id, :matchType, :participants, :teams, :rating, :winner_id, :championship, :finances)");

        query.bindValue(":show_id", showId);
        query.bindValue(":matchType", match.getMatchType());
        query.bindValue(":participants", matchParticipantsString);  // Store participants as CSV
        query.bindValue(":teams", match.isTeam());
        query.bindValue(":rating", match.getRating());
        query.bindValue(":winner_id", match.getWinner() ? match.getWinner()->getID() : QVariant());
        query.bindValue(":championship", match.isChampionship());
        query.bindValue(":finances", match.getFinances());

        if (!query.exec()) {
            qDebug() << "Error saving match data: " << query.lastError().text();
            QSqlDatabase::database().rollback();
            return;
        }
    }

    // Commit the transaction if everything went well
    QSqlDatabase::database().commit();
}

void GameDataManager::loadWrestlers() {
    m_wrestlers.clear();
    QSqlQuery query("SELECT * FROM Wrestlers");

    if (query.exec()) {
        while (query.next()) {
            Wrestler* wrestler = new Wrestler();
            wrestler->setID(query.value("id").toInt());
            wrestler->setName(query.value("name").toString());
            wrestler->setGender(query.value("gender").toBool());
            wrestler->setPopularity(query.value("popularity").toInt());
            wrestler->setAge(query.value("age").toInt());
            wrestler->setPotential(query.value("potential").toInt());
            wrestler->setPowerhouse(query.value("powerhouse").toInt());
            wrestler->setBrawler(query.value("brawler").toInt());
            wrestler->setHighFlyer(query.value("highFlyer").toInt());
            wrestler->setTechnician(query.value("technician").toInt());
            wrestler->setMMA(query.value("mma").toInt());
            wrestler->setCharisma(query.value("charisma").toInt());
            wrestler->setStamina(query.value("stamina").toInt());
            wrestler->setRole(query.value("role").toInt());
            wrestler->setHealth(query.value("health").toInt());
            wrestler->setInjury(query.value("injury").toInt());

            wrestler->clearContractSegments(); // ensure contract segments are cleared

            // Now load contract segments
            QSqlQuery contractQuery;
            contractQuery.prepare("SELECT matchesRemaining, salaryPerMatch FROM Contracts WHERE wrestler_id = :wrestler_id");
            contractQuery.bindValue(":wrestler_id", wrestler->getID());
            if (contractQuery.exec()) {
                while (contractQuery.next()) {
                    ContractSegment segment;
                    segment.matchesRemaining = contractQuery.value("matchesRemaining").toInt();
                    segment.salaryPerMatch = contractQuery.value("salaryPerMatch").toInt();
                    wrestler->addContractSegment(segment); // you should have a method like this
                }
            }

            m_wrestlers.append(wrestler);
        }
    } else {
        qDebug() << "Error loading wrestlers: " << query.lastError().text();
    }
}

void GameDataManager::loadChampionships() {
    QSqlQuery query("SELECT * FROM Championships");

    if (query.exec()) {
        while (query.next()) {
            QString titleName = query.value("titleName").toString();
            bool isTagTitle = query.value("isTagTitle").toBool();
            bool isWomensTitle = query.value("isWomensTitle").toBool();
            int champion1_id = query.value("champion1_id").toInt();
            int champion2_id = query.value("champion2_id").toInt();

            // Fetch wrestlers for championship
            Wrestler* champion1 = nullptr;
            Wrestler* champion2 = nullptr;

            // Load champion1
            if (champion1_id > 0) {
                champion1 = findWrestlerById(champion1_id);
                if (!champion1) {
                    qDebug() << "Warning: Wrestler ID" << champion1_id << "not found!";
                }
            }

            // Load champion2 (for tag championships)
            if (champion2_id > 0) {
                champion2 = findWrestlerById(champion2_id);
                if (!champion2) {
                    qDebug() << "Warning: Wrestler ID" << champion2_id << "not found!";
                }
            }

            // Create and set up the championship object
            championship newChampionship;
            newChampionship.setTitleName(titleName);
            newChampionship.setTag(isTagTitle);
            newChampionship.setWoman(isWomensTitle);

            if (isTagTitle) {
                newChampionship.setChampions({champion1, champion2});
            } else if (isWomensTitle) {
                newChampionship.setChampions({champion1});
            } else {
                newChampionship.setChampions({champion1});
            }

            // Add the new championship to the list
            m_championships.append(newChampionship);
        }
    } else {
        qDebug() << "Error loading championships: " << query.lastError().text();
    }
}

void GameDataManager::loadTeams(QList<team> &teams) {
    teams.clear(); // Always good to clear before loading
    QSqlQuery query("SELECT * FROM Teams");

    if (!query.exec()) {
        qDebug() << "Error loading teams:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        team t;
        int teamId = query.value("id").toInt();
        QString teamName = query.value("team_name").toString();
        t.setTeamName(teamName);

        QSqlQuery queryMembers;
        queryMembers.prepare("SELECT wrestler_id FROM TeamMembers WHERE team_id = :teamId");
        queryMembers.bindValue(":teamId", teamId);

        if (queryMembers.exec()) {
            int memberCount = 0;
            while (queryMembers.next()) {
                int wrestlerId = queryMembers.value("wrestler_id").toInt();

                Wrestler* w = findWrestlerById(wrestlerId);
                if (w) {
                    t.addMember(w);
                    memberCount++;
                }
            }
        } else {
            qDebug() << "Error loading team members:" << queryMembers.lastError().text();
        }

        teams.append(t);
    }
}


void GameDataManager::loadRivalries(QList<rivalry*>& rivalries) {
    // Clean up any existing rivalries first
    for (rivalry* r : rivalries) {
        delete r;
    }
    rivalries.clear();

    QSqlQuery query("SELECT * FROM Rivalries");

    if (query.exec()) {
        while (query.next()) {
            int wrestler1Id = query.value("wrestler1_id").toInt();
            int wrestler2Id = query.value("wrestler2_id").toInt();
            int bonusWeeks = query.value("bonusWeeks").toInt();
            int penaltyWeeks = query.value("penaltyWeeks").toInt();
            int status = query.value("status").toInt();

            Wrestler* wrestler1 = findWrestlerById(wrestler1Id);
            Wrestler* wrestler2 = findWrestlerById(wrestler2Id);

            if (wrestler1 && wrestler2) {
                rivalry* newRivalry = new rivalry(wrestler1, wrestler2, bonusWeeks, penaltyWeeks);
                newRivalry->setStatus(status);
                rivalries.append(newRivalry);  // Append pointer, not dereferenced object
            } else {
                qDebug() << "Error: Could not find wrestlers for rivalry.";
            }
        }
    } else {
        qDebug() << "Error loading rivalries: " << query.lastError().text();
    }
}


void GameDataManager::loadGameInfo(int &money, int &fans, int &year, int &currentWeek,
                                   QList<int> &moneyHistory, QList<int> &fanHistory,
                                   bool &darkMode) {
    QSqlQuery query("SELECT * FROM GameInfo WHERE id = 1");

    if (query.exec() && query.next()) {
        money = query.value("money").toInt();
        fans = query.value("fans").toInt();
        year = query.value("year").toInt();
        currentWeek = query.value("currentWeek").toInt();

        // Load money history
        QStringList moneyHistStrList = query.value("moneyHistory").toString().split(",");
        for (const QString &str : moneyHistStrList) {
            moneyHistory.append(str.toInt());
        }

        // Load fan history
        QStringList fanHistStrList = query.value("fanHistory").toString().split(",");
        for (const QString &str : fanHistStrList) {
            fanHistory.append(str.toInt());
        }
        // Load Dark mode settings
        darkMode = query.value("darkMode").toBool();
    } else {
        qDebug() << "Error loading game info: " << query.lastError().text();
    }
    qDebug() << "game info loaded";
}

void GameDataManager::loadShow(show &currentShow) {
    QSqlQuery query("SELECT * FROM Show ORDER BY id DESC LIMIT 1"); // Load the most recent show

    if (query.exec() && query.next()) {
        currentShow.setShowRating(query.value("showRating").toInt());
        currentShow.setTotalRevenue(query.value("totalRevenue").toInt());
        currentShow.setTotalCosts(query.value("totalCosts").toInt());
        currentShow.setShowProfit(query.value("showProfit").toInt());
        currentShow.setFanImpact(query.value("fanImpact").toInt());
        currentShow.setShowType(query.value("showType").toInt());

        int showId = query.value("id").toInt();

        // Load matches for the show
        QSqlQuery matchQuery;
        matchQuery.prepare("SELECT * FROM Matches WHERE show_id = :show_id");
        matchQuery.bindValue(":show_id", showId);

        if (matchQuery.exec()) {
            while (matchQuery.next()) {
                match m;
                m.setMatchType(matchQuery.value("matchType").toString());
                m.setTag(matchQuery.value("teams").toBool());
                m.setMatchRating(matchQuery.value("rating").toFloat());
                m.setFinances(matchQuery.value("finances").toInt());

                // Load participants
                QStringList participantIds = matchQuery.value("participants").toString().split(",");
                QList<Wrestler*> participants;
                for (const QString &id : participantIds) {
                    Wrestler* wrestler = findWrestlerById(id.toInt());
                    if (wrestler) {
                        participants.append(wrestler);
                    }
                }
                m.setParticipants(participants);

                // Load winner
                int winnerId = matchQuery.value("winner_id").toInt();
                if (winnerId > 0) {
                    Wrestler* winner = findWrestlerById(winnerId);
                    m.setWinner(winner);
                }

                m.setChampionship(matchQuery.value("championship").toBool());

                // Add match to the show
                currentShow.addMatch(m);
            }
        } else {
            qDebug() << "Error loading matches: " << matchQuery.lastError().text();
        }
    } else {
        qDebug() << "Error loading show data: " << query.lastError().text();
    }
}
Wrestler* GameDataManager::findWrestlerById(int wrestlerId) {
    for (Wrestler* wrestler : m_wrestlers) {
        if (wrestler->getID() == wrestlerId) {
            return wrestler;
        }
    }
    return nullptr;
}

void GameDataManager::loadDefaultRoster( const QString& defaultDbPath) {
    QString connName = "defaultRosterConn";

    QSqlDatabase defaultDb = QSqlDatabase::addDatabase("QSQLITE", connName);
    defaultDb.setDatabaseName(defaultDbPath);

    if (!defaultDb.open()) {
        qDebug() << "Failed to open default roster DB:" << defaultDb.lastError().text();
        return;
    }
    //qDebug() << "Attempting to open default DB at:" << QFileInfo(defaultDbPath).absoluteFilePath();

    loadDefaultWrestlers(defaultDb); // Load using this connection

    defaultDb.close();
    QSqlDatabase::removeDatabase(connName); // Clean up!
}
void GameDataManager::loadDefaultWrestlers(QSqlDatabase db) {
    m_wrestlers.clear(); // Ensure list is empty before loading
    QSqlQuery query(db); // Use the passed-in database

    if (query.exec("SELECT * FROM Wrestlers")) {
        while (query.next()) {
            Wrestler* wrestler = new Wrestler();
            wrestler->setName(query.value("name").toString());
            wrestler->setGender(query.value("gender").toBool());
            wrestler->setPopularity(query.value("popularity").toInt());
            wrestler->setAge(query.value("age").toInt());
            wrestler->setPotential(query.value("potential").toInt());
            wrestler->setPowerhouse(query.value("powerhouse").toInt());
            wrestler->setBrawler(query.value("brawler").toInt());
            wrestler->setHighFlyer(query.value("highFlyer").toInt());
            wrestler->setTechnician(query.value("technician").toInt());
            wrestler->setMMA(query.value("mma").toInt());
            wrestler->setCharisma(query.value("charisma").toInt());
            wrestler->setStamina(query.value("stamina").toInt());
            wrestler->setSalary(query.value("salary").toInt());
            wrestler->setRole(query.value("role").toInt());
            wrestler->setHealth(query.value("health").toInt());
            wrestler->setInjury(query.value("injury").toInt());
            wrestler->setWeeks(query.value("weeksOnContract").toInt());

            m_wrestlers.append(wrestler);
        }
    } else {
        qDebug() << "Error loading wrestlers: " << query.lastError().text();
    }

    qDebug() << "Total wrestlers loaded:" << m_wrestlers.size();
}


void GameDataManager::clearDatabase() {
    QSqlQuery query;

    // Delete all records from the tables
    query.exec("DELETE FROM Wrestlers;");
    query.exec("DELETE FROM Championships;");
    query.exec("DELETE FROM Teams;");
    query.exec("DELETE FROM GameInfo;");
    query.exec("DELETE FROM Show;");
    query.exec("DELETE FROM Matches;");

    // Reset auto-increment for each table (if using AUTOINCREMENT)
    query.exec("DELETE FROM sqlite_sequence WHERE name='Wrestlers';");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Championships';");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Teams';");
    query.exec("DELETE FROM sqlite_sequence WHERE name='GameInfo';");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Show';");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Matches';");

}

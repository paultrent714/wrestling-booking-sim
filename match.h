#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QList>
#include <QtGlobal> // for QRand

#include "randomUtilities.h"
#include "wrestler.h"
#include "championship.h"

class match
{
public:

    match();
    match(QString type, bool hasTeams);
    match(const QString &matchType, const QList<Wrestler*> &participants, bool teams,
          float rating, Wrestler* winner, bool championship, int finances)
        : m_matchType(matchType), m_participants(participants), m_teams(teams),
        m_rating(rating), m_winner(winner), m_championship(championship), m_finances(finances) {}

    void addWrestler(Wrestler* wrestler);// Add a wrestler to the match
    void removeWrestler(int index); // Removes wrestler from match

    void setParticipants(QList<Wrestler*> &wrestlerList) { m_participants = wrestlerList;}
    void setMatchRating(float rating) {m_rating = rating; }
    void setMatchType(QString type) { m_matchType = type; }
    void setWinner(Wrestler* winner) { m_winner = winner; }    // Decide a winner (random or user-defined)
    void setChampionship(bool title) { m_championship = title; }    // Whether it is a title match
    void setTag(bool teams) { m_teams = teams; }    // Whether there are teams in a match
    void setFinances(int cost) {m_finances = cost; }
    void decideWinner(QList<Wrestler*> participants);   // Decides winner of match
    Wrestler* randomWinner() const;   // Random winner based off popularity

    void calcMatchRating(QList<Wrestler*> participants);  // Determines match quality based on participants skills, 1-5 *
    QStringList getAvailableMatchTypes();

    void clearParticipants() { m_participants.clear(); }   // Empties list of participents

    void applyTitleChange(championship* title);

    // Getters for the match details
    QString getMatchType() const { return m_matchType; }
    QList<Wrestler*> getParticipants() const { return m_participants;}
    float getRating() const { return m_rating; }
    Wrestler* getWinner() const { return m_winner; }
    bool isChampionship() const { return m_championship; }
    bool isTeam() const { return m_teams; }
    int getFinances() const { return m_finances; }
    QMap<Wrestler*, QMap<QString, int>> getAttributeChanges() const {
        return m_attributeChanges;
    }


    bool isValidMatch() const;  // Method to check if match is valid (correct number of wrestlers)
    void calculateHealthLoss ( Wrestler* wrestler) ;    // calculates health lost by wrestler in a match
    void determineInjuryDuration ( Wrestler* wrestler);

    int matchTypeDamage(); // determines base health loss of a match type

    void applyAttributeGains();        // calculates change in attributes for all participants of a match
    int calculateAttributeGain(int current, int potential);
    int calculatePopularityGain(Wrestler* w);

private:
    QString m_matchType;
    QList<Wrestler*> m_participants; // Who is competing
    QMap<Wrestler*, QMap<QString, int>> m_attributeChanges;  // wrestler -> {attributeName -> changeAmount}

    bool m_teams; // True if the match has teams
    float m_rating;  // Rating from 0 to 5 stars
    Wrestler* m_winner = NULL; // User can choose who wins
    bool m_championship; // Whether the match is for a championship

    int m_finances;   // cost of the match

};

#endif // MATCH_H

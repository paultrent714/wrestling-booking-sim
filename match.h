#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QList>

#include "randomUtilities.h"
#include "wrestler.h"

class match
{
public:


    match();
    match(QString type, bool hasTeams);
    QStringList getAvailableMatchTypes();

    void setMatchType(QString type);
    void setWinner(QString winner);    // Decide a winner (random or user-defined)
    void setChampionship(bool title) { m_championship = title; }    // Whether it is a title match
    void setTag(bool teams) { m_teams = teams; }    // Whether there are teams in a match



    void addWrestler(Wrestler* wrestler);// Add a wrestler to the match
    void removeWrestler(int index); // Removes wrestler from match
    void setMatchRating(QList<Wrestler*> participants);  // Determines match quality based on participants skills, 1-5 *

    void decideWinner(QList<Wrestler*> participants);   // Decides winner of match
    QString randomWinner() const;   // Random winner based off popularity

    void clearParticipants() { m_participants.clear(); }   // Empties list of participents


    // Getters for the match details
    QString getMatchType() const { return m_matchType; }
    QList<Wrestler*> getParticipants() const { return m_participants;}
    float getRating() const { return m_rating; }
    QString getWinner() const { return m_winner; }
    bool isChampionship() const { return m_championship; }
    bool isTeam() const { return m_teams; }

    // Method to check if match is valid (correct number of wrestlers)
    bool isValidMatch() const;

private:
    QString m_matchType;
    QList<Wrestler*> m_participants; // Who is competing
    bool m_teams; // True if the match has teams
    float m_rating;  // Rating from 1 to 5 stars
    QString m_winner = "random"; // User can choose who wins
    bool m_championship; // Whether the match is for a championship

    int finances;   // Financial impact of the match

};

#endif // MATCH_H

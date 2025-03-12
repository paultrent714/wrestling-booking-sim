#ifndef TEAM_H
#define TEAM_H

#include "wrestler.h"
#include <QString>
#include <QList>


class team
{
public:
    team();
    team(QString teamName, QList<Wrestler*> members);

    QString getTeamName() const { return m_teamName; }
    QList<Wrestler*> getMembers() const { return m_members; }
    Wrestler* getAtIndex(int index) { return m_members[index]; }    // Return the wrestler at given index

    bool containsWrestler(Wrestler* wrestler) const;    // Whether wrestler is included in m_members

    QList<Wrestler*> getDefaultTagTeam() const; // Returns first 2 members

    void setTeamName(QString name){ m_teamName = name; }

    void addMember(Wrestler* wrestler);
    void removeMember(Wrestler* wrestler);

    void clearWrestlers() { m_members.clear(); }

private:
    QString m_teamName;
    QList<Wrestler*> m_members;
};

#endif // TEAM_H

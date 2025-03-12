#include "team.h"
team::team(){
    m_teamName = "";
    m_members = {};
}

team::team(QString teamName, QList<Wrestler*> members)
    : m_teamName(teamName), m_members(members) {}

bool team::containsWrestler(Wrestler* wrestler) const {
    return m_members.contains(wrestler);
}

QList<Wrestler*> team::getDefaultTagTeam() const {
    if (m_members.size() >= 2) {
        return {m_members[0], m_members[1]};  // Select first two members
    }
    return {}; // If less than 2 members, return an empty list
}

void team::addMember(Wrestler* wrestler) {
    if (!m_members.contains(wrestler)) {
        m_members.append(wrestler);
    }
}

void team::removeMember(Wrestler* wrestler) {
    m_members.removeAll(wrestler);
}

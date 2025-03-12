#include "championship.h"

// default
championship::championship() {
    m_titleName = "Generic Belt";
}

championship::championship(QString beltName) {
    m_titleName = beltName;
    //m_champions = nullptr;
}

championship::championship(QString titleName, bool isTag, bool isWomen)
    : m_titleName(titleName), m_isTagTitle(isTag), m_isWomensTitle(isWomen) {}

void championship::setChampions( const QList<Wrestler*>& champions ){
    if (isValidChampions(champions)) {
        m_champions = champions;
    }
}

bool championship::isValidChampions(QList<Wrestler*> champions)  {
    if (m_isTagTitle) {
        return champions.size() == 2;  // Tag titles require exactly 2 wrestlers
    }
    if (m_isWomensTitle) {
        return champions.size() == 1 && champions[0]->getGender() == 1;  // Women's title must be held by a woman
    }
    return champions.size() == 1;  // Default: title needs exactly 1 champion
}


void championship::setTagTeamChampions(team* tagTeam) {
    if (m_isTagTitle) {
        QList<Wrestler*> team = tagTeam->getDefaultTagTeam();
        if (team.size() == 2) {
            m_champions = team;
        }
    }
}

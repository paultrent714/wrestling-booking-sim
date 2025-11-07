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
    m_champions.clear();

    // Ensure only valid wrestlers are added
    for (Wrestler* champ : champions) {
        if (champ) {  // Check if not nullptr
            m_champions.append(champ);
        }
    }

    if (!isValidChampions(m_champions)) {
        m_champions.clear();  // Reset champions if invalid
    }
}

bool championship::isValidChampions(QList<Wrestler*> champions)  {
    if (m_isTagTitle) {
        return champions.size() == 2;  // Tag titles require exactly 2 wrestlers
    }
    if (m_isWomensTitle) {
        return champions.size() == 1 && champions[0]->isFemale() == 1;  // Women's title must be held by a woman
    }
    return champions.size() == 1;  // Default: title needs exactly 1 champion
}

Wrestler* championship::getChampion() {
    if (m_champions.isEmpty()) {
        return nullptr;
    }
    return m_champions[0];
}

void championship::setTagTeamChampions(team* tagTeam) {
    if (m_isTagTitle) {
        QList<Wrestler*> team = tagTeam->getDefaultTagTeam();
        if (team.size() == 2) {
            m_champions = team;
        }
    }
}

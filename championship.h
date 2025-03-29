#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "wrestler.h"
#include "team.h"
#include <QString>


class championship
{
public:
    championship();
    championship(QString beltName);
    championship(QString titleName, bool isTag, bool isWomen);

    void setTitleName(QString name) { m_titleName = name; }
    void setChampions(const QList<Wrestler*>& champions);
    void setTagTeamChampions(team* tagTeam);  // Explicitly for tag team champions

    void setTag(bool selection) { m_isTagTitle = selection; }
    void setWoman(bool selection) { m_isWomensTitle = selection; }

    bool isTagTitle() const { return m_isTagTitle; }
    bool isWomensTitle() const { return m_isWomensTitle; }
    bool isValidChampions (QList<Wrestler*> champions) ;

    QList<Wrestler*> getChampions()  { return m_champions; }
    Wrestler* getChampion() ;      // For singles championships
    QString getTitleName() const { return m_titleName; }

private:
    QString m_titleName; // name of the championship
    bool m_isTagTitle;    // True if this is a tag team championship
    bool m_isWomensTitle; // True if this title is exclusive to female wrestlers
    QList<Wrestler*> m_champions; // Stores 0 (vacant), 1 (singles), or 2 (tag team) wrestlers
};

#endif // CHAMPIONSHIP_H

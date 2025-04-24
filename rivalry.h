#ifndef RIVALRY_H
#define RIVALRY_H

#include "wrestler.h"

class rivalry
{
public:

    rivalry(Wrestler* w1, Wrestler* w2, int bonusWeeks = 4, int penaltyWeeks = 4);

    Wrestler* getWrestler1() const { return m_wrestler1;}
    Wrestler* getWrestler2() const { return m_wrestler2;}
    int getStatus() const { return m_status;}
    int getWeeksLeft() const { return m_weeksRemaining;}
    int getPenaltyWeeksLeft() const { return m_penaltyWeeksRemaining;}

    void advanceWeek(); // Call this once per in-game week

    bool involves(Wrestler* wrestler) const;
    bool matchesPair(Wrestler* w1, Wrestler* w2) const;

    void setStatus(int s) { m_status = s; }
    void setWeeksRemaining(int b) { m_weeksRemaining = b;}
    void setPenaltyWeeksRemaining( int p ) { m_penaltyWeeksRemaining = p;}

private:
    Wrestler* m_wrestler1;
    Wrestler* m_wrestler2;
    int m_weeksRemaining;   // number of weeks for rivalry to boost matches
    int m_status;   // 2 for rivalry currently giving bonus, 1 for rivalry in cooldown, 0 for rivalry about to be deleted
    int m_penaltyWeeksRemaining;    // number of weeks for rivalry penalty to go away
};


#endif // RIVALRY_H

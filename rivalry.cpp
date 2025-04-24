#include "rivalry.h"


rivalry::rivalry(Wrestler* w1, Wrestler* w2, int bonusWeeks, int penaltyWeeks)
    : m_wrestler1(w1), m_wrestler2(w2),
    m_weeksRemaining(bonusWeeks),
    m_status(2),
    m_penaltyWeeksRemaining(penaltyWeeks) {}


void rivalry::advanceWeek() {
    if (m_status == 2) {
        --m_weeksRemaining;
        if (m_weeksRemaining <= 0) {
            m_status = 1;
            m_weeksRemaining = m_penaltyWeeksRemaining;
        }
    } else if (m_status == 1) {
        --m_weeksRemaining;
        if (m_weeksRemaining <= 0) {
            m_status = 0;
        }
    }
}

bool rivalry::involves(Wrestler* wrestler) const {
    return wrestler == m_wrestler1 || wrestler == m_wrestler2;
}

bool rivalry::matchesPair(Wrestler* w1, Wrestler* w2) const {
    return (w1 == m_wrestler1 && w2 == m_wrestler2) || (w1 == m_wrestler2 && w2 == m_wrestler1);
}

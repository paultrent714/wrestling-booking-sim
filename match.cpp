#include "match.h"

match::match() {
    m_matchType = "Standard";
    m_teams = false;
    m_rating = 0;
    m_winner = NULL;
    m_participants.clear();

    finances = 0;

}

// Constructor
match::match(QString type, bool hasTeams)
    : m_matchType(type), m_rating(0), m_teams(hasTeams)
{

}

// Add a wrestler to the match
void match::addWrestler (Wrestler* wrestler)
{
    m_participants.append(wrestler);
}
void match::removeWrestler(int index) {
    if (index >= 0 && index < m_participants.size()) {
        m_participants.removeAt(index);
    }
}

void match::setMatchType(QString type){
    m_matchType = type;
}
void match::setWinner(QString winner){
    m_winner = winner;
}

// Select winner based on popularity
QString match::randomWinner() const
{
    // Initialize random generator
    std::mt19937& gen = RandomUtils::getGenerator();

    // Create a normal distribution with mean = 60 and stddev = 15 for popularity
    std::normal_distribution<> dist(60, 15);

    // Sum the popularity of all participants
    int totalPopularity = 0;
    for (auto* wrestler : m_participants) {
        totalPopularity += wrestler->getPopularity();  // Sum up all participants' popularity
    }

    // Generate a random winner based on their popularity
    int randomValue = std::round(dist(gen));  // Generate a random value based on normal distribution

    // Normalize it within the totalPopularity range
    int accumulatedPopularity = 0;
    for (auto* wrestler : m_participants) {
        accumulatedPopularity += wrestler->getPopularity();
        if (accumulatedPopularity > randomValue) {
            return wrestler->getName();  // Return the winner's name
        }
    }

    return "";  // This should not happen
}

QStringList match::getAvailableMatchTypes() {

    // Return a list of predefined match types
    return QStringList{"Standard", "Ladder", "Hardcore", "Steel Cage", "Battle Royal"};
}

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

void match::setMatchRating(QList<Wrestler*> participants) {
    if (participants.isEmpty()) {
        m_rating = 0.0; // Default low rating if no wrestlers
        return;
    }

    float totalSkill = 0;
    for (Wrestler* wrestler : participants) {
        float wrestlerSkill = (wrestler->getBrawler() + wrestler->getPowerhouse() +
                               wrestler->getMMA() + wrestler->getHighFlyer() +
                               wrestler->getTechnician()) / 5.0;
        totalSkill += wrestlerSkill;
    }

    float avgSkill = totalSkill / participants.size();

    // Normalize skill to a rating between 1 and 5
    float baseRating = (avgSkill / 100.0) * 5.0;

    // Introduce randomness (±0.5)
    std::uniform_real_distribution<float> randomDist(-0.5, 0.5);
    float randomness = randomDist(RandomUtils::getGenerator());

    baseRating += randomness;

    /*
    // Apply Feud Boost if applicable
    if (m_feud) {
        baseRating += (m_feud->getIntensity() * 0.1);
    }*/

    // Ensure the rating stays between 1 and 5
    if (baseRating < 0.0) baseRating = 0.0;
    if (baseRating > 5.0) baseRating = 5.0;

    m_rating = baseRating;
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

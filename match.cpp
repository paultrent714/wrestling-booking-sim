#include "match.h"

match::match() {
    m_matchType = "Standard";
    m_teams = false;
    m_rating = 0;
    m_winner = NULL;
    m_participants.clear();

    m_finances = 0;

}

// Constructor
match::match(QString type, bool hasTeams)
    : m_matchType(type), m_rating(0), m_teams(hasTeams)
{

}

// Add a wrestler to the match
void match::addWrestler (Wrestler* wrestler)
{
    // For simplicity sake, match can have at most 10 people
    if (m_participants.size() < 10 &&
        wrestler && !m_participants.contains(wrestler)) {
        m_participants.append(wrestler);
    }
}
void match::removeWrestler(int index) {
    if (index >= 0 && index < m_participants.size()) {
        m_participants.removeAt(index);
    }
}

void match::calcMatchRating(QList<Wrestler*> participants) {
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
Wrestler* match::randomWinner() const
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
            return wrestler;  // Return the winner's name
        }
    }

    return NULL;  // This should not happen
}

QStringList match::getAvailableMatchTypes() {

    // Return a list of predefined match types
    return QStringList{"Standard", "Ladder", "Hardcore", "Steel Cage", "Battle Royal"};
}
void match::applyTitleChange(championship* championship)
{
    // Check if it's a singles championship
    if (championship->getChampions().size() == 1) {
        Wrestler* currentChampion = championship->getChampions().first();

        // If the champion is in the match or if there is no champion (Vacant), update it
        if (!currentChampion || m_participants.contains(currentChampion)) {
            if (m_participants.contains(m_winner)) {
                championship->setChampions({m_winner});
            }
        }
    }
    // Check if it's a tag team championship
    else if (championship->getChampions().size() == 2) {
        // If the match is a tag match and has at least one tag team champion in the participants list
        if (m_teams && m_participants.size() == 4) {  // Example for tag team match, check if there are 4 participants
            bool isChampionInMatch = false;
            for (auto& champ : championship->getChampions()) {
                if (m_participants.contains(champ)) {
                    isChampionInMatch = true;
                    break;
                }
            }

            if (isChampionInMatch) {
                // If the winner is in one of the teams, set the team as the new champions
                int winnerIndex = m_participants.indexOf(m_winner);
                QList<Wrestler*> tagChampions;
                if (winnerIndex < m_participants.size() / 2) {  // First half of participants (team 1)
                    tagChampions = {m_participants[0], m_participants[1]};
                } else {  // Second half of participants (team 2)
                    tagChampions = {m_participants[2], m_participants[3]};
                }
                championship->setChampions(tagChampions);  // Set the tag team champions
            }
        }
    }

    // Check if it's a women's championship
    else if (championship->isWomensTitle()) {
        if (m_winner->getGender() == 1) {  // Ensure the winner is a woman (1 represents female)
            QList<Wrestler*> newChampion = {m_winner};
            championship->setChampions(newChampion);  // Set the new champion (as a list of one)
        }
    }
}

void match::calculateHealthLoss( Wrestler& wrestler)  {
    int baseDamage = matchTypeDamage();  // Function that returns damage based on match type
    int staminaFactor = std::max(1, 100 - wrestler.getStamina());  // Higher stamina = less damage

    int healthLoss = (baseDamage * staminaFactor) / 100; // Scale based on stamina
    healthLoss = std::clamp(healthLoss, 1, 50); // Ensures at least 1 health lost, max 50

    int newHealth = std::max(0, wrestler.getHealth() - healthLoss);  // Prevent negative health
    wrestler.setHealth(newHealth);
}

void match::determineInjuryDuration(Wrestler& wrestler) {
    int health = wrestler.getHealth();

    // Calculate normalized factor: 0 when health is 100, 1 when health is 0.
    double normalized = (100 - health) / 100.0;

    // Use a quadratic scaling for injury chance:
    // At full health: 5% chance, at 0 health: 90% chance.
    int injuryChance = static_cast<int>(5 + (90 - 5) * pow(normalized, 2));
    injuryChance = std::min(injuryChance, 90); // Cap at 90%

    int roll = rand() % 100; // Random number between 0 and 99
    // If injury occurs
    if (roll < injuryChance) {
        // Determine injury duration based on health.
        // Generate a duration between 1 and 12 weeks.
        // Use the normalized factor to bias the base duration.
        int baseDuration = 1 + static_cast<int>(11 * (1 - normalized));
        // Add a random offset between -1 and 1 to add variability.
        int randomOffset = (rand() % 3) - 1;
        int injuryDuration = std::clamp(baseDuration + randomOffset, 1, 12);

        wrestler.setInjury(injuryDuration);
    }
}

int  match::matchTypeDamage(){
    if (m_matchType == "Steel Cage") { return 15;}
    else if (m_matchType == "Ladder") { return 20; }
    else if (m_matchType == "Battle Royal") { return 25; }
    else if (m_matchType == "Squash") { return 5; }
    else { return 10; } // standard or wierd invalid match type
}



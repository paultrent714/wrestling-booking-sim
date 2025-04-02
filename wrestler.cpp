#include "wrestler.h"


#include <QDir>

Wrestler::Wrestler(){
    // Member variables (attributes)
    std::mt19937& gen = RandomUtils::getGenerator(); // Use shared generator

    std::normal_distribution<> dist(60, 15); // Mean = 60, Std Dev = 15
    std::normal_distribution<> ageDist(32, 11); // Keeps age of randomly generated wrestlers somewhere around 30
    std::uniform_int_distribution<> roleDist(0, 2);
    std::uniform_int_distribution<> genderDist(0, 1);

    std::uniform_int_distribution<> healthDist(40,99); // Don't want them to start at constant or low health

    this->m_gender = genderDist(gen);
    this->m_name = generateRandomName(gen).trimmed();

    this->m_popularity = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_age = std::clamp<int>(std::round(ageDist(gen)), 18, 67);

    this->m_powerhouse = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_brawler = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_highFlyer = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_technician = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_mma = std::clamp<int>(std::round(dist(gen)), 0, 99);

    // Calculate the sum of the individual attributes
    int sumOfAttributes = m_powerhouse + m_brawler + m_highFlyer + m_technician + m_mma;

    // Ensure potential is greater than the sum but not more than 99 * 5
    std::uniform_int_distribution<> potentialDist(sumOfAttributes + 1, 99 * 5);
    this->m_potential = potentialDist(gen);

    this->m_charisma = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_stamina = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_salary = calcSalary();
    this->m_role = roleDist(gen);
    this->m_health = healthDist(gen);
    this->m_injury = 0;     // Don't start injured
}
Wrestler::Wrestler(int id) {
    // Member variables (attributes)
    std::mt19937& gen = RandomUtils::getGenerator(); // Use shared generator

    std::normal_distribution<> dist(60, 15); // Mean = 60, Std Dev = 15

    std::normal_distribution<> ageDist(32, 11); // Keeps age of randomly generated wrestlers somewhere around 30

    std::uniform_int_distribution<> roleDist(0, 2);
    std::uniform_int_distribution<> genderDist(0, 1);

    std::uniform_int_distribution<> healthDist(40, 99); // Don't want them to start at constant or low health

    this->m_id = id;
    this->m_gender = genderDist(gen);
    this->m_name = generateRandomName(gen).trimmed();

    this->m_popularity = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_age = std::clamp<int>(std::round(ageDist(gen)), 18, 67);

    this->m_powerhouse = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_brawler = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_highFlyer = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_technician = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_mma = std::clamp<int>(std::round(dist(gen)), 0, 99);

    // Calculate the sum of the individual attributes
    int sumOfAttributes = m_powerhouse + m_brawler + m_highFlyer + m_technician + m_mma;

    // Ensure potential is greater than the sum but not more than 99 * 5
    std::uniform_int_distribution<> potentialDist(sumOfAttributes + 1, 99 * 5);
    this->m_potential = potentialDist(gen);

    this->m_charisma = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_stamina = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->m_salary = calcSalary();
    this->m_role = roleDist(gen);
    this->m_health = healthDist(gen);
    this->m_injury = 0;     // Don't start injured
}

void Wrestler::setName(const QString& n) {
    QString trimmedName = n.trimmed(); // Remove leading and trailing spaces

    if (trimmedName.isEmpty()) {
        return; // Do not set an empty name
    }
    m_name = trimmedName;
}

QString Wrestler::generateRandomName(std::mt19937& gen) {
    // Choose first name file based on m_gender
    QString firstNameFile = (m_gender == 0) ? "data/first_name_male.txt" : "data/first_name_female.txt";
    QStringList firstNames = loadNamesFromFile(firstNameFile);
    QStringList lastNames = loadNamesFromFile("data/last_name.txt");

    if (firstNames.isEmpty() ) {
        return "Nameless"; // Fallback if files are empty
    }

    std::uniform_int_distribution<> firstDist(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDist(0, lastNames.size() - 1);

    // For edge case if randomly generated name would end up as " "
    QString firstName, lastName;
    do {
        firstName = firstNames[firstDist(gen)].trimmed();
        lastName = lastNames[lastDist(gen)].trimmed();
    } while (firstName.isEmpty() && lastName.isEmpty()); // Regenerate if both are empty

    return firstNames[firstDist(gen)] + " " + lastNames[lastDist(gen)];
}

QStringList Wrestler::loadNamesFromFile(const QString& filename) {
    QStringList names;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filename;
        return names; // Return empty list if file cannot be opened
    }

    QTextStream in(&file);
    // This will load empty lines for the chance of wrestlers without first or last name
    while (!in.atEnd()) {
        QString line = in.readLine();
        names.append(line);
    }
    return names;
}
int Wrestler::calcSalary() const {
    const int minSalary = 500;   // Base pay per appearance
    const int maxSalary = 50000; // Max pay per appearance
    const int maxPopularity = 100; // Popularity is on a 0-100 scale

    // Calculate salary proportionally
    double scale = static_cast<double>(m_popularity) / maxPopularity;
    return static_cast<int>(minSalary + scale * (maxSalary - minSalary));
}


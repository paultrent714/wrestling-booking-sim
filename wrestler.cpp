#include "wrestler.h"


#include <QDir>

Wrestler::Wrestler(){

    // Member variables (attributes)

    std::mt19937& gen = RandomUtils::getGenerator(); // Use shared generator

    std::normal_distribution<> dist(60, 15); // Mean = 60, Std Dev = 15
    std::uniform_int_distribution<> ageDist(18, 67);
    std::uniform_int_distribution<> potentialDist(0, 499);
    std::uniform_int_distribution<> salaryDist(0, 999);
    std::uniform_int_distribution<> roleDist(0, 2);
    std::uniform_int_distribution<> genderDist(0, 2);

    this->name = generateRandomName(gen);
    this->gender = genderDist(gen);
    this->popularity = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->age = ageDist(gen);
    this->potential = potentialDist(gen);
    this->powerhouse = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->brawler = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->highFlyer = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->technician = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->mma = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->charisma = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->stamina = std::clamp<int>(std::round(dist(gen)), 0, 99);
    this->salary = salaryDist(gen) * 1000;
    this->role = roleDist(gen);
}

QString Wrestler::generateRandomName(std::mt19937& gen) {

    qDebug() << "Current working directory:" << QDir::currentPath();

    // Choose first name file based on gender
    QString firstNameFile = (gender == 0) ? "data/first_name_male.txt" : "data/first_name_female.txt";
    QStringList firstNames = loadNamesFromFile(firstNameFile);
    QStringList lastNames = loadNamesFromFile("data/last_name.txt");

    if (firstNames.isEmpty() ) {
        return "Nameless"; // Fallback if files are empty
    }

    std::uniform_int_distribution<> firstDist(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDist(0, lastNames.size() - 1);

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

    // Debugging output to check if names are being read
    qDebug() << "Loaded names from " << filename << ": " << names;
    return names;
}

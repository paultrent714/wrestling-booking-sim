#ifndef WRESTLER_H
#define WRESTLER_H

#include <QSqlDatabase>  // Include this for database connection
#include <QSqlQuery>     // Include this for running queries
#include <QSqlError>     // Include this for error handling
#include <QDebug>        // For debugging output
#include <QFile>
#include <QTextStream>
#include <QString>


#include "randomUtilities.h"

class Wrestler
{
public:
    // Default constructor
    Wrestler();

    // Constructor to initialize a Wrestler object
    Wrestler(QString name, bool gender, int popularity, int age, int potential, int powerhouse, int brawler,
             int highFlyer, int technician, int mma, int charisma, int stamina, int salary, int role)
        : name(name), popularity(popularity), age(age), potential(potential), powerhouse(powerhouse),
        brawler(brawler), highFlyer(highFlyer), technician(technician), mma(mma), charisma(charisma),
        stamina(stamina), salary(salary), role(role){}

    QString getName() const {return name; }
    bool getGender() const { return gender; }
    int getPopularity() const { return popularity; }
    int getAge() const { return age; }
    int getPotential() const { return potential; }
    int getPowerhouse() const { return powerhouse;}
    int getBrawler() const { return brawler; }
    int getHighFlyer() const { return highFlyer; }
    int getTechnician() const { return technician; }
    int getMMA() const { return mma; }
    int getCharisma() const { return charisma; }
    int getStamina() const { return stamina; }
    int getSalary() const { return salary; }
    int getRole() const { return role; }

    // member function to display wrestler info (for debugging)
    void displayInfo() const {
        qDebug() << name
                 << popularity
                 << age
                 << potential
                 << powerhouse
                 << brawler
                 << highFlyer
                 << technician
                 << mma
                 << charisma
                 << stamina
                 << salary
                 << role;
    }

private:
    // Member variables (attributes)
    QString name;
    bool gender; // 0  for men's division, 1 for women's
    int popularity, age, potential, powerhouse, brawler, highFlyer, technician, mma, charisma, stamina, salary;
    int role;   // 1 for bad, 2 for good, 0 for neutral




    QString generateRandomName(std::mt19937& gen);
    QStringList loadNamesFromFile(const QString& filename);

};

#endif // WRESTLER_H

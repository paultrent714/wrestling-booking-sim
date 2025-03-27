#ifndef WRESTLER_H
#define WRESTLER_H

#include <QSqlDatabase>  // Include this for database connection
#include <QSqlQuery>     // Include this for running queries
#include <QSqlError>     // Include this for error handling
#include <QDebug>        // For debugging output
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMetaType>     // used to store wrestler data in combo boxes

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

    // Getters
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

    // Setters
    void setName(const QString& n);
    void setGender(bool g) { gender = g; }
    void setPopularity(int p) { popularity = p; }
    void setAge(int a) { age = a; }
    void setPotential(int p) { potential = p; }
    void setPowerhouse(int p) { powerhouse = p; }
    void setBrawler(int b) { brawler = b; }
    void setHighFlyer(int h) { highFlyer = h; }
    void setTechnician(int t) { technician = t; }
    void setMMA(int m) { mma = m; }
    void setCharisma(int c) { charisma = c; }
    void setStamina(int s) { stamina = s; }
    void setSalary(int s) { salary = s; }
    void setRole(int r) { role = r; }


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
    int calcSalary() const;         // Calculates pay based on popularity

};

Q_DECLARE_METATYPE(Wrestler*)


#endif // WRESTLER_H

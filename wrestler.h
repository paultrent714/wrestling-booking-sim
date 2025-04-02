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
    Wrestler(int id, QString name, bool gender, int popularity, int age, int potential, int powerhouse, int brawler,
             int highFlyer, int technician, int mma, int charisma, int stamina, int salary, int role)
        : m_id(id), m_name(name), m_gender(gender), m_popularity(popularity), m_age(age), m_potential(potential), m_powerhouse(powerhouse),
        m_brawler(brawler), m_highFlyer(highFlyer), m_technician(technician), m_mma(mma), m_charisma(charisma),
        m_stamina(stamina), m_salary(salary), m_role(role){}

    Wrestler(int id);

    // Getters
    QString getName() const {return m_name; }
    int getID() const { return m_id; }
    bool getGender() const { return m_gender; }
    int getPopularity() const { return m_popularity; }
    int getAge() const { return m_age; }
    int getPotential() const { return m_potential; }
    int getPowerhouse() const { return m_powerhouse;}
    int getBrawler() const { return m_brawler; }
    int getHighFlyer() const { return m_highFlyer; }
    int getTechnician() const { return m_technician; }
    int getMMA() const { return m_mma; }
    int getCharisma() const { return m_charisma; }
    int getStamina() const { return m_stamina; }
    int getSalary() const { return m_salary; }
    int getRole() const { return m_role; }
    int getHealth() const { return m_health; }
    int getInjury() const { return m_injury; }

    // Setters
    void setName(const QString& n);
    void setID(int id) { m_id = id;}
    void setGender(bool g) { m_gender = g; }
    void setPopularity(int p) { m_popularity = p; }
    void setAge(int a) { m_age = a; }
    void setPotential(int p) { m_potential = p; }
    void setPowerhouse(int p) { m_powerhouse = p; }
    void setBrawler(int b) { m_brawler = b; }
    void setHighFlyer(int h) { m_highFlyer = h; }
    void setTechnician(int t) { m_technician = t; }
    void setMMA(int m) { m_mma = m; }
    void setCharisma(int c) { m_charisma = c; }
    void setStamina(int s) { m_stamina = s; }
    void setSalary(int s) { m_salary = s; }
    void setRole(int r) { m_role = r; }
    void setHealth( int h) { m_health = h; }
    void setInjury(int i) {m_injury = i; }

    void recoverHealth(int amount) { setHealth(m_health + amount); } // Called at week's end

    // member function to display wrestler info (for debugging)
    void displayInfo() const {
        qDebug() << m_name
                 << m_popularity
                 << m_age
                 << m_potential
                 << m_powerhouse
                 << m_brawler
                 << m_highFlyer
                 << m_technician
                 << m_mma
                 << m_charisma
                 << m_stamina
                 << m_salary
                 << m_role;
    }

private:
    // Member variables (attributes)
    int m_id;       // for storing in SQLite
    QString m_name;
    bool m_gender; // 0  for men's division, 1 for women's
    int m_popularity, m_age;
    int m_potential;    // max sum of the 5 match related traits
    // match related traits
    int m_powerhouse, m_brawler, m_highFlyer, m_technician, m_mma;
    int m_charisma, m_stamina, m_salary;
    int m_role;   // 1 for bad, 2 for good, 0 for neutral
    int m_health;   // Affects odds/ duration of injury
    int m_injury;   // Duration of wrestler's injury

    QString generateRandomName(std::mt19937& gen);
    QStringList loadNamesFromFile(const QString& filename);
    int calcSalary() const;         // Calculates pay based on popularity

};

Q_DECLARE_METATYPE(Wrestler*)


#endif // WRESTLER_H

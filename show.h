#ifndef SHOW_H
#define SHOW_H

#include <QString>
#include <QList>
#include "match.h"  // Include the Match class

class show
{
public:
    enum ShowType {
        Weekly,
        PVP // Pay-Per-View show
    };

    show();
    // Constructor for the Show class
    show(ShowType type);

    void clear();

    // Methods to add matches, calculate and get show data
    void addMatch(const match &m);  // Add match to the show
    void removeMatch(int matchIndex);

    void calculateShowRating();  // Calculate the average show rating
    void calculateShowRevenue(int totalFans); // Calculate revenue based on show rating and fans.
    void calculateCosts();  // Calculate costs for show
    void calculateFanImpact(int totalFans);   // Calculate the total fan impact

    // Getters for the show data
    int getShowRating() const { return showRating; }
    int getTotalCosts() const { return totalCosts; }
    int getTotalRevenue() const { return totalRevenue; }
    int getFanImpact() const { return fanImpact; }
    QList<match>& getMatchesEdit()  { return matches; } // Getter specifically for editing the matches
    const QList<match> getMatches() const { return matches; }

    ShowType getShowType() const { return showType; } // Get show type (Weekly or PVP)


private:
    QList<match> matches; // List of matches in the show
    int showRating;     // Average rating for the show
    int totalRevenue;
    int totalCosts;     // Costs associated with the show
    int showProfit;     // Revenue - costs
    int fanImpact;      // Total fan impact from the show
    ShowType showType;  // Type of the show (Weekly or PVP)

};


#endif // SHOW_H

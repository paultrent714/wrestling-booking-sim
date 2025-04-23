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
    show(int type);

    void clear();

    // Methods to add matches, calculate and get show data
    void addMatch(const match &m);  // Add match to the show
    void removeMatch(int matchIndex);

    void calculateShowRating();  // Calculate the average show rating
    void calculateShowRevenue(int totalFans); // Calculate revenue based on show rating and fans.
    void calculateCosts();  // Calculate costs for show
    void calculateFanImpact(int totalFans);   // Calculate the total fan impact

    void setShowRating(float rating) { showRating = rating;}
    void setTotalCosts(int costs) { totalCosts = costs; }
    void setTotalRevenue(int revenue) { totalRevenue = revenue; }
    void setShowProfit(int profit) {showProfit = profit;}
    void setFanImpact(int fans) { fanImpact = fans;}
    void setShowType(int type) { showType = type;}

    // Getters for the show data
    float getShowRating() const { return showRating; }
    int getTotalCosts() const { return totalCosts; }
    int getTotalRevenue() const { return totalRevenue; }
    int getShowProfit() const { return showProfit;}
    int getFanImpact() const { return fanImpact; }
    QList<match>& getMatchesEdit()  { return matches; } // Getter specifically for editing the matches
    const QList<match> getMatches() const { return matches; }

    bool getShowType() const { return showType; } // Get show type (Weekly or PVP)


private:
    QList<match> matches; // List of matches in the show
    float showRating;     // Average rating for the show
    int totalRevenue;
    int totalCosts;     // Costs associated with the show
    int showProfit;     // Revenue - costs
    int fanImpact;      // Total fan impact from the show
    bool showType;  // Type of the show (Weekly 0  or PVP 1)

};


#endif // SHOW_H

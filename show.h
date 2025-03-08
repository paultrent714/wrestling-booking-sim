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

    // Methods to add matches, calculate and get show data
    void addMatch(const match &m);  // Add match to the show
    void removeMatch(int matchIndex);

    void calculateShowRating();  // Calculate the average show rating
    void calculateShowRevenue(); // Calculate revenue based on matches' fan impact
    void calculateFanImpact();   // Calculate the total fan impact

    // Getters for the show data
    int getShowRating() const { return showRating; }
    int getTotalCosts() const { return totalCosts; }
    int getFanImpact() const { return fanImpact; }
    QList<match>& getMatchesEdit()  { return matches; } // Getter specifically for editing the matches
    const QList<match> getMatches() const { return matches; }

    ShowType getShowType() const { return showType; } // Get show type (Weekly or PVP)

private:
    QList<match> matches; // List of matches in the show
    int showRating;     // Average rating for the show
    int totalCosts;     // Costs associated with the show
    int fanImpact;      // Total fan impact from the show
    ShowType showType;  // Type of the show (Weekly or PVP)

    // Helper methods for calculating revenue and fan impact
    void applyMultiplicativeFactors();
};


#endif // SHOW_H

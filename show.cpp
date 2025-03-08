#include "show.h"

#include "Show.h"
#include <QDebug>

show::show(){
    showType = Weekly;
    showRating = totalCosts = fanImpact = 0;
    matches.clear();
}

show::show(ShowType type)
    : showRating(0), totalCosts(0), fanImpact(0), showType(type) {}

void show::calculateShowRating()
{
    int totalRating = 0;
    int matchCount = matches.size();

    for (const match& match : matches) {
        totalRating += match.getRating();
    }

    if (matchCount > 0) {
        showRating = totalRating / matchCount;
    } else {
        showRating = 0;
    }
}

void show::calculateShowRevenue()
{
    int totalRevenue = 0;


    // Apply multiplicative factors for PVP or weekly show
    applyMultiplicativeFactors();
}

void show::applyMultiplicativeFactors()
{
    float multiplier = 1.0;

    if (showType == PVP) {
        multiplier = 2.0; // Example: PVP shows double the revenue
    } else if (showType == Weekly) {
        multiplier = 1.2; // Example: Weekly shows get a small bonus
    }

}

void show::addMatch(const match &m) {
    matches.append(m);  // Add the match to the matches list
}

void show::removeMatch(int matchIndex) {
    if (matchIndex >= 0 && matchIndex < matches.size()) {
        matches.removeAt(matchIndex);  // Remove the match at the given index
    }
}

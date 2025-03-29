#include "show.h"

#include "Show.h"
#include <QDebug>

show::show(){
    showType = Weekly;
    showRating = totalCosts = fanImpact = showProfit = totalRevenue = 0;
    matches.clear();
}

show::show(int type)
    : showRating(0), totalCosts(0), fanImpact(0), showType(type) {}

void show::clear(){
    showRating = totalCosts = fanImpact = showProfit = totalRevenue = 0;
    matches.clear();
}
void show::addMatch(const match &m) {
    matches.append(m);  // Add the match to the matches list
}

void show::removeMatch(int matchIndex) {
    if (matchIndex >= 0 && matchIndex < matches.size()) {
        matches.removeAt(matchIndex);  // Remove the match at the given index
    }
}

void show::calculateShowRating()
{
    if (matches.isEmpty()) {
        showRating = 0.0; // Default to lowest rating if no matches
        return;
    }

    float totalRating = 0.0;
    for (const match &m : matches) {
        totalRating += m.getRating();
    }

    showRating = totalRating / matches.size();
}

void show::calculateShowRevenue(int totalFans)
{
    // numbers that affect how the values are weighed when calculating revenue
    float ratingFactor = showRating / 5.0;
    float fanFactor = totalFans * 20;

    int ratingMultiplier = 2000;
    int fanMultiplier = 10;

    totalRevenue = -500 + (ratingFactor * ratingMultiplier) + (fanFactor * fanMultiplier);

    // Apply multiplicative factors for PVP
    if (showType == PVP){
        totalRevenue = totalRevenue * 1.5;
    }
}

void show::calculateCosts(){
    totalCosts = 0; // Reset cost calculation

    for (const match &m : matches) {
        for (Wrestler* wrestler : m.getParticipants()) {
            totalCosts += wrestler->getSalary();
        }
    }
}

void show::calculateFanImpact(int totalFans){
    float ratingFactor = (showRating - 3.0) / 2.0;
    float fanGrowthRate = 0.05;

    // Logarithmic scaling (reduces fan gain as fans grow)
    int fanChange = static_cast<int>((log(totalFans + 1) * 10) * ratingFactor);

    fanImpact = std::clamp(fanChange, -500, 2000); // Prevent extreme loss/gain
}


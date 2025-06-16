#pragma once
#include "Account.h"

//class for tvAccount set up
class TVAccount : public Account {
protected:
    //attributes that will be available through inheritance to other classes
    std::string tvPackage; //REGULAR or PREMIUM
    int channelCount;
    bool sportsChannels;
    bool payPerView;
    bool channelsLocked;
    double tvCost;

public:
    //default constructor
    TVAccount(std::shared_ptr<double> balance, const std::string& passcode = "", const std::string& iban = "",
        const std::string& kidsMode = "OFF");

    //discount amount that will be taken in case of presenting two packages
    double discountPercentage = 1.0;

    //getters
    std::string getTVPackage() const;
    int getChannelCount() const;
    bool hasSportsChannels() const;
    bool hasPayPerView() const;
    bool areChannelsLocked() const;
    double getTVCost() const;

    //setters
    void setTVPackage(const std::string& package);
    void setSportsChannels(bool hasSports);
    void setPayPerView(bool hasPPV);
    void setChannelsLocked(bool locked);
    void setTVCost(double cost);

    //account management
    void printDetails() const;

    void toggleChannelLock();
    void togglePayPerView();
    void toggleSportsChannels();
    void upgradeDowngrade();

    //menu system
    void showMenu();

    void updatePackageDetails();
    void setupTV();

};

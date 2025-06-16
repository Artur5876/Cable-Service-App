#pragma once
#include "Account.h"


class InternetAccount : public virtual Account/*, public PackageAccount*/ {
protected:
    std::string internetPackage; // "REGULAR" or "PREMIUM"
    double downloadSpeed;
    double uploadSpeed;
    double internetCost;

public:
    //discount amount that will be taken in case of presenting two packages
    double discountPercentage = 1.00;

    //default constructor
    InternetAccount(std::shared_ptr<double> balance, const std::string& passcode = "", const std::string& iban = "",
        const std::string& kidsMode = "OFF");

    //getters
    std::string getInternetPackage() const;
    double getDownloadSpeed() const;
    double getUploadSpeed() const;
    double getInternetCost() const;

    //setters
    void setInternetPackage(const std::string& package);
    void setDownloadSpeed(double speed);
    void setUploadSpeed(double speed);
    void setInternetCost(double cost);

    //account management
    void printDetails() const;
    void printInternetServices();
    void printAccountDetailsOptions() const;
    void kidsRestrictionsToggle();
    void upgradeDowngrade();
    void existedUserMenu();
    //Setup methods
    void setupRegularInternet();
    void setupPremiumInternet();
    void setupAccount();
    void printExistedUserMenu() const;
    // Menu system
    void showMenu();
};


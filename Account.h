#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <memory>

class Account {
protected:

    //attributes that will be available through inheritance to other classes
    std::string passcode;
    std::string iban;
    std::shared_ptr<double> balance;//pointer
    std::string kidsMode; //ON or OFF
    bool hasInternet;
    bool hasTV;
    bool isPackageAccount;
    std::string subscriptionDate;

    // Helper methods
    bool validatePasscode(const std::string& code);
    bool validateIBAN(const std::string& iban);
    std::string getCurrentDate();

public:
    //default constructor
    Account(std::shared_ptr<double> balance = std::make_shared<double>(123.45), const std::string& passcode = "", const std::string& iban = "",
        /*double balance = 123.45,*/ const std::string& kidsMode = "OFF",
        bool hasInternet = false, bool hasTV = false);

    //getters
    std::string getPasscode() const;
    std::string getIBAN() const;
    double getBalance() const;
    bool hasInternetService() const;
    bool hasTVService() const;
    std::string getKidsMode() const;
    bool isPackage() const;
    std::string getSubscriptionDate() const;

    //setters with validation
    bool setPasscode(const std::string& newPasscode, const std::string& confirmPasscode);
    bool setIBAN(const std::string& newIban);
    void setBalance(double amount);
    void setHasInternet(bool hasInternet);
    void setHasTV(bool hasTV);
    void setKidsMode(const std::string& mode);
    void setPackage(bool isPackage);
    void setSubscriptionDate(const std::string& date);

    // Common functionality
    double deductPayment(double amount);
    bool changePasscode();
    void printExistedUserMenu() const;
    void setupPasscode();
    void existedPasscodeCheck();};
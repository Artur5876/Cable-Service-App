//Main.cpp
#include <iostream>
#include "Account.h"
#include "InternetAccount.h"
#include "TVAccount.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    //the balance variable from the Account.h will be shared between classes(InternetAccount.h and TVAccount.h)
    //and will have default value ($123.45), once user created an account
    auto sharedBalance = std::make_shared<double>(123.45); // Starting with €500

    //accounts with the shared balance
    InternetAccount internetAccount(sharedBalance, "", "");
    TVAccount tvAccount(sharedBalance, "", "");

    int choice;

    std::cout << "=== WELCOME TO KINGDOM CABLE SERVICE ===\n";

    do {
        std::cout << "\n=== MAIN MENU ===\n";

        std::cout << "1. Set up Internet Account\n";
        std::cout << "2. Set up TV Account\n";
        std::cout << "3. Set up Package Account (Internet + TV, 10% discount)\n";
        std::cout << "4. Already have account (login)\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice (1-5): ";

        //once we selecting another option -- > we need to clean the choice string variable either its correct or incorrect choice
        if (!(std::cin >> choice)) {
            clearInputBuffer();
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            //internet account setup case
        case 1: {
            if (internetAccount.hasInternetService()) {
                std::cout << "You already have an Internet account. Please login (option 4).\n";
            }
            else {
                // Setup internet account
                if (tvAccount.getPasscode().empty()) {
                    internetAccount.setupPasscode();
                    if (internetAccount.getPasscode().empty()) break;
                }

                if (tvAccount.getIBAN().empty()) {
                    std::string iban;
                    std::cout << "Enter Irish IBAN: ";
                    std::cin >> iban;
                    if (!internetAccount.setIBAN(iban)) {
                        std::cout << "Invalid IBAN.\n";
                        break;
                    }
                }

                internetAccount.setupAccount();
                std::cout << "Internet account setup complete!\n";
            }
            break;
        }
        case 2: {
            if (tvAccount.hasTVService()) {
                std::cout << "You already have a TV account. Please login (option 4).\n";
            }
            else {
                // Setup TV account
                if (internetAccount.getPasscode().empty()) {
                    tvAccount.setupPasscode();
                    if (tvAccount.getPasscode().empty()) break;
                }

                if (internetAccount.getIBAN().empty()) {
                    std::string iban;
                    std::cout << "Enter Irish IBAN: ";
                    std::cin >> iban;
                    if (!tvAccount.setIBAN(iban)) {
                        std::cout << "Invalid IBAN.\n";
                        break;
                    }
                }

                if (internetAccount.hasInternetService()) {
                    tvAccount.discountPercentage = 0.9;
                }
                tvAccount.setupTV();
                std::cout << "TV account setup complete!\n";
            }
            break;
        }
              //set up both accounts (internet+tv)
        case 3: {
            //if user already had created an tvaccount -- > message will be shown
            if (internetAccount.hasInternetService()) {
                std::cout << "Sorry, you already have Internet account, you need to login into your account!" << std::endl;
            }
            else {
                //PackageAccount packageAccount;
                if (tvAccount.getIBAN() == "") {
                    std::string iban;
                    std::cout << "Enter Irish IBAN: " << internetAccount.getIBAN();
                    std::cin >> iban;
                    /*setupAccount*/

                    //if iban is invalid -->user will be notified
                    if (!internetAccount.setIBAN(iban)) {
                        std::cout << "Your IBAN is not valid" << std::endl;
                        break;
                    }
                    //if user has no passccode (no account yet) then user required to create new passcode
                }
                if (tvAccount.getPasscode() == "") {
                    internetAccount.setupPasscode();
                }
                internetAccount.setupAccount();
            }
            if (tvAccount.hasTVService()) {
                std::cout << "Sorry, you already have TV account, you need to login into your account!" << std::endl;
            }
            else {
                //PackageAccount packageAccount;
                if (internetAccount.getPasscode() == "") {
                    std::string iban;
                    std::cout << "Enter Irish IBAN: " << internetAccount.getPasscode();
                    std::cin >> iban;
                    /*setupAccount*/

                    //if iban is invalid -->user will be notified
                    if (!tvAccount.setIBAN(iban)) {
                        std::cout << "Your IBAN is not valid" << std::endl;
                        break;
                    }
                    //if user has no passccode (no account yet) then user required to create new passcode
                }
                if (internetAccount.getPasscode() == "") {
                    tvAccount.setupPasscode();
                    // tvAccount.setupTV();
                }
                tvAccount.setupTV();
            }
            break;
        }
        case 4: {
            std::string passcode;
            std::cout << "=== LOGIN ===" << std::endl;
            std::cout << "Enter your passcode: ";
            std::cin >> passcode;
            std::cout << std::endl;

            // Check if any account exists and passcode matches
            bool validPasscode = false;
            bool hasInternet = (internetAccount.getPasscode() != "");
            bool hasTV = (tvAccount.getPasscode() != "");

            if (hasInternet && passcode == internetAccount.getPasscode()) {
                validPasscode = true;
            }
            else if (hasTV && passcode == tvAccount.getPasscode()) {
                validPasscode = true;
            }

            if (validPasscode) {
                std::string loginChoice;
                bool validChoice = false;

                while (!validChoice) {
                    std::cout << "\nChoose the account to login:" << std::endl;
                    std::cout << "1. Internet Account" << std::endl;
                    std::cout << "2. TV Account" << std::endl;
                    std::cout << "3. Change Passcode" << std::endl;
                    std::cout << "4. Back to Main Menu" << std::endl;
                    std::cout << "Enter choice (1-4): ";
                    std::cin >> loginChoice;

                    // clear input buffer to handle bad input
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (loginChoice == "1" && internetAccount.getInternetPackage() != "") {
                        validChoice = true;
                        internetAccount.showMenu();
                    }
                    else if (loginChoice == "2" && tvAccount.getTVPackage() != "") {
                        validChoice = true;
                        tvAccount.showMenu();
                    }
                    else if (loginChoice == "3") {
                        bool passcodeChanged = false;
                        if (hasInternet) {
                            passcodeChanged = internetAccount.changePasscode();
                        }
                        else if (hasTV) {
                            passcodeChanged = tvAccount.changePasscode();
                        }

                        if (!passcodeChanged) {
                            std::cout << "Passcode change failed. Please try again." << std::endl;
                            continue;  // This will re-show the menu
                        }
                        validChoice = true;
                    }
                    else if (loginChoice == "4") {
                        validChoice = true;
                        std::cout << "Returning to main menu..." << std::endl;
                    }
                    else {
                        std::cout << "Invalid choice! Please try again." << std::endl;
                    }
                }
            }
            //i
            else if (hasInternet || hasTV) {
                std::cout << "Incorrect passcode! Please try again." << std::endl;
            }
            else {
                std::cout << "No accounts detected! Please set up an account first." << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "Thank you for using Kingdom Cable Service!\n";
            return 0;
        }
        default: {
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (true);  // Exit is handled by case 5's return

    return 0;
}

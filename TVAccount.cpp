#include "TVAccount.h"
#include <iomanip>

// Constructor (default values)
TVAccount::TVAccount(std::shared_ptr<double> balance, const std::string& passcode, const std::string& iban,
    const std::string& kidsMode)
    : Account(balance, passcode, iban, kidsMode, false, false) {
    tvPackage = "";
    channelCount = 0;
    sportsChannels = false;
    payPerView = false;
    channelsLocked = true;
    tvCost = 0.0;
}

//getters
std::string TVAccount::getTVPackage() const { return tvPackage; }
int TVAccount::getChannelCount() const { return channelCount; }
bool TVAccount::hasSportsChannels() const { return sportsChannels; }
bool TVAccount::hasPayPerView() const { return payPerView; }
bool TVAccount::areChannelsLocked() const { return channelsLocked; }
double TVAccount::getTVCost() const { return tvCost; }

//setters
void TVAccount::setTVPackage(const std::string& package) {
    tvPackage = package;
    updatePackageDetails();
}

//update package details when package type changes
void TVAccount::updatePackageDetails() {
    if (tvPackage == "REGULAR") {
        channelCount = 100;
        sportsChannels = false;
        tvCost = 25.0 * discountPercentage;
        channelsLocked = true;
    }
    else if (tvPackage == "PREMIUM") {
        channelCount = 200;
        sportsChannels = true;
        tvCost = 40.0 * discountPercentage; 
        channelsLocked = true;
    }
}

void TVAccount::setSportsChannels(bool hasSports) { sportsChannels = hasSports; }
void TVAccount::setPayPerView(bool hasPPV) { payPerView = hasPPV; }
void TVAccount::setChannelsLocked(bool locked) { channelsLocked = locked; }
void TVAccount::setTVCost(double cost) { tvCost = cost; }

// Print account details
void TVAccount::printDetails() const {
    std::cout << "\n-------------------------------------------";
    std::cout << "\n|            TV ACCOUNT DETAILS           |";
    std::cout << "\n|-----------------------------------------|";
    std::cout << "\n| Package: " << std::left << std::setw(30) << getTVPackage() << "|";

    if (discountPercentage == 0.9) {
        std::cout << "\n| Monthly Cost: $" << std::setw(19) << getTVCost() << " (10% discount) |";
    }
    else {
        std::cout << "\n| Monthly Cost: $" << std::setw(30) << getTVCost() << "|";
    }

    std::cout << "\n| Available Channels: " << std::setw(17) << getChannelCount() << " (";
    if (getTVPackage() == "REGULAR") {
        std::cout << "1-89 unlocked, 90-100 " << (areChannelsLocked() ? "locked" : "unlocked") << ") |";
    }
    else {
        std::cout << "1-179 unlocked, 180-200 " << (areChannelsLocked() ? "locked" : "unlocked") << ") |";
    }

    std::cout << "\n| Sports Channels: " << std::setw(21) << (hasSportsChannels() ? "ON" : "OFF") << "|";
    std::cout << "\n| Pay Per View: " << std::setw(24) << (hasPayPerView() ? "ON" : "OFF") << "|";
    std::cout << "\n| Kids Restrictions: " << std::setw(19) << getKidsMode() << "|";
    std::cout << "\n| Subscription Date: " << std::setw(19) << getSubscriptionDate() << "|";
    std::cout << "\n| Balance: $" << std::setw(31) << getBalance() << "|";
    std::cout << "\n|------------------------------------------|\n";
}

//TV setup method
void TVAccount::setupTV() {
    std::string choice;
    bool validChoice = false;

    while (!validChoice) {
        std::cout << "\n+============================================+";
        std::cout << "\n|           TV SERVICE PACKAGES            |";
        std::cout << "\n+--------------------------------------------+";
        std::cout << "\n| 1. REGULAR Package                      |";
        std::cout << "\n|    -> 100 Channels                       |";
        std::cout << "\n|    -> $25/month                          |";
        std::cout << "\n|                                          |";
        std::cout << "\n| 2. PREMIUM Package                      |";
        std::cout << "\n|    -> 200 Channels                       |";
        std::cout << "\n|    -> Includes Sports                    |";
        std::cout << "\n|    -> $40/month                          |";
        std::cout << "\n+============================================+";
        std::cout << "\n\n* Enter your choice (1-2): ";

        std::cin >> choice;

        if (choice == "1") {
            setTVPackage("REGULAR");
            deductPayment(25 * discountPercentage);
            validChoice = true;
        }
        else if (choice == "2") {
            setTVPackage("PREMIUM");
            deductPayment(40 * discountPercentage);
            validChoice = true;
        }
        else {
            std::cout << "\n! Invalid choice! Please select 1 or 2.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        setHasTV(true);
        std::cout << "\n+============================================+";
        std::cout << "\n|       TV SERVICE ACTIVATED!             |";
        std::cout << "\n+--------------------------------------------+";
        std::cout << "\n| [OK] " << std::left << std::setw(34) << (getTVPackage() + " package configured") << " |";
        std::cout << "\n| --> Monthly cost: $" << std::setw(22) << getTVCost() << " |";
        std::cout << "\n+============================================+\n";
        printDetails();
    }
}

//toggle channel lock status
void TVAccount::toggleChannelLock() {
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n|         CHANNEL LOCK SETTINGS           |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| Current Status: " << std::left << std::setw(23)
        << (areChannelsLocked() ? "LOCKED" : "UNLOCKED") << " |";
    std::cout << "\n+--------------------------------------------+\n";

    std::cout << "\n* Would you like to " << (areChannelsLocked() ? "UNLOCK" : "LOCK") << " channels? (Y/N): ";

    char choice;
    std::cin >> choice;

    if (toupper(choice) == 'Y') {
        if (areChannelsLocked()) {
            std::cout << "\n! This will cost $10. Confirm? (Y/N): ";
            std::cin >> choice;
            if (toupper(choice) == 'Y' && deductPayment(10.0)) {
                setChannelsLocked(false);
                std::cout << "\n* Channels successfully UNLOCKED!\n";
            }
        }
        else {
            setChannelsLocked(true);
            std::cout << "\n* Channels successfully LOCKED!\n";
        }
        printDetails();
    }
}

// Toggle Pay Per View
void TVAccount::togglePayPerView() {
    if (hasPayPerView()) {
        std::cout << "\n! Pay Per View is already ACTIVE.\n";
        return;
    }

    std::cout << "\n* Activate Pay Per View for $10? (Y/N): ";
    char choice;
    std::cin >> choice;

    if (toupper(choice) == 'Y' && deductPayment(10.0)) {
        setPayPerView(true);
        std::cout << "\n* Pay Per View successfully ACTIVATED!\n";
        printDetails();
    }
}

// Toggle Sports Channels
void TVAccount::toggleSportsChannels() {
    if (hasSportsChannels()) {
        std::cout << "\n! Sports channels are already ACTIVE.\n";
        return;
    }

    std::cout << "\n* Activate Sports Channels for $20? (Y/N): ";
    char choice;
    std::cin >> choice;

    if (toupper(choice) == 'Y' && deductPayment(20.0)) {
        setSportsChannels(true);
        std::cout << "\n* Sports Channels successfully ACTIVATED!\n";
        printDetails();
    }
}

//upgrade or downgrade method
void TVAccount::upgradeDowngrade() {
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n|       PACKAGE UPGRADE/DOWNGRADE         |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| Current Package: " << std::left << std::setw(23)
        << (getTVPackage() == "REGULAR" ? "REGULAR ($25)" : "PREMIUM ($40)") << " |";
    std::cout << "\n+--------------------------------------------+\n";

    std::cout << "\n* Would you like to "
        << (getTVPackage() == "REGULAR" ? "UPGRADE to PREMIUM" : "DOWNGRADE to REGULAR") << "? (Y/N): ";

    char choice;
    std::cin >> choice;

    if (toupper(choice) == 'Y') {
        if (getTVPackage() == "REGULAR") {
            if (deductPayment(15.0)) {
                setTVPackage("PREMIUM");
                std::cout << "\n+--------------------------------------------+";
                std::cout << "\n|       UPGRADE COMPLETE!                 |";
                std::cout << "\n+--------------------------------------------+";
                std::cout << "\n| [OK] Now subscribed to PREMIUM TV       |";
                std::cout << "\n| --> New balance: $" << std::setw(24) << getBalance() << " |";
                std::cout << "\n+--------------------------------------------+\n";
            }
            else {
                std::cout << "\n! TRANSACTION FAILED!";
                std::cout << "\n* Needed: $15 | Available: $" << getBalance() << "\n";
            }
        }
        else {
            setTVPackage("REGULAR");
            std::cout << "\n+--------------------------------------------+";
            std::cout << "\n|       DOWNGRADE COMPLETE!               |";
            std::cout << "\n+--------------------------------------------+";
            std::cout << "\n| [OK] Now subscribed to REGULAR TV       |";
            std::cout << "\n+--------------------------------------------+\n";
        }
        printDetails();
    }
}

// account management menu
void TVAccount::showMenu() {
    int choice;
    do {
        std::cout << "\n+============================================+";
        std::cout << "\n|            TV ACCOUNT MENU              |";
        std::cout << "\n+--------------------------------------------+";
        std::cout << "\n| 1. View Account Details                 |";
        std::cout << "\n| 2. Toggle Channel Lock                 |";
        std::cout << "\n| 3. Upgrade/Downgrade Package           |";
        std::cout << "\n| 4. Toggle Pay Per View                 |";
        std::cout << "\n| 5. Toggle Sports Channels              |";
        std::cout << "\n| 6. Change Passcode                     |";
        std::cout << "\n| 7. Exit to Main Menu                   |";
        std::cout << "\n+============================================+";
        std::cout << "\n\n* Enter your choice (1-7): ";

        std::cin >> choice;

        switch (choice) {
        case 1: printDetails(); break;
        case 2: toggleChannelLock(); break;
        case 3: upgradeDowngrade(); break;
        case 4: togglePayPerView(); break;
        case 5: toggleSportsChannels(); break;
        case 6: changePasscode(); break;
        case 7: break;
        default: std::cout << "\n! Invalid choice! Please select 1-7.\n";
        }    } while (choice != 7);}
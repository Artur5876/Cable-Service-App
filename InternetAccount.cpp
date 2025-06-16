#include "InternetAccount.h"
#include <iomanip>
#include "TVAccount.h"

// Constructor (default value initiation)
InternetAccount::InternetAccount(std::shared_ptr<double> balance, const std::string& passcode, const std::string& iban,
    const std::string& kidsMode)
    : Account(balance, passcode, iban, kidsMode, false, false) {
    internetPackage = "";
    downloadSpeed = 0.0;
    uploadSpeed = 0.0;
    internetCost = 0.0;
}

// Getters
std::string InternetAccount::getInternetPackage() const { return internetPackage; }
double InternetAccount::getDownloadSpeed() const { return downloadSpeed; }
double InternetAccount::getUploadSpeed() const { return uploadSpeed; }
double InternetAccount::getInternetCost() const { return internetCost; }

// Setters
void InternetAccount::setInternetPackage(const std::string& package) { internetPackage = package; }
void InternetAccount::setDownloadSpeed(double speed) { downloadSpeed = speed; }
void InternetAccount::setUploadSpeed(double speed) { uploadSpeed = speed; }
void InternetAccount::setInternetCost(double cost) { internetCost = cost; }

void InternetAccount::printDetails() const {
    // Header section
    std::cout << "\n+============================================+";
    std::cout << "\n|        INTERNET ACCOUNT DETAILS         |";
    std::cout << "\n+--------------------------------------------+";

    // Package and speed information
    std::cout << "\n| Package: " << std::left << std::setw(30) << getInternetPackage() << " |";
    std::cout << "\n| Download Speed: " << std::setw(20) << getDownloadSpeed() << " Mbps |";
    std::cout << "\n| Upload Speed: " << std::setw(22) << getUploadSpeed() << " Mbps |";

    // Pricing information
    if (discountPercentage == 0.9) {
        std::cout << "\n| Monthly Cost: $" << std::setw(19) << getInternetCost() << " (10% discount) |";
    }
    else {
        std::cout << "\n| Monthly Cost: $" << std::setw(30) << getInternetCost() << " |";
    }

    // Account settings and status
    std::cout << "\n| Kids Restrictions: " << std::setw(22) << getKidsMode() << " |";
    std::cout << "\n| Subscription Date: " << std::setw(22) << getSubscriptionDate() << " |";
    std::cout << "\n| Balance: $" << std::setw(31) << getBalance() << " |";
    std::cout << "\n+============================================+\n";
}

void InternetAccount::printInternetServices() {
    int choice;
    bool validChoice = false;

    while (!validChoice) {
        std::cout << "\n+============================================+";
        std::cout << "\n|           INTERNET SERVICE PLANS         |";
        std::cout << "\n+--------------------------------------------+";
        std::cout << "\n| 1. REGULAR Package                      |";
        std::cout << "\n|    -> 15.6 Mbps Download                |";
        std::cout << "\n|    -> 2.97 Mbps Upload                  |";
        std::cout << "\n|    -> $35/month                         |";
        std::cout << "\n|                                          |";
        std::cout << "\n| 2. PREMIUM Package                      |";
        std::cout << "\n|    -> 23.9 Mbps Download                |";
        std::cout << "\n|    -> 3.8 Mbps Upload                   |";
        std::cout << "\n|    -> $50/month                         |";
        std::cout << "\n|                                          |";
        std::cout << "\n| 3. Back to Previous Menu                |";
        std::cout << "\n+============================================+";
        std::cout << "\n\n* Enter your choice (1-3): ";

        std::cin >> choice;

        switch (choice) {
        case 1:
            setupRegularInternet();
            validChoice = true;
            break;
        case 2:
            setupPremiumInternet();
            validChoice = true;
            break;
        case 3:
            validChoice = true;
            break;
        default:
            std::cout << "\n! Invalid choice! Please select 1-3.\n";
            //clear any error flags and ignore the rest of the line
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void InternetAccount::setupRegularInternet() {
    setInternetPackage("REGULAR");
    setDownloadSpeed(15.6);
    setUploadSpeed(2.97);
    setInternetCost(35.0 * discountPercentage);
    setHasInternet(true);
    deductPayment(35 * discountPercentage);

    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n|      REGULAR INTERNET ACTIVATED!         |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| [OK] Service successfully configured     |";
    std::cout << "\n| --> Monthly cost: $" << std::setw(22) << getInternetCost() << " |";
    std::cout << "\n+--------------------------------------------+\n";
    printDetails();
}

void InternetAccount::setupPremiumInternet() {
    setInternetPackage("PREMIUM");
    setDownloadSpeed(23.9);
    setUploadSpeed(3.8);
    setInternetCost(50.0 * discountPercentage);
    setHasInternet(true);
    deductPayment(50 * discountPercentage);

    std::cout << "\n==============================================";
    std::cout << "\n|      PREMIUM INTERNET ACTIVATED!         |";
    std::cout << "\n|--------------------------------------------|";
    std::cout << "\n| * Service successfully configured        |";
    std::cout << "\n| > Monthly cost: $" << std::setw(24) << getInternetCost() << " |";
    std::cout << "\n==============================================\n";
    printDetails();
}

//method for kids restrictions toggle
void InternetAccount::kidsRestrictionsToggle() {
    std::cout << "\n+============================================+";
    std::cout << "\n|       PARENTAL CONTROL SETTINGS         |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| Current Status: " << std::left << std::setw(25) << getKidsMode() << " |";
    std::cout << "\n+============================================+\n";

    std::cout << "\n* Would you like to " << (getKidsMode() == "OFF" ? "ENABLE" : "DISABLE") << " parental controls? (Y/N): ";

    char choice;
    std::cin >> choice;

    //if yes< -> toggle to the opposite
    //if no-- > nothing will happen
    if (toupper(choice) == 'Y') {
        std::cout << "\n----------------------------------------";
        std::cout << "\n|   SECURITY VERIFICATION REQUIRED     |";
        std::cout << "\n----------------------------------------";
        std::string inputPasscode;
        std::cout << "\n* Enter your passcode: ";
        std::cin >> inputPasscode;

        if (inputPasscode == getPasscode()) {
            setKidsMode(getKidsMode() == "OFF" ? "ON" : "OFF");

            std::cout << "\n+============================================+";
            std::cout << "\n|        SETTING CHANGED SUCCESSFULLY      |";
            std::cout << "\n+--------------------------------------------+";
            std::cout << "\n| New Status: " << std::left << std::setw(28) << getKidsMode() << " |";
            std::cout << "\n+============================================+\n";
            printDetails();
        }
        else {
            std::cout << "\n! ACCESS DENIED! Incorrect passcode.\n";
        }
    }
}

//method for upgrading the subscription package
void InternetAccount::upgradeDowngrade() {
    std::cout << "\n+============================================+";
    std::cout << "\n|       SUBSCRIPTION MANAGEMENT           |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| Current Package: " << std::left << std::setw(23) << (getInternetPackage() == "REGULAR" ? "REGULAR ($35)" : "PREMIUM ($50)") << " |";
    std::cout << "\n+============================================+\n";

    std::cout << "\n* Would you like to " << (getInternetPackage() == "REGULAR" ? "UPGRADE to PREMIUM" : "DOWNGRADE to REGULAR") << "? (Y/N): ";

    char choice;
    std::cin >> choice;


    if (toupper(choice) == 'Y') {
        if (getInternetPackage() == "REGULAR") {
            if (deductPayment(50.0 - 35.0)) {
                setInternetPackage("PREMIUM");
                setDownloadSpeed(23.9);
                setUploadSpeed(3.8);
                setInternetCost(50.0);

                std::cout << "\n+============================================+";
                std::cout << "\n|       UPGRADE COMPLETE!                    |";
                std::cout << "\n+--------------------------------------------+";
                std::cout << "\n| > Now subscribed to PREMIUM Internet       |";
                std::cout << "\n| > New balance: $" << std::setw(26) << getBalance() << " |";
                std::cout << "\n+============================================+\n";
            }
            else {
                std::cout << "\n TRANSACTION FAILED!";
                std::cout << "\n* Needed: $50 | Available: $" << getBalance() << "\n";
            }
        }
        else {
            setInternetPackage("REGULAR");
            setDownloadSpeed(15.6);
            setUploadSpeed(2.97);
            setInternetCost(35.0);

            std::cout << "\n+--------------------------------------------+";
            std::cout << "\n|       DOWNGRADE COMPLETE!                  |";
            std::cout << "\n+--------------------------------------------+";
            std::cout << "\n| > Now subscribed to REGULAR Internet       |";
            std::cout << "\n+--------------------------------------------+\n";
        }
        //all details printed out
        //printDetails();
    }
}

//account setup method
void InternetAccount::setupAccount() {
    printInternetServices();
}

void InternetAccount::printExistedUserMenu() const {
    std::cout << "\n--------------------------------------------";
    std::cout << "\n|       INTERNET ACCOUNT MANAGEMENT        |";
    std::cout << "\n|------------------------------------------|";
    std::cout << "\n| 1. View Account Details                  |";
    std::cout << "\n| 2. Toggle Kids Restrictions              |";
    std::cout << "\n| 3. Upgrade/Downgrade Subscription        |";
    std::cout << "\n| 4. Change Passcode                       |";
    std::cout << "\n| 5. Back to Main Menu                     |";
    std::cout << "\n-------------------------------------------|";
    std::cout << "\n\n* Enter your choice (1-5): ";
}
//menu for internetaccount
void InternetAccount::showMenu() {
    int choice;
    do {
        printExistedUserMenu();
        std::cin >> choice;

        // Clear input buffer and error flags if input fails
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; // Force the default case
        }

        switch (choice) {
        case 1:
            printDetails();
            break;
        case 2:
            kidsRestrictionsToggle();
            break;
        case 3:
            upgradeDowngrade();
            break;
        case 4:
            if (!changePasscode()) {
                std::cout << "\n! Passcode change failed.\n";
            }
            break;
        case 5:
            break;
        default:
            std::cout << "\n! Invalid choice! Please select 1-5.\n";
            // Pause to let user see the error message
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } while (choice != 5);
}

//text print for internet account menu
void InternetAccount::printAccountDetailsOptions() const {
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n|        INTERNET ACCOUNT MENU               |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n| 1. View Account Details                    |";
    std::cout << "\n| 2. Toggle Kids Restrictions                |";
    std::cout << "\n| 3. Upgrade/Downgrade Subscription          |";
    std::cout << "\n| 4. Change Passcode                         |";
    std::cout << "\n| 5. Back to Main Menu                       |";
    std::cout << "\n+--------------------------------------------+";
    std::cout << "\n\n* Enter your choice (1-5): ";
}


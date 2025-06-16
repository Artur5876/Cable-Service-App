#include "Account.h"
#include <regex>
#include "InternetAccount.h"

// CONSTRUCTOR
Account::Account(std::shared_ptr<double> balance, const std::string& passcode, const std::string& iban,
    const std::string& kidsMode, bool hasInternet, bool hasTV)
    : balance(balance ? balance : std::make_shared<double>(123.45)),
    passcode(passcode),
    iban(iban),
    kidsMode(kidsMode),
    hasInternet(hasInternet),
    hasTV(hasTV),
    isPackageAccount(false) {
    subscriptionDate = getCurrentDate();
}

// VALIDATION METHODS
bool Account::validatePasscode(const std::string& code) {
    //no longer then 4 digits
    return code.length() == 4 && std::all_of(code.begin(), code.end(), ::isdigit);
}


bool Account::validateIBAN(const std::string& iban) {
    //length has to be 22 characters
    if (iban.length() != 22) {
        return false;
    }

    //first characters(IE)
    if ((iban[0] != 'I' && iban[0] != 'i') || (iban[1] != 'E' && iban[1] != 'e')) {
        return false;
    }

    //next characters required to be digits
    if (!isdigit(iban[2]) || !isdigit(iban[3])) {
        return false;
    }

    //next characters required to be alphabetic characters
    for (int i = 4; i <= 7; i++) {
        if (!isalpha(iban[i])) {
            return false;
        }
    }

    //the rest are digits!
    for (int i = 8; i < 22; i++) {
        if (!isdigit(iban[i])) {
            return false;
        }
    }

    return true;
}

//method that will give me the current subscription time
std::string Account::getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", &now);
    return buffer;
}

// GETTERS
std::string Account::getPasscode() const { return passcode; }
std::string Account::getIBAN() const { return iban; }
double Account::getBalance() const { return *balance; }
bool Account::hasInternetService() const { return hasInternet; }
bool Account::hasTVService() const { return hasTV; }
std::string Account::getKidsMode() const { return kidsMode; }
bool Account::isPackage() const { return isPackageAccount; }
std::string Account::getSubscriptionDate() const { return subscriptionDate; }

// SETTERS
bool Account::setPasscode(const std::string& newPasscode, const std::string& confirmPasscode) {
    if (!validatePasscode(newPasscode)) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|            VALIDATION ERROR              |";
        std::cout << "\n|------------------------------------------|";
        std::cout << "\n| Passcode must be exactly 4 digits        |";
        std::cout << "\n|------------------------------------------|\n";
        return false;
    }

    if (newPasscode != confirmPasscode) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|            VALIDATION ERROR              |";
        std::cout << "\n|----------------------------------------- |";
        std::cout << "\n| Passcodes do not match                   |";
        std::cout << "\n|------------------------------------------|\n";
        return false;
    }

    passcode = newPasscode;
    return true;
}

//iban setup method
bool Account::setIBAN(const std::string& newIban) {
    if (!validateIBAN(newIban)) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|            VALIDATION ERROR              |";
        std::cout << "\n|------------------------------------------|";
        std::cout << "\n| Invalid Irish IBAN format:               |";
        std::cout << "\n| * Must be 22 characters                  |";
        std::cout << "\n| * Must start with 'IE'                   |";
        std::cout << "\n| * Format: IEkk BBBB SSSS SSCC CCCC CC    |";
        std::cout << "\n|------------------------------------------|\n";
        return false;
    }
    iban = newIban;
    return true;
}

//setters
void Account::setBalance(double amount) { *balance = amount; }
void Account::setHasInternet(bool hasInternet) { this->hasInternet = hasInternet; }
void Account::setHasTV(bool hasTV) { this->hasTV = hasTV; }
void Account::setKidsMode(const std::string& mode) { kidsMode = mode; }
void Account::setPackage(bool isPackage) { isPackageAccount = isPackage; }
void Account::setSubscriptionDate(const std::string& date) { subscriptionDate = date; }

// PAYMENT PROCESSING method
double Account::deductPayment(double amount) {
    if (*balance >= amount) {
        *balance -= amount;
        return *balance;
    }
    return false;
}

// MENU DISPLAY


// PASSCODE MANAGEMENT
void Account::setupPasscode() {
    std::string newPasscode, confirmPasscode;

    std::cout << "\n--------------------------------------------";
    std::cout << "\n|          PASSCODE SETUP                  |";
    std::cout << "\n--------------------------------------------";
    std::cout << "\n\n* Enter new passcode (4 digits): ";
    std::cin >> newPasscode;

    std::cout << "* Confirm passcode: ";
    std::cin >> confirmPasscode;

    if (setPasscode(newPasscode, confirmPasscode)) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|          PASSCODE SET SUCCESSFULLY       |";
        std::cout << "\n--------------------------------------------";
        std::cout << std::endl;
    }
}

//passcode change method
bool Account::changePasscode() {
    std::string newPasscode, confirmPasscode;

    std::cout << "\n--------------------------------------------";
    std::cout << "\n|          CHANGE PASSCODE                 |";
    std::cout << "\n--------------------------------------------";
    std::cout << "\n\n* Enter current passcode: ";
    std::cin >> newPasscode;

    if (newPasscode != passcode) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|          SECURITY ALERT                  |";
        std::cout << "\n|------------------------------------------|";
        std::cout << "\n| Incorrect passcode! Access denied.       |";
        std::cout << "\n--------------------------------------------\n";
        return false;
    }

    std::cout << "* Enter new passcode (4 digits): ";
    std::cin >> newPasscode;
    std::cout << "* Confirm new passcode: ";
    std::cin >> confirmPasscode;

    if (setPasscode(newPasscode, confirmPasscode)) {
        std::cout << "\n--------------------------------------------";
        std::cout << "\n|       PASSCODE CHANGED SUCCESSFULLY      |";
        std::cout << "\n--------------------------------------------\n";
        return true;
    }
}

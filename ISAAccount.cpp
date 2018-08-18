#include "ISAAccount.h"

ISAAccount::ISAAccount() :maximumYearlyDeposit(0), currentYearlyDeposit(0), endDepositPeriod(Date::currentDate()) {}

// Input / Output

double ISAAccount::getMaximumYearlyDeposit()
{
	return maximumYearlyDeposit;
}

double ISAAccount::getCurrentYearlyDeposit()
{
	return currentYearlyDeposit;
}

const Date & ISAAccount::getEndDepositPeriod() const
{
	return endDepositPeriod;
}

ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) CurrentAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit << "\n";					//put maximumYearlyDeposit
	os << currentYearlyDeposit << "\n";					//put currentYearlyDespsit
	os << endDepositPeriod << "\n";						//put endDepositPeriod
	return os;
}
istream& ISAAccount::getAccountDataFromStream(istream& is) {
	//get CurrentAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);
	is >> maximumYearlyDeposit;							//get maximumYearlyDeposit
	is >> currentYearlyDeposit;							//get currentYearlyDespsit
	is >> endDepositPeriod;								//get endDepositPeriod
	return is;
}

const string ISAAccount::prepareFormattedAccountDetails() const
{
	string message = SavingsAccount::prepareFormattedAccountDetails();
	ostringstream os;
	os << message;
	os << "\n      MAXIMUM YEARLY DEPOSIT: " << setw(10) << "\234" <<maximumYearlyDeposit;
	os << "\n      CURRENT YEARLY DEPOSIT: " << setw(10) << "\234" << currentYearlyDeposit;
	os << "\n      END DEPOSIT DATE:	   " << setw(10) << endDepositPeriod;
	os << "\n      ----------------------------------------";

	return os.str();
}

void ISAAccount::updateCurrentYearlyDeposit(double a)
{
	currentYearlyDeposit += a;
}

void ISAAccount::recordDeposit(double amount) {
	updateCurrentYearlyDeposit(amount);
	BankAccount::recordDeposit(amount);
}

bool ISAAccount::canDesposit(double amount) const
{
	bool inDate = Date::currentDate() < endDepositPeriod;

	// if amount is less than the yearly allowance left, do it, and return true
	return (inDate && amount <= maximumYearlyDeposit - currentYearlyDeposit);
}


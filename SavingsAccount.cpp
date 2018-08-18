#include "SavingsAccount.h"

SavingsAccount::SavingsAccount():minimumBalance(0){}

double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance;
}

double SavingsAccount::maxBorrowable() const {
	//return borrowable amount
	return BankAccount::maxBorrowable() - minimumBalance;
}

// Input / Output

ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) CurrentAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << minimumBalance << "\n";					//put overdraft
	return os;
}
istream& SavingsAccount::getAccountDataFromStream(istream& is) {
	//get CurrentAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> minimumBalance;							//get overdraft
	return is;
}

const string SavingsAccount::prepareFormattedAccountDetails() const{

	string message = BankAccount::prepareFormattedAccountDetails();
	ostringstream os;
	os << message;
	os << "\n      MINIMUM BALANCE: " << setw(10) << "\234" << minimumBalance;
	os << "\n      ----------------------------------------";

	return os.str();
}
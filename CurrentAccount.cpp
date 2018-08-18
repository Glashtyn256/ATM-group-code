#include "CurrentAccount.h"

CurrentAccount::CurrentAccount():overdraftLimit(0){}

double CurrentAccount::getOverdraftLimit() const
{
	return overdraftLimit;
}

double CurrentAccount::maxBorrowable() const {
	//return borrowable amount
	return BankAccount::maxBorrowable() + overdraftLimit;
}

// Input / Output

ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) CurrentAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << overdraftLimit << "\n";					//put overdraft
	return os;
}
istream& CurrentAccount::getAccountDataFromStream(istream& is) {
	//get CurrentAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> overdraftLimit;							//get overdraft
	return is;
}

const string CurrentAccount::prepareFormattedAccountDetails() const
{
	string message = BankAccount::prepareFormattedAccountDetails();
	ostringstream os;
	os << message;
	os << "\n      OVERDRAFT LIMIT: "<< setw(10) << "\234" << overdraftLimit;
	os << "\n      ----------------------------------------";

	return os.str();
}

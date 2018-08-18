#include "ChildAccount.h"

ChildAccount::ChildAccount():maximumPaidIn(0), minimumPaidIn(0){}

double ChildAccount::getMaximumPaidIn() const
{
	return maximumPaidIn;
}

double ChildAccount::getMinimumPaidIn() const
{
	return minimumPaidIn;
}

bool ChildAccount::canWithdraw(double amount) const
{
	return false;
}

bool ChildAccount::canDeposit(double amount) const {
	return (amount >= minimumPaidIn && amount <= maximumPaidIn);
}
const string ChildAccount::prepareFormattedAccountDetails() const
{
	string message = SavingsAccount::prepareFormattedAccountDetails();
	ostringstream os;
	os << message;
	os << "\n      MAXIMUM PAID IN: " << setw(10) << "\234" << maximumPaidIn;
	os << "\n      MINIMUM PAID IN: " << setw(10) << "\234" << minimumPaidIn;
	os << "\n      ----------------------------------------";

	return os.str();
}

// Input / Output

ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) CurrentAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << minimumPaidIn << "\n";					//put minium paid in
	os << maximumPaidIn << "\n";					//put maximumPaidIn
	return os;
}
istream& ChildAccount::getAccountDataFromStream(istream& is) {
	//get CurrentAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);
	is >> minimumPaidIn;							//get minium paid in
	is >> maximumPaidIn;							//get maximum paid in
	return is;
}
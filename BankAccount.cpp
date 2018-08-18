//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "BankAccount.h"
#include "Constants.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
	: balance_(0.0)
{}
BankAccount::~BankAccount()
{}


//____other public member functions

const string BankAccount::getAccountNumber() const {
	return accountNumber_;
}
const Date BankAccount::getCreationDate() const {
	return creationDate_;
}
double BankAccount::getBalance() const {
	return balance_;
}
const TransactionList BankAccount::getTransactions() const {
	return transactions_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}
void BankAccount::produceTransactionsUpToDate(const Date & d, string* const str, int* const _size) const
{
	TransactionList trl = transactions_.getTransactionsUpToDate(d);
	*_size = trl.size();
	*str = trl.toFormattedString();
}

//static
const string BankAccount::getAccountType(const string& filename) {
	return getAccountType(filename[13]); //14th char from the filename ("data/account_101.txt")
}
//static
const string BankAccount::getAccountType(char n) {
	//return account type ("BANK" for '0', "CURRENT" for '1', etc. or "UNKNOWN") 
	//(simply) identify type/class of account from the account number
	//'0' for bank account, '1' for current account, '2' for saving account, etc.
	switch (n)
	{
	//case BANKACCOUNT_TYPE:		return "BANK"; break;
	//case SAVINGSACCOUNT_TYPE:   return "SAVING"; break;
	case CURRENTACCOUNT_TYPE:	return "CURRENT"; break;
	case CHILDACCOUNT_TYPE:	    return "CHILD"; break;
	case ISAACCOUNT_TYPE:	    return "ISAACCOUNT"; break;
//etc..
	default:					return "UNKNOWN";
	}
}

void BankAccount::recordDeposit(double amountToDeposit) {
	//create a deposit transaction
	Transaction aTransaction("deposit_to_ATM", amountToDeposit);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(amountToDeposit);			//increase balance_
}

void BankAccount::recordTransferIn(double amountToDeposit, const string& depositedFrom) {
	//create a deposit transaction
	Transaction inTransaction("transfer_in_from_acc_" + depositedFrom, amountToDeposit);
	//update active bankaccount
	transactions_.addNewTransaction(inTransaction);		//update transactions_
	updateBalance(amountToDeposit);						//increase balance_
}

bool BankAccount::canDeposit(double amount) const
{
	return true;
}

double BankAccount::maxBorrowable() const {
	//return borrowable amount
	return balance_;
}
bool BankAccount::canWithdraw(double amountToWithdraw) const {
	//check if enough money in account
	return amountToWithdraw <= maxBorrowable();
}

void BankAccount::recordWithdrawal(double amountToWithdraw) {
	//create a withdrawal transaction
	Transaction aTransaction("withdrawal_from_ATM", -amountToWithdraw);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-amountToWithdraw);			//decrease balance_
}

void BankAccount::recordTransferOut(double amountToWithdraw, const string& sentTo) {
	//create a withdrawal transaction
	Transaction aTransaction("transfer_out_to_acc_" + sentTo, -amountToWithdraw);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-amountToWithdraw);			//decrease balance_
}

void BankAccount::recordDeletionOfTransactionUpToDate(const Date& d)
{
	transactions_.deleteTransactionsUpToDate(d);
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}
void BankAccount::readInBankAccountFromFile(const string& fileName) {
	ifstream fromFile;
	fromFile.open(fileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		fromFile >> (*this);  	//read  all info from bank account file
	fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\n      AN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
		toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& BankAccount::putDataInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	putAccountDetailsInStream(os);			//put bank account core information in stream
	putTransactionInStream(os);				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putTransactionInStream(ostream& os) const {
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions in stream, one per line
	return os;
}
ostream& BankAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountNumber_ << "\n";			//put account number
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& BankAccount::getDataFromStream(istream& is) {
	//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	getTransactionsDataFromStream(is);		//get all transactions from stream (if any)
	return is;
}
istream& BankAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountNumber_;					//get account number
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}
istream& BankAccount::getTransactionsDataFromStream(istream& is) {
	is >> transactions_;					//get all transactions from stream (if any)
	return is;
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------
void BankAccount::updateBalance(double amount) {
	balance_ += amount;   //add/take amount to/from balance_
}
const string BankAccount::prepareFormattedAccountDetails() const
{
	assert(getAccountType(accountNumber_[0]) != "UNKNOWN");
	ostringstream os;

	os << "\n      ACCOUNT TYPE:    " << getAccountType(accountNumber_[0]) << " ACCOUNT";
	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << "\n      CREATION DATE:   " << creationDate_.toFormattedString();
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE:         \234" << setw(10) << balance_;
	os << "\n      ----------------------------------------";
	return os.str();
}

const string BankAccount::prepareFormattedTransactionList() const
{
	ostringstream os;

	if (!transactions_.size() == 0)
	{
		os << "\n      TRANSACTIONS:";
		os << transactions_.toFormattedString();
	}
	else
	{
		os << "\n      NO TRANSACTIONS IN BANK ACCOUNT!";
	}

	return os.str();
}

const string BankAccount::prepareFormattedMiniAccountDetails() const
{
	ostringstream os;

	os << "\n	   ";
	os << "\n      ACCOUNT NUMBER:  " << accountNumber_;
	os << "\n      SORT CODE:   "; // <<	IMPLEMENT THIS
	os << fixed << setprecision(2) << setfill(' ');
	os << "\n      BALANCE:         \234" << setw(10) << balance_;
	os << "\n      AVAILABLE FUNDS:         \234" << setw(10) << maxBorrowable();
	os << "\n      ----------------------------------------";

	return os.str();

}

void BankAccount::produceNMostRecentTransactions(const int& nTransactions, string* const str, double* const total) const
{
	TransactionList trl = transactions_.getMostRecentTransactions(nTransactions);
	*total = trl.getTotalTransactions();
	*str = trl.toFormattedString();
}

//void BankAccount::produceTransactionsForAmount(double amount, string* message) const 
//{
//	TransactionList* tri = transactions_.getTransactionsForAmount(amount);
//}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
	//put (unformatted) BankAccount details in stream
	return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
	//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}

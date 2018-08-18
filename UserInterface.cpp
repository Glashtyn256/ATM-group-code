//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "UserInterface.h"

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

void UserInterface::wait() const
{
	cout << "\n";
	outputLine("Press RETURN to go back to menu...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
void UserInterface::endProgram() const
{
	cout << "\n";
	outputLine("Press RETURN to end program...");
	char ch;
	cin.get(ch);
	cin.get(ch);
}
int UserInterface::showMainMenuAndGetCommand() const
{
	system("cls");
	cout << "\n\n";
	outputHeader("WELCOME TO THE ATM");
	outputLine(" 0                            Leave ATM ");
	outputLine(" 1                      Enter your card ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

int UserInterface::showAccountMenuAndGetCommand(const string& accNum) const
{
	outputHeader("ACCOUNT " + accNum + " MENU");
	outputLine(" 0                    Back to card menu ");
	outputLine(" 1                      Display balance ");
	outputLine(" 2                Withdraw from account ");
	outputLine(" 3                 Deposit into account ");
	outputLine(" 4                       Show statement ");
	outputLine(" 5                    Show all deposits ");
	outputLine(" 6                  Show mini statement ");
	outputLine(" 7                  Search Transactions ");
	outputLine(" 8    Clear all transactions up to date ");
	outputLine(" 9          Transfer to another account ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

const string UserInterface::readInCardToBeProcessed() const {
	return askForInput("ENTER YOUR CARD NUMBER");
}

void UserInterface::showValidateCardOnScreen(int validCode, const string& cardNumber) const
{
	switch (validCode)
	{
	case VALID_CARD: {
		// Card exists and is accessible (and is not already open: TO BE IMPLEMENTED)
	} break;
	case UNKNOWN_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT EXIST");
	} break;
	case EMPTY_CARD: {
		outputLine("ERROR: CARD " + cardNumber + " DOES NOT LINK TO ANY ACCOUNTS");
	} break;
	}
}

int UserInterface::showCardMenuAndGetCommand(const string& cardNumber) const
{
	outputHeader("CARD " + cardNumber + " MENU");
	outputLine(" 0           Stop banking & remove card ");
	outputLine(" 1            Manage individual account ");
	outputLine(" 2           Show total funds available ");
	outputLine("----------------------------------------");
	return (readInCommand());
}

void UserInterface::showCardAccounts(const string& cardNumber, const string& cardDetails) const
{
	outputHeader("CARD " + cardNumber + " ACCOUNTS");
	cout << cardDetails;
	outputLine("----------------------------------------\n");
}

const string UserInterface::readInAccountToBeProcessed() const {
	return askForInput("SELECT ACCOUNT TO MANAGE");
}

void UserInterface::showValidateAccountOnScreen(int validCode, const string& accNum) const
{
	switch (validCode)
	{
	case VALID_ACCOUNT:
	{
		outputLine("ACCOUNT " + accNum + " IS VALID...");
		// Account exists and is accessible with that card (and not already open: TO BE IMPLEMENTED)
	} break;
	case DUPLICATE_ACCOUNT: {
		outputLine("CAN'T TRANSFER TO SAME ACCOUNT " + accNum + "!");
	} break;
	case INVALID_ACCOUNT_TYPE:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT A RECOGNISED TYPE OF ACCOUNT!");
	} break;
	case UNKNOWN_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " DOES NOT EXIST!");
	} break;
	case UNACCESSIBLE_ACCOUNT:
	{
		outputLine("ERROR: ACCOUNT " + accNum + " IS NOT ACCESSIBLE WITH THIS CARD!");
	} break;
	}
}

void UserInterface::showTransactionsUpToDateOnScreen(const bool & isEmpty, const Date & d, const int & size, const string & message) const
{
	if (isEmpty) {
		outputLine("NO TRANSACTIONS IN BANK ACCOUNT");
	}
	else if (size > 0)	{
		outputLine(size + " TRANSACTIONS UP TO " + d.toFormattedString() + " WERE FOUND");
		cout << "\n" << message;
		outputLine("----------------------------------------\n");
	}
	else {
		outputLine("NO TRANSACTIONS UP TO " + d.toFormattedString() + " WERE FOUND");
	}
}

void UserInterface::showDeletionOfTransactionsUpToDateOnScreen(const int & size, const Date & d, const bool & deletionConfirmed) const
{
	if (deletionConfirmed)
		outputLine(to_string(size) + " TRANSACTIONS IN BANK ACCOUNT UP TO DATE " + d.toFormattedString() + " HAVE BEEN DELETED");
	else
		outputLine("DELETION OPERATION HAS BEEN CANCELLED");
}


void UserInterface::showFundsAvailableOnScreen(const bool& empty, const string& message, const double& total) const
{
	if (!empty) {
		outputLine("ALL ACCOUNTS MINI DETAILS");
		cout << message << "\n";
		stringstream temp;
		temp << "TOTAL FUNDS AVAILABLE ACROSS ALL ACCOUNTS: \234" << total;
		
		outputLine(temp.str());
	}
}

//static 
const string UserInterface::cardFilename(const string& cn) {
	//read in card name & produce cashcard filename
	return FILEPATH + "card_" + cn + ".txt";	//read in card name & produce cashcard filename
}
//static
const string UserInterface::accountFilename(const string& an) {
	return FILEPATH + "account_" + an + ".txt";
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
	//ask for the amount to withdraw
	outputLine("AMOUNT TO WITHDRAW: \234");
	return (readInPositiveAmount());
}
double UserInterface::readInTransferAmount() const {
	//ask for the amount to withdraw
	outputLine("AMOUNT TO TRANSFER: \234");
	return (readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
	//ask for the amount to deposit
	outputLine("AMOUNT TO DEPOSIT: \234");
	return (readInPositiveAmount());
}

int UserInterface::readInNumberOfTransactions() const
{
	//ask for the amount to deposit
	outputLine("NUMBER OF TRANSACTIONS: ");
	return (static_cast<int>(readInPositiveAmount()));
}
int UserInterface::readInSearchCommand() const 
{
	outputLine("OPTION: ");
	int opt = static_cast<int>( readInPositiveAmount());


	
	// If user hasn't entered a vaild command
	while (!(opt >= 1 && opt <= 4)) {
		showErrorInvalidCommand();
		outputLine("OPTION: ");
		opt = static_cast<int>(readInPositiveAmount());
	}

	return opt;
}
Date UserInterface::readInValidDate(const Date & cd) const
{
	Date date;
	outputLine("Format: dd/mm/yyyy");
	outputLine("Date to delete up to: ");
	cin >> date;

	while (!date.isValid(cd))
	{
		outputLine("ERROR, DATE INVALID");
		outputLine("Date to delete up to: ");
		cin >> date;
	}

	return date;
}
bool UserInterface::readInConfirmDeletion() const
{
	char option;
	outputLine("WOULD YOU LIKE TO THE DELETE TRANSACTIONS?");
	outputLine("PLEASE ENTER Y(yes) OR N(no)\n      ");
	cin >> option;

	while (option != 'y' && option != 'Y' && option != 'n' && option != 'N') {
		outputLine("INVALID CHOICE, Y(yes) OR N(no)\n");
		cin >> option;
	}
	outputLine("----------------------------------------\n");
	outputLine("");

	return toupper(option) == 'Y' ? true : false;
}
//output functions

void UserInterface::showProduceBalanceOnScreen(double balance) const
{
	cout << "\n      THE CURRENT BALANCE IS: " << fixed << setprecision(2) << setfill(' ') << "\234" << setw(12) << balance;
}

void UserInterface::showWithdrawalOnScreen(bool trAuthorised, double withdrawnAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << withdrawnAmount << " WITHDRAWN FROM ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // not enough money
	}
}

void UserInterface::showDepositOnScreen(bool trAuthorised, double depositAmount) const
{
	if (trAuthorised)
	{
		cout << "\n      TRANSACTION AUTHORISED. \234" << setw(0) << depositAmount << " DEPOSITED INTO ACCOUNT";
	}
	else
	{
		outputLine("TRANSACTION IMPOSSIBLE!"); // too much to deposit
	}
}
void UserInterface::showStatementOnScreen(const string& statement) const {
	outputHeader("PREPARING STATEMENT...");
	cout << statement;
	outputLine("----------------------------------------\n");
}

void UserInterface::showMiniStatementOnScreen(const bool& isEmpty, const double& total, const string& message) const
{
	outputHeader("PREPARING STATEMENT...");
	if (isEmpty) {
		outputLine("\n      NO TRANSACTIONS IN BANK ACCOUNT.");
	}
	else {
		cout << message;
		cout << "\n\n      DISPLAYED TRANSACTIONS TOTAL: " << total;
	}
	outputLine("----------------------------------------\n");
}

void UserInterface::showNoTransactionsOnScreen() const
{
	cout << "\n      NO TRANSACTIONS IN BANK ACCOUNT";
}

void UserInterface::showSearchMenu() const {
	outputHeader("SEARCH FOR TRANSACTION");
	outputLine(" 1           Show transactions for amount ");
	outputLine(" 2           Show transactions for title ");
	outputLine(" 3           Show transactions for date");
	outputLine(" 4           Exit without searching");
	outputLine("----------------------------------------");
}

void UserInterface::showTransferOnScreen(const bool& trOutOK, const bool&  trInOK, const double&  transAmount) const
{
	outputHeader("TRANSFER ATTEMPT:");

	if (trOutOK && trInOK)
	{
		cout << "\n\tTRANSFER OF \234 " << transAmount << " SUCCESSFUL";
	}
	else if (!trOutOK)
	{
		cout << "\n\tINSUFFICIENT FUNDS IN THIS ACCOUNT TO TRANSFER \234" << transAmount;
	}
	else if (!trInOK) {
		cout << "\n\tACCOUNT CANNOT RECEIVE THE PROPOSED \234 " << transAmount;
	}
}

//---------------------------------------------------------------------------
// private support member functions
//---------------------------------------------------------------------------

// SINGLETON PATTERN
UserInterface * UserInterface::GetInstance()
{
	static UserInterface userInterface;
	return &userInterface;
}

//--------------------------

void UserInterface::showByeScreen() const
{
	outputLine("");
	outputHeader("THANK YOU FOR USING THE ATM");
	endProgram();
}

int UserInterface::readInCommand() const
{
	cout << "\n";
	outputLine("ENTER YOUR COMMAND: ");
	int com;
	cin >> com;
	return com;
}

void UserInterface::showErrorInvalidCommand() const
{
	outputLine("INVALID COMMAND CHOICE, TRY AGAIN");
}

double UserInterface::readInPositiveAmount() const
{
	double amount;
	cin >> amount;

	while (amount <= 0.0)
	{
		outputLine("AMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ");
		cin >> amount;
	}

	return amount;
}

void UserInterface::outputHeader(const string& header) const
{
	// calculate lengths so we can centre the header
	const int length = header.size();
	const int borderWidth = 40;
	const int leftSpacePad = 6;
	const int paddingRequired = ((borderWidth - length) / 2) + leftSpacePad;

	outputLine("========================================");
	cout << "\n" << setfill(' ') << setw(paddingRequired) << ' ' << header;
	outputLine("========================================");
}

string UserInterface::askForInput(const string& promptForUser) const
{
	outputLine(promptForUser + ": ");
	string userInput;
	cin >> userInput;
	return userInput;
}

void UserInterface::outputLine(const string& text) const
{
	cout << "\n      " << text;
}
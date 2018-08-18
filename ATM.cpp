//Pascale Vacher - February 18
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "ATM.h"

//---------------------------------------------------------------------------
//ATM: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

ATM::ATM()
	: p_theActiveAccount_(nullptr), p_theCard_(nullptr), theUI_(*UserInterface::GetInstance())
{}

ATM::~ATM()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCard_ == nullptr);
}

//____other public member functions

void ATM::activateCashPoint() {
	int command(theUI_.showMainMenuAndGetCommand());
	while (command != QUIT_COMMAND)
	{
		executeCardCommand(command);
		theUI_.wait();
		command = theUI_.showMainMenuAndGetCommand();
	}
	theUI_.showByeScreen();
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void ATM::executeCardCommand(int option) {
	switch (option)
	{
	case 1:
	{
		string cardNum(theUI_.readInCardToBeProcessed());
		string cardFilename(theUI_.cardFilename(cardNum));
		int validCardCode(validateCard(cardFilename));
		theUI_.showValidateCardOnScreen(validCardCode, cardNum);
		if (validCardCode == VALID_CARD)
		{
			//dynamically create a card and store card data
			activateCard(cardFilename);

			//select request for active card 
			int option = theUI_.showCardMenuAndGetCommand(cardNum);
			while (option != QUIT_COMMAND)
			{
				switch (option)
				{
				case 1: m_card1_manageIndividualAccount();
					break;
				case 2: m_card2_showFundsAvailableOnAllAccounts();
					break;
				default:
					theUI_.showErrorInvalidCommand();
				}

				theUI_.wait();
				option = theUI_.showCardMenuAndGetCommand(cardNum);
			}

			//free memory space used by active card
			releaseCard();
		}
		break;
	}
	default:theUI_.showErrorInvalidCommand();
	}
}
void ATM::m_card1_manageIndividualAccount() {
	assert(p_theCard_ != nullptr);
	theUI_.showCardAccounts(p_theCard_->getCardNumber(), p_theCard_->toFormattedString());
	executeAccountCommand();
}
void ATM::m_card2_showFundsAvailableOnAllAccounts() {
	assert(p_theCard_ != nullptr);

	//string containing all accounts mini account details
	string mad = "";
	//total available funds
	double m = 0;
	//list of accounts associated with the card
	List<string> accts = p_theCard_->getAccountsList();
	//bool for is empty
	bool empty = accts.isEmpty();

	while (!accts.isEmpty())
	{
		string filename = theUI_.accountFilename(accts.first());

		//dynamically create bank account to store data from file
		p_theActiveAccount_ = activateAccount(filename);
		
		m += p_theActiveAccount_->maxBorrowable();
		mad += p_theActiveAccount_->prepareFormattedMiniAccountDetails();

		//release the account from memory
		p_theActiveAccount_ = releaseAccount(p_theActiveAccount_, filename);
		accts.deleteFirst();
	}

	theUI_.showFundsAvailableOnScreen(empty, mad, m);
}

int ATM::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
		return UNKNOWN_CARD;
	else
		//card empty (exist but no bank account listed on card)
		if (!accountsListedOnCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}
int ATM::validateAccount(const string& filename) const {
	//check that the account is valid 
	//NOTE: MORE WORK NEEDED here in case of transfer


	// This should still fail if there isn't an active account though.
	if (p_theActiveAccount_ != nullptr)
	{
		string activeAccountFilename = theUI_.accountFilename(p_theActiveAccount_->getAccountNumber());

		if (filename == activeAccountFilename)
			return DUPLICATE_ACCOUNT;
	}


	if (!canOpenFile(filename))
		//account does not exist
		return UNKNOWN_ACCOUNT;
	else
		//account type not recognised
		if (BankAccount::getAccountType(filename) == "UNKNOWN")
			//if (getAccountTypeCode(filename) == UNKNOWN_ACCOUNT_TYPE)
			return INVALID_ACCOUNT_TYPE;
		else
			//unaccessible account (exists but not listed on card)
			if (!p_theCard_->onCard(filename))
				return UNACCESSIBLE_ACCOUNT;
			else
				//account valid (exists and accessible)
				return VALID_ACCOUNT;
}
void ATM::executeAccountCommand() {
	assert(p_theActiveAccount_ == nullptr);
	//process from one account
	//select active account and check that it is valid
	const string anAccountNumber(theUI_.readInAccountToBeProcessed());
	const string bankAccountFilename(theUI_.accountFilename(anAccountNumber));
	const int validAccountCode(validateAccount(bankAccountFilename));
	theUI_.showValidateAccountOnScreen(validAccountCode, anAccountNumber);
	if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card and not already open
	{
		//dynamically create a bank account to store data from file
		p_theActiveAccount_ = activateAccount(bankAccountFilename);

		//select request for active account 
		int option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());
		while (option != QUIT_COMMAND)
		{
			switch (option)
			{
			case 1:	m_acct1_produceBalance();
				break;
			case 2: m_acct2_withdrawFromBankAccount();
				break;
			case 3:	m_acct3_depositToBankAccount();
				break;
			case 4:	m_acct4_produceStatement();
				break;
				// case 5 = Tutorial :)
					// break;
			case 6: m_acct6_showMiniStatement();
				break;
			case 7: m_acct7_searchForTransactions();
				break;
			case 8: m_acct8_clearTransactionsUpToDate();
				break;
			case 9: m_acct9_transferCashToAnotherAccount();
				break;

			default:theUI_.showErrorInvalidCommand();
			}
			theUI_.wait();
			option = theUI_.showAccountMenuAndGetCommand(p_theActiveAccount_->getAccountNumber());   //select another option
		}

		//store new state of bank account in file and free bank account memory space
		p_theActiveAccount_ = releaseAccount(p_theActiveAccount_, bankAccountFilename);
	}
}


void ATM::searchTransactions() const {
	theUI_.showSearchMenu();
	int opt = theUI_.readInSearchCommand();

	switch (opt) {
	case 1: // Show transactions for amount
		m_trl1_showTransactionsForAmount();
		break;
	case 2: // Show transactions for title
		sm2_showTransactionsForTitle();
		break;
	case 3: // Show transactions for date
		sm3_showTransactionsForDate();
		break;
	case 4: // Exit without searching
		break;
	}
}

//----search for transactions menus----

//-transaction search-->option 1
void ATM::m_trl1_showTransactionsForAmount() const
{
	assert(p_theActiveAccount_ != nullptr);
	double a(0);
	do {
		a = theUI_.readInSearchCriterion<double>();
	} while (a <= 0);
	string message;
	int total(0);
	bool isEmpty(false);
	p_theActiveAccount_->produceTransactionsForCriterion<double>(a, &message, &total);
	theUI_.showMatchingTransactionsOnScreen(a, total, message);
}

void ATM::sm2_showTransactionsForTitle() const
{
	assert(p_theActiveAccount_ != nullptr);
	string a;
	do {
		a = theUI_.readInSearchCriterion<string>();
	} while (a.length() <= 0);
	string message;
	int total(0);
	bool isEmpty(false);
	p_theActiveAccount_->produceTransactionsForCriterion<string>(a, &message, &total);
	theUI_.showMatchingTransactionsOnScreen(a, total, message);
}

void ATM::sm3_showTransactionsForDate() const
{
	assert(p_theActiveAccount_ != nullptr);
	Date d = theUI_.readInSearchCriterion<Date>();

	// Checks if date is vaild
	while (!d.isValid(p_theActiveAccount_->getCreationDate())) {
		cout << "\n      " << d << " IS NOT VALID, PLEASE TRY AGAIN." << endl;
		d = theUI_.readInSearchCriterion<Date>();
	}

	string message;
	int total(0);
	bool isEmpty(false);
	p_theActiveAccount_->produceTransactionsForCriterion<Date>(d, &message, &total);
	theUI_.showMatchingTransactionsOnScreen(d, total, message);
}

//------ menu options
//---option 1
void ATM::m_acct1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen(balance);
}
//---option 2
void ATM::m_acct2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_.readInWithdrawalAmount());
	bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
	if (transactionAuthorised)
	{   //transaction is accepted: money can be withdrawn from account
		p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
	}   //else do nothing
	theUI_.showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void ATM::m_acct3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_.readInDepositAmount());

	bool canDeposit = p_theActiveAccount_->canDeposit(amountToDeposit);

	if (canDeposit)
		p_theActiveAccount_->recordDeposit(amountToDeposit);

	theUI_.showDepositOnScreen(canDeposit, amountToDeposit);
}
//---option 4
void ATM::m_acct4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//---option 6
void ATM::m_acct6_showMiniStatement() const {
	assert(p_theActiveAccount_ != nullptr);

	cout << "\n      RECENT TRANSACTIONS REQUESTED AT " << Time::currentTime() << " ON " << Date::currentDate() << endl;

	string message;
	double total;

	if (!(p_theActiveAccount_->isEmptyTransactionList())) {
		int numOfTransactions = theUI_.readInNumberOfTransactions();
		p_theActiveAccount_->produceNMostRecentTransactions(numOfTransactions, &message, &total);
	}

	string mad = p_theActiveAccount_->prepareFormattedMiniAccountDetails();
	//according to sequence diagram total is passed to showMiniStatementOnScreen, but therefore cannot be displayed with transactions
	theUI_.showMiniStatementOnScreen(p_theActiveAccount_->isEmptyTransactionList(), total, mad + message);
}

//---option 7
void ATM::m_acct7_searchForTransactions() const {
	assert(p_theActiveAccount_ != nullptr);
	if (p_theActiveAccount_->isEmptyTransactionList()) {
		theUI_.showNoTransactionsOnScreen();
	}
	else {
		searchTransactions();
	}
}
//---option 8
void ATM::m_acct8_clearTransactionsUpToDate() {
	assert(p_theActiveAccount_ != nullptr);
	string message; //message to display transaction list
	int _size = 0;	//number of transactions
	Date d;

	//is the transaction list empty or not?
	bool isEmpty = p_theActiveAccount_->isEmptyTransactionList();

	if (!isEmpty) {
		Date cd = p_theActiveAccount_->getCreationDate();	//creation date of the account
		d = theUI_.readInValidDate(cd);   //date being deleted 

		p_theActiveAccount_->produceTransactionsUpToDate(d, &message, &_size);
	}

	theUI_.showTransactionsUpToDateOnScreen(isEmpty, d, _size, message);

	if (!isEmpty && message.length() > 0) {
		bool deletionConfirmed = theUI_.readInConfirmDeletion();
		if (deletionConfirmed)
			p_theActiveAccount_->recordDeletionOfTransactionUpToDate(d);
		theUI_.showDeletionOfTransactionsUpToDateOnScreen(_size, d, deletionConfirmed);
	}
}
//---option 9
void ATM::m_acct9_transferCashToAnotherAccount() {
	assert(p_theActiveAccount_ != nullptr);

	const string outAccountFString = p_theCard_->toFormattedString();			//	1	Fetch active card information
	theUI_.showCardAccounts(p_theCard_->getCardNumber(), outAccountFString);	//	2	Display accounts on this card
	const string inString = theUI_.readInAccountToBeProcessed();				//	3	User Inputs an acc number
	const string inAccountFString = theUI_.accountFilename(inString);			//	4	UI func turns that to an acc filename
	int incode = validateAccount(inAccountFString);								//	5	Check input is a valid account
	theUI_.showValidateAccountOnScreen(incode, inString);						//	6	Display progress based on account code

	if (incode == VALID_ACCOUNT) {												//	GUARD
		BankAccount* tempAccount = activateAccount(inAccountFString);			//	7	Receiving transfer account activated
		attemptTransfer(tempAccount);											//	8	Attempt transfer

		releaseAccount(tempAccount, inAccountFString);							//	9	Release the receiving account.
	}
}
//------private file functions

bool ATM::canOpenFile(const string& filename) const {
	//check if a file already exist
	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail() return true
	return (!inFile.fail());	//close file automatically when inFile goes out of scope
}

bool ATM::accountsListedOnCard(const string& cashCardFileName) const {
	//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
	assert(!inFile.fail()); //file should exist at this point 
	//check that it contains some info in addition to card number
	string temp;
	inFile >> temp; //read card number
	inFile >> temp;	//ready first account data or eof if end of file found
	return (!inFile.eof());
}

void ATM::activateCard(const string& filename) {
	//dynamically create a cash card to store data from file
	//effectively create the cash card instance with the data
	assert(p_theCard_ == nullptr);
	p_theCard_ = new Card;
	assert(p_theCard_ != nullptr);
	p_theCard_->readInCardFromFile(filename);
}

void ATM::releaseCard() {
	//release the memory allocated to the dynamic instance of a card
	delete p_theCard_;
	p_theCard_ = nullptr;
}
//static member function
char ATM::getAccountTypeCode(const string& filename) {
	//(simply) identify type/class of account from the account number
	//starts with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return filename[13]; //14th char from the filename ("data/account_101.txt")
}

BankAccount* ATM::activateAccount(const string& filename) {
	//Pre-condition: type of the account is valid
	assert(BankAccount::getAccountType(filename) != "UNKNOWN");						//	TRANSFER 7.1
	//effectively create the active bank account instance of the appropriate class
	//and store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch (getAccountTypeCode(filename))											//	TRANSFER 7.2 - CAUTION
	{
		//case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
		//	p_BA = new BankAccount;    //points to a BankAccount object
		//	break;
	case CURRENTACCOUNT_TYPE:
		p_BA = new CurrentAccount;
		break;
	case ISAACCOUNT_TYPE:
		p_BA = new ISAAccount;
		break;
	case CHILDACCOUNT_TYPE:
		p_BA = new ChildAccount;
		break;
	}
	assert(p_BA != nullptr); //check that the dynamic allocation has succeeded
	p_BA->readInBankAccountFromFile(filename); //read account details from file		//	TRANSFER 7.3
	//use dynamic memory allocation: the bank account created will have to be released in releaseAccount
	return p_BA;
}

BankAccount* ATM::releaseAccount(BankAccount* p_BA, string filename) {
	//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}

void ATM::attemptTransfer(BankAccount * receiveAccount) {						//	8 received
	const double transAmount = theUI_.readInTransferAmount();						//	8.1
	const bool trOutOK = p_theActiveAccount_->canWithdraw(transAmount);				//	8.2
	const bool trInOK = receiveAccount->canDeposit(transAmount);					//	8.3

	if (trInOK && trOutOK)
	{
		recordTransfer(transAmount, receiveAccount);								//	8.4 call
	}

	theUI_.showTransferOnScreen(trOutOK, trInOK, transAmount);						//	8.5
}

void ATM::recordTransfer(double amount, BankAccount* receiveAccount) {			//	8.4 received

	string tAN = receiveAccount->getAccountNumber();								//	8.4.1
	string aAN = p_theActiveAccount_->getAccountNumber();							//	8.4.2

	p_theActiveAccount_->recordTransferOut(amount, tAN);							//	8.4.3
	receiveAccount->recordTransferIn(amount, aAN);									//	8.4.4
}
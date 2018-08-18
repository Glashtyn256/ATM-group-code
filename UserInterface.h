//Matt Perkins
//Tom Dunn
//Adam Pusey
//Ben Moore- February 18
//OOP Assignment Task 1c - Semester 2
//Group Number: 3



#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class UserInterface {
public:
	// SINGLETON PATTERN
	static UserInterface* GetInstance();
	//---------------

	void showByeScreen() const;

	int showMainMenuAndGetCommand() const;
	int showCardMenuAndGetCommand(const string& cardNum) const;
	int showAccountMenuAndGetCommand(const string& accNum) const;

	void showErrorInvalidCommand() const;
	void wait() const;
	void endProgram() const;
	const string readInCardToBeProcessed() const;
	void showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void showCardAccounts(const string& cardNum, const string& cardSt) const;
	const string readInAccountToBeProcessed() const;
	void showValidateAccountOnScreen(int valid, const string& acctNum) const;
	void showTransactionsUpToDateOnScreen(const bool& isEmpty, const Date& d, const int& size, const string& message) const;
	void showDeletionOfTransactionsUpToDateOnScreen(const int& size, const Date& d, const bool& deletionConfirmed) const;
	void showFundsAvailableOnScreen(const bool& empty, const string& message, const double& total) const;

	static const string cardFilename(const string& cn);
	static const string accountFilename(const string& an);

	double readInWithdrawalAmount() const;
	double readInTransferAmount() const;
	double readInDepositAmount() const;
	int readInNumberOfTransactions() const;
	int readInSearchCommand() const;
	Date readInValidDate(const Date& cd) const;
	bool readInConfirmDeletion() const;

	//! new template readInCriterion !
	template <class C>
	C readInSearchCriterion() const {
		C criterion;
		outputLine("CRITERIA: ");
		cin >> criterion;
		return criterion;
	};

	void showProduceBalanceOnScreen(double bal) const;
	void showDepositOnScreen(bool auth, double deposit) const;
	void showWithdrawalOnScreen(bool auth, double withdrawal) const;
	void showStatementOnScreen(const string&) const;
	void showMiniStatementOnScreen(const bool& isEmpty, const double& total, const string&) const;
	void showNoTransactionsOnScreen() const;
	void showSearchMenu() const;

	void showTransferOnScreen(const bool& trOutOK, const bool& trInOK, const double& transAmount) const;

	template <class C>
	void showMatchingTransactionsOnScreen(const C& criterion, const int& total, const string& message) const {
		outputHeader("PREPARING SEARCH RESULTS...");
		if (total > 0) {
			cout << "\n      Transactions matching " << criterion << ":\n";
			cout << message;
			cout << "\n\n      THERE ARE " << total << " TRANSACTIONS IN BANK ACCOUNT MATCHING THAT SEARCH CRITERION";
		}
		else {
			outputLine("\n      NO TRANSACTIONS IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN\n");
		}
		outputLine("----------------------------------------\n");
	};

private:
	//Ensures nobody can make an instance of UserInterface
	UserInterface() = default;
	~UserInterface() = default;
	UserInterface(const UserInterface& userInterface) = delete;
	UserInterface& operator=(const UserInterface& userInterface) = delete;
	//--------------------------------------------------

	//support functions
	int readInCommand() const;
	double readInPositiveAmount() const;
	void outputHeader(const string&) const;
	string askForInput(const string&) const;
	void outputLine(const string&) const;
};

#endif
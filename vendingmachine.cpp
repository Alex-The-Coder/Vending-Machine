#include <iostream>
using namespace std;

const int NO_SUCH_ITEM = -2;
const int USER_QUITTING = -3;

const int ONE_VALUE = 100;
const int QUARTER_VALUE = 25;
const int DIME_VALUE = 10;
const int NICKEL_VALUE = 5;

int min(int, int);

double getMoneyForDisplay(int);

void setupMachine(int&, int&, int&);

int selectOption();

int requestMoney(int, int&, int&, int&, int&);

void dispenseChange(int, int&, int&, int&, int&);

int main()
{
	int ones;
	int quarters;
	int dimes;
	int nickels;

	ones = 0;
	setupMachine(nickels, dimes, quarters);

	//Constantly display options
	while (true)
	{
		int cost = selectOption();

		//If an item was chosen
		if (cost > 0)
		{
			int change = requestMoney(cost, nickels, dimes, quarters, ones);
			dispenseChange(change, nickels, dimes, quarters, ones);
			cout << endl;
		}
		//If the item selected is not an option
		else if (cost == NO_SUCH_ITEM)
		{
			cout << "Invalid selection! Please try again!" << endl;
			continue;
		}

		//Display stock of coins
		cout << "Machine Internal Stock:" << endl;
		cout << ones << " one-dollar bill(s)" << endl;
		cout << quarters << " quarter(s)" << endl;
		cout << dimes << " dime(s)" << endl;
		cout << nickels << " nickel(s)" << endl;

		if (cost == USER_QUITTING)
		{
			//Calculate total value of coins in stock
			cout << "Machine Currency Total: $" << getMoneyForDisplay((ones * ONE_VALUE) + (quarters * QUARTER_VALUE) + (dimes * DIME_VALUE) + (nickels * NICKEL_VALUE)) << "!" << endl;
			return 0;
		}
		cout << endl;
	}

	return 0;
}

int min(int a, int b)
{
	return a > b ? b : a;
}

double getMoneyForDisplay(int internalMoney)
{
	return static_cast<double>(internalMoney) / 100.0;
}

void setupMachine(int& nickels, int& dimes, int& quarters)
{
	cout << "Greetings user. Vending Machine ready." << endl;
	cout << "Pre-loading Currency:" << endl;

	cout << "Quarters:" << endl;
	cin >> quarters;
	cout << endl << "Dimes:" << endl;
	cin >> dimes;
	cout << endl << "Nickels:" << endl;
	cin >> nickels;

	cout << "The machine has been pre-loaded with " << quarters << " quarters, " << dimes << " dimes, and " << nickels << " nickels." << endl << endl;
}

int selectOption()
{
	char selected;

	cout << "Select an option:" << endl;
	cout << "a - Juicy Fruit, $1.10" << endl;
	cout << "b - Big Red, $0.10" << endl;
	cout << "c - Jolly Ranchers, $0.05" << endl;
	cout << "d - Oreos, $1.15" << endl;
	cout << "e - Reeces Peanut Butter Cups, $1.20" << endl;
	cout << "Enter 'q' to quit" << endl;

	cin >> selected;

	int cost = -1;

	//Determine which option was chosen
	switch (selected)
	{
	case 'a':
		cost = 110;
		break;
	case 'b':
		cost = 10;
		break;
	case 'c':
		cost = 5;
		break;
	case 'd':
		cost = 115;
		break;
	case 'e':
		cost = 120;
		break;
	case 'q':
		cost = USER_QUITTING;
		break;
	default:
		cost = NO_SUCH_ITEM;
		break;
	}

	return cost;
}

int requestMoney(int cost, int& nickels, int& dimes, int& quarters, int& ones)
{
	int deposited = 0;

	char inputCur;
	//Put in money until item is paid for
	while (deposited < cost)
	{
		cout << endl;
		cout << "Currency required: $" << getMoneyForDisplay(cost - deposited) << endl;
		cout << "Menu for deposit:" << endl;
		cout << "n - Deposit a nickel" << endl;
		cout << "d - Deposit a dime" << endl;
		cout << "q - Deposit a quarter" << endl;
		cout << "o - Deposit a one-dollar bill" << endl;

		cin >> inputCur;
		switch (inputCur)
		{
		case 'o':
			cout << "Inserting one one-dollar bill!" << endl;
			ones++;
			deposited += ONE_VALUE;
			break;
		case 'q':
			cout << "Inserting one quarter!" << endl;
			quarters++;
			deposited += QUARTER_VALUE;
			break;
		case 'd':
			cout << "Inserting one dime!" << endl;
			dimes++;
			deposited += DIME_VALUE;
			break;
		case 'n':
			cout << "Inserting one nickel!" << endl;
			nickels++;
			deposited += NICKEL_VALUE;
			break;
		default:
			cout << "Invalid input! Please try again!" << endl;
			continue;
		}
	}

	return deposited - cost;
}

void dispenseChange(int totalChange, int& nickelCount, int& dimeCount, int& quarterCount, int& onesCount)
{
	cout << endl;
	if (totalChange == 0)
	{
		cout << "Exact Payment, No change due!" << endl;
		return;
	}
	int nickelChange = 0, dimeChange = 0, quarterChange = 0, onesChange = 0;
	int count = 0;
	while (totalChange > 0)
	{
		if (totalChange >= ONE_VALUE && onesCount > 0)
		{
			count = min(totalChange / ONE_VALUE, onesCount);
			totalChange -= (ONE_VALUE * count);
			onesCount -= count;
			onesChange += count;
		}
		else if (totalChange >= QUARTER_VALUE && quarterCount > 0)
		{
			count = min(totalChange / QUARTER_VALUE, quarterCount);
			totalChange -= (QUARTER_VALUE * count);
			quarterCount -= count;
			quarterChange += count;
		}
		else if (totalChange >= DIME_VALUE && dimeCount > 0)
		{
			count = min(totalChange / DIME_VALUE, dimeCount);
			totalChange -= (DIME_VALUE * count);
			dimeCount -= count;
			dimeChange += count;
		}
		else if (totalChange >= NICKEL_VALUE && nickelCount > 0)
		{
			count = min(totalChange / NICKEL_VALUE, nickelCount);
			totalChange -= (NICKEL_VALUE * count);
			nickelCount -= count;
			nickelChange += count;
		}
		else
		{
			break;
		}
	}

	cout << "Change:" << endl;
	if (onesChange > 0)
	{
		cout << "Dispensed " << onesChange << " one-dollar bill(s)" << endl;
	}
	if (quarterChange > 0)
	{
		cout << "Dispensed " << quarterChange << " quarter(s)" << endl;
	}
	if (dimeChange > 0)
	{
		cout << "Dispensed " << dimeChange << " dime(s)" << endl;
	}
	if (nickelChange > 0)
	{
		cout << "Dispensed " << nickelChange << " nickel(s)" << endl;
	}
	//If there is more change to be given but no valid coins
	if (totalChange > 0)
	{
		cout << "$" << getMoneyForDisplay(totalChange) << " unable to be dispensed, please contact a manager!" << endl;
	}
}

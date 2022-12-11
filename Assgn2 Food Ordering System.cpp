#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Function prototypes for manager
void getID(int &);
void updateMenuPrice();
void displayOrder(double &, int &, double &);
void calcSales(double &newPrice);
void calcDeliveryTime();


// Function prototypes for customer
void mainmenuCustomer();
void getOrder();
void confirmOrder(int &);
void makePayment(int &, double &);


// Global variable
const int arrSize = 50;		// Size of all arrays in this program

int main()
{
	int choice, staffID, accept;
	
	// Main menu of the system
	cout << "\t\t=====[Dine Fine Restaurant]=====\t\t\n";
	cout << "\n";
	cout << "\t\tDo you wish to log in as a...?\t\t\n";
	cout << "\n";
	cout << "\t\t1) Customer\n";
	cout << "\t\t2) Restaurant Manager\n";
	cout << "\t\t\tOR\n";
	cout << "\t\t3) Exit\n";
	cout << "\n";
	cout << "\t\tEnter the number of your choice: ";
	cin >> choice;
	
	// Input validation for log in option.
	while (choice < 1 || choice > 3)
	{
		cout << "\t\tInvalid choice input! Please enter number 1, 2 or 3 only: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		mainmenuCustomer();
	}
	else if (choice == 2)
	{
		getID(accept);
	}
	else if (choice == 3)
	{
		cout << "Thank you for visiting our online shop. Please come again!";
		exit;	// exiting the system
	}	
	return 0;
}

// Restaurant Manager
// Function 1: Ask for staff ID (security purpose) and proceed to manager's task menu
void getID(int &accept)							
{
	int choice, staffID, quantity;
	double price, totalPerOrder, newPrice;
	
	cout << "\n";
	cout << "Enter your staff ID: ";
	cin >> staffID;
	
	// Input validation: Will keep looping while staff ID is not in between 1200 - 1250. 
	while (staffID < 1200 || staffID > 1240)
	{
		cout << "Invalid staff ID. Please enter a valid ID: ";
		cin >> staffID;
	}
	
	// menu bar for manager
	cout << "\n";
	cout << "\t\t1) Update Menu And Price\n";
	cout << "\t\t2) See Online Orders\n";
	cout << "\t\t3) See Sales For The Day\n";
	cout << "\t\t4) Back to Home Page\n";
	cout << "\n";
	cout << "Enter number of option: ";
	cin >> choice;
	
	// Input validation: will keep looping while user's input is not 1, 2, 3, or 4.
	while (choice < 1 || choice > 4)
	{
		cout << "Invalid input. Choose either 1, 2, 3 or 4: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		updateMenuPrice();
	}
	else if (choice == 2)
	{
		displayOrder(price, quantity, totalPerOrder);	// Display customer's order
		cout << "\n";
		cout << "Press 1 to accept order\n";			// Option to accept or reject order. Staff has to check availability of stock manually.
		cout << "Press 2 to reject order\n";
		cout << "Enter choice: ";
		cin >> accept;
	}
	else if (choice == 3)
	{
		calcSales(newPrice);									// Calculate total sales for the day
	}
	else if (choice == 4)
	{
		cout << "Exiting the system...\n";
		exit;
	}
}

// Function 2: Create/update menu and price in MenuPrice.txt file
void updateMenuPrice()			
{
	int staffID, accept;
	char proceed;
	double price[arrSize]; 
	string menu[arrSize];
	ofstream MenuFile;
	MenuFile.open("MenuPrice.txt"); 
	
	for (int count = 0; count < arrSize; count++)
	{
		cin.ignore();
		cout << "Update menu: ";
		getline(cin, menu[count]);
		cout << "Update price (RM): ";
		cin >> price[count];
		MenuFile << right << menu[count] << "\t" << setprecision(2) << price[count] << endl;
		cout << "Do you wish to continue? (Press Y for YES / N for NO): ";
		cin >> proceed;
		
		while(proceed == 'Y' || proceed == 'y')
		{
			cout << "\n";
			cout << "Continue updating menu...\n";
			cin.ignore();
			cout << "Update menu: ";
			getline(cin, menu[count]);
			cout << "Update price (RM): ";
			cin >> price[count];
			MenuFile << menu[count] << "\t" << setprecision(2) << price[count] << endl;
			cout << "Do you wish to continue? (Press Y for YES / N for NO): ";
			cin >> proceed;
		} 
		if(proceed == 'N' || proceed == 'n')
		{
			cout << "Your update is successful!\n";
			cout << "Returning to previous page...\n";	// Returning to manager's homepage so other tasks can be done
			cout << "\n";
			getID(accept);
		}
		MenuFile.close();
	}
}

// Function 3: Display order list from customer
void displayOrder(double &price, int &quantity, double &totalPerOrder)
{
	int counter = 0; // calculate rows in file
	string menu;
	double sumPerDish;
	ifstream OrderFile;
	totalPerOrder = 0;
	OrderFile.open("Order.txt");
	
	cout << "\n";
	cout << "Customer's Order:\n";
	cout << "\n";
	cout << "\t" << "MENU" << "\t\t" << "PRICE(RM)" << "\t" << "QUANTITY\n";
	cout << "-------------------------------------------------------\n";
	while(OrderFile)
	{
		getline(OrderFile, menu, '\t');
		OrderFile >> price;
		OrderFile >> quantity;
		OrderFile.ignore();
		
		if (OrderFile.eof())
			break;
		cout << right << menu << "\t\t" << right << price << right << "\t\t   " << quantity<< endl;
		
		sumPerDish = (price * quantity);		// Calculate total payment per food
		totalPerOrder += sumPerDish;			// Calculate total payment for the whole order
		counter++;								// Calculation is done along the number of rows in file
	}
	OrderFile.close();
}
	
// Function 4: Calculate total sales per day and save the result in Sales.txt file.
void calcSales(double &newPrice)
{
	int counter = 0;
	double totalSales = 0;
	ifstream SalesFile;
	SalesFile.open("Sales.txt");			
	
	while (SalesFile)
	{
		SalesFile >> newPrice;
		if (SalesFile.eof())
			break;
		totalSales += newPrice;
		counter++;
	}
	SalesFile.close();	
	cout << fixed << showpoint << setprecision(2) << endl;
	cout << "Total sales for today is RM" << totalSales << endl;
}

// Function 5: Calculate delivery time
void calcDeliveryTime()
{
	int choice, time, deliverytime;
	cout << "\n";
	cout << "We provide delivery service from:\n";
	cout << "\t\t1) 12 p.m. to 6 p.m.\n";
	cout << "\t\t2) 7 p.m. to 11 p.m.\n";
	cout << "Choose number of option above: ";
	cin >> choice;
	cout << "\n";
	
	// Input validation. It will keep looping if user enter a number other than 1 or 2.
	while (choice < 1 || choice > 2)
	{
		cout << "Invalid input. Please choose either 1 or 2: ";
		cin >> choice;
	}
	while (choice == 1)
	{
		cout << "Delivery time in 24-hour format (i.e.: 1200 for 12 p.m.): ";
		cin >> time;
		
		if (time >= 1200 && time <= 1800)
		{
			deliverytime = time + 20;
			cout << "Estimated time for delivery to reach the address is " << deliverytime << endl;
			break;	// breaking the while loop
		}
		else
		{
			cout << "Please choose time between 1200 and 1800.\n";
		}
	}
	while (choice == 2)
	{
		cout << "Delivery time in 24-hour format (i.e.: 2000 for 8 p.m.): ";
		cin >> time;
		
		if (time >= 1900 && time <= 2300)
		{
			deliverytime = time + 30;
			cout << "Estimated time for delivery to reach the address is " << deliverytime << endl;
			break;	// breaking the while loop
		}
		else
		{
			cout << "Please choose time between 1900 and 2300.\n";
		}
	}
}

// Customer
// Function 1: Display menu bar for customer
void mainmenuCustomer()
{
	int choice, accept;
	double totalPerOrder, newPrice;

	cout << "\n";
	cout << "\t\t1) Place Order\n";
	cout << "\t\t2) Make Payment\n";
	cout << "\t\t3) Back to Home Page\n";
	cout << "\n";
	cout << "Enter number of option: ";
	cin >> choice;
	
	// Input validation. It will keep looping while user's input is other than 1 or 2.
	while (choice < 1 || choice > 3)
	{
		cout << "Invalid input. Choose either 1, 2 or 3: ";
		cin >> choice;
	}
	if (choice == 1)
	{
		getOrder();
	}
	else if (choice == 2)
	{
		makePayment(accept, newPrice);
	}
	else if (choice == 3)
	{
		cout << "Exiting the sytem..." << endl;
		exit;
	}
}

// Function 2: Get order from customer and save the order data to CustomerOrder.txt file
void getOrder()
{
	
	int order[arrSize], quantity[arrSize];
	int linenumber = 0, numMenu;			// linenumber is number of row in file
	string menulist, menuArr[arrSize];
	char proceed;
	ifstream MenuFile;
	ofstream OrderFile;
	
	MenuFile.open("MenuPrice.txt");
	OrderFile.open("Order.txt");
	
	// display menu
	while (MenuFile)
	{
		cout << "\n";
		cout << "\t" << "MENU" << "\t\t" << "PRICE(RM)\n";
		cout << "---------------------------------------------------------------------------\n";
		while (getline(MenuFile, menulist))	
		{
			menuArr[linenumber] = menulist;
			numMenu = linenumber + 1;										// numMenu is to list number of menu e.g.: menu 1 for menuArr[0] 
			cout << numMenu << "\t" << menuArr[linenumber] << endl;
			linenumber++;
		}
		
		for (int i = 0; i < arrSize; i++)
		{
			cout << "\n";
			cout << "Which dish would you like to order? (Enter number corresponding to dish): ";
			cin >> order[i];
			cout << "Quantity: ";
			cin >> quantity[i];
			cout << "Continue ordering? (Press Y = YES / Press N = NO): ";
			cin >> proceed;
			
			// Write to CustomerOrder.txt according to the chosen menu
			linenumber = order[i] - 1;												// e.g.: if menu chosen is menu no. 2, menuArr[1] will be the output
			OrderFile << menuArr[linenumber] << "\t" << quantity[i] << endl;
			
			while (proceed == 'Y' || proceed == 'y')		// will keep looping as long as customer wants to keep ordering
			{
				cout << "\n";
				cout << "Which dish would you like to order? (Enter number corresponding to dish): ";
				cin >> order[i];
				cout << "Quantity: ";
				cin >> quantity[i];
				cout << "Continue ordering? (Press Y = YES / Press N = NO): ";
				cin >> proceed;
				
				linenumber = order[i] - 1;
				OrderFile << menuArr[linenumber] << right << "\t" << quantity[i] << endl;
			}
			if (proceed == 'N' || proceed == 'n')		// will proceed to customer's main menu to check order confirmation and make payment
			{
				cout << "\n";
				mainmenuCustomer();
			}
		}
		MenuFile.close();
		OrderFile.close();
	}
}

// Function 3: Receive confirmation of payment
void confirmOrder(int &accept)
{
	
	if (accept == 1)
	{
		cout << "-----------------Your order is saved!------------------\n";	// Order is accepted to process
	}
	else if (accept == 2)
	{
		cout << "Order is rejected due to unavailability of stock.\n";			// Order is rejected and proceed to customer's homepage to place another order again.
		cout << "\n";
		exit;
	}
}

// Function 3: Make payment
void makePayment(int &accept, double &newPrice)
{
	double discount, deliveryFee = 3.50, price, totalPerOrder;
	int time, deliverytime, payOption, quantity;
	string bankName, accNum, name, contact, address;
	char proceed;
	ofstream SalesFile;
	
	// Display order list
	displayOrder(price, quantity, totalPerOrder);
	
	cout << "\n";
	confirmOrder(accept);	// Display whether customer's order is accepted or rejected.
	cout << "\n";
	
	// Ask for customer details
	cin.ignore();
	cout << "\n";
	cout << "Full name: ";
	getline(cin, name);
	
	cout << "Contact Number: ";
	getline(cin, contact);
	
	cout << "Address: ";
	getline(cin, address);
	
	cout << fixed << showpoint << setprecision(2) << endl;
	cout << "\n";
	cout << "Total price: RM" << totalPerOrder << endl;
	if (totalPerOrder >= 50)
	{
		discount = totalPerOrder * 0.1;
		newPrice = totalPerOrder - discount;
		cout << "You get discount 10% and free delivery fee!\n";
		cout << "Total payment: RM" << newPrice << endl;
	}
	else if(totalPerOrder < 50)
	{
		newPrice = totalPerOrder + deliveryFee;
		cout << "Delivery fee: RM" << deliveryFee << endl;
		cout << "Total payment: RM" << newPrice << endl;
	}
	
	SalesFile.open("Sales.txt", ofstream::app);					// File is in append mode so that the sales data of other customers can be added without overwriting the old data
	SalesFile << fixed << showpoint << setprecision(2);
	SalesFile << newPrice << endl;							// Sales data is written to Sales.txt file
	SalesFile.close();
	
	calcDeliveryTime();		// Display delivery time option
	
	// Choose option to make payment
	cout << "\n";
	cout << "1) Cash on Delivery\n";
	cout << "2) Online Banking\n";
	cout << "\n";
	cout << "Enter number of payment option: ";
	cin >> payOption;
	
	if(payOption == 1)
	{
		cout << "\n";
		cout << "Please pay your order to our delivery man, thank you!\n";
		exit;
	}
	if(payOption == 2)
	{
		cout << "\n";
		cout << "Bank: ";
		cin >> bankName;
		cout << "Bank account number: ";
		cin >> accNum;
		cout << "Amount of payment: RM" << newPrice << endl;
		cout << "\n";
		cout << "Continue transaction? (Press Y = YES / N = NO): ";
		cin >> proceed;
		
		if(proceed == 'y' || proceed == 'Y')		// If YES, transaction is done.
		{
			cout << "Transaction is successful!\n";
			cout << "\n";
			
			// Display customer details
			cout << "Name: " << name << endl;
			cout << "Phone number: " << contact << endl;
			cout << "Address: " << address << endl;
			cout << "Paid: RM" << newPrice << endl;
			cout << "\n";
			cout << "Exiting the system...\n";
			exit;
		}
		if (proceed == 'n' || proceed == 'N')		// If NO, transaction is cancelled and customer will exit the system.
		{
			cout << "Transaction is cancelled.\n";
			cout << "Exiting the system...\n";
			exit;
		}
	}
}


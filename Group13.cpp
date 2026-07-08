#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void menuHandling();
void addDurian();
void updateDurian();
void deleteDurian();
void splitPriceAndWeight(const string& pricePerKg_weight, string& price, string& weight);//
void transactionHandling();
void addOrder();
void editOrder();
int getNewCustomerNumber();
void printInvoice();
void rrManagement();
bool dateExists(string allDates[], int size, string date);
void viewAllOrders();
void dailyReport();
void filter();
bool checkDurianType(const string& durianType);

int main() {
	system("cls");
	std::cout << R"( 

      _________________________________
     / _______________________________ \
    / /                               \ \              
   / /        M A I N  M E N U         \ \
  /_/ __________________________________\_\
  | _____________________________________|
  | |  [ ]    [ ]    [ ]    [ ]    [ ] | |
  | |                                  | |
  | |  A. Menu Handling                | |
  | |  B. Transaction Handling         | |
  | |  C. Report & Record Management   | |
  | |   ___  ___  ___  ___  ___  ___   | |
  | |   / \  / \  / \  / \  / \  / \   | |
  | |   (D)  (U)  (R)  (I)  (A)  (N)   | |
  | |   \__/\__/ \__/ \__/ \__/ \__/   | |
  | |__________________________________| |
  |______________________________________|
     ||    ||     ||     ||     ||     ||
     ||    ||     ||     ||     ||     ||
    (__)  (__)   (__)   (__)   (__)   (__)
                         )" << endl;

	char choice;
	
	cout << "Please select your choice (Press 'Q' to exit) >> ";
	// Prompt user to enter choice
	cin >> choice;
	while (choice != 'Q' && choice != 'q') {
		if (choice == 'A' || choice == 'a') {
			menuHandling();
		}
		else if (choice == 'B' || choice == 'b') {
			transactionHandling();
		}
		else if (choice == 'C' || choice == 'c') {
			rrManagement();
		}
		else {
			cout << "Invalid input." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please select your choice (Press 'Q' to exit)>> ";
			cin >> choice;
		}
	}


	cout << "Exiting..." << endl;
	exit(0);
}


void menuHandling() {
	system("cls");
	cout << R"(
        ||             ||
        ||             ||
   .-=======================-.
  /       MENU HANDLING       \
 |          1. Add             |
 |          2. Update          |
  \         3. Delete         /
   '-=======================-'
)" << endl;
	
	int choice;
	while (true) {
		cout << "Please select your choice (Press '0' to exit) >> ";
		// Input validation
		if (!(cin >> choice)) {
			cout << "Invalid input." << endl;
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n'); // discard invalid input
			continue;
		}
		if (choice == 1) {
			addDurian();
		}
		else if (choice == 0) {
			break;
		}
		else if (choice == 2) {
			updateDurian();
		}
		else if (choice == 3) {
			deleteDurian();
		}
		else {
			cout << "Invalid input." << endl;
		}
	}
	main();
}
bool checkDurianType(const string& durianType) {
	ifstream file("durian.txt");

	string line;
	while (getline(file, line)) {
		// if the durian type entered is in the txt file --> return true
		if (line == durianType) {
			return true;
		}
	}
	return false;
}
void addDurian() {
	system("cls");
	cout << R"(
   o------------------------o
   |                        |
   |  A D D   D U R I A N   |
   |                        |
   o------------------------o
)" << endl;
	
	bool repeat = true;
	while (repeat) {
		string durianType, priceRange;
		ifstream file("durian.txt");
		cin.ignore(1000, '\n');
		cout << "Please enter the information below: " << endl;

		// Check if durian type exists
		while (true) {
			cout << "Durian type>> ";
			getline(cin, durianType);
			if (checkDurianType(durianType)) {
				cout << "Durian type has been entered. Please enter a different durian type.\n";

			}
			else {
				break;
			}
		}
		file.close();
		cout << "Price range>> ";
		getline(cin, priceRange);

		// Write to file
		ofstream write("durian.txt", ios::app);
		write << durianType << '\n' << priceRange << '\n';
		write.close();

		string more;
		cout << "Do you want to repeat? (PRESS 'Y' to repeat)>>";
		cin >> more;
		if (more != "y" && more != "Y") {
			repeat = false;
		}
	}
	menuHandling();
}

void updateDurian() {
	system("cls");
	
	bool repeat = true;
	cout << R"(
   o-----------------------------o
   |                             |
   |  U P D A T E   D U R I A N  |
   |                             |
   o-----------------------------o
)" << endl;
	while (repeat) {

		ifstream file("durian.txt");
		ofstream tempFile("temporary.txt");

		if (!file) {
			cout << "Error: Could not open durian.txt" << endl;
			return;
		}

		string userChoice, priceRange, durianType;
		cout << "Please enter the durian type that you want to update" << endl;
		cout << "Durian Type>> ";
		cin.ignore();
		getline(cin, userChoice);

		bool found = false;

		while (getline(file, durianType) && getline(file, priceRange)) {
			if (durianType == userChoice) {
				found = true;
				//Display the choseen durian
				cout << "Found:\nDurian Type: " << durianType << "\nPrice Range: " << priceRange << endl;

				string newDurianType=durianType;
				string newPriceRange=priceRange;
				int choice;
				bool correctChoice = false;
				while (!correctChoice) {
					cout << "Please enter what you want to update (1. Durian type, 2. Price range): ";
					if (!(cin >> choice)) {
						cout << "Invalid input." << endl;
						cin.clear(); // clear the error flag
						cin.ignore(1000, '\n'); // discard invalid input
						continue;

					}
					cin.ignore();
					if (choice == 1) {
						correctChoice = true;
						string input;
						cout << "Enter new durian type (or press ENTER to keep current): ";
						getline(cin, input);
						if (!input.empty()) newDurianType = input;
						
					}
					else if (choice == 2) {
						correctChoice = true;
						cout << "Enter new price range (or press ENTER to keep current): ";
						string input;
						getline(cin, input);
						if (!input.empty()) newPriceRange = input;

						
					}
					else {
						cout << "Invalid choice.\n";
						correctChoice = false; //Repeat if choice is false
					}
				}
				
             //WRite the new durian type and price range
			tempFile << newDurianType << endl << newPriceRange << endl;
			}
			else {
				tempFile << durianType << endl << priceRange << endl; //Remain the same
			}
		}

		file.close();
		tempFile.close();

		if (!found) {
			cout << "Durian type does not exist.\n";
		}

		remove("durian.txt");
		rename("temporary.txt", "durian.txt");

		string more;
		//ask to repeat
		cout << "Do you want to update more types of durian? (PRESS 'Y' to repeat) >> ";
		cin >> more;

		if (more != "Y" && more != "y") {
			repeat = false;
		}

	}
	menuHandling();
}

void deleteDurian() {
	system("cls");
	cout << R"(
   o-----------------------------o
   |                             |
   |  D E L E T E   D U R I A N  |
   |                             |
   o-----------------------------o
)" << endl;
	bool repeat = true;

	while (repeat) {
		ifstream file("durian.txt");
		if (!file) {
			cout << "Error: Could not open durian.txt" << endl;
			return;
		}

		// First, display all durians and count lines
		string durianType[100], priceRange[100];
		int count = 0;

		cout << "Durian List:\n";
		while (getline(file, durianType[count]) && getline(file, priceRange[count])) {
			cout << left << "[" << count + 1 << "] " << setw(17) << durianType[count] << priceRange[count] << endl;
			count++;
		}
		file.close();

		if (count == 0) {
			cout << "No durians found to delete." << endl;
			return;
		}

		int deleteIndex;
		cout << "Please select the type of durian that you want to delete >> ";

		if (!(cin >> deleteIndex)) {
			cout << "Invalid input. Please enter a number.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		cin.ignore(1000, '\n');
		//check if index number exists
		if (deleteIndex < 1 || deleteIndex > count) {
			cout << "Invalid number. No durian deleted." << endl;
			continue;
		}

		// Write all durians except the one to delete into a temp file
		ofstream tempFile("temporary.txt");
		for (int i = 0; i < count; i++) {
			if (i != deleteIndex - 1) {
				tempFile << durianType[i] << '\n' << priceRange[i] << '\n';
			}
		}
		tempFile.close();

		remove("durian.txt");
		rename("temporary.txt", "durian.txt");

		cout << "Durian number " << deleteIndex << " deleted successfully!!\n";

		// Show updated list
		ifstream updatedFile("durian.txt");
		string newDurian, newPrice;
		int number = 0;
		cout << "Here is the latest list:\n";
		while (getline(updatedFile, newDurian) && getline(updatedFile, newPrice)) {
			cout << left << "[" << ++number << "] " << setw(17) << newDurian << newPrice << endl;
		}
		updatedFile.close();

		string more;
		cout << "Do you want to delete more types of durian? (Press 'Y' to repeat) >> ";
		cin >> more;
		if (more != "Y" && more != "y") {
			repeat = false;
		}
	}
	menuHandling();
}

void transactionHandling() {
	system("cls");
	cout << R"(
         ||             ||
         ||             ||
   .-==========================-.
  /    TRANSACTION HANDLING     \
 |        1. Add Order           |
 |        2. Edit Order          |
  \       3. Print Invoice      /
   '-==========================-'
)" << endl;
	while (true) {
		int choice;
		cout << "Please select your choice (Press '0' to exit) >> ";
		// Input validation
		if (!(cin >> choice)) {
			cout << "Invalid input." << endl;
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n'); // discard invalid input
			continue;

		}
		if (choice == 1) {
			addOrder();
		}
		else if (choice == 0) {
			break;
		}
		else if (choice == 2) {
			editOrder();
		}
		else if (choice == 3) {
			printInvoice();
		}
		else {
			cout << "Invalid input." << endl;
		}
	}
	main();

}

int getNewCustomerNumber() {
	ifstream file("transaction.txt");
	string line;
	int customerNo = 0;
	int lineCount = 0;

	while (getline(file, line)) {
		if (lineCount % 5 == 0) {  // Every 5 lines, check the customer number line
			if (!line.empty() && isdigit(line[0])) {
				int currentNo = stoi(line);
				if (currentNo > customerNo)
					customerNo = currentNo;
			}
		}
		lineCount++;
	}
	file.close();
	return customerNo + 1; // Next available customer number
}

void addOrder() {
	system("cls");
	cout << R"(
   o---------------------o 
   |                     |
   |  A D D   O R D E R  |
   |                     |
   o---------------------o
)" << endl;
	// Get customer number at the start
	int customerNo = getNewCustomerNumber();

	// Read durians from durian.txt
	ifstream file("durian.txt");
	if (!file) {
		cout << "Error: durian.txt not found." << endl;
		return;
	}

	string durianType[100], priceRange[100];
	int count = 0;

	while (getline(file, durianType[count]) && getline(file, priceRange[count])) {
		count++;
	}
	file.close();

	ofstream tfile("transaction.txt", ios::app);
	if (!tfile) {
		cout << "Error: Cannot write to transaction.txt\n";
		return;
	}

	//Display durian list
	cout << "\n===== Available Durian Types =====\n";
	for (int i = 0; i < count; ++i) {
		cout << "[" << i + 1 << "] " << durianType[i] << "\n      Price Range: " << priceRange[i] << endl;
	}
	cout << endl;

	bool repeat = true;
	while (repeat) {
		int choice;
		cout << "Please choose the durian type (1,2,3) : ";
		// Input validation
		if (!(cin >> choice)) {
			cout << "Invalid input." << endl;
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n'); // discard invalid input
			continue;

		}


		if (choice < 1 || choice > count) {
			cout << "Invalid choice. Please try again.\n";
			continue;
		}

		string selectedDurian = durianType[choice - 1];
		string selectedRange = priceRange[choice - 1];

		// Parse price range (e.g. "20 - 25")
		double minPrice = 0, maxPrice = 0;
		string minStr = "", maxStr = "";
		int i = 0;

		while (i < selectedRange.size() && (isdigit(selectedRange[i]) || selectedRange[i] == '.')) {
			minStr += selectedRange[i++];
		}
		while (i < selectedRange.size() && !isdigit(selectedRange[i]) && selectedRange[i] != '.') i++;
		while (i < selectedRange.size() && (isdigit(selectedRange[i]) || selectedRange[i] == '.')) {
			maxStr += selectedRange[i++];
		}

		if (minStr.empty() || maxStr.empty()) {
			cout << "Error: Could not read price range.\n";
			break;
		}

		minPrice = stod(minStr);
		maxPrice = stod(maxStr);

		// Get price, weight, date
		double pricePerKg, weight, total;
		string date;
		cout << "Price per kg: ";
		cin >> pricePerKg;

		while (pricePerKg < minPrice || pricePerKg > maxPrice) {
			cout << "Please enter the price in the range of " << selectedRange << "!!\n";
			cout << "Price per kg: ";
			cin >> pricePerKg;
		}

		while (true) {
			cout << "Weight (kg): ";
			cin >> weight;
			//Input validation for weight
			if (weight <=0) {
				cout << "Invalid weight. Please enter a positive value.\n";
			}
			else {
				break;  
			}
		}
		cin.ignore(1000, '\n');

		cout << "Date (dd/mm/yy): ";
		getline(cin, date);

		total = pricePerKg * weight;
		cout << fixed << setprecision(2);
		cout << "Total price for " << weight << "kg " << selectedDurian << " is RM" << total << ".\n";
		//write into file
		tfile << customerNo << '\n'
			<< selectedDurian << '\n'
			<< pricePerKg << " "
			<< weight << '\n'
			<< date << '\n'
			<< fixed << setprecision(2) << total << '\n';

		string more;
		cout << "Do you want to enter another order? (PRESS 'Y' to repeat): ";
		cin >> more;

		if (more != "Y" && more != "y") {
			repeat = false;
		}
	}
	tfile.close();
	transactionHandling();
}

void splitPriceAndWeight(const string& pricePerKg_weight, string& price, string& weight) {
	price = "";
	weight = "";

	int i = 0;

	// Extract price (before space)
	while (i < pricePerKg_weight.length() && pricePerKg_weight[i] != ' ') {
		price += pricePerKg_weight[i];
		i++;
	}

	// Skip the space
	i++;

	// Extract weight (after space)
	while (i < pricePerKg_weight.length()) {
		weight += pricePerKg_weight[i];
		i++;
	}
}
void editOrder() {
	system("cls");
	cout << R"(
   o------------------------o
   |                        |
   |  E D I T    O R D E R  |
   |                        |
   o------------------------o
)" << endl;
	bool repeat = true;
	while (repeat) {
		ifstream file("transaction.txt");
		if (!file) {
			cout << "Error: Could not open transaction.txt" << endl;
			return;
		}
		cout << "Order List:\n";
		string customerNo, durianType, pricePerKg_weight, date, total;
		string allOrders[100][5]; // store up to 100 orders, each has 5 lines
		int index = 0;
		int number = 1;
		// Read and store all orders
		while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_weight) && getline(file, date) && getline(file, total)) {

			allOrders[index][0] = customerNo;
			allOrders[index][1] = durianType;
			allOrders[index][2] = pricePerKg_weight;
			allOrders[index][3] = date;
			allOrders[index][4] = total;

			// Display all orders
			string price, weight;
			splitPriceAndWeight(pricePerKg_weight, price, weight);

			cout << "[" << number << "]\n";
			cout << "Customer No: " << customerNo << endl;
			cout << "Durian Type: " << durianType << endl;
			cout << "Date: " << date << endl;
			cout << "Price per kg: " << price << endl;
			cout << "Weight: " << weight << " kg" << endl;
			cout << "Total: RM" << total << "\n\n";
			number++;
			index++;
		}

		file.close();

		if (index == 0) {
			cout << "No orders found." << endl;
			return;
		}

		// Ask which order to edit
		int choice;
		cout << "Please enter the index number that you want to update >> ";
		cin >> choice;
		choice--;

		while (choice < 0 || choice >= index) {
			cout << "Invalid index. No update made." << endl;
			cout << "Please enter the index number that you want to update >> ";
			cin >> choice;
			choice--;

		}
		//Display chosen order
		string displayDurianType = allOrders[choice][1];
		string displayPrice;
		string displayWeight;
		string displayTotal = allOrders[choice][4];
		string displayDate = allOrders[choice][3];
		splitPriceAndWeight(allOrders[choice][2], displayPrice, displayWeight);
		cout << "Found as below: " << endl;
		cout << "Customer No: " << allOrders[choice][0] << endl;
		cout << "Date :" << displayDate << endl;
		cout << "Durian type: " << displayDurianType << endl;
		cout << "Price per kg: " << displayPrice << endl;
		cout << "Weight: " << displayWeight << endl;
		cout << "Total Price RM:" << displayTotal << endl;

		// Ask for new data
		int userChoice;
		string input;
		string newDurianType = allOrders[choice][1];
		string newPrice;
		string newWeight;
		string newDate = allOrders[choice][3];
		splitPriceAndWeight(allOrders[choice][2], newPrice, newWeight);
		bool correctInfo = false;
		while (!correctInfo) {
			cout << "Please enter the information that you want to update (1.Price per kg 2.Weight 3.Durian type 4.Date)>>";
			if (!(cin >> userChoice)) {
				cout << "Invalid input. Please enter a number.\n";
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}
			cin.ignore();
			if (userChoice == 1) {
				cout << "Enter new price per kg (Press ENTER to keep current): ";
				getline(cin, input);
				if (!input.empty()) newPrice = input;
				correctInfo = true;

			}
			else if (userChoice == 2) {
				cout << "Enter new weight (kg) (Press ENTER to keep current): ";
				getline(cin, input);
				if (!input.empty()) newWeight = input;
				correctInfo = true;

			}
			else if (userChoice == 3) {
				while (true) {
					cout << "Enter new durian type (Press ENTER to keep current): ";
					getline(cin, input);
					if (!input.empty()) newDurianType = input;
					if (!checkDurianType(input)) {
						cout << "Durian type not available. Please enter a different durian type.\n";
					}
					else {
						break;
					}
				}
				
				correctInfo = true;

			}
			else if (userChoice == 4) {
				cout << "Enter new date (dd/mm/yy) (Press ENTER to keep current): ";
				getline(cin, input);
				if (!input.empty()) newDate = input;
				correctInfo = true;
			}
			else {
				cout << "Wrong information index" << endl;
				correctInfo = false;
			}
		}


		// Calculate new total
		double priceDouble = stod(newPrice);
		double weightDouble = stod(newWeight);
		double newTotal = priceDouble * weightDouble;

		// Update the selected order
		allOrders[choice][1] = newDurianType;
		allOrders[choice][2] = newPrice + " " + newWeight;
		allOrders[choice][3] = newDate;

		//calculate the total with two decimal points
		char buffer[20];
		sprintf_s(buffer, "%.2f", newTotal);
		allOrders[choice][4] = buffer;

		// Write back all orders
		ofstream out("transaction.txt");
		for (int i = 0; i < index; i++) {
			out << fixed << setprecision(2)
				<< allOrders[i][0] << '\n'
				<< allOrders[i][1] << '\n'
				<< allOrders[i][2] << '\n'
				<< allOrders[i][3] << '\n'
				<< allOrders[i][4] << '\n';
		}

		out.close();
		cout << "Order updated successfully!" << endl;

		string more;
		cout << "Do you want to update another order? (PRESS 'Y' to repeat): ";
		cin >> more;

		if (more != "Y" && more != "y") {
			repeat = false;
		}
	}
	transactionHandling();
}

void printInvoice() {
	system("cls");
	cout << R"(
   o-----------------------------o
   |                             |
   |  P R I N T   I N V O I C E  |
   |                             |
   o-----------------------------o
)" << endl;
	bool repeat = true;
	while (repeat) {
		string allOrders[100][4]; //Store all orders each has 4 lines
		ifstream file("transaction.txt");
		string customerNo, price, weight, total, durianType, date, pricePerKg_Weight;
		int dateIndex = 0;
		string no, userDate;
		string allDates[100];
		string allCustomerNo;

		cout << "Choose Customer No to display invoice >> ";
		cin >> no;
		bool exist = false;
		while (!exist) {
			file.clear();
			file.seekg(0, ios::beg);
			while (getline(file, customerNo) && getline(file, durianType) &&
				getline(file, pricePerKg_Weight) && getline(file, date) &&
				getline(file, total)) {

				if (no == customerNo) {
					exist = true;
					if (!dateExists(allDates, dateIndex, date)) {
						allDates[dateIndex++] = date;
					}

				}
			}
			if (!exist) {
				cout << "Customer no does not exist" << endl;
				cout << "Choose Customer No to display invoice >> ";
				cin >> no;
			}

		}
		cout << "Dates are: " << endl;



		// Display the dates found
		for (int i = 0; i < dateIndex; i++) {
			cout << allDates[i] << endl;
		}

		file.clear();              // Reset file stream state
		file.seekg(0, ios::beg);   // Go back to beginning of file

		cout << "Choose a date>> ";
		cin >> userDate;
		int index = 0;
		bool found = false;
		while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
			if (no == customerNo && date == userDate) {
				found = true;
				splitPriceAndWeight(pricePerKg_Weight, price, weight);
				allOrders[index][0] = durianType;
				allOrders[index][1] = price;
				allOrders[index][2] = weight;
				allOrders[index][3] = total;

				index++;
			}
		}
		//if the date chosen is not available
		if (!found) {
			cout << "Date is incorrect" << endl;
			found = false;
		}
		else {
			//show invoice
			cout << "============================================================" << endl;
			cout << "                   DURIAN DURIAN STALL               " << endl;
			cout << "                        INVOICE                      " << endl;
			cout << "============================================================" << endl;
			cout << "Customer No: " << no << endl;
			cout << "Date: " << userDate << endl;
			cout << "\nItems:" << endl;
			cout << "------------------------------------------------------------" << endl;
			cout << left << setw(15) << "Durian Type"
				<< right << setw(12) << "Price/kg"
				<< setw(15) << "Weight(kg)"
				<< setw(15) << "Total(RM)" << endl;
			cout << "------------------------------------------------------------" << endl;

			double grandTotal = 0;
			for (int i = 0; i < index; i++) {
				cout << fixed << setprecision(2);
				cout << left << setw(15) << allOrders[i][0]
					<< right << setw(12) << allOrders[i][1]
					<< setw(15) << stod(allOrders[i][2])
					<< setw(15) << stod(allOrders[i][3]) << endl;
				grandTotal += stod(allOrders[i][3]);
			}
			cout << "============================================================" << endl;
			cout << "TOTAL:                                             RM " << fixed << setprecision(2) << grandTotal << endl;
			cout << "============================================================" << endl;
			cout << "Thank you for your purchase!" << endl;

		}
		string more;
		cout << "Do you want to print another invoice? (PRESS 'Y' to repeat)>> ";
		cin >> more;
		if (more != "y" && more != "Y") {
			repeat = false;
		}

	}
	transactionHandling();
}

void rrManagement() {
	system("cls");
	cout << R"(
               ||             ||
               ||             ||
   .-=====================================-.
  /      REPORT AND RECORD MANAGEMENT       \
 |  1. Filter to view transaction history   |
 |        2. Generate daily report          |
  \       3. View all orders                /
   '-=====================================-'
)" << endl;

	while (true) {
		int choice;
		cout << "Please select your choice (Press '0' to exit) >> ";
		// Input validation
		if (!(cin >> choice)) {
			cout << "Invalid input." << endl;
			cin.clear(); // clear the error flag
			cin.ignore(1000, '\n'); // discard invalid input
			continue;

		}
		if (choice == 1) {
			filter();
		}
		else if (choice == 0) {
			break;
		}
		else if (choice == 2) {
			dailyReport();
		}
		else if (choice == 3) {
			viewAllOrders();
		}
		else {
			cout << "Invalid input." << endl;
		}
	}
	main();

}


void filter() {
	cout << R"(
   o---------------------------------------o
   |                                       |
   |  F I L T E R   T R A N S A C T I O N  |
   |                                       |
   o---------------------------------------o
)" << endl;

	bool repeat = true;
	while (repeat) {
		ifstream file("transaction.txt");
		if (!file) {
			cout << "Error: Could not open transaction.txt" << endl;
			return;
		}
		cout << "Please select the attribute to filter" << endl;
		cout << "1. Date" << endl;
		cout << "2. Durian type" << endl;
		cout << "3. Customer No" << endl;

		
		string customerNo, durianType, pricePerKg_Weight, date, total, price, weight;
		bool correctChoice = false;
		while (!correctChoice) {
			int choice;
			cout << "Please select your choice >> ";
			// Input validation
			if (!(cin >> choice)) {
				cout << "Invalid input." << endl;
				cin.clear(); // clear the error flag
				cin.ignore(1000, '\n'); // discard invalid input
				continue;

			}
			bool found = false;
			if (choice == 1) {
				//Display based on date
				correctChoice = true;
				string userDate;
				cout << "Enter a date>> ";
				cin.ignore(1000, '\n');
				getline(cin, userDate);
				while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
					if (userDate == date) {
						splitPriceAndWeight(pricePerKg_Weight, price, weight);
						cout << "===============================================" << endl;
						cout << "Date: " << date << endl;
						cout << "Customer No: " << customerNo << endl;
						cout << "Durian type: " << durianType << endl;
						cout << "Price per kg: " << price << endl;
						cout << "Weight: " << weight << endl;
						cout << "Total RM: " << fixed << setprecision(2) << total << endl;
						found = true;
					}
				}if (!found) {
					cout << "No data found for that date" << endl;
				}
			}
			else if (choice == 2) {
				//display based on durian type
				correctChoice = true;
				string userDurianType;
				cout << "Enter a durian type>> ";
				cin.ignore(1000, '\n');
				getline(cin, userDurianType);
				while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
					if (userDurianType == durianType) {
						splitPriceAndWeight(pricePerKg_Weight, price, weight);
						cout << "===============================================" << endl;
						cout << "Durian type: " << durianType << endl;
						cout << "Customer No: " << customerNo << endl;
						cout << "Date: " << date << endl;
						cout << "Price per kg: " << price << endl;
						cout << "Weight: " << weight << endl;
						cout << "Total RM: " << total << endl;
						found = true;
					}

				}if (!found) {
					cout << "No data found for that durian type" << endl;
				}

			}
			else if (choice == 3) {
				//Display based on customer number
				correctChoice = true;
				string userCustomerNo;
				cout << "Enter a customer no>> ";
				cin >> userCustomerNo;
				while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
					if (userCustomerNo == customerNo) {
						splitPriceAndWeight(pricePerKg_Weight, price, weight);
						cout << "===============================================" << endl;
						cout << "Customer No: " << customerNo << endl;
						cout << "Durian type: " << durianType << endl;
						cout << "Date: " << date << endl;
						cout << "Price per kg: " << price << endl;
						cout << "Weight: " << weight << endl;
						cout << "Total: RM" << fixed << setprecision(2) << total << endl;
						found = true;
					}
				}
				if (!found) {
					cout << "No data found for that customer no" << endl;
				}

			}
			else {
				cout << "Invalid input." << endl;
				correctChoice=false;
			}
		}

		
		string more;
		cout << "Do you want to repeat? (PRESS 'Y' to repeat)>>";
		cin >> more;
		if (more != "y" && more != "Y") {
			repeat = false;
		}

	}
	rrManagement();
}

bool dateExists(string allDates[], int size, string date) {
	//check if date exists
	for (int i = 0; i < size; i++) {
		if (allDates[i] == date) {
			return true;
		}
	}
	return false;
}

void dailyReport() {
	system("cls");
	ifstream file("transaction.txt");
	if (!file) {
		cout << "Error opening transaction.txt" << endl;
		return;
	}
	cout << "=================================================" << endl;
	cout << "               DURIAN DURIAN STALL               " << endl;
	cout << "                DAILY SALES REPORT               " << endl;
	cout << "=================================================" << endl;
	string allDates[100]; //Store the dates
	int index = 0;
	double grandTotal = 0;
	string customerNo, durianType, pricePerKg_Weight, total, price, weight, date;
	while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
		if (!dateExists(allDates, index, date)) {
			allDates[index] = date;
			index++;
		}
	}
	file.close();

	for (int j = 0; j < index; j++) {
		string displayDate = allDates[j];
		ifstream read("transaction.txt");
		double dailyTotal = 0;
		cout << "\nDate: " << displayDate << endl;
		cout << "=================================================" << endl;
		cout << left << setw(15) << "Customer No" << setw(20) << "Durian Type" << setw(15) << "Total(RM)" << endl;
		cout << "=================================================" << endl;

		while (getline(read, customerNo) && getline(read, durianType) && getline(read, pricePerKg_Weight) && getline(read, date) && getline(read, total)) {
			if (displayDate == date) {
				cout << left << setw(15) << customerNo << setw(20) << durianType << setw(15) << total << endl;
				dailyTotal += stod(total);
			}

		}
		cout << "................................................." << endl;
		cout << "Total sales for " << displayDate << ":  RM" << dailyTotal << endl;
		cout << "................................................." << endl;
		grandTotal += dailyTotal;
		read.close();
	}
	cout << "=================================================" << endl;
	cout << "TOTAL SALES OVERALL: RM " << fixed << setprecision(2) << grandTotal << '\n' << endl;

	cout << "End of order. Press ENTER to exit...";
	cin.ignore(10000, '\n');
	cin.get();
	rrManagement();

}

void viewAllOrders() {
	system("cls");
	cout << "\nTransaction History (Displaying all) : " << endl;

	ifstream file("transaction.txt");
	string customerNo, durianType, pricePerKg_Weight, price, weight, date, total;

	while (getline(file, customerNo) && getline(file, durianType) && getline(file, pricePerKg_Weight) && getline(file, date) && getline(file, total)) {
		splitPriceAndWeight(pricePerKg_Weight, price, weight);
		cout << fixed << setprecision(2);
		cout << "Customer No: " << customerNo << endl;
		cout << "Date: " << date << endl;
		cout << "Durian Type: " << durianType << endl;
		cout << "Price per KG: " << price << endl;
		cout << "Weight: " << weight << " kg" << endl;
		cout << "Total: RM " << total << endl;
		cout << '\n';
	}
	cout << "End of order. Press ENTER to exit...";
	cin.ignore(10000, '\n');
	cin.get();
	rrManagement();
}



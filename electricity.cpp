
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Consumer
{
public:
    int id;
    string name;
    string address;
    string phone;
    int previousReading;
    int currentReading;
    double billAmount;
    double paidAmount;

    Consumer()
    {
        previousReading = 0;
        currentReading = 0;
        billAmount = 0;
        paidAmount = 0;
    }

    // Module 1: Register a new consumer
    void registerConsumer()
    {
        cout << "\nEnter Consumer ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Consumer Name: ";
        getline(cin, name);

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        previousReading = 0;
        currentReading = 0;
        billAmount = 0;
        paidAmount = 0;

        cout << "\nConsumer registered successfully!\n";
    }

    // Display consumer details
    void displayConsumer()
    {
        cout << "\nConsumer ID: " << id;
        cout << "\nName: " << name;
        cout << "\nAddress: " << address;
        cout << "\nPhone: " << phone << endl;
    }

    // Module 2: Enter meter readings
    void enterReadings()
    {
        cout << "\nEnter Previous Meter Reading: ";
        cin >> previousReading;

        cout << "Enter Current Meter Reading: ";
        cin >> currentReading;

        if (previousReading < 0 ||
            currentReading < previousReading)
        {
            cout << "Invalid meter readings!\n";
            previousReading = 0;
            currentReading = 0;
            return;
        }

        cout << "Meter readings saved successfully!\n";
    }

    // Module 3: Calculate electricity bill
    void calculateBill()
    {
        if (currentReading < previousReading)
        {
            cout << "Please enter valid meter readings first.\n";
            return;
        }

        int units = currentReading - previousReading;
        double amount = 0;

        // Simple example of unit-based rates
        if (units <= 100)
        {
            amount = units * 3;
        }
        else if (units <= 200)
        {
            amount = 100 * 3 + (units - 100) * 5;
        }
        else
        {
            amount = 100 * 3 + 100 * 5
                     + (units - 200) * 7;
        }

        billAmount = amount;

        cout << fixed << setprecision(2);
        cout << "\n========== ELECTRICITY BILL ==========\n";
        cout << "Consumer ID       : " << id << endl;
        cout << "Consumer Name     : " << name << endl;
        cout << "Previous Reading  : " << previousReading << endl;
        cout << "Current Reading   : " << currentReading << endl;
        cout << "Units Consumed    : " << units << endl;
        cout << "Total Bill Amount : Rs. " << billAmount << endl;
        cout << "Amount Paid       : Rs. " << paidAmount << endl;
        cout << "Balance Due       : Rs. "
             << billAmount - paidAmount << endl;
        cout << "======================================\n";
    }

    // Module 4: Record payment and generate receipt
    void makePayment()
    {
        if (billAmount <= 0)
        {
            cout << "Please calculate the bill first.\n";
            return;
        }

        double balance = billAmount - paidAmount;

        if (balance <= 0)
        {
            cout << "This bill is already fully paid.\n";
            return;
        }

        double payment;

        cout << "\nTotal Bill: Rs. " << billAmount << endl;
        cout << "Already Paid: Rs. " << paidAmount << endl;
        cout << "Remaining Balance: Rs. " << balance << endl;

        cout << "Enter Payment Amount: Rs. ";
        cin >> payment;

        if (payment <= 0 || payment > balance)
        {
            cout << "Invalid payment amount!\n";
            return;
        }

        paidAmount = paidAmount + payment;

        cout << fixed << setprecision(2);
        cout << "\n========== PAYMENT RECEIPT ==========\n";
        cout << "Consumer ID    : " << id << endl;
        cout << "Consumer Name  : " << name << endl;
        cout << "Payment Amount : Rs. " << payment << endl;
        cout << "Total Paid     : Rs. " << paidAmount << endl;
        cout << "Balance Due    : Rs. "
             << billAmount - paidAmount << endl;

        if (paidAmount == billAmount)
        {
            cout << "Payment Status : PAID\n";
        }
        else
        {
            cout << "Payment Status : PARTIALLY PAID\n";
        }

        cout << "=====================================\n";
    }

    // Save consumer details in a file
    void saveToFile()
    {
        ofstream file("consumers.txt", ios::app);

        file << id << "\n";
        file << name << "\n";
        file << address << "\n";
        file << phone << "\n";
        file << previousReading << "\n";
        file << currentReading << "\n";
        file << billAmount << "\n";
        file << paidAmount << "\n";

        file.close();
    }
};

int main()
{
    Consumer consumers[100];
    int count = 0;
    int choice;

    do
    {
        cout << "\n\n===== ELECTRICITY BILLING SYSTEM =====\n";
        cout << "1. Register Consumer\n";
        cout << "2. View Consumer Details\n";
        cout << "3. Enter Meter Readings\n";
        cout << "4. Calculate Electricity Bill\n";
        cout << "5. Record Payment and Print Receipt\n";
        cout << "6. Save Consumer Records\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (count < 100)
            {
                consumers[count].registerConsumer();
                count++;
            }
            else
            {
                cout << "Consumer limit reached!\n";
            }
        }
        else if (choice == 2)
        {
            int id, found = 0;

            cout << "Enter Consumer ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
            {
                if (consumers[i].id == id)
                {
                    consumers[i].displayConsumer();
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                cout << "Consumer not found!\n";
            }
        }
        else if (choice == 3)
        {
            int id, found = 0;

            cout << "Enter Consumer ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
            {
                if (consumers[i].id == id)
                {
                    consumers[i].enterReadings();
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                cout << "Consumer not found!\n";
            }
        }
        else if (choice == 4)
        {
            int id, found = 0;

            cout << "Enter Consumer ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
            {
                if (consumers[i].id == id)
                {
                    consumers[i].calculateBill();
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                cout << "Consumer not found!\n";
            }
        }
        else if (choice == 5)
        {
            int id, found = 0;

            cout << "Enter Consumer ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
            {
                if (consumers[i].id == id)
                {
                    consumers[i].makePayment();
                    found = 1;
                    break;
                }
            }

            if (found == 0)
            {
                cout << "Consumer not found!\n";
            }
        }
        else if (choice == 6)
        {
            ofstream file("consumers.txt");

            for (int i = 0; i < count; i++)
            {
                file << consumers[i].id << "\n";
                file << consumers[i].name << "\n";
                file << consumers[i].address << "\n";
                file << consumers[i].phone << "\n";
                file << consumers[i].previousReading << "\n";
                file << consumers[i].currentReading << "\n";
                file << consumers[i].billAmount << "\n";
                file << consumers[i].paidAmount << "\n";
            }

            file.close();
            cout << "Consumer records saved to consumers.txt\n";
        }
        else if (choice == 7)
        {
            cout << "Thank you for using the system!\n";
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}

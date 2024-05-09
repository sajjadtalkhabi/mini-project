#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <locale>

using namespace std;

time_t makeTime(string date)
{
    tm t = {};
    istringstream ss(date);

    ss >> get_time(&t, "%Y-%m-%d");
    put_time(&t, "%c");
    time_t epoch = mktime(&t);
    return epoch;
}

class File
{
public:
    fstream f;

    void open(string& path,ios_base::openmode openMode)
    {
        f.open(path,openMode);
    }

    void write(string text)
    {
        f << text;
    }

    void close()
    {
        f.close();
    }

    bool is_open()
    {
        return  f.is_open();
    }
};

class Product
{
private:
    string name;
    int quantity;
    double price;

public:
    Product(string n, int q, double p) : name(n), quantity(q), price(p) {}

    string getName()
    {
        return name;
    }

    int getQuantity()
    {
        return quantity;
    }

    double getPrice()
    {
        return price;
    }
};

class Order
{
private:
    string productName, customerName, date;
    int quantity;
    double price;

public:
    Order(string pn, string cn, string d, int qu, double p) : productName(pn), customerName(cn), date(d), quantity(qu), price(p) {}

    string getProductName()
    {
        return productName;
    }

    string getCustomerName()
    {
        return customerName;
    }

    string getDate()
    {
        return date;
    }

    int getQuantity()
    {
        return quantity;
    }

    double getPrice()
    {
        return price;
    }
};

class Factor
{
private:
    string customerName, phoneNumber, date;
    double totalPrice;

public:

    Factor(string cn, string pn, string d, double tp = 0) : customerName(cn), phoneNumber(pn), date(d), totalPrice(tp) {}

    void addOrder(Order o)
    {
        this->totalPrice += o.getPrice();
    }

    double getTotalPrice()
    {
        return totalPrice;
    }

    string getCustomerName()
    {
        return customerName;
    }
    string getPhoneNumber()
    {
        return phoneNumber;
    }
    string getDate()
    {
        return date;
    }
};

class Manager
{
public:
    void addProduct(Product p);

    void displayProducts();

    bool checkProduct(string name);

    Product findProduct(string name);

    void updateProduct(string name, string new_name, int new_quantity, double new_price);

    void addOrder(Order o);

    bool checkFactor(string customerName, string date);

    Factor findFactor(string customerName, string date);

    void addFactor(Factor f);

    void printFactorOrders(string customerName, string date);

    void displayOrders();
    
    void transactionBalance(time_t start, time_t end);
};

void Manager::addProduct(Product p)
{
    File myFile;
    string fileName = "products.txt";
    myFile.open(fileName, ios::out | ios::app);
    myFile.write(p.getName() + "," + to_string(p.getQuantity()) + "," + to_string(p.getPrice()) + "\n");
    myFile.close();
}

void Manager::displayProducts()
{
    ifstream myFile("products.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string name,quantity,price;
            getline(ss, name, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');
            cout << "Name: " << name << setw(30) << "Quantity: " << quantity << setw(30) << "Price: " << price << endl;
        }
        myFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
}

bool Manager::checkProduct(string name)
{
    ifstream myFile("products.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string n, q, p;
            getline(ss, n, ',');
            getline(ss, q, ',');
            getline(ss, p, ',');
            
            if (name == n)
                return true;
        }
        myFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    return false;
}

Product Manager::findProduct(string name)
{
    ifstream myFile("products.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string n, q, p;
            getline(ss, n, ',');
            getline(ss, q, ',');
            getline(ss, p, ',');

            if (name == n)
            {
                double doubleP = stod(p);
                int intQ = stoi(q);
                Product product(n, intQ, doubleP);

                return product;
            }
        }
        myFile.close();
    }
}

void Manager::updateProduct(string name, string new_name, int new_quantity, double new_price)
{
    ifstream myFile("products.txt");
    ofstream temp("temp.txt");
    string line;
    string n, q, p;

    while (getline(myFile, line))
    {
        stringstream ss(line);
        getline(ss, n, ',');
        getline(ss, q, ',');
        getline(ss, p, ',');
        if (n != name)
        {
            temp << line << endl;
        }
    }
    temp << new_name + "," + to_string(new_quantity) + "," + to_string(new_price) + "\n";
    myFile.close();
    temp.close();
    remove("products.txt");
    rename("temp.txt", "products.txt");
}

void Manager::addOrder(Order o)
{
    File myFile;
    string fileName = "orders.txt";
    myFile.open(fileName, ios::out | ios::app);
    myFile.write(o.getProductName() + "," + o.getCustomerName() + "," + o.getDate() + "," + to_string(o.getQuantity()) + "," + to_string(o.getPrice()) + "\n");
    myFile.close();
}

bool Manager::checkFactor(string customerName, string date)
{
    ifstream myFile("factors.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string cn, pn, d, tp;
            getline(ss, cn, ',');
            getline(ss, pn, ',');
            getline(ss, d, ',');
            getline(ss, tp, ',');

            if (customerName == cn && date == d)
                return true;

        }
        myFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
    return false;
}

Factor Manager::findFactor(string customerName, string date)
{
    ifstream myFile("factors.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string cn, pn, d, tp;
            getline(ss, cn, ',');
            getline(ss, pn, ',');
            getline(ss, d, ',');
            getline(ss, tp, ',');

            if (customerName == cn && date == d)
            {
                double numberAsDouble = stod(tp);

                Factor factor(cn, pn, d, numberAsDouble);

                return factor;
            }
        }
        myFile.close();
    }
}

void Manager::addFactor(Factor f)
{
    File myFile;
    string fileName = "factors.txt";
    myFile.open(fileName, ios::out | ios::app);
    myFile.write(f.getCustomerName() + "," + f.getPhoneNumber() + "," + f.getDate() + "," + to_string(f.getTotalPrice()) + "\n");
    myFile.close();
}

void Manager::printFactorOrders(string customerName, string date)
{
    ifstream myFile("orders.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string cn, pn, d, q, p;
            getline(ss, pn, ',');
            getline(ss, cn, ',');
            getline(ss, d, ',');
            getline(ss, q, ',');
            getline(ss, p, ',');

            if (customerName == cn && date == d)
            {
                cout << "ProductName: " << pn << setw(30) << "CustomerName: " << cn << setw(15) << "Date: " << d << setw(15) << "Quantity: " << q << setw(15) << "Price: " << p << endl;
            }
        }
        myFile.close();
    }
}

void Manager::displayOrders()
{
    ifstream myFile("orders.txt");
    string line;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string productName,customerName,date,quantity,price;
            getline(ss, productName, ',');
            getline(ss, customerName, ',');
            getline(ss, date, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');
            cout << "ProductName: " << productName << setw(30) << "CustomerName: " << customerName << setw(30) << "Date: " << date << setw(30) << "Quantity: " << quantity << setw(30) << "Price: " << price << endl;
        }
        myFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
}

void Manager::transactionBalance(time_t start, time_t end)
{
    ifstream myFile("orders.txt");
    string line;
    unsigned int intS = (unsigned int)start;
    unsigned int intE = (unsigned int)end;

    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            stringstream ss(line);
            string pn,cn,d,q,p;
            getline(ss, pn, ',');
            getline(ss, cn, ',');
            getline(ss, d, ',');
            getline(ss, q, ',');
            getline(ss, p, ',');
            
            time_t dEpoch = makeTime(d);
            unsigned int intO = (unsigned int)dEpoch;

            if (intO > intS && intO < intE) {
                cout << "ProductName: " << pn << setw(30) << "CustomerName: " << cn << setw(30) << "Date: " << d << setw(30) << "Quantity: " << q << setw(30) << "Price: " << p << endl;
            }
        }
        myFile.close();
    }
    else
    {
        cerr << "Unable to open file" << endl;
    }
}

void load(string name)
{
    ifstream file(name);
    if (!file.is_open())
    {
        File myFile;
        myFile.open(name, ios::out);
        myFile.close();
    }
}

int main()
{
    Manager m;
    string sMonth, sDay;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    switch (month) {
    case 1:
        sMonth = "01";
        break;

    case 2:
        sMonth = "02";
        break;

    case 3:
        sMonth = "03";
        break;

    case 4:
        sMonth = "04";
        break;

    case 5:
        sMonth = "05";
        break;

    case 6:
        sMonth = "06";
        break;

    case 7:
        sMonth = "07";
        break;

    case 8:
        sMonth = "08";
        break;

    case 9:
        sMonth = "09";
        break;

    case 10:
        sMonth = "10";
        break;

    case 11:
        sMonth = "11";
        break;

    case 12:
        sMonth = "12";
        break;
    }
    
    int day = ltm->tm_mday;
    switch (day) {
    case 1:
        sDay = "01";
        break;

    case 2:
        sDay = "02";
        break;

    case 3:
        sDay = "03";
        break;

    case 4:
        sDay = "04";
        break;

    case 5:
        sDay = "05";
        break;

    case 6:
        sDay = "06";
        break;

    case 7:
        sDay = "07";
        break;

    case 8:
        sDay = "08";
        break;

    case 9:
        sDay = "09";
        break;

    case 10:
        sDay = "10";
        break;

    case 11:
        sDay = "11";
        break;

    case 12:
        sDay = "12";
        break;

    case 13:
        sDay = "13";
        break;

    case 14:
        sDay = "14";
        break;

    case 15:
        sDay = "15";
        break;

    case 16:
        sDay = "16";
        break;

    case 17:
        sDay = "17";
        break;

    case 18:
        sDay = "18";
        break;

    case 19:
        sDay = "19";
        break;

    case 20:
        sDay = "20";
        break;

    case 21:
        sDay = "21";
        break;

    case 22:
        sDay = "22";
        break;

    case 23:
        sDay = "23";
        break;

    case 24:
        sDay = "24";
        break;

    case 25:
        sDay = "25";
        break;

    case 26:
        sDay = "26";
        break;

    case 27:
        sDay = "27";
        break;

    case 28:
        sDay = "28";
        break;

    case 29:
        sDay = "29";
        break;

    case 30:
        sDay = "30";
        break;

    case 31:
        sDay = "31";
        break;

    case 32:
        sDay = "32";
        break;
    }

    string date = to_string(year) + "-" + sMonth + "-" + sDay;

    load("products.txt");
    load("orders.txt");
    load("factors.txt");

    while(true)
    {
        int input;
        cout << endl << "what do you want ? \n" << "1 => storeProduct \t 2 => updateProduct \t 3 => indexProducts \n" << "4 => storeOrder \t 5 => indexOrders \t 6 => factor \t 7 => transaction balance \n" << "Press any other thing to exit" << endl ;
        cin >> input;

        if(input == 1)
        {
            string name;
            int quantity;
            double price;

            cout << "name : ";
            cin.ignore();
            getline(cin,name);

            cout << "quantity : ";
            cin >> quantity;
            cout << "price : ";
            cin >> price;

            Product p(name, quantity, price);
            m.addProduct(p);
        }
        else if (input == 2)
        {
            string name, new_name;
            int new_quantity;
            double new_price;

            m.displayProducts();

            cout << "Enter name of product you want to update :\n";
            cin.ignore();
            getline(cin,name);
            if (!m.checkProduct(name))
            {
                cout << "There is no product with this name\n";
                continue;
            }
            cout << "New name : ";
            cin.ignore();
            getline(cin,new_name);
            cout << "New quantity : ";
            cin >> new_quantity;
            cout << "New price : ";
            cin >> new_price;

            m.updateProduct(name, new_name, new_quantity, new_price);
        }
        else if (input == 3)
        {
            m.displayProducts();
        }
        else if (input == 4)
        {
            string customerName, productName, phoneNumber;
            int quantity;

            cout << "customerName : ";
            cin >> customerName;
            if (!m.checkFactor(customerName, date))
            {
                cout << "phoneNumber : ";
                cin >> phoneNumber;
                Factor f(customerName, phoneNumber, date);
                m.addFactor(f);
            }
            Factor f = m.findFactor(customerName, date);

            cout << "productName : ";
            cin >> productName;
            while (!m.checkProduct(productName))
            {
                cout << "Enter a valid product name : ";
                cin >> productName;
            }
            Product p = m.findProduct(productName);

            cout << "quantity : ";
            cin >> quantity;
            while (quantity > p.getQuantity())
            {
                cout << "There isn't such amount of this product... So enter a less amount : ";
                cin >> quantity;
            }

            m.updateProduct(productName, productName, (p.getQuantity() - quantity), p.getPrice());

            double price = p.getPrice() * quantity;
            Order o(productName, customerName, date, quantity, price);

            m.addOrder(o);
            f.addOrder(o);
        }
        else if (input == 5)
        {
            m.displayOrders();
        }
        else if (input == 6)
        {
            string cn, d;
            cout << "customerName : ";
            cin >> cn;
            cout << "date of order : ";
            cin >> d;
            if (m.checkFactor(cn, d))
            {
                Factor f = m.findFactor(cn, d);
                cout << "CustomerName: " << f.getCustomerName() << setw(30) << "PhoneNumber: " << f.getPhoneNumber() << setw(15) << "Date: " << f.getDate() << setw(15) << "TotalPrice: " << f.getTotalPrice() << endl;
                cout << "Orders :\n";
                m.printFactorOrders(f.getCustomerName(), f.getDate());
            }
            else
            {
                cout << "There is no factor with this details\n";
                continue;
            }
        }
        else if (input == 7)
        {
            string sDate, eDate;
            time_t start, end;
            cout << "Enter start date(e.g. 2010-07-25) : ";
            cin >> sDate;

            if (sDate == "") {
                time_t month = 30 * 24 * 60 * 60;
                start = (makeTime(date) - month);
            } else {
                start = makeTime(sDate);
                if (start == 0) {
                    cout << "The start date is invalid\n";
                    continue;
                }
            }

            cout << "Enter end date(e.g. 2024-04-02) : ";
            cin >> eDate;
            if (eDate.empty()) {
                eDate = date;
            }
            end = makeTime(eDate);
            if (end == 0) {
                cout << "The end date is invalid\n";
                continue;
            }

            m.transactionBalance(start, end);
        }
        else
        {
            exit(0);
        }
    }
}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iomanip>
#include <ctime>

using namespace std;

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

    void printOrders(string customerName, string date);

    void displayOrders();
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

    // for (auto& p : products) {
    //     cout << " Name: " << p.getName() << ", Quantity: " << p.getQuantity() << ", Price: " << p.getPrice() << endl;
    // }
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
            cout << name << "\t" << n << "\t";
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
    // for (auto& o : orders)
    // {
    //  if (o.orderDate.year >= year && o.orderDate.year <= year2 &&
    //    o.orderDate.month >= month && o.orderDate.month <= month2 &&
    //      o.orderDate.day >= day && o.orderDate.day <= day2)
    //{
    //    total += o.getTotalPrice();
    //  }
    //}
    // return total;
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

void Manager::printOrders(string customerName, string date)
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
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
    int intNow = stoi(to_string(year) + to_string(month) + to_string(day));

    load("products.txt");
    load("orders.txt");
    load("factors.txt");

    while(true)
    {
        int input;
        cout << "what do you want ? \n" << "1 => storeProduct \t 2 => updateProduct \t 3 => indexProducts \n" << "4 => storeOrder \t 5 => indexOrders \t 6 => factor \t 7 => transaction balance \n" << "Press any other thing to exit" << endl ;
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

            cout << "Enter name of product you want to update : ";
            cin.ignore();
            getline(cin,name);
            if (!m.checkProduct(name))
            {
                cout << "this name not exist.";
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
            Product p = m.findProduct(productName);
            if(!m.checkProduct(productName))
            {
                cout << "Enter a valid product name : ";
                cin >> productName;
                p = m.findProduct(productName);
            }

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
            if (!m.checkFactor(cn, d))
            {
                Factor f = m.findFactor(cn, d);
                cout << "CustomerName: " << f.getCustomerName() << setw(30) << "PhoneNumber: " << f.getPhoneNumber() << setw(15) << "Date: " << f.getDate() << setw(15) << "TotalPrice: " << f.getTotalPrice() << endl;
                cout << "Orders :\n";
                m.printOrders(f.getCustomerName(), f.getDate());
            }
            else
            {
                cout << "There is no factor with this details\n";
                continue;
            }
        }
        else if (input == 7)
        {

        }
        else
        {
            exit(0);
        }
    }
}

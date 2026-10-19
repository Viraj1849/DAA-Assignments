
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

struct Order {
    int orderID, customerID;
    string timestamp;
};

void merge(vector<Order>& a, int l, int m, int r) {
    vector<Order> L(a.begin()+l, a.begin()+m+1);
    vector<Order> R(a.begin()+m+1, a.begin()+r+1);
    int i=0, j=0, k=l;

    while(i<L.size() && j<R.size()) {
        if(L[i].timestamp <= R[j].timestamp)
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while(i<L.size()) a[k++] = L[i++];
    while(j<R.size()) a[k++] = R[j++];
}

void mergeSort(vector<Order>& a, int l, int r) {
    if(l < r) {
        int m = l + (r-l)/2;
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        merge(a, l, m, r);
    }
}

vector<Order> readCSV(string filename) {
    vector<Order> orders;
    ifstream file(filename);
    string line;

    if(!file.is_open()) {
        cerr << "Error: Cannot open file\n";
        return orders;
    }

    getline(file, line); // Skip header

    while(getline(file, line)) {
        stringstream ss(line);
        string id, customer, timestamp;

        getline(ss, id, ',');
        getline(ss, customer, ',');
        getline(ss, timestamp, ',');

        if(id.empty() || customer.empty() || timestamp.empty())
            continue;

        try {
            Order o;
            o.orderID = stoi(id);
            o.customerID = stoi(customer);
            o.timestamp = timestamp;
            orders.push_back(o);
        } catch(...) {
            continue;
        }
    }
    return orders;
}

void displayOrders(const vector<Order>& orders, int limit=10) {
    cout << "OrderID\tCustomerID\tTimestamp\n";
    for(int i=0; i<orders.size() && i<limit; i++)
        cout << orders[i].orderID << "\t"
             << orders[i].customerID << "\t\t"
             << orders[i].timestamp << "\n";
}

int main() {
    string filename = "orders.csv";
    vector<Order> orders = readCSV(filename);

    if(orders.empty()) {
        cout << "No data found!\n";
        return 1;
    }

    cout << "Total Orders Imported: "
         << orders.size() << "\n";

    cout << "\nBefore Sorting:\n";
    displayOrders(orders);

    auto start = high_resolution_clock::now();
    mergeSort(orders, 0, (int)orders.size()-1);
    auto stop = high_resolution_clock::now();

    cout << "\nAfter Merge Sort:\n";
    displayOrders(orders);

    auto duration =
        duration_cast<milliseconds>(stop-start);

    cout << "\nSorting Time: "
         << duration.count() << " ms\n";

    return 0;
}

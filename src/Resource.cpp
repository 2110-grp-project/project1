
#include "../include/Resource.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

// Convert text to lowercase for case-insensitive comparisons.
string toLowerCase(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(s[i]))
        );
    }
    return s;
}

// Sorting comparison functions
bool comparebyname(Resource a, Resource b) {
    return toLowerCase(a.name) < toLowerCase(b.name);
}

bool comparebyid(Resource a, Resource b) {
    return a.id < b.id;
}

bool comparebytype(Resource a, Resource b) {
    return toLowerCase(a.type) < toLowerCase(b.type);
}

bool comparebystatus(Resource a, Resource b) {
    return toLowerCase(a.status) < toLowerCase(b.status);
}

// Merge Sort helper
void merge(vector<Resource>& Res, int left, int mid, int right,
           bool (*cmp)(Resource, Resource)) {
    vector<Resource> leftHalf(
        Res.begin() + left, Res.begin() + mid + 1
    );
    vector<Resource> rightHalf(
        Res.begin() + mid + 1, Res.begin() + right + 1
    );

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftHalf.size() && j < rightHalf.size()) {
        if (cmp(leftHalf[i], rightHalf[j])) {
            Res[k++] = leftHalf[i++];
        } else {
            Res[k++] = rightHalf[j++];
        }
    }

    while (i < leftHalf.size()) {
        Res[k++] = leftHalf[i++];
    }

    while (j < rightHalf.size()) {
        Res[k++] = rightHalf[j++];
    }
}

void mergesort(vector<Resource>& Res, int left, int right,
               bool (*cmp)(Resource, Resource)) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergesort(Res, left, mid, cmp);
    mergesort(Res, mid + 1, right, cmp);
    merge(Res, left, mid, right, cmp);
}

// Load resources from the data file
vector<Resource> loadresources(string filename) {
    vector<Resource> Res;
    ifstream inFile(filename);

    if (!inFile) {
        cout << "No file found: " << filename << endl;
        return Res;
    }

    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, type, status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        if (id.empty()) {
            cout << "Invalid ID. Skipping this entry." << endl;
            continue;
        }

        bool isduplicate = false;

        for (const Resource& existing : Res) {
            if (existing.id == id) {
                cout << "Duplicate ID " << id
                     << " found. Skipping this entry." << endl;
                isduplicate = true;
                break;
            }
        }

        if (isduplicate) {
            continue;
        }

        Resource r;
        r.id = id;
        r.name = name;
        r.type = type;
        r.status = status;

        Res.push_back(r);
    }

    return Res;
}

// Display all resources
void displayresources(const vector<Resource>& Res) {
    cout << "File has " << Res.size()
         << " stored resources." << endl;

    for (const Resource& r : Res) {
        cout << "ID: " << r.id
             << " | Name: " << r.name
             << " | Type: " << r.type
             << " | Status: " << r.status << endl;
    }
}

// Sort resources using Merge Sort
void sortresources(vector<Resource>& Res) {
    if (Res.empty()) {
        cout << "No resources to sort." << endl;
        return;
    }

    cout << "\nSort by:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Name" << endl;
    cout << "3. Type" << endl;
    cout << "4. Status" << endl;
    cout << "Enter choice: ";

    int sortchoice;

    if (!(cin >> sortchoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input." << endl;
        return;
    }

    cin.ignore(10000, '\n');

    if (sortchoice == 1) {
        mergesort(Res, 0, static_cast<int>(Res.size()) - 1,
                  comparebyid);
    } else if (sortchoice == 2) {
        mergesort(Res, 0, static_cast<int>(Res.size()) - 1,
                  comparebyname);
    } else if (sortchoice == 3) {
        mergesort(Res, 0, static_cast<int>(Res.size()) - 1,
                  comparebytype);
    } else if (sortchoice == 4) {
        mergesort(Res, 0, static_cast<int>(Res.size()) - 1,
                  comparebystatus);
    } else {
        cout << "Invalid sorting choice." << endl;
        return;
    }

    cout << "\nSorted results:" << endl;
    displayresources(Res);
}

// Linear Search: search resources by ID, name, or type
void searchresources(const vector<Resource>& Res) {
    if (Res.empty()) {
        cout << "No resources available to search." << endl;
        return;
    }

    cout << "\nSearch Resources" << endl;
    cout << "1. Search by ID" << endl;
    cout << "2. Search by Name" << endl;
    cout << "3. Search by Type" << endl;
    cout << "Enter choice: ";

    int choice;

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        return;
    }

    cin.ignore(10000, '\n');

    if (choice < 1 || choice > 3) {
        cout << "Invalid search option." << endl;
        return;
    }

    string searchterm;

    cout << "Enter search term: ";
    getline(cin, searchterm);

    if (searchterm.empty()) {
        cout << "Search term cannot be empty." << endl;
        return;
    }

    bool found = false;

    // Check each resource one at a time.
    for (const Resource& r : Res) {
        bool match = false;

        if (choice == 1) {
            match = (r.id == searchterm);
        } else if (choice == 2) {
            match = (toLowerCase(r.name) ==
                     toLowerCase(searchterm));
        } else if (choice == 3) {
            match = (toLowerCase(r.type) ==
                     toLowerCase(searchterm));
        }

        if (match) {
            cout << "ID: " << r.id
                 << " | Name: " << r.name
                 << " | Type: " << r.type
                 << " | Status: " << r.status << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "No matching resources found." << endl;
    }
}


// Reports.cpp
// Reporting module: active reservations, resource utilization,
// most requested resources, and waiting-list statistics.

#include "Reports.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <limits>
using namespace std;

// Counts reservations in the linked list for one resource ("" = all).
static int countReservations(const ReservationList& list, const string& resourceID) {
    int count = 0;
    const ReservationNode* cur = list.getHead();
    while (cur != nullptr) {
        if (resourceID == "" || cur->data.getResourceID() == resourceID) {
            count++;
        }
        cur = cur->next;
    }
    return count;
}

// Counts students waiting for one resource ("" = all).
// Uses a COPY of the queue, so the real waiting list is unchanged.
static int countWaiting(const WaitingList& waiting, const string& resourceID) {
    queue<WaitingStudent> copy = waiting.getQueue();
    int count = 0;
    while (!copy.empty()) {
        if (resourceID == "" || copy.front().resourceID == resourceID) {
            count++;
        }
        copy.pop();
    }
    return count;
}

// Report 1: Active reservations
void reportActiveReservations(const ReservationList& list) {
    cout << "\n--- Active Reservations Report ---\n";
    int total = countReservations(list, "");
    if (total == 0) {
        cout << "There are no active reservations.\n";
        return;
    }
    cout << "Total active reservations: " << total << "\n\n";
    list.displayReservations();
}

// Report 2: Resource utilization
void reportUtilization(const vector<Resource>& resources, const ReservationList& list) {
    cout << "\n--- Resource Utilization Report ---\n";
    if (resources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(25) << "Name"
         << setw(12) << "Status" << "Reservations\n";
    for (const Resource& r : resources) {
        cout << left << setw(10) << r.id << setw(25) << r.name
             << setw(12) << r.status << countReservations(list, r.id) << "\n";
    }
}

// Report 3: Waiting-list statistics
void reportWaitingListStats(const vector<Resource>& resources, const WaitingList& waiting) {
    cout << "\n--- Waiting-List Statistics ---\n";
    if (resources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(25) << "Name" << "Students Waiting\n";
    for (const Resource& r : resources) {
        cout << left << setw(10) << r.id << setw(25) << r.name
             << countWaiting(waiting, r.id) << "\n";
    }
    cout << "Total students waiting: " << countWaiting(waiting, "") << "\n";
}

// Report 4: Most requested resources
// Requests = active reservations + students waiting.
// Ranked with a hand-written insertion sort (no std::sort).
struct ResourceDemand {
    string id;
    string name;
    int reservations;
    int waiting;
    int total;
};

void reportMostRequested(const vector<Resource>& resources,
                         const ReservationList& list, const WaitingList& waiting) {
    cout << "\n--- Most Requested Resources ---\n";
    if (resources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }
    vector<ResourceDemand> demand;
    for (const Resource& r : resources) {
        ResourceDemand d;
        d.id = r.id;
        d.name = r.name;
        d.reservations = countReservations(list, r.id);
        d.waiting = countWaiting(waiting, r.id);
        d.total = d.reservations + d.waiting;
        demand.push_back(d);
    }
    for (size_t i = 1; i < demand.size(); i++) {
        ResourceDemand key = demand[i];
        int j = (int)i - 1;
        while (j >= 0 && demand[j].total < key.total) {
            demand[j + 1] = demand[j];
            j--;
        }
        demand[j + 1] = key;
    }
    cout << left << setw(6) << "Rank" << setw(10) << "ID" << setw(25) << "Name"
         << setw(14) << "Reservations" << setw(10) << "Waiting" << "Total\n";
    for (size_t i = 0; i < demand.size(); i++) {
        cout << left << setw(6) << (i + 1) << setw(10) << demand[i].id
             << setw(25) << demand[i].name << setw(14) << demand[i].reservations
             << setw(10) << demand[i].waiting << demand[i].total << "\n";
    }
}

// Reports sub-menu
void reportsMenu(const vector<Resource>& resources,
                 const ReservationList& list, const WaitingList& waiting) {
    while (true) {
        cout << "\n----- Reports -----\n"
             << " 1. Active reservations\n"
             << " 2. Resource utilization\n"
             << " 3. Most requested resources\n"
             << " 4. Waiting-list statistics\n"
             << " 0. Back to main menu\n"
             << "Choose an option: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        switch (choice) {
            case 1: reportActiveReservations(list); break;
            case 2: reportUtilization(resources, list); break;
            case 3: reportMostRequested(resources, list, waiting); break;
            case 4: reportWaitingListStats(resources, waiting); break;
            case 0: return;
            default: cout << "Invalid option. Please enter 0-4.\n";
        }
    }
}

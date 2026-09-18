#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include <string>
using namespace std;

struct CancelledReservation {
    int reservationID;
    int studentID;
    string resourceID;
    string date;
};

class CancellationHistory {
private:
    stack<CancelledReservation> cancellationStack;

public:
    void addCancellation(int reservationID, int studentID,
                         string resourceID, string date);

    CancelledReservation undoCancellation();

    void displayHistory();

    bool isEmpty();
};

#endif
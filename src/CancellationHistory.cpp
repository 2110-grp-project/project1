#include "../include/CancellationHistory.h"
#include <iostream>
using namespace std;

void CancellationHistory::addCancellation(int reservationID, int studentID,
                                          string resourceID, string date) {
    CancelledReservation reservation;

    reservation.reservationID = reservationID;
    reservation.studentID = studentID;
    reservation.resourceID = resourceID;
    reservation.date = date;

    cancellationStack.push(reservation);

    cout << "Reservation " << reservationID
         << " was added to cancellation history." << endl;
}

CancelledReservation CancellationHistory::undoCancellation() {
    if (cancellationStack.empty()) {
        cout << "There are no cancellations to undo." << endl;

        CancelledReservation emptyReservation;
        emptyReservation.reservationID = -1;

        return emptyReservation;
    }

    CancelledReservation reservation = cancellationStack.top();

    cancellationStack.pop();

    cout << "Reservation " << reservation.reservationID
         << " was restored." << endl;

    return reservation;
}

void CancellationHistory::displayHistory() {
    if (cancellationStack.empty()) {
        cout << "Cancellation history is empty." << endl;
        return;
    }

    stack<CancelledReservation> temp = cancellationStack;

    cout << "Cancellation History:" << endl;

    while (!temp.empty()) {
        cout << "Reservation ID: " << temp.top().reservationID
             << " | Student ID: " << temp.top().studentID
             << " | Resource ID: " << temp.top().resourceID
             << " | Date: " << temp.top().date
             << endl;

        temp.pop();
    }
}

bool CancellationHistory::isEmpty() {
    return cancellationStack.empty();
}

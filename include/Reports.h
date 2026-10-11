#ifndef REPORTS_H
#define REPORTS_H

#include <vector>
#include "Resource.h"
#include "Reservation.h"
#include "WaitingList.h"
using namespace std;

void activereservation(const ReservationList& list);
void utilization(const vector<Resource>& resources, const ReservationList& list);
void mostrequested(const vector<Resource>& resources, const ReservationList& list, const WaitingList& waiting);
void waitingliststats(const vector<Resource>& resources, const WaitingList& waiting);
void menu(const vector<Resource>& resources, const ReservationList& list, const WaitingList& waiting);

#endif

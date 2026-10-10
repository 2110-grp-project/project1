#ifndef REPORTS_H
#define REPORTS_H

#include <vector>
#include "Resource.h"
#include "Reservation.h"
#include "WaitingList.h"
using namespace std;

void reportActiveReservations(const ReservationList& list);
void reportUtilization(const vector<Resource>& resources, const ReservationList& list);
void reportMostRequested(const vector<Resource>& resources,
                         const ReservationList& list, const WaitingList& waiting);
void reportWaitingListStats(const vector<Resource>& resources, const WaitingList& waiting);
void reportsMenu(const vector<Resource>& resources,
                 const ReservationList& list, const WaitingList& waiting);

#endif

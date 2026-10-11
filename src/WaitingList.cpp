```cpp
#include "Reports.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;

static int reservationcount(const ReservationList& list, const string& resourceID)
{
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    list.displayReservations();

    cout.rdbuf(old);

    int count = 0;
    string line;
    string tag = "Resource ID: ";

    while (getline(buffer, line))
    {
        if (line.compare(0, tag.size(), tag) == 0)
        {
            if (resourceID == "" || line.substr(tag.size()) == resourceID)
            {
                count++;
            }
        }
    }

    return count;
}

static int waitingcount(const WaitingList& waiting, const string& resourceID)
{
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    const_cast<WaitingList&>(waiting).displayWaitingList();

    cout.rdbuf(old);

    int count = 0;
    string line;
    string tag = "Resource ID: ";

    while (getline(buffer, line))
    {
        size_t pos =

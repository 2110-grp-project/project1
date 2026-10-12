#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <string>
using namespace std;

struct WaitingStudent {
    int studentID;
    string resourceID;
};

class WaitingList {
private:
    queue<WaitingStudent> waitingQueue;

public:
    void addStudent(int studentID, string resourceID);
    void removeStudent();
    void displayWaitingList();
    bool isEmpty();
    queue<WaitingStudent> getQueue() const{
	return waitingQueue;
    }

};

#endif

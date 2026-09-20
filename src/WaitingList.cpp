#include "../include/WaitingList.h"
#include <iostream>
using namespace std;

void WaitingList::addStudent(int studentID, string resourceID) {
    WaitingStudent student;

    student.studentID = studentID;
    student.resourceID = resourceID;

    waitingQueue.push(student);

    cout << "Student " << studentID
         << " added to the waiting list for resource "
         << resourceID << "." << endl;
}

void WaitingList::removeStudent() {
    if (waitingQueue.empty()) {
        cout << "The waiting list is empty." << endl;
        return;
    }

    WaitingStudent student = waitingQueue.front();

    cout << "Student " << student.studentID
         << " removed from the waiting list for resource "
         << student.resourceID << "." << endl;

    waitingQueue.pop();
}

void WaitingList::displayWaitingList() {
    if (waitingQueue.empty()) {
        cout << "The waiting list is empty." << endl;
        return;
    }

    queue<WaitingStudent> temp = waitingQueue;

    cout << "Waiting List:" << endl;

    while (!temp.empty()) {
        cout << "Student ID: " << temp.front().studentID
             << " | Resource ID: " << temp.front().resourceID
             << endl;

        temp.pop();
    }
}

bool WaitingList::isEmpty() {
    return waitingQueue.empty();
}
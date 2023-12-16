/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include <cmath>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    string input = commandString;
    if (input.empty()) {
        isPass = true;
        return;
    }
    char nextChar;
    stringstream ss(input);
    ss >> nextChar;
    if (nextChar == 'Q') {
        isQuit = true;
        return;
    }
    else if (nextChar == 'S') {
        isSave = true;
        return;
    }
    else if (nextChar == 'e') {
        ss >> elevatorId;

        char target;
        ss >> target;
        if (target == 'p') {
            isPickup = true;
        }
        else {
            ss >> targetFloor;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPassMove() || isQuitMove() || isSaveMove()) {
        return true;
    }
    if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS)
        && !(elevators[elevatorId].isServicing())) {
        if (isPickupMove()) {
            return true;
        }
        else if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) && (targetFloor != elevators[elevatorId].getCurrentFloor())) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int oldDistance = 0;

    for (int i = 0; i < pickupList.size(); i++) {
        int num = static_cast<int>(pickupList[i]) - 48;
        peopleToPickup[i] = num;
        numPeopleToPickup++;

        Person p = pickupFloor.getPersonByIndex(num);
        totalSatisfaction += (MAX_ANGER - p.getAngerLevel());

        int newDistance = abs(currentFloor - p.getTargetFloor());
        if (newDistance > oldDistance) {
            oldDistance = newDistance;
            targetFloor = p.getTargetFloor();
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
    return isPass;
}

bool Move::isSaveMove() const {
    return isSave;
}

bool Move::isQuitMove() const {
    return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}


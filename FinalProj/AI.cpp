/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Sofie Vos, Sydney Liang, Grace Coppola, Rebecca Zhang
 * sevos, sfliang, gcoppola, rbzhang
 *
 * Final Project - Elevators
 */
#include "AI.h"
#include <cassert>
#include "math.h"

 // This file is used only in the Reach, not the Core.
 // You do not need to make any changes to this file for the Core


 //taking a turn
 // iterate through every floor to see which one has the most people
 // ultimately otuputs a move
 // first find floor then decide which elevator is closest and not servicing
 // floor w most ppl in same direction
 // if number of people on each floor is same, go to one that is closest
 // if no people waiting = pass move
 // if high number ppl on floor elevator dropped ppl off at, then pickup ppl instead of going to floor w higher num people


 /* for the elevators absolute value of current floor if elevator minus floor w most people for each elevator
  Elevator bestElevator;
  */
string getAIMoveString(const BuildingState& buildingState) {

    string move = "";
    move += "e";
    // finding floor w/ most ppl
    int floorMaxPeople = 0;
    int floorMax = -1;
    int count = 0;
    for (int i = 0; i < NUM_FLOORS; i++) {
        _Floor floor = buildingState.floors[i];
        if (floor.numPeople > floorMaxPeople) {
            floorMaxPeople = floor.numPeople;
            floorMax = i;
        }
        count += floor.numPeople;
    }

    // finding whcih elevator is best to go to floor w/ most ppl
    _Elevator bestElevator = buildingState.elevators[0];
    double smallDiff = 11;
    for (int i = 0; i < NUM_ELEVATORS; i++) {
        int curr = buildingState.elevators[i].currentFloor;
        double difference = fabs(curr - floorMax);
        if (difference < smallDiff && !buildingState.elevators[i].isServicing) {
            bestElevator = buildingState.elevators[i];
            smallDiff = difference;
        }
    }
    //elevator number
    // need to make the elevator number a char to return with the "e" that is in the move string
    string elevator = to_string(bestElevator.elevatorId);
    string toFloor = to_string(floorMax);
    int elev1curr = buildingState.elevators[0].currentFloor;
    _Floor elev1Floor = buildingState.floors[elev1curr];
    int elev2curr = buildingState.elevators[1].currentFloor;
    _Floor elev2Floor = buildingState.floors[elev2curr];
    int elev3curr = buildingState.elevators[2].currentFloor;
    _Floor elev3Floor = buildingState.floors[elev3curr];
    string elevator1 = to_string(buildingState.elevators[0].elevatorId);
    string elevator2 = to_string(buildingState.elevators[1].elevatorId);
    string elevator3 = to_string(buildingState.elevators[2].elevatorId);

    if ((buildingState.elevators[0].isServicing && buildingState.elevators[1].isServicing && buildingState.elevators[2].isServicing) || count == 0) {
        return "";
    }
    else if (elev1Floor.numPeople >= 7 && !buildingState.elevators[0].isServicing) {
        move += elevator1;
        move += "p";
    }
    else if (elev2Floor.numPeople >= 7 && !buildingState.elevators[1].isServicing) {
        move += elevator2;
        move += "p";
    }
    else if (elev3Floor.numPeople >= 7 && !buildingState.elevators[2].isServicing) {
        move += elevator3;
        move += "p";
    }
    else if (bestElevator.currentFloor != floorMax) {
        move += elevator;
        move += "f";
        move += toFloor;
    }
    else {
        move += elevator;
        move += "p";
    }

    return move;
}

string getAIPickupList(const Move& move, const BuildingState& buildingState,
    const Floor& floorToPickup) {
    string pickupList = "";
    int countUp = 0;
    int countDown = 0;
    _Elevator bestElevator = buildingState.elevators[0];
    //_Floor floor = buildingState.floors[floorToPickup];
    for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
        Person p = floorToPickup.getPersonByIndex(i);
        int direction = p.getCurrentFloor() - p.getTargetFloor();
        if (direction < 0) {
            countDown++;
        }
        else {
            countUp++;
        }
    }
    if (countDown > countUp) {
        for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
            Person p = floorToPickup.getPersonByIndex(i);
            int direction = p.getCurrentFloor() - p.getTargetFloor();
            if (direction < 0) {
                string index = to_string(i);
                pickupList += index;
            }
        }
    }
    else {
        for (int i = 0; i < floorToPickup.getNumPeople(); i++) {
            Person p = floorToPickup.getPersonByIndex(i);
            int direction = p.getCurrentFloor() - p.getTargetFloor();
            if (direction > 0) {
                string index = to_string(i);
                pickupList += index;
            }
        }
    }

    return pickupList;
}

/*
 * Copyright 2022 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"
using namespace std;

void person_tests();
void elevators_tests();
void floor_tests();


void start_tests() {
   // person_tests();
   // elevators_tests();  
    //floor_tests();
    //Game game;
    //string pickUpList = "12345";
    //game.isValidPickupList(pickUpList, 6);
   
    return;
}



void person_tests() {
    //initialize a person with targetFloor 5, anger 5
    Person p("0f0t5a5");
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    //simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 0" << endl;
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    //simulate time not being a multiple
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    //no change
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    cout << exploded << " Expected 1" << endl;
    p.tick(7);
    exploded = p.tick(7);
    cout << exploded;

    Person q("7f5t9a4");
    cout << "\nThe person you just entered is: ";
    q.print(cout);
    q.tick(24);
    cout << endl;
   
    cout << q.tick(7);
    cout << q.tick(35);
    cout << p.tick(-10);
    cout << q.tick(-7);
    cout << p.tick(44);
    cout << q.tick(TICKS_PER_ELEVATOR_MOVE);
}

void elevators_tests()
{
    Elevator e;
    e.setCurrentFloor(4);
    e.tick(TICKS_PER_ELEVATOR_MOVE);

    cout << "expected: 0; actual: " << e.isServicing();
    cout << "expected: 4; actual: " << e.getCurrentFloor();
    e.serviceRequest(7);
    cout << "expected: 1; actual: " << e.isServicing();
    cout << "expected: 7; actual: " << e.getTargetFloor();
    e.tick(TICKS_PER_ELEVATOR_MOVE); //5
    e.tick(TICKS_PER_ELEVATOR_MOVE); //6 
    e.isServicing();
    cout << e.getCurrentFloor();
    e.serviceRequest(4);
    e.tick(TICKS_PER_ANGER_INCREASE);
    e.tick(4); 
    e.getCurrentFloor(); // 5
    e.isServicing();
    e.tick(3); // 8
    e.isServicing();
    e.tick(7);
    e.tick(-27);
    e.tick(0);

}


void floor_tests()
{
    
}


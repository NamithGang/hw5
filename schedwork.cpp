#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, size_t day, map<Worker_T, size_t>& shiftNum);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    map<Worker_T, size_t> shiftNum;
    sched.assign(avail.size(), vector<Worker_T>());
    return helper(avail, dailyNeed, maxShifts, sched, 0, shiftNum);
}

bool helper(const AvailabilityMatrix& avail, size_t d, size_t m, DailySchedule& sched, size_t day, map<Worker_T, size_t>& shiftNum){
    if(day >= avail.size()){
        return true;
    }
    if(sched[day].size() == d){
        return helper(avail, d, m, sched, day+1,shiftNum); 
    }

    for(Worker_T worker = 0; worker < avail[day].size(); worker++){
        if(!avail[day][worker]){ // 0 in avail matrix;
            continue;
        }
        if(shiftNum[worker] >= m){ // max number in shift
            continue;
        }
        if(find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()){ // already working a shift for the day
            continue;
        }

        sched[day].push_back(worker);
        shiftNum[worker]++;


        //found solution
        if(helper(avail, d, m, sched, day,shiftNum)){
            return true;
        }

        //reset
        sched[day].pop_back();
        shiftNum[worker]--;
    }

    return false;
}


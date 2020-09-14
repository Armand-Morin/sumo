/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2020-2020 German Aerospace Center (DLR) and others.
// This program and the accompanying materials are made available under the
// terms of the Eclipse Public License 2.0 which is available at
// https://www.eclipse.org/legal/epl-2.0/
// This Source Code may also be made available under the following Secondary
// Licenses when the conditions for such availability set forth in the Eclipse
// Public License 2.0 are satisfied: GNU General Public License, version 2
// or later which is available at
// https://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
/****************************************************************************/
/// @file    StopWatch.h
/// @author  Michael Behrisch
/// @date    2020-09-09
///
// A stop watch for keeping time,
// based on https://github.com/vukis/Cpp-Utilities/tree/master/ThreadPool
/****************************************************************************/
#pragma once

#include <vector>
#include <chrono>
#include <numeric>

template<typename TimeT = std::chrono::milliseconds, typename ClockT = std::chrono::steady_clock>
class StopWatch {
public:
    StopWatch() {
        start();
    }

    void start() {
        myStart = myEnd = ClockT::now();
    }

    long long int stop() {
        myEnd = ClockT::now();
        return elapsed();
    }

    long long int elapsed() const {
        const TimeT& delta = std::chrono::duration_cast<TimeT>(myEnd - myStart);
        myHistory.push_back(delta);
        return (long long int)delta.count();
    }

    const std::vector<TimeT>& getHistory() const {
        return myHistory;
    }

    long long int getAverage() const {
        return (long long int)(std::accumulate(myHistory.begin(), myHistory.end(), TimeT{}) / myHistory.size()).count();
    }

private:
    std::chrono::time_point<ClockT> myStart;
    std::chrono::time_point<ClockT> myEnd;
    mutable std::vector<TimeT>      myHistory;
};
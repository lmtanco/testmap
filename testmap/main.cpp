 //
//  main.cpp
//  testmap
//
//  Created by Diana UMA on 2/12/15.
//  Copyright © 2015 diana. All rights reserved.
//

#include "HTRFUtil.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

int main(int argc, const char * argv[])
{
    int azimuthStep = 6, elevationStep = 6;
    HTRF h(azimuthStep,elevationStep);
    hrir oneHrir = std::make_pair(std::vector<float>{0.234,0.4567,0.987}, std::vector<float>{0.1234,0.45234,0.987});
//    h.beginSetup(vleft.size());
//    h.add(azimuth, elevation, vleft, vright);
//    h.endSetup();
    h.insert(78,0,move(oneHrir)); // azimuth = 78, elevation = 0
    cout << "** HTRFMap h(6,6);" << endl;
    cout << "** hrir vleft{0.234,0.4567,0.987};"  << endl;
    cout << "** h.insert(78,0,move(vleft)); // azimuth = 78, elevation = 0" << endl;

    const hrir& v5 = h(78,0);
    cout << "** const hrir& v5 = h(78,0);" << endl;
    cout << " size of left v5 is: v5.first.size(): " << v5.first.size() << endl;
    
    const hrir& v6 = h(78.00001,0.00001);
    cout << "** const hrir& v6 = h(78.00001,0.00001);" << endl;
    cout << " size of left v6 is: v6.first.size(): " << v6.first.size() << endl;
    
    const hrir& v7 = h(79,2);
    cout << "** const hrir& v7 = h(79,2);" << endl;
    cout << " size of left v7 is: v7.first.size(): " << v7.first.size() << endl;
    
    return 0;
}

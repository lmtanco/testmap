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


class HoldingHTRF {
    HTRFMapAz theMap;
public:
    void loadHRTF(HTRFMapAz && _theMap)
    {
        theMap = forward<HTRFMapAz>(_theMap); // not sure if forward is required here.
    }
    size_t size()
    {
        return theMap.size();
    }
};


int main(int argc, const char * argv[])
{
    HTRFMapAz h;
    hrir v{0.33,0.12345,0.25};
    cout << "Size of v is " << v.size() << endl;
    cout << "v[1] = " << v[1] << endl;
    
    h.insert(3.25, move(v));
    cout << "Size of HRTF map is "  << h.size() << endl;
    cout << "Size of hrir is " << h[3.25].size() << endl;
    cout << "Size of v is now " << v.size() << endl;
    
    hrir v2 = h[3.25];
    cout << "size of hrir[3.25] is " << v2.size() << endl;
    cout << "recovering hrir[3.25][1]: " << v2[1] << endl;
    
    hrir v3 = h[3.26];
    cout << "size of hrir[3.26] is " << v3.size() << endl;
    
    HoldingHTRF container;
    container.loadHRTF(move(h));
    cout << "Size of contained HRTF map is "  << container.size() << endl;
    cout << "Size of HRTF map is now " << h.size() << endl;
    
}

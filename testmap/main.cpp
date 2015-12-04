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


class HoldingHTRFAz { // This would be the core.
    HTRFMapAz theMap;
public:
    void loadHRTF(HTRFMapAz && _theMap)
    {
        theMap = forward<HTRFMapAz>(_theMap);
    }
    size_t size()
    {
        return theMap.size();
    }
};

class HoldingHTRF { // This would be the core.
    HTRFMap theMap;
public:
    void loadHRTF(HTRFMap && _theMap)
    {
        theMap = forward<HTRFMap>(_theMap);
    }
    size_t size()
    {
        return theMap.size();
    }
};

int main(int argc, const char * argv[])
{
    cout << "*****************************************" << endl;
    
    HTRFMapAz hAz;
    hrir v{0.33,0.12345,0.25};
    cout << "** HTRFMapAz hAz;" << endl;
    cout << "** hrir v{0.33,0.12345,0.25};" << endl;
    cout << "Size of v is " << v.size() << endl;
    
    hAz.insert(3.25, move(v));
    cout << "** hAz.insert(3.25, move(v));"<<endl;
    cout << "Size of HRTF map is "  << hAz.size() << endl;
    cout << "Size of v is now " << v.size() << endl;
    
    HoldingHTRFAz container;
    container.loadHRTF(move(hAz));
    cout << "** HoldingHTRF container;"<<endl;
    cout << "** container.loadHRTF(move(h));"<<endl;
    cout << "Size of contained HRTF map is "  << container.size() << endl;
    cout << "Size of HRTF map is now " << hAz.size() << endl;
    
    cout << "******************************************" << endl;
    
    HTRFMap h(6,6);
    hrir v4{0.234,0.4567,0.987};
    h.insert(78,0,move(v4)); // azimuth = 78, elevation = 0
    cout << "** HTRFMap h(6,6);" << endl;
    cout << "** hrir v4{0.234,0.4567,0.987};"  << endl;
    cout << "** h.insert(78,0,move(v4)); // azimuth = 78, elevation = 0" << endl;

    const hrir& v5 = h(78,0);
    cout << "** const hrir& v5 = h(78,0);" << endl;
    cout << " size of v5 is: v5.size(): " << v5.size() << endl;
    
    const hrir& v6 = h(78.00001,0.00001);
    cout << "** const hrir& v6 = h(78.00001,0.00001);" << endl;
    cout << " size of v6 is: v6.size(): " << v6.size() << endl;
    
    const hrir& v7 = h(79,2);
    cout << "** const hrir& v7 = h(79,2 );" << endl;
    cout << " size of v7 is: v7.size(): " << v7.size() << endl;
    
    return 0;
}

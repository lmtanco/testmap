//
//  HTRFUtil.h
//  testmap
//
//  Created by Diana UMA on 3/12/15.
//  Copyright © 2015 diana. All rights reserved.
//

#ifndef HTRFUtil_h
#define HTRFUtil_h

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

typedef std::vector<float> hrir;
typedef std::unordered_map<float,hrir> table;


class HTRFMapAz
{
private:
    table hrirByAzimuth;
public:
    
    void insert(float azimuth, std::vector<float> && hrir)
    {
        hrirByAzimuth.insert(make_pair(azimuth,std::forward<std::vector<float>>(hrir))); // not sure if forward is required here.
    }
    const hrir & operator[](float index)
    {
        auto it = hrirByAzimuth.find(index);
        if (it != hrirByAzimuth.end())
        {
            return it->second;
        }
        else
        {
            return std::move(hrir());
        }
    }
    size_t size()
    {
        return hrirByAzimuth.size();
    }
};



#endif /* HTRFUtil_h */

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

struct orientation
{
    int azimuth;
    int elevation;
    orientation(int _azimuth, int _elevation):azimuth{_azimuth}, elevation{_elevation}{}
    orientation():orientation{0,0}{}
    bool operator==(const orientation& oth) const
    {
        return ((this->azimuth == oth.azimuth) && (this->elevation == oth.elevation));
    }
};

namespace std
{
    template<>
    struct hash<orientation>
    {
        // adapted from http://en.cppreference.com/w/cpp/utility/hash
        size_t operator()(const orientation & key) const
        {
            size_t h1 = std::hash<int>()(key.azimuth);
            size_t h2 = std::hash<int>()(key.elevation);
            return h1 ^ (h2 << 1);  // exclusive or of hash functions for each float.
        }
    };
}

typedef std::pair<std::vector<float>,std::vector<float>> hrir;
typedef std::unordered_map<orientation,hrir> table;

class HTRF
{
    
private:
    int azimuthStep;
    int elevationStep;
    table t;
    hrir empty;
public:
    HTRF(int _azimuthStep, int _elevationStep):
        azimuthStep{_azimuthStep},
        elevationStep{_elevationStep}
    {}
    
    HTRF() : HTRF{15,15} // default constructor takes 15 as quant. step. 
    {}
    
    void insert(float azimuth, float elevation, hrir && newhrir)
    {
        int iAzimuth = round(azimuth/azimuthStep) * azimuthStep;
        int iElevation = round(elevation/elevationStep) * elevationStep;
        t.emplace(orientation(iAzimuth,iElevation), std::forward<hrir>(newhrir));
    }
    
    size_t size()
    {
        return t.size();
    }
    
    const hrir& operator()(float azimuth, float elevation)
    {
        int iAzimuth = round(azimuth/azimuthStep) * azimuthStep;
        int iElevation = round(elevation/elevationStep) * elevationStep;
        auto it = t.find(orientation(iAzimuth,iElevation));
        if (it != t.end())
        {
            return it->second; // return a const reference so the caller sees changes.
        }
        else
        {
            return empty; // returning an empty hrir.
        }
    }
    
};


#endif /* HTRFUtil_h */

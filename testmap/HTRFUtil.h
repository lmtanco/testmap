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
typedef std::unordered_map<float,hrir> tableAz;


class HTRFMapAz
{
private:
    tableAz hrirByAzimuth;
public:
    
    void insert(float azimuth, std::vector<float> && hrir)
    {
        hrirByAzimuth.emplace(azimuth,std::forward<std::vector<float>>(hrir));
    }
    const hrir & operator[](float index)
    {
        auto it = hrirByAzimuth.find(index);
        if (it != hrirByAzimuth.end())
        {
            return it->second; // return a const reference so the caller sees changes. 
        }
        else
        {
            return std::move(hrir()); // returning an empty hrir.
        }
    }
    size_t size()
    {
        return hrirByAzimuth.size();
    }
};

// Adapted from http://stackoverflow.com/questions/17333/most-effective-way-for-float-and-double-comparison/253874#253874
//
const float defaultepsilon = 0.1; // Just testing.

inline bool essentiallyEqual(float a, float b, float epsilon=defaultepsilon)
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}


struct orientation
{
    int azimuth;
    int elevation;
    orientation(int _azimuth, int _elevation):azimuth{_azimuth}, elevation{_elevation}{}
    orientation():orientation{0,0}{}
    bool operator==(const orientation& oth) const
    {
        //return essentiallyEqual(this->azimuth, oth.azimuth) && essentiallyEqual(this->elevation, oth.elevation);
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
            size_t h1 = std::hash<float>()(key.azimuth);
            size_t h2 = std::hash<float>()(key.elevation);
            return h1 ^ (h2 << 1);  // exclusive or of hash functions for each float.
        }
    };
}

typedef std::unordered_map<orientation,hrir> table;

class HTRFMap
{
private:
    int azimuthStep;
    int elevationStep;
    table t;
    hrir empty;
public:
    HTRFMap(int _azimuthStep, int _elevationStep):
        azimuthStep{_azimuthStep},
        elevationStep{_elevationStep}
    {}
    
    HTRFMap() : HTRFMap{15,15}
    {}
    
    void insert(float azimuth, float elevation, std::vector<float> && hrir)
    {
        int iAzimuth = round(azimuth/azimuthStep) * azimuthStep;
        int iElevation = round(elevation/elevationStep) * elevationStep;
        t.emplace(orientation(iAzimuth,iElevation), std::forward<std::vector<float>>(hrir));
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

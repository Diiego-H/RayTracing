#pragma once
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

#include "HitRecord.hh"

using namespace glm;
using namespace std;

class Ray {
  private:
    vec3 origin;
    vec3 direction;
    float tmin, tmax;
    vector<shared_ptr<HitRecord>> hits;

  public:
    Ray() {}

    Ray(const vec3 &orig, const vec3 &dir, float t_min_=0.01f, float t_max_=std::numeric_limits<float>::infinity()):
      origin(orig),
      direction(dir), 
      tmin(t_min_),
      tmax(t_max_)
    {}

    /* retorna el punt del raig en en temps/lambda t */
    vec3 operator() (const float &t) const {
      return origin + direction*t;
    }

    vec3 getOrigin() const       { return origin; }
    vec3 getDirection() const    { return direction; }
    vec3 pointAt(float t) const  { return origin + t*direction; }
    float getTmin() const {return tmin;};
    float getTmax() const {return tmax;};
    void  setTmin(float tmin_) {tmin = tmin_;};
    void  setTmax(float tmax_) {tmax = tmax_;};
    void  addHit(shared_ptr<HitRecord> h) {hits.push_back(h);};
    shared_ptr<HitRecord> getHit(int i) const {return hits[i];};
    vector<shared_ptr<HitRecord>> getHitRecords() const { return hits;};

    void addHit0(shared_ptr<HitRecord> h) { 
        if (hits.empty()) {
            hits.push_back(h);
        } else {
            hits[0] = h;
        }
    }

    void insertHit(shared_ptr<HitRecord> h) {
        auto it = lower_bound(hits.begin(),hits.end(),h,
          [](const shared_ptr<HitRecord> &lhs, const shared_ptr<HitRecord> &rhs){ return lhs->t < rhs->t; });
        hits.insert(it, h);
    }

    ~Ray() {
        hits.clear();
    }

};


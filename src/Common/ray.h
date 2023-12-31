﻿#ifndef RAY_H
#define RAY_H
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

#include "Vec3.h"


class ray {
    public:
        ray() {}
        ray(const Point3& origin, const Vec3& direction)
            : orig(origin), dir(direction), tm(0)
        {}

        ray(const Point3& origin, const Vec3& direction, double time)
            : orig(origin), dir(direction), tm(time)
        {}

        Point3 origin() const  { return orig; }
        Vec3 direction() const { return dir; }
        double time() const    { return tm; }

        Point3 at(double t) const {
            return orig + t*dir;
        }

    public:
        Point3 orig;
        Vec3 dir;
        double tm;
};

#endif

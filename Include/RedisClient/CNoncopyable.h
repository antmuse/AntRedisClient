#pragma once

#include "HConfig.h"

namespace irr {

class CNoncopyable {

protected:
    CNoncopyable() {}
    ~CNoncopyable() {}

private:
    CNoncopyable(const CNoncopyable&);
    const CNoncopyable& operator=(const CNoncopyable&);
};

}  // namespace irr

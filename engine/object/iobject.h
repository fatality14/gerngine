#pragma once
#include <common/alist.h>
#include <common/common.h>

class IObject : public ICommon {
public:
    virtual void draw(int flags = 0) = 0;
    virtual ~IObject(){};
};

class IObjectList : public AListO<IObject> {};
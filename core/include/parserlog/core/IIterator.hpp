#pragma once

#include <parserlog/core/export.hpp>

#include <memory>

namespace parserlog {
namespace core {

class IRepeated
{
public:
    using Ptr = std::shared_ptr<IRepeated>;

public:
    virtual void rewind() = 0;
};

class IForward
{
public:
    using Ptr = std::shared_ptr<IForward>;

public:
    virtual bool next() = 0;
};

class IBackward
{
public:
    using Ptr = std::shared_ptr<IBackward>;

public:
    virtual bool prev() = 0;
};

class IForwardNavigator
    :public IForward, public IRepeated
{
public:
    using Ptr = std::shared_ptr<IForwardNavigator>;
};

class IBidirectionalNavigator
    :public IForward, public IBackward, public IRepeated
{
public:
    using Ptr = std::shared_ptr<IBidirectionalNavigator>;
};

template <typename T, typename TNavigator = IForwardNavigator>
class TIterator
    : public TNavigator
{
public:
    using Ptr = std::shared_ptr<TIterator>;

public:
    virtual T current() = 0;
};

}
}
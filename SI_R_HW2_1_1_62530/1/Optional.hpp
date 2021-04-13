#pragma once
// Add whatever else is required to exist in or out the class
// as well as whatever you think is good to be declared too

template <typename T>

class Optional {
private:
    bool isNone = false;
    T item;
public:
    Optional();
    Optional(const T& value);

    bool is_none() const;
    T get_value() const;
}; 
template<typename T>
Optional<T>::Optional():item(T())
{
    isNone = true;
}

template<typename T>
Optional<T>::Optional(const T& value) : item(value){}

template<typename T>
bool Optional<T>::is_none() const
{
    return isNone;
}

template<typename T>
T Optional<T>::get_value() const
{
    return item;
}


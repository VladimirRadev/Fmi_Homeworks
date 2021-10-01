#pragma once

// Add whatever else is required to exist in or out the class
// as well as whatever you think is good to be declared too

#include "Error.hpp"
#include "Optional.hpp"

template<typename T>

class Result {
private:
    Optional<Error>potentialError;
    Optional<T>item;
public:
    Result();
    Result(const T& result);
    Result(const std::string& error_message);

    bool operator==(const T& item);
    bool operator==(const Error& item);
    Optional<T> get_result() const;
    Optional<Error> get_error() const;

};
template<typename T>
Result<T>::Result():potentialError(Optional<Error>()),item(Optional<T>())
{

}

template<typename T>
Result<T>::Result(const T& result): item(Optional<T>(result)) , potentialError(Optional<Error>())
{}


template<typename T>
Result<T>::Result(const std::string& error_message) : item(Optional<T>()) , potentialError(Optional<Error>(error_message))
{}

template<typename T>
bool Result<T>::operator==(const T& item)
{
    if (!this->item.is_none() && this->potentialError.is_none())
    {
        return true;
    }
    else
    {
        return false;
    }
}
template<typename T>
bool Result<T>::operator==(const Error& error)
{
    if (!this->potentialError.is_none())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
Optional<T> Result<T>::get_result() const
{
    return this->item;

}

template<typename T>
Optional<Error> Result<T>::get_error() const
{
    return this->potentialError;
}
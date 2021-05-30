#pragma once
class Comparable
{
public:
	virtual ~Comparable() = default;
	virtual bool operator==(const Comparable*)const = 0;
	virtual bool operator!=(const Comparable*)const = 0;

};
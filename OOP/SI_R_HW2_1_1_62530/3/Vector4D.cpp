#include "Vector4D.hpp"
void Vector4D::initializeVector(const double& v1, const double& v2, const double& v3, const double& v4)
{
	elements.push_back(v1);
	elements.push_back(v2);
	elements.push_back(v3);
	elements.push_back(v4);
}
Vector4D::Vector4D()
{
	initializeVector(0, 0, 0, 0);
}
Vector4D::Vector4D(double v1, double v2, double v3, double v4)
{
	initializeVector(v1, v2, v3, v4);
}
Vector4D::Vector4D(const Vector4D& rhs)
{
	initializeVector(rhs.elements[0], rhs.elements[1], rhs.elements[2], rhs.elements[3]);
}
Vector4D& Vector4D::operator=(const Vector4D& rhs)
{
	if (this != &rhs)
	{
		elements[0] = rhs.elements[0];
		elements[1] = rhs.elements[1];
		elements[2] = rhs.elements[2];
		elements[3] = rhs.elements[3];
	}
	return *this;
}
double& Vector4D::operator[](const int& index)
{
	if (index < 0 || index>3)
	{
		double error = 0;
		return error;
	}
	return elements[index];
}
Vector4D Vector4D::operator+(const Vector4D& rhs)const
{
	return Vector4D(elements[0] + rhs.elements[0],
		elements[1] + rhs.elements[1],
		elements[2] + rhs.elements[2],
		elements[3] + rhs.elements[3]);
}
Vector4D& Vector4D::operator+=(const Vector4D& rhs)
{
	elements[0] += rhs.elements[0];
	elements[1] += rhs.elements[1];
	elements[2] += rhs.elements[2];
	elements[3] += rhs.elements[3];
	return *this;

}
Vector4D Vector4D::operator-(const Vector4D& rhs)const
{
	return Vector4D(elements[0] - rhs.elements[0],
		elements[1] - rhs.elements[1],
		elements[2] - rhs.elements[2],
		elements[3] - rhs.elements[3]);
}
Vector4D& Vector4D::operator-=(const Vector4D& rhs)
{
	elements[0] -= rhs.elements[0];
	elements[1] -= rhs.elements[1];
	elements[2] -= rhs.elements[2];
	elements[3] -= rhs.elements[3];
	return *this;
}
Vector4D Vector4D::operator*(const Vector4D& rhs)const
{
	return Vector4D(elements[0] * rhs.elements[0],
		elements[1] * rhs.elements[1],
		elements[2] * rhs.elements[2],
		elements[3] * rhs.elements[3]);
}
Vector4D Vector4D::operator*(const double& num)const
{
	return Vector4D(elements[0] * num,
		elements[1] * num,
		elements[2] * num,
		elements[3] * num);
}
Vector4D& Vector4D::operator*=(const Vector4D& rhs)
{
	this->elements[0] *= rhs.elements[0];
	this->elements[1] *= rhs.elements[1];
	this->elements[2] *= rhs.elements[2];
	this->elements[3] *= rhs.elements[3];
	return *this;


}
Vector4D& Vector4D::operator*=(const double& num)
{
	this->elements[0] *= num;
	this->elements[1] *= num;
	this->elements[2] *= num;
	this->elements[3] *= num;
	return *this;
}
Vector4D Vector4D::operator/(const Vector4D& rhs)const
{
	return Vector4D(elements[0] / rhs.elements[0],
		elements[1] / rhs.elements[1],
		elements[2] / rhs.elements[2],
		elements[3] / rhs.elements[3]);
}
Vector4D& Vector4D::operator/=(const Vector4D& rhs)
{
	elements[0] /= rhs.elements[0];
	elements[1] /= rhs.elements[1];
	elements[2] /= rhs.elements[2];
	elements[3] /= rhs.elements[3];
	return *this;

}
bool Vector4D::operator==(const Vector4D& rhs)const
{
	return((elements[0] == rhs.elements[0]) &&
		(elements[1] == rhs.elements[1]) &&
		(elements[2] == rhs.elements[2]) &&
		(elements[3] == rhs.elements[3]));

}
bool Vector4D::operator!=(const Vector4D& rhs)const
{
	return!(*this == rhs);
}
bool Vector4D::operator<(const Vector4D& rhs)const
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == rhs.elements[i])
		{
			continue;
		}
		if (elements[i] < rhs.elements[i])
		{
			return true;
		}
		if (elements[i] > rhs.elements[i])
		{
			return false;
		}

	}
	return false;

}
bool Vector4D::operator>(const Vector4D& rhs)const
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == rhs.elements[i])
		{
			continue;
		}
		if (elements[i] < rhs.elements[i])
		{
			return false;
		}
		if (elements[i] > rhs.elements[i])
		{
			return true;
		}

	}
	return false;
}
bool Vector4D::operator<=(const Vector4D& rhs)const
{
	return ((*this < rhs) || (*this == rhs));
}
bool Vector4D::operator>=(const Vector4D& rhs)const
{
	return ((*this > rhs) || (*this == rhs));
}
bool Vector4D::operator!()const
{
	return((elements[0] == 0) &&
		(elements[1] == 0) &&
		(elements[2] == 0) &&
		(elements[3] == 0));

}
Vector4D Vector4D::operator-()const
{
	return Vector4D(-elements[0], -elements[1], -elements[2], -elements[3]);
}
#ifndef POINT_INL_INCLUDED
#define POINT_INL_INCLUDED
#pragma once

#include <corecrt.h>
#include <memory>

namespace NidentalE
{

template <size_t Dimension>
struct Point
{
	Point(const double x, const double y, const double z)
	{
		static_assert(Dimension == 3, "Wrong dimension!");
		coordinates_[0] = x;
		coordinates_[1] = y;
		coordinates_[2] = z;
	}

	Point(const double x, const double y)
	{
		static_assert(Dimension == 2, "Wrong dimension!");
		coordinates_[0] = x;
		coordinates_[1] = y;
	}

	Point()
		: coordinates_()
	{
	}

	double X() const
	{
		return coordinates_[0];
	}

	double Y() const
	{
		return coordinates_[1];
	}

	double Z() const
	{
		static_assert(Dimension == 3, "Wrong dimension!");
		return coordinates_[2];
	}

	double operator[](const size_t index) const
	{
		return coordinates_[index];
	}

	void operator-=(
			const Point& other_point)
	{
		for (size_t index = 0; index < Dimension; ++index)
		{
			coordinates_[index] -= other_point.coordinates_[index];
		}
	}

	friend Point operator-(
			const Point& first_point,
			const Point& second_point)
	{
		Point result(first_point);
		result -= second_point;
		return result;
	}

	bool operator==(
			const Point& other_point) const
	{
		for (size_t index = 0; index < Dimension; ++index)
		{
			if (coordinates_[index] != other_point.coordinates_[index])
			{
				return false;
			}
		}

		return true;
	}

private:
	double coordinates_[Dimension];
};

using Point2D = Point<2>;
using Point3D = Point<3>;
using Vector3D = Point<3>;

} // namespace NidentalE

#endif // POINT_INL_INCLUDED

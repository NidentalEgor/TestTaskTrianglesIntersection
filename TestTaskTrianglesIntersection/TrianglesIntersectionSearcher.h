#ifndef TRIANGLES_INTERSECTION_SEACHER_H_INCLUDED
#define TRIANGLES_INTERSECTION_SEACHER_H_INCLUDED
#pragma once

#include "Point.inl"
#include "Triangle.h"

namespace NidentalE
{

using MinimumElementsIndexes = std::pair<size_t, size_t>;
using ParametersT = std::pair<double, double>;
using ParametersTPtr = std::shared_ptr<ParametersT>;

/*!
* Class that can to determine whether there is a intersection between triangles.
*/
class TrianglesIntersectionSearcher
{
public:
	/*!
	* Default constructor.
	*/
	TrianglesIntersectionSearcher();

	/*!
	* Default destructor.
	*/
	~TrianglesIntersectionSearcher();

	/*!
	* Determines whether there is a intersection between triangles.
	* It is implementation of Tomas Moller's "A Fast Triangle-Triangle Intersection Test" algorithm.
	*
	\param[in] t1 - sequence of coordinates of first triangle {X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3}.
	\param[in] t2 - sequence of coordinates of second triangle {X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3}.
	*
	\return True if triangles have at least one common point, false - otherwise.
	*/
	bool AreTrianglesIntersect(
			double t1[9],
			double t2[9]) const;

private:
	ParametersTPtr CalculateIntervals(
			const double  triangle_first_point_projection,
			const double  triangle_second_point_projection,
			const double triangle_third_point_projection,
			const TriangleDescription& triangle_description) const;
	
	TriangleDescription CalculateDistancesFromTriangleVertexesToPlane(
			const Plane& plane,
			const Triangle& triangle) const;

	double CalculateDistanceFromVertexToPlane(
			const Point3D& point,
			const Vector3D& plane_normal,
			const double plane_coefficient_d) const;

	ParametersT CalculateParametersT(
			const double first_side_point_projection,
			const double second_side_first_point_projection,
			const double second_side_second_point_projection,
			const double first_side_point_distance,
			const double second_side_first_point_distance,
			const double second_side_second_point_distance) const;

	bool AreCoplanarTrianglesIntersect(
			const Triangle& first_triangle,
			const Triangle& second_triangle,
			const Vector3D& plane_normal) const;

	std::pair<size_t, size_t> Find2MinimalElementsIndexes(
			const Vector3D& vector) const;

	bool IsSameSignOfDistances(
			const TriangleDescription& triangle_description) const;
};

} // namespace NidentalE

#endif // TRIANGLES_INTERSECTION_SEACHER_H_INCLUDED

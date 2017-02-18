#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#pragma once

#include "Point.inl"

namespace NidentalE
{

/*!
* Ñalculates vector product.
*
\param[in] first_vector - first vector.
\param[in] second_vector - second vector.
*
\return Vector which is the vector product.
*/
Vector3D CalculateVectorProduct(
		const Vector3D& first_vector,
		const Vector3D& second_vector);

/*!
* Ñalculates dot product.
*
\param[in] first_vector - first vector.
\param[in] second_vector - second vector.
*
\return Vector which is the dot product.
*/
double CalculateDotProduct(
		const Vector3D& first_vector,
		const Vector3D& second_vector);

/*!
* Ñalculates vector.
*
\param[in] begin_point - first point.
\param[in] end_point - second point.
*
\return Vector between points begin_point and end_point.
*/
Point3D CalculateVector(
		const Point3D& begin_point,
		const Point3D& end_point);

/*!
* Ñhecks value for equality to zero.
*
\param[in] value - checking value.
*
\return 0 if value is less than std::numeric_limits<double>::epsilon(), value - otherwise.
*/
double CheckEqualZero(
			const double value);

/*!
* Determines whether there is intersection between two segments.
* It is implementation of Franlin Antonio's "Faster Line Segment Intersection"
* algorithm from David Kirk's book "Graphics Gems III".
*
\param[in] first_segment_first_point - first point of first segment.
\param[in] first_segment_second_point - second point of first segment.
\param[in] second_segment_first_point - first point of second segment.
\param[in] second_segment_second_point - second point of second segment.
*
\return True if segments have at least one common point, false - otherwise.
*/
bool AreSegmentsIntersect(
		const Point2D& first_segment_first_point,
		const Point2D& first_segment_second_point,
		const Point2D& second_segment_first_point,
		const Point2D& second_segment_second_point);

/*!
* Determines whether a point is inside the triangle.
*
\param[in] point - first point of first segment.
\param[in] triangle_first_point - first point of the triangle.
\param[in] triangle_second_point - second point of the triangle.
\param[in] triangle_third_point - third point of the triangle.
*
\return True if point is inside the triangle, false - otherwise.
*/
bool IsPointInsideTriangle(
		const Point2D& point,
		const Point2D& triangle_first_point,
		const Point2D& triangle_second_point,
		const Point2D& triangle_third_point);

} // namespace NidentalE

#endif // UTILITIES_H_INCLUDED

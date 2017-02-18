#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED
#pragma once

#include "Point.inl"

namespace NidentalE
{

struct Triangle
{
	Triangle(
			double coordinates[9])
		: first_point(coordinates[0], coordinates[1], coordinates[2])
		, second_point(coordinates[3], coordinates[4], coordinates[5])
		, third_point(coordinates[6], coordinates[7], coordinates[8])
	{
	}

	Triangle()
		: first_point()
		, second_point()
		, third_point()
	{
	}

	Point3D first_point;
	Point3D second_point;
	Point3D third_point;
};

using Plane = Triangle;

struct TriangleDescription
{
	TriangleDescription(
			const double first_point_to_plane_distance,
			const double second_point_to_plane_distance,
			const double third_point_to_plane_distance,
			const Vector3D& normal)
		: first_point_to_plane_distance(first_point_to_plane_distance)
		, second_point_to_plane_distance(second_point_to_plane_distance)
		, third_point_to_plane_distance(third_point_to_plane_distance)
		, normal(normal)
	{
	}

	double first_point_to_plane_distance;
	double second_point_to_plane_distance;
	double third_point_to_plane_distance;
	Vector3D normal;
};

} // namespace NidentalE

#endif // TRIANGLE_H_INCLUDED

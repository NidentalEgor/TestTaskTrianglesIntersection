#include <array>
#include "Utilities.h"
#include "TrianglesIntersectionSearcher.h"

namespace NidentalE
{

TrianglesIntersectionSearcher::TrianglesIntersectionSearcher()
{
}


TrianglesIntersectionSearcher::~TrianglesIntersectionSearcher()
{
}

bool TrianglesIntersectionSearcher::AreTrianglesIntersect(
		double first_triangle_coordinares[9],
		double second_triangle_coordinares[9]) const
{
	try
	{
		const Triangle first_triangle(first_triangle_coordinares);
		const Triangle second_triangle(second_triangle_coordinares);

		const TriangleDescription first_triangle_description =
				CalculateDistancesFromTriangleVertexesToPlane(first_triangle, second_triangle);

		if (IsSameSignOfDistances(first_triangle_description))
		{
			return false;
		}

		const TriangleDescription second_triangle_description =
				CalculateDistancesFromTriangleVertexesToPlane(second_triangle, first_triangle);
		if (IsSameSignOfDistances(second_triangle_description))
		{
			return false;
		}

		// Algorithm optimization. See "A Fast Triangle-Triangle Intersection Test".
		size_t largest_element_index = 0;
		{
			const Vector3D intersection_line_direction_vector =
				CalculateVectorProduct(
					first_triangle_description.normal,
					second_triangle_description.normal);


			if (std::abs(intersection_line_direction_vector.X()) <
				std::abs(intersection_line_direction_vector.Y()))
			{
				largest_element_index = 1;
			}
			if (std::abs(intersection_line_direction_vector.Y()) <
				std::abs(intersection_line_direction_vector.Z()))
			{
				largest_element_index = 2;
			}
		}

		const double first_triangle_first_point_projection = first_triangle.first_point[largest_element_index];
		const double first_triangle_second_point_projection = first_triangle.second_point[largest_element_index];
		const double first_triangle_third_point_projection = first_triangle.third_point[largest_element_index];

		const double second_triangle_first_point_projection = second_triangle.first_point[largest_element_index];
		const double second_triangle_second_point_projection = second_triangle.second_point[largest_element_index];
		const double second_triangle_third_point_projection = second_triangle.third_point[largest_element_index];

		const ParametersTPtr first_triangle_interval =
				CalculateIntervals(
					first_triangle_first_point_projection,
					first_triangle_second_point_projection,
					first_triangle_third_point_projection,
					second_triangle_description);

		if (!first_triangle_interval)
		{
			return AreCoplanarTrianglesIntersect(
					first_triangle,
					second_triangle,
					first_triangle_description.normal);
		}

		const ParametersTPtr second_triangle_interval =
				CalculateIntervals(
					second_triangle_first_point_projection,
					second_triangle_second_point_projection,
					second_triangle_third_point_projection,
					first_triangle_description);

		if (!second_triangle_interval)
		{
			return AreCoplanarTrianglesIntersect(
					second_triangle,
					first_triangle,
					second_triangle_description.normal);
		}

		if (first_triangle_interval->first > first_triangle_interval->second)
		{
			std::swap(first_triangle_interval->first, first_triangle_interval->second);
		}

		if (second_triangle_interval->first > second_triangle_interval->second)
		{
			std::swap(second_triangle_interval->first, second_triangle_interval->second);
		}

		if (first_triangle_interval->second < second_triangle_interval->first ||
			second_triangle_interval->second < first_triangle_interval->first)
		{
			return false;
		}

		return true;
	}
	catch(...)
	{
		// Catch all possible exceptions.
		return false;
	}
}

TriangleDescription TrianglesIntersectionSearcher::CalculateDistancesFromTriangleVertexesToPlane(
		const Plane& plane,
		const Triangle& triangle) const
{
	Vector3D plane_normal;
	{
		const Vector3D plane_first_vector =
				CalculateVector(
					plane.second_point,
					plane.first_point);
		const Vector3D plane_second_vector =
				CalculateVector(
					plane.third_point,
					plane.first_point);

		plane_normal =
				CalculateVectorProduct(
					plane_first_vector,
					plane_second_vector);
	}

	double triangle_first_point_to_plane_distance = 0.0;
	double triangle_second_point_to_plane_distance = 0.0;
	double triangle_third_point_to_plane_distance = 0.0;
	{
		const double plane_coefficient_d =
				-CalculateDotProduct(plane_normal, plane.first_point);

		triangle_first_point_to_plane_distance =
				CalculateDistanceFromVertexToPlane(
					triangle.first_point,
					plane_normal,
					plane_coefficient_d);

		triangle_second_point_to_plane_distance =
				CalculateDistanceFromVertexToPlane(
					triangle.second_point,
					plane_normal,
					plane_coefficient_d);

		triangle_third_point_to_plane_distance =
				CalculateDistanceFromVertexToPlane(
					triangle.third_point,
					plane_normal,
					plane_coefficient_d);
	}
	return TriangleDescription(
			triangle_first_point_to_plane_distance,
			triangle_second_point_to_plane_distance,
			triangle_third_point_to_plane_distance,
			plane_normal);
}

double TrianglesIntersectionSearcher::CalculateDistanceFromVertexToPlane(
		const Point3D& point,
		const Vector3D& plane_normal,
		const double plane_coefficient_d) const
{
	const double distance =
			CalculateDotProduct(point, plane_normal) +
			plane_coefficient_d;

	return CheckEqualZero(distance);
}

ParametersT TrianglesIntersectionSearcher::CalculateParametersT(
		const double first_side_point_projection,
		const double second_side_first_point_projection,
		const double second_side_second_point_projection,
		const double first_side_point_distance,
		const double second_side_first_point_distance,
		const double second_side_second_point_distance) const
{
	double first_t_parameter;
	{
		const double second_first_projections_difference =
				second_side_first_point_projection -
				first_side_point_projection;
		const double first_second_distances_difference =
				first_side_point_distance -
				second_side_first_point_distance;

		first_t_parameter =
				first_side_point_projection +
				second_first_projections_difference *first_side_point_distance /
				first_second_distances_difference;
	}

	double second_t_parameter;
	{
		const double third_first_projections_difference =
				second_side_second_point_projection -
				first_side_point_projection;
		const double first_third_distances_difference =
				first_side_point_distance -
				second_side_second_point_distance;

		second_t_parameter =
				first_side_point_projection +
				third_first_projections_difference * first_side_point_distance /
				first_third_distances_difference;
	}

	return std::make_pair(
			first_t_parameter,
			second_t_parameter);
}

bool TrianglesIntersectionSearcher::AreCoplanarTrianglesIntersect(
		const Triangle& first_triangle,
		const Triangle& second_triangle,
		const Vector3D& plane_normal) const
{
	// Protection from projections in the form of segments.
	const MinimumElementsIndexes minimum_elements_indexes =
			Find2MinimalElementsIndexes(plane_normal);

	const Point2D first_triangle_first_point_2D
	{
		first_triangle.first_point[minimum_elements_indexes.first],
		first_triangle.first_point[minimum_elements_indexes.second]
	};

	const Point2D first_triangle_second_point_2D
	{
		first_triangle.second_point[minimum_elements_indexes.first],
		first_triangle.second_point[minimum_elements_indexes.second]
	};
	const Point2D first_triangle_third_point_2D
	{
		first_triangle.third_point[minimum_elements_indexes.first],
		first_triangle.third_point[minimum_elements_indexes.second]
	};

	const Point2D second_triangle_first_point_2D
	{
		second_triangle.first_point[minimum_elements_indexes.first],
		second_triangle.first_point[minimum_elements_indexes.second]
	};
	const Point2D second_triangle_second_point_2D
	{
		second_triangle.second_point[minimum_elements_indexes.first],
		second_triangle.second_point[minimum_elements_indexes.second]
	};
	const Point2D second_triangle_third_point_2D
	{
		second_triangle.third_point[minimum_elements_indexes.first],
		second_triangle.third_point[minimum_elements_indexes.second]
	};

	if (AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_second_point_2D,
				second_triangle_first_point_2D,
				second_triangle_second_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_third_point_2D,
				second_triangle_first_point_2D,
				second_triangle_second_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_second_point_2D,
				first_triangle_third_point_2D,
				second_triangle_first_point_2D,
				second_triangle_second_point_2D) ||

		AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_second_point_2D,
				second_triangle_first_point_2D,
				second_triangle_third_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_third_point_2D,
				second_triangle_first_point_2D,
				second_triangle_third_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_second_point_2D,
				first_triangle_third_point_2D,
				second_triangle_first_point_2D,
				second_triangle_third_point_2D) ||

		AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_second_point_2D,
				second_triangle_second_point_2D,
				second_triangle_third_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_first_point_2D,
				first_triangle_third_point_2D,
				second_triangle_second_point_2D,
				second_triangle_third_point_2D) ||
		AreSegmentsIntersect(
				first_triangle_second_point_2D,
				first_triangle_third_point_2D,
				second_triangle_second_point_2D,
				second_triangle_third_point_2D))
	{
		return true;
	}
	else
	{
		return 
			IsPointInsideTriangle(
					first_triangle_first_point_2D,
					second_triangle_first_point_2D,
					second_triangle_second_point_2D,
					second_triangle_third_point_2D) ||

			IsPointInsideTriangle(
					second_triangle_first_point_2D,
					first_triangle_first_point_2D,
					first_triangle_second_point_2D,
					first_triangle_third_point_2D);
	}
}

MinimumElementsIndexes TrianglesIntersectionSearcher::Find2MinimalElementsIndexes(
		const Vector3D& vector) const
{
	using AbsoluteValueToIndex = std::pair<double, size_t>;
	std::array<AbsoluteValueToIndex, 3> absolute_values_to_indexes
	{
		AbsoluteValueToIndex(std::abs(vector.X()), 0),
		AbsoluteValueToIndex(std::abs(vector.Y()), 1),
		AbsoluteValueToIndex(std::abs(vector.Z()), 2)
	};

	std::sort(
			std::begin(absolute_values_to_indexes),
			std::end(absolute_values_to_indexes),
			[](const AbsoluteValueToIndex& left, const AbsoluteValueToIndex& right)
			{
				return left.first < right.first;
			});

	return MinimumElementsIndexes(absolute_values_to_indexes[0].second, absolute_values_to_indexes[1].second);
}

bool TrianglesIntersectionSearcher::IsSameSignOfDistances(
		const TriangleDescription& triangle_description) const
{
	return triangle_description.first_point_to_plane_distance *
			triangle_description.second_point_to_plane_distance > 0.0 &&
			triangle_description.first_point_to_plane_distance *
			triangle_description.third_point_to_plane_distance > 0.0;
}

ParametersTPtr TrianglesIntersectionSearcher::CalculateIntervals(
		const double  triangle_first_point_projection,
		const double  triangle_second_point_projection,
		const double triangle_third_point_projection,
		const TriangleDescription& triangle_description) const
{
	ParametersT parameters;

	if(triangle_description.first_point_to_plane_distance *
		triangle_description.second_point_to_plane_distance >
		std::numeric_limits<double>::epsilon())
	{
		// First and second triangles point are on the same side.
		parameters = CalculateParametersT(
				triangle_third_point_projection,
				triangle_first_point_projection,
				triangle_second_point_projection,
				triangle_description.third_point_to_plane_distance,
				triangle_description.first_point_to_plane_distance,
				triangle_description.second_point_to_plane_distance);
	}
	else if(triangle_description.first_point_to_plane_distance *
			triangle_description.third_point_to_plane_distance >
			std::numeric_limits<double>::epsilon())
	{
		// First and third triangle points are on the same side.
		parameters = CalculateParametersT(
				triangle_second_point_projection,
				triangle_first_point_projection,
				triangle_third_point_projection,
				triangle_description.second_point_to_plane_distance,
				triangle_description.first_point_to_plane_distance,
				triangle_description.third_point_to_plane_distance
		);
	}
	else if(std::abs(triangle_description.first_point_to_plane_distance) >
			std::numeric_limits<double>::epsilon())
	{
		// Second and third triangle points are on the same side.
		parameters = CalculateParametersT(
				triangle_first_point_projection,
				triangle_second_point_projection,
				triangle_third_point_projection,
				triangle_description.first_point_to_plane_distance,
				triangle_description.second_point_to_plane_distance,
				triangle_description.third_point_to_plane_distance);
	}
	else if(std::abs(triangle_description.second_point_to_plane_distance) >
			std::numeric_limits<double>::epsilon())
	{
		parameters = CalculateParametersT(
				triangle_second_point_projection,
				triangle_first_point_projection,
				triangle_third_point_projection,
				triangle_description.second_point_to_plane_distance,
				triangle_description.first_point_to_plane_distance,
				triangle_description.third_point_to_plane_distance);
	}
	else if(std::abs(triangle_description.third_point_to_plane_distance) >
			std::numeric_limits<double>::epsilon())
	{
		parameters = CalculateParametersT(
				triangle_third_point_projection,
				triangle_first_point_projection,
				triangle_second_point_projection,
				triangle_description.third_point_to_plane_distance,
				triangle_description.first_point_to_plane_distance,
				triangle_description.second_point_to_plane_distance);
	}
	else
	{
		// Triangles are on the same plane.
		return nullptr;
	}

	return std::make_shared<ParametersT>(parameters);
}

} // namespace NidentalE
#include <limits>
#include "Point.inl"
#include "Utilities.h"

namespace NidentalE
{

Vector3D CalculateVectorProduct(
		const Vector3D& first_vector,
		const Vector3D& second_vector)
{
	return Vector3D(
			first_vector.Y() * second_vector.Z() - first_vector.Z() * second_vector.Y(),
			first_vector.Z() * second_vector.X() - first_vector.X() * second_vector.Z(),
			first_vector.X() * second_vector.Y() - first_vector.Y() * second_vector.X());
}

double CalculateDotProduct(
		const Vector3D& first_vector,
		const Vector3D& second_vector)
{
	return first_vector.X() * second_vector.X() +
			first_vector.Y() * second_vector.Y() +
			first_vector.Z() * second_vector.Z();
}

Point3D CalculateVector(
		const Point3D& begin_point,
		const Point3D& end_point)
{
	return NidentalE::Point3D(
			end_point.X() - begin_point.X(),
			end_point.Y() - begin_point.Y(),
			end_point.Z() - begin_point.Z());
}

double CheckEqualZero(const double value)
{
	if (std::abs(value) < std::numeric_limits<double>::epsilon())
	{
		return 0.0;
	}
	else
	{
		return value;
	}
}

bool AreSegmentsIntersect(
		const Point2D& first_line_first_point,
		const Point2D& first_line_second_point,
		const Point2D& second_line_first_point,
		const Point2D& second_line_second_point)
{
	const Point2D A(first_line_second_point - first_line_first_point);
	const Point2D B(second_line_first_point - second_line_second_point);
	const Point2D C(first_line_first_point - second_line_first_point);

	const double alpha_beta_denominator = A.Y() * B.X() - A.X() * B.Y();
	const double alpha_numinator = B.Y() * C.X() - B.X() * C.Y();
	if ((alpha_beta_denominator > 0.0 &&
		alpha_numinator >= 0.0 &&
		alpha_numinator <= alpha_beta_denominator)
		||
		(alpha_beta_denominator < 0.0 &&
		alpha_numinator <= 0.0 &&
		alpha_numinator >= alpha_beta_denominator))
	{
		const double beta_numinator = A.X() * C.Y() - A.Y() * C.X();
		if (alpha_beta_denominator > 0.0)
		{
			if (beta_numinator >= 0.0 &&
				beta_numinator <= alpha_beta_denominator)
			{
				return true;
			}
		}
		else
		{
			if (beta_numinator <= 0.0 &&
				beta_numinator >= alpha_beta_denominator)
			{
				return true;
			}
		}
	}

	return false;
}

bool IsPointInsideTriangle(
		const Point2D& point,
		const Point2D& triangle_first_point,
		const Point2D& triangle_second_point,
		const Point2D& triangle_third_point)
{
	double coefficient_a;
	double coefficient_b;
	double coefficient_c;
	double distance_from_first_side;
	double distance_from_second_side;
	double distance_from_third_side;

	coefficient_a = triangle_second_point.Y() - triangle_first_point.Y();
	coefficient_b = -(triangle_second_point.X() - triangle_first_point.X());
	coefficient_c =
			-coefficient_a * triangle_first_point.X() - coefficient_b * triangle_first_point.Y();

	distance_from_first_side =
			coefficient_a * point.X() + coefficient_b * point.Y() + coefficient_c;

	coefficient_a = triangle_third_point.Y() - triangle_second_point.Y();
	coefficient_b = -(triangle_third_point.X() - triangle_second_point.X());
	coefficient_c =
			-coefficient_a * triangle_second_point.X() - coefficient_b * triangle_second_point.Y();

	distance_from_second_side =
			coefficient_a * point.X() + coefficient_b * point.Y() + coefficient_c;

	coefficient_a = triangle_first_point.Y() - triangle_third_point.Y();
	coefficient_b = -(triangle_first_point.X() - triangle_third_point.X());
	coefficient_c =
			-coefficient_a * triangle_third_point.X() - coefficient_b * triangle_third_point.Y();

	distance_from_third_side =
			coefficient_a * point.X() + coefficient_b * point.Y() + coefficient_c;

	if (distance_from_first_side * distance_from_second_side > std::numeric_limits<double>::epsilon())
	{
		if (distance_from_first_side * distance_from_third_side > std::numeric_limits<double>::epsilon())
		{
			return true;
		}
	}

	return false;
}

} // namespace NidentalE

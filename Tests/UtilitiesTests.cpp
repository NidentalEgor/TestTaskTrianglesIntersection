#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TestTaskTrianglesIntersection/Utilities.h"
#include "../TestTaskTrianglesIntersection/Utilities.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(UtilitiesTests)
	{
	public:

		TEST_METHOD(VectorProductNotZeroResultTest)
		{
			const NidentalE::Vector3D first_vector(1, 2, 3);
			const NidentalE::Vector3D second_vector(3, 2, 1);

			const NidentalE::Vector3D expected_result(-4, 8, -4);

			const NidentalE::Vector3D vector_product = NidentalE::CalculateVectorProduct(
					first_vector,
					second_vector);

			Assert::AreEqual(
					true,
					expected_result == vector_product,
					L"CalculateVectorProduct return wrong result!");
		}

		TEST_METHOD(VectorProductZeroResultTest)
		{
			const NidentalE::Vector3D first_vector(1, 2, 3);
			const NidentalE::Vector3D second_vector(-2, -4, -6);

			const NidentalE::Vector3D expected_result(0, 0, 0);

			const NidentalE::Vector3D vector_product = NidentalE::CalculateVectorProduct(
					first_vector,
					second_vector);

			Assert::AreEqual(
					true,
					expected_result == vector_product,
					L"CalculateVectorProduct return wrong result!");
		}

		TEST_METHOD(DotProductNotZeroResultTest)
		{
			const NidentalE::Vector3D first_vector(1, 1, 3);
			const NidentalE::Vector3D second_vector(0, 1, 4);

			const double expected_result = 13;

			const double dot_product = NidentalE::CalculateDotProduct(
					first_vector,
					second_vector);

			Assert::AreEqual(
					true,
					dot_product == expected_result,
					L"CalculateDotProduct return wrong result!");
		}

		TEST_METHOD(DotProductZeroResultTest)
		{
			const NidentalE::Vector3D first_vector(1, 0, 0);
			const NidentalE::Vector3D second_vector(0, 1 , 0);

			const double expected_result = 0;

			const double dot_product = NidentalE::CalculateDotProduct(
					first_vector,
					second_vector);

			Assert::AreEqual(
					true,
					dot_product == expected_result,
					L"CalculateDotProduct return wrong result!");
		}

		TEST_METHOD(CalculateVectorTest)
		{
			const NidentalE::Point3D begin_point(1, 2, 3);
			const NidentalE::Point3D end_point(3, 2, 1);

			const NidentalE::Vector3D expected_result(2, 0, -2);

			const NidentalE::Point3D vector = NidentalE::CalculateVector(
					begin_point, 
					end_point);

			Assert::AreEqual(
					true,
					vector == expected_result,
					L"CalculateVector return wrong result!");
		}

		TEST_METHOD(CheckEqualZeroValueIsZeroTest)
		{
			const double expected_result = 0;

			const double result = NidentalE::CheckEqualZero(
					std::numeric_limits<double>::epsilon()/2);

			Assert::AreEqual(
					true,
					result == expected_result,
					L"CheckEqualZero return wrong result!");
		}

		TEST_METHOD(CheckEqualZeroValueIsNotZeroTest)
		{
			const double expected_result = 2;

			const double result = NidentalE::CheckEqualZero(2);

			Assert::AreEqual(
					true,
					result == expected_result,
					L"CheckEqualZero return wrong result!");
		}

		TEST_METHOD(AreSegmentsIntersectSegmentsIntersectInMiddleTest)
		{
			const NidentalE::Point2D first_segment_first_point(0, 3);
			const NidentalE::Point2D first_segment_second_point(3, 0);
			const NidentalE::Point2D second_segment_first_point(0, 0);
			const NidentalE::Point2D second_segment_second_point(3, 3);

			const bool expected_result = true;

			const bool result = NidentalE::AreSegmentsIntersect(
					first_segment_first_point,
					first_segment_second_point,
					second_segment_first_point,
					second_segment_second_point);

			Assert::AreEqual(
					expected_result,
					result,
					L"AreSegmentsIntersect return wrong result!");
		}

		TEST_METHOD(AreSegmentsIntersectSegmentsIntersectByOnePointTest)
		{
			const NidentalE::Point2D first_segment_first_point(0, 3);
			const NidentalE::Point2D first_segment_second_point(3, 0);
			const NidentalE::Point2D second_segment_first_point(3, 0);
			const NidentalE::Point2D second_segment_second_point(3, 3);

			const bool expected_result = true;

			const bool result = NidentalE::AreSegmentsIntersect(
					first_segment_first_point,
					first_segment_second_point,
					second_segment_first_point,
					second_segment_second_point);

			Assert::AreEqual(
					expected_result,
					result,
					L"AreSegmentsIntersect return wrong result!");
		}

		TEST_METHOD(IsPointInsideTrianglePointInsideTriangleTest)
		{
			const NidentalE::Point2D triangle_first_point(0, 3);
			const NidentalE::Point2D triangle_second_point(3, 0);
			const NidentalE::Point2D triangle_third_point(3, 3);
			const NidentalE::Point2D point(2, 2);

			const bool expected_result = true;

			const bool result = NidentalE::IsPointInsideTriangle(
					point,
					triangle_first_point,
					triangle_second_point,
					triangle_third_point);

			Assert::AreEqual(
					expected_result,
					result,
					L"AreSegmentsIntersect return wrong result!");
		}

		TEST_METHOD(IsPointInsideTrianglePointOutsideTriangleTest)
		{
			const NidentalE::Point2D triangle_first_point(0, 3);
			const NidentalE::Point2D triangle_second_point(3, 0);
			const NidentalE::Point2D triangle_third_point(3, 3);
			const NidentalE::Point2D point(1, 1);

			const bool expected_result = false;

			const bool result = NidentalE::IsPointInsideTriangle(
					point,
					triangle_first_point,
					triangle_second_point,
					triangle_third_point);

			Assert::AreEqual(
					expected_result,
					result,
					L"AreSegmentsIntersect return wrong result!");
		}
	};
}
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TestTaskTrianglesIntersection/TrianglesIntersectionSearcher.h"
#include "../TestTaskTrianglesIntersection/TrianglesIntersectionSearcher.cpp"
#include <array>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(TrianglesIntersectionSearcherTests)
	{
	public:

		enum class ExpectedResult
		{
			TrianglesNotIntersect = 0,
			TrianglesIntersect = 1
		};

		std::array<double, 9> TriangleEdgesConfiguration(
				const NidentalE::Triangle& triangle,	
				const size_t configuration_index)
		{
			if (configuration_index == 0)
			{
				return std::array<double, 9>
				{
					triangle.first_point.X(),
					triangle.first_point.Y(),
					triangle.first_point.Z(),
					triangle.second_point.X(),
					triangle.second_point.Y(),
					triangle.second_point.Z(),
					triangle.third_point.X(),
					triangle.third_point.Y(),
					triangle.third_point.Z()
				};
			}
			else if (configuration_index == 1)
			{
				return std::array<double, 9>
				{
					triangle.second_point.X(),
					triangle.second_point.Y(),
					triangle.second_point.Z(),
					triangle.third_point.X(),
					triangle.third_point.Y(),
					triangle.third_point.Z(),
					triangle.first_point.X(),
					triangle.first_point.Y(),
					triangle.first_point.Z()
				};
			}
			else
			{
				return std::array<double, 9>
				{
					triangle.third_point.X(),
					triangle.third_point.Y(),
					triangle.third_point.Z(),
					triangle.first_point.X(),
					triangle.first_point.Y(),
					triangle.first_point.Z(),
					triangle.second_point.X(),
					triangle.second_point.Y(),
					triangle.second_point.Z()
				};
			}
		}

		void AreTrianglesIntersect(
				const NidentalE::Triangle first_triangle,
				const NidentalE::Triangle second_triangle,
				const bool expected_result)
		{
			const NidentalE::TrianglesIntersectionSearcher triangles_intersection_searcher;

			for (size_t first_index = 0; first_index < 3; ++first_index)
			{
				for (size_t second_index = 0; second_index < 3; ++second_index)
				{
					const bool are_triangles_intersect =
							triangles_intersection_searcher.AreTrianglesIntersect(
								TriangleEdgesConfiguration(first_triangle, first_index).data(),
								TriangleEdgesConfiguration(second_triangle, second_index).data());

					std::string error_message("Error! New version test failed! First triangle configuration index = ");
					{
						error_message += std::to_string(first_index);
						error_message += ". First triangle configuration index = ";
						error_message += std::to_string(second_index);
						error_message += ".";
					}

					const std::wstring error_message_native(
							error_message.begin(),
							error_message.end());

					Assert::AreEqual(
							are_triangles_intersect,
							expected_result,
							error_message_native.c_str());
				}
			}

			
		}

		TEST_METHOD(TrianglesOnParallelPlanesTest)
		{
			// Треугольники расположены на параллельных плоскостях.
			double first_triangle[9]{ 1,1,1,3,1,1,3,3,1 };
			double second_triangle[9]{ 1,1,2,3,1,2,3,3,2 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					false);
		}

		TEST_METHOD(TrianglesIntersectByCommonLineTest)
		{
			// Треугольники пересекаются по общей стороне.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 0,0,0,3,0,0,0,3,2 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(TrianglesIntersectByPointTest)
		{
			// Треугольники имеют 1 общую точку.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 0,0,0,3,0,2,0,3,2 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(FirstTriangleContainsSecondTriangleTest)
		{
			// Треугольники вложены.
			double first_triangle[9]{ 0,0,0,5,0,0,0,5,0 };
			double second_triangle[9]{ 1,1,0,3,1,0,1,3,0 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(TrianglesIntersectOnOnePlaneTest)
		{
			// Треугольники расположены на одной плоскости и пересекаются.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 1,1,0,3,1,0,1,3,0 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(FirstTriangleIsLineIntersectSecondTriangleTest)
		{
			// Один из треугольников вырожден в прямую, пересекающую первый треугольник.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 1,1,-1,1,1,0,1,1,1 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(SecondTriangleIsPointInsideFirstTriangleTest)
		{
			// Один из треугольников вырожден в точку, лежащую в первом треугольнике.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 1,1,0,1,1,0,1,1,0 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(EpsilonTest)
		{
			// Треугольники не пересекаются по общей стороне из-за минимального
			// отличия в координатах.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 
					0,0,0 + std::numeric_limits<double>::epsilon(),
					3,0,0 + std::numeric_limits<double>::epsilon(),
					0,3,2 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					false);
		}

		TEST_METHOD(TrianglesIntersectInOnePointOnTheSidesTest)
		{
			// Общая точка лежит на одной из сторон каждого треугольника.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 0,1,-1,-3,1,-1,0,1,4 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}

		TEST_METHOD(TrianglesIntersectInOnePointOnTheSideInTheVertexTest)
		{
			// Общая точка лежит на одной из сторон одного треугольника и
			// является вершиной второго.
			double first_triangle[9]{ 0,0,0,3,0,0,0,3,0 };
			double second_triangle[9]{ 0,1,0,-3,1,-1,0,1,4 };

			AreTrianglesIntersect(
					first_triangle,
					second_triangle,
					true);
		}
	};
}
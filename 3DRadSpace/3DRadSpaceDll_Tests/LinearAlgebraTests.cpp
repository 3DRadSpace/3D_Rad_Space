#include "pch.h"
#include "Matrix.hpp"

namespace LinearAlgebraTests
{
	TEST(VectorCrossProduct, VectorTests)
	{
		Engine3DRadSpace::Vector3 a = Engine3DRadSpace::Vector3::UnitX();
		Engine3DRadSpace::Vector3 b = Engine3DRadSpace::Vector3::UnitY();

		Engine3DRadSpace::Vector3 a_b = a.Cross(b);

		EXPECT_EQ(a_b, Engine3DRadSpace::Vector3::UnitZ());
	}

	TEST(MatrixScalar, MatrixTests)
	{
		Engine3DRadSpace::Matrix identity;
		identity *= 5;

		Engine3DRadSpace::Matrix expected_matrix(
			5, 0, 0, 0,
			0, 5, 0, 0,
			0, 0, 5, 0,
			0, 0, 0, 5
		);

		EXPECT_EQ(identity, expected_matrix);
	}

	TEST(LinearTransformation, MatrixTests)
	{
		Engine3DRadSpace::Matrix m = Engine3DRadSpace::Matrix::CreateScale(5);
		m *= Engine3DRadSpace::Matrix::CreateRotationY((float)(std::numbers::pi / 2));
		m *= Engine3DRadSpace::Matrix::CreateTranslation({ 1,2,3 });

		Engine3DRadSpace::Matrix expected_matrix(
			-2.18556949e-07f, 0.f, -5.f, 0.f,
			0.f, 5.f, 0.f, 0.f,
			5.f, 0.f, -2.18556949e-07f, 0.f,
			1.f, 2.f, 3.f, 1.f
		);

		EXPECT_EQ(m, expected_matrix);
	}
}
#pragma once

namespace nc
{
	class Random
	{
	public:

		static void seedRandom(unsigned int seed)
		{
			std::srand(seed);
		}

		static float random01()
		{
			return std::rand() / float(RAND_MAX);
		}

		static float random(float min, float max)
		{
			if (min > max) std::swap(min, max);

			return min + (max - min) * random01();
		}
	};
}
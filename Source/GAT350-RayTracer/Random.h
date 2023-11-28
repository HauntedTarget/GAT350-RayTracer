#pragma once

namespace nc
{
	class Random
	{
	public:

		void seedRandom(unsigned int seed)
		{
			srand(seed);
		}

		float random01()
		{
			return rand() / float(RAND_MAX);
		}

		float random(float min, float max)
		{
			if (min > max) swap(min, max);

			return rand() / max + min;
		}
	};
}
#pragma once

#include <cstdint>
#include <array>
#include <functional>
#include "eFloatingPointKind.h"

namespace ipgdlib
{
	namespace processor
	{


		template <
			eFloatingPointKind fpkPartition,
			eFloatingPointKind fpkSignal,
			uint8_t nPartition
		>
		struct COscSplitter
		{
			using TSignal		= TFPKind<fpkSignal>;
			using TThreshold	= TFPKind<fpkPartition>;

			COscSplitter(
				std::array<std::function<TSignal(TSignal)>, nPartition> kernels
			) :
				m_Kernels(kernels),m_Thresholds(nPartition - 1)
			{
				for (size_t li = 0; li < nPartition - 1; li++)
					this->m_Thresholds[li] = (li + 1) / (TThreshold)nPartition;

				for (uint8_t li = 0; li < nPartition; li++)
					if (m_Kernels[li] == nullptr)
						throw std::invalid_argument("Function must not be null");
			}

			COscSplitter(
				std::array<std::function<TSignal(TSignal)>, nPartition> kernels,
				std::array<TThreshold, nPartition - 1> thresholds
			) : 
				m_Kernels(kernels),m_Thresholds(thresholds)
			{
				if (m_Thresholds[nPartition - 2] >= 1)
					throw std::invalid_argument("Max Threshold should less then 1");

				for (uint8_t li = 1; li < nPartition - 1; li++)
				{
					if (m_Thresholds[li - 1] > m_Thresholds[li])
						throw std::invalid_argument("Threshold must be in ascending order");
				}

				for (uint8_t li = 0; li < nPartition; li++)
					if (m_Kernels[li] == nullptr)
						throw std::invalid_argument("Function must not be null");
			}

			TSignal operator()(TSignal x)
			{

				if (x < this->m_Thresholds[0])
				{
					return this->m_Kernels[0](x / this->m_Thresholds[0]);
				}
				else
					if (x >= this->m_Thresholds[nPartition - 2])
					{
						return this->m_Kernels[nPartition - 1](
							(x - this->m_Thresholds[nPartition - 2]) /
								(1 - this->m_Thresholds[nPartition - 2])
						);
					}
					else
					{
						for (uint8_t li = 1; li < nPartition - 1; li++)
						{
							if (
								x >= this->m_Thresholds[li - 1] &&
								x < this->m_Thresholds[li])
							{
								return this->m_Kernels[li](
									(x - this->m_Thresholds[li - 1]) /
									(this->m_Thresholds[li] - this->m_Thresholds[li - 1])
								);
							}
						}
					}

			}

		private:
			std::array<std::function<TSignal(TSignal)>,nPartition>	m_Kernels;
			std::array<TThreshold, nPartition - 1>						m_Thresholds;

		};
	}
}

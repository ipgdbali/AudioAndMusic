#pragma once

#include "eFloatingPointKind.h"
#include <cmath>
#include <functional>

namespace ipgdlib
{
	namespace function
	{

		template <eFloatingPointKind fpKind>
		struct CRemapRange
		{
			using float_type = TFPKind<fpKind>;

			CRemapRange(
				float_type targetFrom,
				float_type targetTo,
				float_type sourceFrom,
				float_type sourceTo) :
				m_TargetFrom(targetFrom),m_TargetTo(m_TargetTo),
				m_SourceFrom(sourceFrom),m_SourceTo(sourceTo)
			{
			}

			float_type operator()(float_type x) const noexcept
			{
				return ((x - this->m_SourceFrom) / this->getDeltaSouce()) * this->getDeltaTarget() + this->m_SourceFrom;
			}

			float_type getDeltaSouce() const noexcept
			{
				return this->m_SourceTo - this->m_SourceFrom;
			}

			float_type getDeltaTarget() const noexcept
			{
				return this->m_TargetTo - this->m_TargetFrom;
			}

		private:
			float_type m_TargetFrom;
			float_type m_TargetTo;
			float_type m_SourceFrom;
			float_type m_SourceTo;

		};

		template <typename T>
		T fnNegate(T x)
		{
			return -x;
		}

		template <typename T>
		T fnLinear(T x)
		{
			return x;
		}

		template <eFloatingPointKind fpKind>
		struct CPower
		{
			using float_type = TFPKind<fpKind>;

			CPower(float_type exponent) :
				m_Exponent(exponent)
			{
			}

			float_type operator()(float_type x) const noexcept
			{
				return std::pow(x, this->m_Exponent);
			}

			float_type getExponent() const noexcept
			{
				return this->m_Exponent;
			}

			void setExponent(float_type exponent) noexcept
			{
				this->m_Exponent = exponent;
			}

		private:
			float_type m_Exponent;
		};

		template <eFloatingPointKind fpKind>
		CPower<fpKind> fnPower(TFPKind<fpKind> exponent)
		{
			return { exponent };
		}

		template <eFloatingPointKind fpKind>
		struct CExponent
		{
			using float_type = TFPKind<fpKind>;

			CExponent(float_type base) :
				m_Base(base)
			{
			}

			float_type operator()(float_type x) const noexcept
			{
				return std::pow(this->m_Base,x);
			}

			float_type getBase() const noexcept
			{
				return this->m_Base;
			}

			void setBase(float_type base) noexcept
			{
				this->m_Base = base;
			}

		private:
			float_type m_Base;
		};

		template <eFloatingPointKind fpKind>
		CExponent<fpKind> fnExponent(TFPKind<fpKind> base)
		{
			return { base };
		}

		template <eFloatingPointKind fpKind>
		TFPKind<fpKind> s2n(TFPKind<fpKind> x)
		{
			return (x + 1.0) / 2.0;
		}

		template <eFloatingPointKind fpKind>
		TFPKind<fpKind> n2s(TFPKind<fpKind> x)
		{
			return x * 2 - 1;
		}


		template <
			eFloatingPointKind fpKind,
			size_t nThreshold
		>
		struct CFuncSplitter
		{
			using float_type = TFPKind<fpKind>;

			CFuncSplitter(std::array<std::function<float_type(float_type)>,nThreshold + 1> funcs) :
				m_Functions(std::move(funcs))
			{
				for (size_t li = 0; li < nThreshold; li++)
					this->m_Threshold[li] = (li + 1) / (nThreshold + 1);
			}

			CFuncSplitter(
				std::array<std::function<float_type(float_type)>, nThreshold + 1> funcs,
				std::array<float_type,nThreshold> thresholds
			) :
				m_Threshold(std::move(thresholds))
			{
			}

			constexpr size_t getThresholdCount() const noexcept
			{
				return nThreshold;
			}

			constexpr size_t getRangeCount() const noexcept
			{
				return nThreshold + 1;
			}

			float_type getRangeStart(size_t iRange) const
			{
				if (iRange == 0)
					return 0;
				else
				{
					return this->m_Threshold[iRange - 1];
				}
			}

			float_type getRangeEnd(size_t iRange) const
			{
				if (iRange == nThreshold)
					return 1;
				else
					return this->m_Threshold[iRange];
			}

			float_type getRangeDelta(size_t iRange) const
			{
				return this->getRangeEnd(iRange) - this->getRangeStart(iRange);
			}

			size_t getRangeIndex(float_type x) const 
			{
				for (size_t li = 0; li < this->getRangeCount(); li++)
					if (this->getRangeStart(li) <= x && x < this->getRangeEnd)
						return li;
			}

			float_type operator () (float_type x)
			{
				size_t range_index = this->getRangeIndex(x);
				return 
					this->getRangeStart(range_index) +
					this->m_Functions[range_index](
						(x - this->getRangeStart(range_index)) / this->getRangeDelta(range_index)
					) * 
					this->getRangeDelta(range_index);
			}

		private:
			std::array<float_type, nThreshold> m_Threshold;
			std::array<std::function<float_type(float_type)>, nThreshold + 1> m_Functions;
		};
	}
}

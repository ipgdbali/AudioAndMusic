#pragma once

#include "IGenerator.h"
#include "eFloatingPointKind.h"

namespace ipgdlib
{
	namespace generator
	{

		template<eFloatingPointKind kind>
		struct CGenFrequency :
			public CAbsGenerator<TFPKind<kind>>
		{
			using type = TFPKind<kind>;

			CGenSinosoid(type freq, size_t sampleRate) :
				m_Freq(0),m_SampleRate(sampleRate)
			{
				this->setFreq(freq);
			}

			size_t getSampleRate() const noexcept
			{
				return this->m_SampleRate;
			}

			type getFreq() const noexcept
			{
				return this->m_Freq;
			}

			void setFrequency(type freq)
			{
				this->m_Freq = freq;
				this->m_PhaseIncrement = this->m_Freq / this->m_SampleRate;
			}

			void reset() noexcept final
			{
				this->m_bFirstTime = true;
				this->m_Phase = 0.0;
			}

			type get() const noexcept final
			{
				this->next();
				return m_Phase;
			}

		private:
			void next()
			{
				if (this->m_bFirstTime)
				{
					this->m_bFirstTime = !this->m_bFirstTime;
				}
				else
				{
					this->m_Phase += this->m_PhaseIncrement;
					if (this->m_Phase < 2)
						this->m_Phase -= 1.0;
					else
						this->m_Phase = modf(this->m_Phase, nullptr);
				}
			}

			bool m_bFirstTime;
			type m_Phase;
			type m_PhaseIncrement;
			type m_Freq;
			size_t m_SampleRate;
		};

	}
}
#pragma once

#include "CAbsOperator.h"
#include "eFloatingPointKind.h"
#include "CGenNotes.h"
#include <functional>

namespace ipgdlib
{
	namespace processor
	{

		template <typename TLength, typename TLevel>
		struct ADSR
		{
			TLength tmAttack;
			TLength tmDecay;
			TLevel lvlSustain;
			TLength tmRelease;
		};

		/// <summary>
		/// Input : Signal Gate (on/off) (check CGenNotes)
		/// Output : Amp Level intensity from 0 to.1;
		/// </summary>
		template <eFloatingPointKind fpKind>
		struct CEnvelope :
			public CAbsOperator<TFPKind<fpKind>>
		{
			using float_type = TFPKind<fpKind>;
			
			CEnvelope(
				ADSR<size_t,float_type> adsr,
				std::array<std::function<float_type(float_type)>, 3> funcs, // attack,decay,release
				pointer_deleter<IOperatorT<eGateKind>> opGate
			) :
				m_Funcs(std::move(funcs)),
				m_ADSR(std::move(adsr)),
				CAbsOperator<float_type>({ opGate.as<IOperator>() })
			{
				this->reset();
			}

			CEnvelope(
				ADSR<size_t, float_type> adsr,
				pointer_deleter<IOperatorT<eGateKind>> opGate
			) : CEnvelope<fpKind>(
				std::move(adsr),
				{
					[](float_type x) { return x; },
					[](float_type x) { return x; },
					[](float_type x) { return x; }
				},
				std::move(opGate)
			)
			{
			}

			void reset() noexcept final
			{
				CAbsOperator<TFPKind<fpKind>>::reset();
				this->m_Ticks = 0;
				this->m_CurrState = eEnvelopeState::OFF;
			}

			float_type get() noexcept final
			{

				float_type ret;
				eGateKind gk = this->getOperand(0).as<eGateKind>().get();
				
				switch (this->m_CurrState)
				{
					case eEnvelopeState::OFF :
					{
						// Gate Input
						switch (gk)
						{
							case egkOff: break;
							case egkOn: {

								if (this->m_ADSR.tmAttack > 0)
								{
									this->m_CurrState = eEnvelopeState::ATTACK;
									
									//start from 1 to not delay 1 sample
									this->m_Ticks = 1;
								}
								else
									if (this->m_ADSR.tmDecay > 0)
									{
										this->m_CurrState = eEnvelopeState::DECAY;
										this->m_Ticks = 0;
									}
									else
									{
										this->m_CurrState = eEnvelopeState::SUSTAIN;
										this->m_Ticks = 0;
									}
							}break;
							case egkChangeFreq: break;
						}
					}break;

					case eEnvelopeState::ATTACK:
						{
							switch (gk)
							{
								case egkOn:
								{

									if (this->m_Ticks == this->m_ADSR.tmAttack + 1) // because start from 1
									{
										this->m_Ticks = 0;
										this->m_CurrState = eEnvelopeState::DECAY;
									}

								}break;

								case egkOff:
								{
									// change to release
									m_ReleaseStartLevel = this->m_Ticks / ((float_type)this->m_ADSR.tmAttack + 1);
									this->m_Ticks = 0;
									this->m_CurrState = eEnvelopeState::RELEASE;
								}break;

								case egkChangeFreq:
								{
									this->m_Ticks = 0;
								}break;
							}

						}break;

					case eEnvelopeState::DECAY :
					{
						switch (gk)
						{
							case egkOff: {
								m_ReleaseStartLevel = 1 - (1 - this->m_ADSR.lvlSustain) * (this->m_Ticks / this->m_ADSR.tmDecay);
								this->m_Ticks = 0;
								this->m_CurrState = eEnvelopeState::RELEASE;
							}break;

							case egkOn: {
								if (this->m_Ticks == this->m_ADSR.tmDecay)
								{
									this->m_Ticks = 0;
									this->m_CurrState = eEnvelopeState::SUSTAIN;
								}
							}break;

							case egkChangeFreq: 
							{
								this->m_Ticks = 0;
								this->m_CurrState = eEnvelopeState::ATTACK;
							}break;
						}
					}break;

					case eEnvelopeState::SUSTAIN:
					{
						switch (gk)
						{
							case egkOff: {
								this->m_Ticks = 0;
								this->m_CurrState = eEnvelopeState::RELEASE;
								this->m_ReleaseStartLevel = this->m_ADSR.lvlSustain;
							}break;

							case egkOn: {
							}break;

							case egkChangeFreq: {
								this->m_Ticks = 1;
								this->m_CurrState = eEnvelopeState::ATTACK;
							}break;
						}
					}break;

					case eEnvelopeState::RELEASE: 
					{
						switch (gk)
						{
							case egkOff:
								if (this->m_Ticks == this->m_ADSR.tmRelease)
								{
									this->m_Ticks = 0;
									this->m_CurrState = eEnvelopeState::OFF;
								}
								break;

							case egkOn: {
								this->m_Ticks = 0;
								this->m_CurrState = eEnvelopeState::ATTACK;
							}	break;

							case egkChangeFreq: 
								break; // undefined
						}
					}break;
				}

				// process
				switch (this->m_CurrState)
				{
					case eEnvelopeState::OFF:	
						ret = 0.0;
						break;

					case eEnvelopeState::ATTACK:
						ret = this->m_Funcs[0]((float_type)this->m_Ticks / (this->m_ADSR.tmAttack + 1.0));
						break;

					case eEnvelopeState::DECAY:		
						ret = 1.0  - (1.0 - this->m_ADSR.lvlSustain) * this->m_Funcs[1]((float_type)this->m_Ticks / this->m_ADSR.tmDecay);
						break;

					case eEnvelopeState::SUSTAIN:	
						ret = this->m_ADSR.lvlSustain;
						break;

					case eEnvelopeState::RELEASE:	
						ret = this->m_ReleaseStartLevel * (1 - this->m_Funcs[2]((float_type)this->m_Ticks / this->m_ADSR.tmRelease));
						break;
				}

				this->m_Ticks++;

				return ret;
			}

			const ADSR<size_t,float_type>& getADSR() const noexcept
			{
				return this->m_ADSR;
			}

		protected:
			enum class eEnvelopeState : uint8_t { OFF, ATTACK, DECAY, SUSTAIN, RELEASE };

		private:
			ADSR<size_t,float_type>									m_ADSR;
			std::array<std::function<float_type(float_type)>, 3 >	m_Funcs;

			size_t													m_Ticks;
			eEnvelopeState											m_CurrState;

			float_type												m_ReleaseStartLevel;
		};

	}

}

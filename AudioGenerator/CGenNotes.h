#pragma once

#include "CAbsProducer.h"
#include "CAbsProducerVector.h"
#include "eFloatingPointKind.h"
#include "audio.h"

using ipgdlib::audio::CNotes;

namespace ipgdlib
{
    namespace processor
    {

        enum eGateKind : uint8_t { egkOff, egkOn, egkChangeFreq };

        template <eFloatingPointKind fpk = efpk64Bit>
        struct CGenNotes :
            public CAbsProducerVector
        {
            using float_type = TFPKind<fpk>;

            ~CGenNotes()
            {
            }

            CGenNotes(size_t sampleRate,float_type tempo,CNotes notes) :
                CAbsProducerVector({
                    new COperatorProducerT<float_type>(this,this->m_CurrFreq),
                    new COperatorProducerT<eGateKind>(this,this->m_CurrGate)
                }),
                m_SampleRate(sampleRate),
                m_Tempo(tempo),
                m_Notes(std::move(notes)),
                m_SamplePerBeat(60 * sampleRate / tempo)
            {
                this->reset();
            }

            IOperatorT<float_type> &getOpNoteFreq() noexcept
            {
                return *dynamic_cast<COperatorProducerT<float_type>*>(&this->getOperator(0));
            }

            IOperatorT<eGateKind> &getOpNoteGate() noexcept
            {
                return *dynamic_cast<COperatorProducerT<eGateKind>*>(&this->getOperator(1));
            }

        protected:

            enum eNoteState : bool { ensRest, ensNote};

            void reset() override
            {
                this->m_CurrNoteIndex = 0;
                this->m_CurrNote = this->m_Notes.getNote(0);

                this->m_CurrStatePosition = 0;
                if (m_CurrNote.isRestZero())
                {
                    this->m_CurrState = ensNote;
                    this->m_CurrStateLength = this->m_SamplePerBeat *
                        this->m_CurrNote.length.mul / this->m_CurrNote.length.div;
                    this->m_CurrFreq = audio::freqMap[this->m_CurrNote.note];
                    this->m_CurrGate = egkOn;
                }
                else
                {
                    this->m_CurrState = ensRest;
                    this->m_CurrStateLength = this->m_SamplePerBeat *
                        this->m_CurrNote.prev.mul / this->m_CurrNote.prev.div;
                    this->m_CurrFreq = 0;
                    this->m_CurrGate = egkOff;
                }

                this->m_CurrStatePosition = 0;
                this->m_bFinished = false;
            }

            /// <summary>
            /// Called automatically after all operator has been called.
            /// </summary>
            void next() override
            {
                if (!this->m_bFinished)
                {

                    if (this->m_CurrGate == egkChangeFreq)
                        this->m_CurrGate = egkOn;

                    this->m_CurrStatePosition++;
                    if (this->m_CurrStatePosition == this->m_CurrStateLength)
                    {
                        // change state
                        if (this->m_CurrState == ensRest)
                        {
                            this->m_CurrState = ensNote;
                            this->m_CurrStateLength = this->m_SamplePerBeat *
                                this->m_CurrNote.length.mul / this->m_CurrNote.length.div;

                            this->m_CurrFreq = audio::freqMap[this->m_CurrNote.note];
                            this->m_CurrGate = egkOn;
                        }
                        else
                        {
                            // this->m_CurrState == ensNote

                            // find next note
                            if (this->m_CurrNoteIndex < this->m_Notes.getNoteCount() - 1)
                            {

                                this->m_CurrNoteIndex++;
                                this->m_CurrNote = this->m_Notes.getNote(this->m_CurrNoteIndex);

                                if (this->m_CurrNote.isRestZero())
                                {
                                    // if no previos rest
                                    // jump to note
                                    this->m_CurrState = ensNote;
                                    this->m_CurrStateLength = this->m_SamplePerBeat *
                                        this->m_CurrNote.length.mul / this->m_CurrNote.length.div;
                                    this->m_CurrFreq = audio::freqMap[this->m_CurrNote.note];
                                    this->m_CurrGate = egkChangeFreq;
                                }
                                else
                                {
                                    // if it has rest 
                                    this->m_CurrState = ensRest;
                                    this->m_CurrStateLength = this->m_SamplePerBeat *
                                        this->m_CurrNote.prev.mul / this->m_CurrNote.prev.div;
                                    this->m_CurrGate = egkOff;
                                }
                            }
                            else
                            {
                                this->m_bFinished = true;
                                this->m_CurrGate = egkOff;
                            }
                        }
                        this->m_CurrStatePosition = 0;
                    }
                }
            }

        private:
            size_t                  m_SampleRate;
            float_type              m_Tempo;
            CNotes                  m_Notes;

            float_type              m_SamplePerBeat;

            size_t                  m_CurrNoteIndex;
            CNotes::note_t          m_CurrNote;

            bool                    m_bFinished;

            eNoteState              m_CurrState;
            size_t                  m_CurrStateLength;
            size_t                  m_CurrStatePosition;

            float_type              m_CurrFreq;
            eGateKind               m_CurrGate;
        };

    }
}



/**********************************************************************

  Audacity: A Digital Audio Editor

  Echo.h

  Dominic Mazzoni

**********************************************************************/

#ifndef __AUDACITY_EFFECT_ECHO__
#define __AUDACITY_EFFECT_ECHO__

#include <wx/defs.h>

class wxString;

#include "Effect.h"

class WaveTrack;

class EffectEcho:public Effect {

 public:

   EffectEcho();

   virtual wxString GetEffectName() {
      return wxString("Echo...");
   }
   
   virtual wxString GetEffectAction() {
      return wxString("Performing Echo");
   }
   
   virtual bool PromptUser();
   
   virtual bool Process();

 private:
   bool ProcessOne(int count, WaveTrack * t,
                   sampleCount start, sampleCount len);
 
   float delay;
   float decay;
};

#endif

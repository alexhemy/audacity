/**********************************************************************

  Audacity: A Digital Audio Editor

  Generator.h

  Two Abstract classes, Generator, and BlockGenerator, that effects which
  generate audio should derive from.  
  
  Block Generator breaks the synthesis task up into smaller parts.

  Dominic Mazzoni
  Vaughan Johnson

**********************************************************************/

#include "../Prefs.h"

#include "Generator.h"
#include "TimeWarper.h"

bool Generator::Process()
{
   if (mDuration < 0.0)
      return false;

   BeforeGenerate();

   // Set up mOutputTracks. This effect needs Track::All for grouping
   this->CopyInputTracks(Track::All);

   // Iterate over the tracks
   bool bGoodResult = true;
   int ntrack = 0;
   TrackListIterator iter(mOutputTracks);
   Track* t = iter.First();

   while (t != NULL)
   {
      if (t->GetKind() == Track::Wave && t->GetSelected()) {
         WaveTrack* track = (WaveTrack*)t;
         
         bool editClipCanMove;
         gPrefs->Read(wxT("/GUI/EditClipCanMove"), &editClipCanMove, true);

         //if we can't move clips, check if generation is done on an empty place with enough
         //duration before actually generate anything.
         if (!editClipCanMove && track->IsEmpty(mT0, mT0+1.0/track->GetRate()) &&
            !track->IsEmpty(mT0, mT0+mDuration-1.0/track->GetRate())) {
            wxMessageBox(
               _("There is not enough room available to generate the audio"),
               _("Error"), wxICON_STOP);   
            Failure();
            return false;
         }

         if (mDuration > 0.0)
         {
            // Create a temporary track
            WaveTrack *tmp = mFactory->NewWaveTrack(track->GetSampleFormat(),
                                                    track->GetRate());
            BeforeTrack(*track);

            // Fill it with data
            if (!GenerateTrack(tmp, *track, ntrack))
               bGoodResult = false;
            else {
               // Transfer the data from the temporary track to the actual one
               tmp->Flush();
               SetTimeWarper(new StepTimeWarper(mT1, mDuration-mT1));
               bGoodResult = track->ClearAndPaste(mT0, mT1, tmp, true,
                     false, GetTimeWarper());
               delete tmp;
            }

            if (!bGoodResult) {
               Failure();
               return false;
            }
         }
         else
         {
            // If the duration is zero, there's no need to actually
            // generate anything
            track->Clear(mT0, mT1);
         }

         ntrack++;
      }
      else if (t->IsSynchroSelected()) {
         t->SyncAdjust(mT1, mT0 + mDuration);
      }
      // Move on to the next track
      t = iter.Next();
   }

   Success();

   this->ReplaceProcessedTracks(bGoodResult);

   mT1 = mT0 + mDuration; // Update selection.

   return true;
}

bool BlockGenerator::GenerateTrack(WaveTrack *tmp,
                                   const WaveTrack &track,
                                   int ntrack)
{
   bool bGoodResult = true;
   numSamples = track.TimeToLongSamples(mDuration);
   sampleCount i = 0;
   float *data = new float[tmp->GetMaxBlockSize()];
   sampleCount block = 0;

   while ((i < numSamples) && bGoodResult) {
      block = tmp->GetBestBlockSize(i);
      if (block > (numSamples - i))
         block = numSamples - i;

      GenerateBlock(data, track, block);

      // Add the generated data to the temporary track
      tmp->Append((samplePtr)data, floatSample, block);
      i += block;

      // Update the progress meter
      if (TrackProgress(ntrack, (double)i / numSamples))
         bGoodResult = false;
   }
   delete[] data;
   return bGoodResult;
}

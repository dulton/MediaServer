//
//  FlameDetector.cpp
//  FlameDetection
//
//  Created by liberize on 14-4-5.
//  Copyright (c) 2014年 liberize. All rights reserved.
//

#include "FlameDetector.h"

FlameDetector::FlameDetector()
: mFrameCount(0)
, mFlameCount(0)
, mTrack(false)
{
}

bool FlameDetector::detect(const Mat& frame,void* videoHandler)
{
    //mFrame = frame; nikola
	frame.copyTo(mFrame);
    Mat mymask;
    clock_t start, finish;
    if(++mFrameCount > SKIP_FRAME_COUNT) {
        mTrack = true;
        //start = clock();
    }
    mymask = mExtractor.extract(mFrame, mTargetMap, mTrack);
    if (mTrack) {
        mAnalyzer.analyze(mFrame, mymask, mTargetMap,videoHandler);
        bool result = mDecider.decide(mFrame, mTargetMap);
       //finish = clock();
       //cout << "duration: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << "s" << endl;
        if (result) {
            mFlameCount++;
        }
       // cout << "frame: " << (mFrameCount - SKIP_FRAME_COUNT) << ", flame: " << mFlameCount << endl;
       // cout << "detection rate: " << 1.0 * mFlameCount / (mFrameCount - SKIP_FRAME_COUNT) << endl;
        return result;
    }
	mFrame.release();  //nikola
    mymask.release();
    return false;
}

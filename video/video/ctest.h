//
//  ctest.h
//  video
//
//  Created by chen on 2024/1/15.
//

#ifndef ctest_h
#define ctest_h

#include <stdio.h>
#include "include/libavutil/avutil.h"
#include "include/libavdevice/avdevice.h"
#include "include/libavformat/avformat.h"
#include "include/libavcodec/avcodec.h"
#include "includee/libswresample/swresample.h"
#include "include/libavutil/dict.h"

void set_status(int status);
void rec_audio(void);
 
#endif /* ctest_h */

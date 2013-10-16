/* dtkVideo.h ---
 *
 * Author: Julien Wintz
 * Created: Wed Oct 16 11:59:24 2013 (+0200)
 * Version:
 * Last-Updated:
 *           By:
 *     Update #: 19
 */

/* Change Log:
 *
 * See credits at EOF.
 */

#pragma once

#include <stdint.h>

namespace ffmpeg {

    extern "C" {

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

#include "libavcodec/avcodec.h"
#include "libavcodec/opt.h"

#include "libavformat/avformat.h"

#include "libavutil/mathematics.h"
#include "libavutil/rational.h"
#include "libavutil/avstring.h"

#include "libswscale/swscale.h"

    }
}

// ///////////////////////////////////////////////////////////////////
// Credits
// ///////////////////////////////////////////////////////////////////

/*
  QTFFmpegWrapper - QT FFmpeg Wrapper Class
  Copyright (C) 2009,2010: Daniel Roggen, droggen@gmail.com

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDERS ``AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
*/

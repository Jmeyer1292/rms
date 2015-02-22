#ifndef RMS_PREPROCESS
#define RMS_PREPROCESS

#include <algorithm>

#include "types.h"
#include "line_fitting.h"

namespace rms
{
  Scan filterScan(const Scan& scan);

  Scan lineAdjust(const Scan& scan, const LineCoef<Scan::value_type>& line);
}

#endif
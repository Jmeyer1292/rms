#ifndef RMS_POSTPROCESS_H
#define RMS_POSTPROCESS_H

#include "types.h"

namespace rms
{
  ColoredScan fuseData(const Scan& scan, const std::vector<double> scores)
  {
    int diff = (scan.x_.size() - scores.size()) / 2;
    ColoredScan result;

    for (std::size_t i = 0; i < scores.size(); ++i)
    {
      result.colors_.push_back(scores[i]);
      result.points_.x_.push_back(scan.x_[i + diff]);
      result.points_.y_.push_back(scan.y_[i + diff]);
    }

    return result;
  }
} // end rms 

#endif
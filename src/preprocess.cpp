#include "preprocess.h"

static inline bool inRange(double x) { return x > -20.0; }

rms::Scan rms::filterScan(const Scan& scan)
{
  Scan result;
  result.x_.reserve(scan.x_.size());
  result.y_.reserve(scan.y_.size());

  for (std::size_t i = 0; i < scan.x_.size(); ++i)
  {
    if (inRange(scan.y_[i]))
    {
      result.x_.push_back(scan.x_[i]);
      result.y_.push_back(scan.y_[i]);
    }
  }

  return result;
}

rms::Scan rms::lineAdjust(const Scan& scan, const LineCoef<Scan::value_type>& line)
{
  rms::Scan result;
  result.x_.resize(scan.x_.size());
  result.y_.resize(scan.y_.size());

  for (std::size_t i = 0; i < scan.x_.size(); ++i)
  {
    result.x_[i] = scan.x_[i];
    result.y_[i] = scan.y_[i] - line(scan.x_[i]); 
  }

  return result;
}
#include "io_utils.h"

#include <iostream>

rms::Scan rms::io::read_scan(std::istream& is, size_t max_points)
{
  Scan result;
  result.x_.reserve(max_points);
  result.y_.reserve(max_points);
  std::size_t count = 0;

  while (count < SCAN_SIZE)
  {
    double x, y;
    is >> x >> y;
    
    if (!is) break;

    result.x_.push_back(x);
    result.y_.push_back(y);
    count++;
  }
  return result;
}

void rms::io::write_colored_scan(std::ostream& os, const ColoredScan& scan)
{
  bool print_color = !scan.colors_.empty();
  for (std::size_t i = 0; i < scan.points_.x_.size(); ++i)
  {
    os << scan.points_.x_[i] << " " << scan.points_.y_[i];
    if (print_color) os << " " << scan.colors_[i];
    os << std::endl;
  }
}

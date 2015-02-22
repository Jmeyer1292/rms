#ifndef RMS_IO_UTILS
#define RMS_IO_UTILS

#include <iosfwd>

#include "types.h"

namespace rms
{
namespace io
{

  Scan read_scan(std::istream& is, size_t max_points = rms::SCAN_SIZE);

  void write_colored_scan(std::ostream& os, const ColoredScan& scan);

  inline void write_scan(std::ostream& os, const Scan& scan)
  {
    ColoredScan cscan;
    cscan.points_ = scan;
    write_colored_scan(os, cscan);
  }

} // end namespace io
} // end namespace rms

#endif
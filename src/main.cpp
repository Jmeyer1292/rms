#include <iostream>
#include <fstream>
#include <cmath>

#include "kernel.h"
#include "types.h"
#include "line_fitting.h"
#include "io_utils.h"
#include "postprocess.h"
#include "preprocess.h"

typedef rms::ScanVec::iterator scan_iter;

static double test2(scan_iter a, scan_iter b)
{
  return rms::scoreValleyPeak<double, scan_iter>(a,b);
}

static double test3(scan_iter a, scan_iter b)
{
  return rms::scoreRms<double, scan_iter>(a,b);
}

static double local_line(scan_iter a, scan_iter b)
{
  std::size_t n = std::distance(a, b);
  // dummy x
  std::vector<double> dummyx;
  for (size_t i = 0; i < n; i++)
    dummyx.push_back(0.05 * i);
  // fit line
  rms::LineFitSums<double> sums 
    = rms::calculateSums<double>(dummyx.begin(), a, dummyx.end(), b);

  rms::LineCoef<double> line = rms::calculateLineCoefs(sums);
  
  std::vector<double> delta;
  delta.reserve(n);
  for (size_t i = 0; i < n; i++)
  {
    delta.push_back(*(a + i) - line(dummyx[i]));
  }

  return test3(delta.begin(), delta.end());

}

int main(int argc, char** argv)
{
  typedef typename rms::Scan::value_type FloatType;

  if (argc < 2)
  {
    std::cout << "Usage: ./rms <scan_data_file>" << std::endl;
    return 1;
  }

  std::ifstream file (argv[1]);

  if (!file)
  {
    std::cerr << "Could not open file " << argv[1] << std::endl;
    return 2;
  }

  // Read line data into vector/array
  rms::Scan data = rms::io::read_scan(file);

  // Prepass for invalid points ??? (might combine with the avering pass)
  // Might need to interpolate to fill in gaps in data
  rms::Scan filtered = rms::filterScan(data);
  
  // Calculate relevant sums/means
  rms::LineFitSums<FloatType> sums 
    = rms::calculateSums<FloatType>(filtered.x_.begin(), filtered.y_.begin(), 
                                    filtered.x_.end(), filtered.y_.end());

  // Fit line
  rms::LineCoef<FloatType> line = rms::calculateLineCoefs(sums);
  rms::Scan delta = rms::lineAdjust(filtered, line);

  // Apply a surface roughness scoring function
  std::size_t window = 201;
  std::size_t score_size = std::distance(delta.y_.begin() + window, delta.y_.end());
  std::vector<double> score(score_size, 0.0);
  
  kernel_op(delta.y_.begin(), delta.y_.begin() + window, delta.y_.end(), score.begin(), test3);
  // kernel_op(filtered.y_.begin(), filtered.y_.begin() + window, filtered.y_.end(), score.begin(), local_line);

  // Put the scores together with their respective data points
  rms::ColoredScan result = rms::fuseData(filtered, score);

  // Write to output file
  std::ofstream outfile("out.txt");
  if (!outfile)
  {
    std::cerr << "Could not open outfile\n";
    return -2;
  }
  rms::io::write_colored_scan(outfile, result);

  return 0;
}


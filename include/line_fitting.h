#ifndef LINE_FITTING_H
#define LINE_FITTING_H

#include <algorithm>
#include <numeric>

namespace rms
{

  template<typename FloatType, typename InputIt>
  inline FloatType naive_mean(InputIt begin, InputIt end, FloatType init = FloatType())
  {
    std::size_t n = std::distance(begin, end);
    FloatType sum = std::accumulate(begin, end, init);
    return sum / n;
  }

  template<typename FloatType, typename InputIt>
  inline FloatType online_mean(InputIt begin, InputIt end, FloatType init = FloatType())
  {
    std::size_t n = 1;
    while (begin != end)
    {
      init = init + (*begin - init) / n++;
      ++begin;
    }
    return init;
  }

  template<typename FloatType, typename InputIt>
  inline FloatType sumAbsValue(InputIt begin, InputIt end, FloatType init = FloatType())
  {
    while (begin != end)
    {
      init += std::abs(*begin);
      ++begin;
    }

    return init;
  }

  template<typename FloatType, typename InputIt, typename Op>
  inline FloatType sumOp(InputIt begin, InputIt end, Op op = Op(), FloatType init = FloatType())
  {
    while (begin != end)
    {
      init += op(*begin);
      ++begin;
    }

    return init;
  }

  template<typename FloatType, typename InputIt>
  inline FloatType sumSquared(InputIt begin, InputIt end, FloatType init = FloatType())
  {
    while (begin != end)
    {
      init += (*begin) * (*begin);
      ++begin;
    }

    return init;
  }


  // Assumes no invalid points
  template<typename FloatType, typename InputIt>
  LineFitSums<FloatType> calculateSums(InputIt xbegin, InputIt ybegin, InputIt xend, InputIt yend)
  {
    LineFitSums<FloatType> sums;
    sums.n_ = std::distance(xbegin, xend);
    while (xbegin != xend && ybegin != yend)
    {
      sums.x_ += *xbegin;
      sums.y_ += *ybegin;
      sums.x2_ += ((*xbegin) * (*xbegin));
      sums.xy_ += ((*xbegin) * (*ybegin));

      ++xbegin;
      ++ybegin;
    }

    return sums;
  }

  template<typename FloatType>
  LineCoef<FloatType> calculateLineCoefs(const LineFitSums<FloatType>& sums)
  {
    LineCoef<FloatType> line;
    
    FloatType x_mean = sums.x_ / sums.n_;
    FloatType y_mean = sums.y_ / sums.n_;

    line.slope = (sums.xy_ - sums.x_ * y_mean) / (sums.x2_ - sums.x_ * x_mean);
    line.intercept = y_mean - line.slope * x_mean;

    return line; 
  }

  template<typename FloatType>
  LineCoef<FloatType> calculateLineCoefs(const LineFitMeans<FloatType>& means)
  {
    LineCoef<FloatType> line;

    line.slope = (means.xy_ - means.x_ * means.y_) / (means.x2_ - means.x_ * means.x_);
    line.intercept = means.y_ - line.slope * means.x_;

    return line;
  }

  template<typename FloatType, typename InputIt>
  FloatType scoreAvgAbs(InputIt begin, InputIt end)
  {
    std::size_t n = std::distance(begin, end);
    return sumAbsValue<FloatType>(begin, end) / n;
  }

  template<typename FloatType, typename InputIt>
  FloatType scoreRms(InputIt begin, InputIt end)
  {
    std::size_t n = std::distance(begin, end);
    return std::sqrt(sumSquared<FloatType>(begin, end) / n);
  }

  template<typename FloatType, typename InputIt>
  FloatType scoreValleyPeak(InputIt begin, InputIt end)
  {
    // naive impl for now
    return *std::max(begin, end) - *std::min(begin, end);
  }

  template<typename FloatType, typename InputIt>
  FloatType scoreSkewness(InputIt begin, InputIt end)
  {
    std::size_t n = std::distance(begin, end);
    FloatType rms_cubed = std::pow(scoreRms(begin, end), 3.0);
    FloatType sum_cubed = sumOp(begin, end, [](FloatType x) { return x * x * x; });
    return sum_cubed / (n * rms_cubed);
  }
  

} // end rms namespace


#endif

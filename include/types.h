#ifndef RMS_TYPES
#define RMS_TYPES

#include <vector>

namespace rms
{
  const static std::size_t SCAN_SIZE = 800; 

  typedef std::vector<double> ScanVec; 

  // IO structures
  struct Scan
  {
    typedef typename ScanVec::value_type value_type;
    ScanVec x_;
    ScanVec y_;
  };

  struct ColoredScan
  {
    Scan points_;
    ScanVec colors_;
  };

  /* Internal calculation structures */
  template<typename FloatType>
  struct LineFitSums
  {
    FloatType x_;
    FloatType y_;
    FloatType x2_;
    FloatType xy_;
    std::size_t n_;

    LineFitSums(FloatType x = FloatType(), FloatType y = FloatType(),
                FloatType x2 =  FloatType(), FloatType xy = FloatType(), 
                std::size_t cnt  = size_t())
      : x_(x)
      , y_(y)
      , x2_(x2)
      , xy_(xy)
      , n_(cnt)
    {}
  };

  template<typename FloatType>
  struct LineFitMeans
  {
    FloatType x_;
    FloatType y_;
    FloatType x2_;
    FloatType xy_;

    LineFitMeans(FloatType x = FloatType(), FloatType y = FloatType(),
                FloatType x2 =  FloatType(), FloatType xy = FloatType())
      : x_(x)
      , y_(y)
      , x2_(x2)
      , xy_(xy)
    {}
  };

  template<typename FloatType>
  struct LineCoef
  {
    FloatType slope;
    FloatType intercept;

    FloatType operator()(const FloatType x) const
    {
      return slope * x + intercept;
    }
  };

} // end namespace rms

#endif
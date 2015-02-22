#ifndef RMS_KERNEL_H
#define RMS_KERNEL_H

template<class Op, typename InputIt, typename OutputIt>
void kernel_op(InputIt wbegin, InputIt wend, InputIt in_end, OutputIt out_begin, Op op = Op()) 
{
  while (wend != in_end)
  {
    *out_begin = op(wbegin, wend);

    ++wend;
    ++wbegin;
    ++out_begin;
  }
}

// template<template<typename R, typename P> class Op, typename InputIt, typename OutputIt>
// void kernel_op(InputIt wbegin, InputIt wend, InputIt in_end, OutputIt out_begin) 
// {
//   Op<double, InputIt> op;
//   while (wend != in_end)
//   {
//     *out_begin = Op<double, InputIt>::foo(wbegin, wend);

//     ++wend;
//     ++wbegin;
//     ++out_begin;
//   }
// }

// template<typename R, typename P>
// struct MyOp
// {
//   static R foo(P a, P b)
//   {
//     return rms::score_valley_peak<R>(a, b);
//   }
// };

#endif

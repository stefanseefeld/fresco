/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2002 Massimo Ricci
 * Copyright (C) 2003 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */
#ifndef _Berlin_nurbs_basic_nurbs_hh
#define _Berlin_nurbs_basic_nurbs_hh

#include <Berlin/nurbs/domain.hh>
#include <Berlin/nurbs/array.hh>
#include <vector>

namespace Berlin
{
namespace nurbs
{

//. a 'weighted T' is a T with an
//. associated weighting factor
//. (used to implement the 'R' in NURBS)
template <typename T>
struct Weighted
{
  T numerator;
  double denominator;
};

//. basis function used in nurbs:
//. i and d are indices, p is the actual parameter,
//. K is the knot vector
template <typename K>
double basis_function(size_t i, size_t d, double p, const K &k)
{
  if(d == 0)
  {
    if(k[i] <= p && p <= k[i + 1]) return 1.;
    else return 0.;
  }
  else
  {
    if(k[i] <= p && p <= k[i + d + 1])
    {
      double e1 = k[i + d] - k[i];
      double e2 = k[i + d + 1] - k[i + 1];

      if (e1 == 0. && e2 == 0.) return 0.;
	  
      if (e1 == 0. && e2 != 0.)
	return (k[i + d + 1] - p) / e2 * basis_function(i + 1, d - 1, p, k);
	  
      if (e1 != 0. && e2 == 0.)
	return (p - k[i]) / e1 * basis_function(i, d - 1, p, k);

      if (e1 != 0. && e2 != 0.)
	return (k[i + d + 1] - p) / e2 * basis_function(i + 1, d - 1, p, k) +
	  (p - k[i]) / e1 * basis_function(i, d - 1, p, k);
    }
    else return 0.;
  }
  return 0.;
}

//. computes derivative of a basis function:
//. i and d are indices, p is the actual parameter,
//. K is the knot vector
template <typename K>
double basis_function_derivative(size_t i, size_t d, double p, const K &k)
{
  if (d == 0) return 0.;
  else
  {
    double d1 = k[i + d] - k[i];
    double d2 = k[i + d + 1] - k[i + 1];
      
    double e1, e2, e3, e4;
      
    e1 = e2 = e3 = e4 = 0.0;
      
    if(d1 != 0.)
    {
      e1 = (1. / d1) * basis_function(i, d - 1, p, k);
      e2 = (p - k[i]) / d1 * basis_function_derivative(i, d - 1, p, k);
    }
      
    if(d2 != 0.)
    {
      e3 = (-1. / d2) * basis_function(i + 1, d - 1, p, k);
      e4 = (k[i + d + 1] - p) / d2 * basis_function_derivative(i + 1, d - 1, p, k);
    }
    return e1 + e2 + e3 + e4;
  }
  return 0.;
}

template <typename T, size_t P>
Weighted<T> evaluate_at(const domain<T, P> &ctrls,
			const domain<double, P> weights,
			const array<size_t, P> &degrees,
			const array<std::vector<double>, P> &knots,
			array<double, P> params,
			array<size_t, P> idxs,
			size_t r)
{
  Weighted<T> sum;
  assign(sum.numerator, 0.);
  sum.denominator = 0.;

  if(r > 1)
  {
    for(idxs[r - 1] = 0; idxs[r - 1] < ctrls.size(r - 1); ++idxs[r - 1])
    {
      double basis = basis_function(idxs[r - 1], degrees[r - 1],
                                    params[r - 1], knots[r - 1]);
      if(basis != 0.)
      {
        Weighted<T> point = evaluate_at(ctrls, weights, degrees, knots,
					params, idxs, r - 1);
        sum.numerator += point.numerator * basis;
        sum.denominator += point.denominator * basis;
      }
    }
  }
  else
  {
    for(idxs[r - 1] = 0; idxs[r - 1] < ctrls.size(r - 1); ++idxs[r - 1])
    {
      double basis = basis_function(idxs[r - 1], degrees[r - 1],
				    params[r - 1], knots[r - 1]);
      if(basis != 0.)
      {
        sum.numerator += ctrls(idxs.data()) * basis * weights(idxs.data());
        sum.denominator += basis * weights(idxs.data());
      }
    }
  }
  return sum;
}

template <typename T, size_t P>
T evaluate_at(const domain<T, P> &ctrls,
	      const domain<double, P> &weights,
	      const array<size_t, P> &degrees,
	      const array<std::vector<double>, P> &knots,
	      const array<double, P> &params)
{
  array<size_t, P> idx(0);
  Weighted<T> point = evaluate_at(ctrls, weights, degrees, knots, params, idx, P);
  return point.numerator / point.denominator;
}

template <typename T, size_t P>
void evaluate(const domain<T, P> &ctrls, 
	      const domain<double, P> &weights,
	      const array<size_t, P> &degrees,
	      const array<std::vector<double>, P> &knots,
	      const array<size_t, P> &steps,
	      array<double, P> params,
	      size_t r,
	      std::vector<T> &points)
{
  size_t step = steps[r - 1];
  size_t length = ctrls.size(r - 1) + 1;
  size_t plength = length - degrees[r - 1] +
    (length - degrees[r - 1] - 1) * (step - 1);

  std::vector<double> pvalues(plength);

  size_t index = degrees[r - 1];

  if(step == 1)
  {
    pvalues = knots[r - 1];
    plength = length;
  }
  else
  {
    size_t h = 0;
    for(size_t i = index; i < length - 1; ++i)
    {
      pvalues[h] = knots[r - 1][i];
      double d = (knots[r - 1][i + 1] - knots[r - 1][i]) / step;
      for(size_t j = 0; j < step - 1; ++j)
      {
        ++h;
        pvalues[h] = pvalues[h - 1] + d;
      }
      ++h;
    }
    pvalues[h] = knots[r - 1][length - 1];
    index = 0;
  }
   
  for(size_t i = index; i < plength; ++i)
  {
    params[r - 1] = pvalues[i];
    if(r == 1) points.push_back(evaluate_at(ctrls, weights, degrees, knots, params));
    else evaluate(ctrls, weights, degrees, knots, steps, params, r - 1, points);
  }
}

//. return a P-dimensional domain of points
template <typename T, size_t P>
domain<T, P> *evaluate(const domain<T, P> &ctrls,
		       const domain<double, P> &weights,
		       const array<size_t, P> &degrees,
		       const array<std::vector<double>, P> &knots,
		       const array<size_t, P> &steps)
{
  std::vector<T> points;
  array<size_t, P> length;
  array<double, P> params;

  for(size_t i = 0; i < P; ++i)
  {
    params[i] = knots[i][0];
    length[i] = ctrls.size(i) - degrees[i] + 1 +
      (ctrls.size(i) - degrees[i]) * (steps[i] - 1);
  }
  
  evaluate(ctrls, weights, degrees, knots, steps, params, P, points);

  domain<T, P> *retn = new domain<T, P>(length.data());  
  for(size_t i = 0; i < points.size(); ++i) (*retn)[i] = points[i];
  return retn;
}

//. return a P-dimensional domain of points
//. assume uniform knots
template <typename T, size_t P>
domain<T, P> *evaluate(const domain<T, P> &ctrls,
                       const domain<double, P> &weights,
                       const array<size_t, P> &degrees,
                       const array<size_t, P> &steps)
{
  array<std::vector<double>, P> knots;
  for(size_t i = 0; i < P; ++i)
  {
    knots[i].resize(ctrls.size(i) + degrees[i] + 1);
    double delta = 1. / (ctrls.size(i) + degrees[i]);
    for (size_t j = 0; j != ctrls.size(i) + degrees[i] + 1; ++j)
      knots[i][j] = j * delta;
  }
  return evaluate(ctrls, weights, degrees, knots, steps);
}

template <typename T, size_t P>
array<Weighted<T>, P + 1>
evaluate_with_derivations_at(const domain<T, P> &ctrls,
			     const domain<double, P> &weights,
			     const array<size_t, P> &degrees,
			     const array<std::vector<double>, P> &knots,
			     array<double, P> params,
			     array<size_t, P> idxs,
			     size_t r)
{
  array<Weighted<T>, P + 1> sum;
  for(size_t i = 0; i < P + 1; ++i)
  {
    assign(sum[i].numerator, 0.);
    sum[i].denominator = 0.;
  }
  if(r > 1)
  {
    array<Weighted<T>, P + 1> points;
    for(idxs[r - 1] = 0; idxs[r - 1] < ctrls.size(r - 1); ++idxs[r - 1])
    {
      double derivative = basis_function_derivative(idxs[r - 1], degrees[r - 1],
                                                    params[r - 1], knots[r - 1]);
      double basis = basis_function(idxs[r - 1], degrees[r - 1],
                                    params[r -  1], knots[r - 1]);
      if(basis != 0 || derivative != 0)
        points = evaluate_with_derivations_at(ctrls, weights, degrees, knots,
					      params, idxs, r - 1);
      if(basis != 0)
      {
        sum[0].numerator += points[0].numerator * basis;
        sum[0].denominator += points[0].denominator * basis;
      }  
      for(size_t k = 1; k < P + 1; ++k)
        if(k == r)
        {
          if(derivative != 0)
          {
            sum[k].numerator += points[k].numerator * derivative;
            sum[k ].denominator += points[k].denominator * derivative;
          }
        }
        else
        {
          if(basis != 0)
          {
            sum[k].numerator += points[k].numerator * basis;
            sum[k].denominator += points[k].denominator * basis;
          }
        }
    }
  }
  else
  {
    for(idxs[r - 1] = 0; idxs[r - 1] < ctrls.size(r - 1); ++idxs[r - 1])
    {
      double basis = basis_function(idxs[r - 1], degrees[r - 1],
                                    params[r - 1], knots[r - 1]);
      double derivative = basis_function_derivative(idxs[r - 1], degrees[r - 1],
                                                    params[r - 1], knots[r - 1]);
      if(basis != 0)
      {
        sum[0].numerator += ctrls(idxs.data()) * basis * weights(idxs.data());
        sum[0].denominator += basis * weights(idxs.data());
      }
      for(size_t k = 1; k < P + 1; ++k)
        if(k == r && derivative != 0)
        {
          sum[k].numerator += ctrls(idxs.data()) * derivative * weights(idxs.data());
          sum[k].denominator += weights(idxs.data()) * derivative;
        }
        else
        {
          if(basis != 0)
          {
            sum[k].numerator += ctrls(idxs.data()) * basis * weights(idxs.data());
            sum[k].denominator += weights(idxs.data()) * basis;
          }
        }
    }
  }
  return sum;
}

template <typename T, size_t P>
array<T, P + 1>
evaluate_with_derivations_at(const domain<T, P> &ctrls,
			     const domain<double, P> &weights,
			     const array<size_t, P> &degrees,
			     const array<std::vector<double>, P> &knots,
			     const array<double, P> &params)
{
  array<size_t, P> idx(0);
  array<Weighted<T>, P + 1> points = evaluate_with_derivations_at(ctrls, weights,
								  degrees, knots,
								  params, idx, P);
  T numerator = points[0].numerator;
  double denominator = points[0].denominator;

  array<T, P + 1> derivations;

  for(size_t k = 1; k < P + 1; ++k)
  {
    derivations[k] = points[k].numerator * denominator;
    derivations[k] -= numerator * points[k].denominator;
    if(denominator != 0) derivations[k] /= denominator * denominator;
    else assign(derivations[k], 0.);
  }

  if(denominator != 0) derivations[0] = numerator / denominator;
  else assign(derivations[0], 0.);
  return derivations;
}

template <typename T, size_t P>
void evaluate_with_derivations(const domain<T, P> &ctrls,
			       const domain<double, P> &weights,
			       const array<size_t, P> &degrees,
			       const array<std::vector<double>, P> knots,
			       const array<size_t, P> &steps,
			       array<double, P> params,
			       size_t r,
			       std::vector<array<T, P + 1> > &points)
{
  size_t step = steps[r - 1];
  size_t length = ctrls.size(r - 1) + 1;
  size_t plength = length - degrees[r - 1] +
    (length - degrees[r - 1] - 1) * (step - 1);

  std::vector<double> pvalues(plength);
  size_t index = degrees[r - 1];

  if(step == 1)
  {
    std::copy(knots[r-1].begin(), knots[r-1].end(), pvalues.begin());
    plength = length;
  }
  else
  {
    size_t h = 0;
    for(size_t i = index; i < length - 1; ++i)
    {
      pvalues[h] = knots[r - 1][i];
      double d = (knots[r - 1][i + 1] - knots[r - 1][i]) / step;
      for(size_t j = 0; j < step - 1; ++j)
      {
        ++h;
        pvalues[h] = pvalues[h - 1] + d;
      }
      ++h;
    }
    pvalues[h] = knots[r - 1][length - 1];
    index = 0;
  }
  for(size_t i = index; i < plength; ++i)
  {
    params[r - 1] = pvalues[i];
    if(r == 1)
    {
      points.push_back(evaluate_with_derivations_at(ctrls, weights, degrees, knots,
						    params)); 
    }
    else evaluate_with_derivations(ctrls, weights, degrees, knots, steps,
				   params, r - 1, points);
  }
}

//. return a P-dimensional domain of points arrays
//. each array contains the actual point and the P derivatives
template <typename T, size_t P>
domain<array<T, P + 1>, P> *
evaluate_with_derivations(const domain<T, P> &ctrls,
			  const domain<double, P> &weights,
			  const array<size_t, P> &degrees,
			  const array<std::vector<double>, P> &knots,
			  const array<size_t, P> &steps)
{
  array<size_t, P> length;
  array<double, P> params;

  for(size_t i = 0; i < P; ++i)
  {
    params[i] = knots[i][0];
    length[i] = ctrls.size(i) - degrees[i] + 1 +
      (ctrls.size(i) - degrees[i]) * (steps[i] - 1);
  }
   
  std::vector<array<T, P + 1> > points;
  evaluate_with_derivations(ctrls, weights, degrees, knots, steps, params, P, points);

  domain<array<T, P + 1>, P> *retn = new domain<array<T, P + 1>, P>(length.data());
  for(size_t i = 0; i < points.size(); ++i) (*retn)[i] = points[i];
  return retn;
}

//. return a P-dimensional domain of points arrays
//. each array contains the actual point and the P derivatives.
//. assume uniform knots
template <typename T, size_t P>
domain<array<T, P + 1>, P> *
evaluate_with_derivations(const domain<T, P> &ctrls,
                          const domain<double, P> &weights,
                          const array<size_t, P> &degrees,
                          const array<size_t, P> &steps)
{
  array<std::vector<double>, P> knots;
  for(size_t i = 0; i < P; ++i)
  {
    knots[i].resize(ctrls.size(i) + degrees[i] + 1);
    double delta = 1. / (ctrls.size(i) + degrees[i]);
    for (size_t j = 0; j != ctrls.size(i) + degrees[i] + 1; ++j)
      knots[i][j] = j * delta;
  }
  return evaluate_with_derivations(ctrls, weights, degrees, knots, steps);
}

}
}

#endif





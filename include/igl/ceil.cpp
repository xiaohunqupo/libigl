// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "ceil.h"
#include <cmath>

template < typename DerivedX, typename DerivedY>
IGL_INLINE void igl::ceil(
  const Eigen::MatrixBase<DerivedX>& X,
  Eigen::PlainObjectBase<DerivedY>& Y)
{
  typedef typename DerivedX::Scalar Scalar;
  Y = X.unaryExpr([](const Scalar &x)->Scalar{return std::ceil(x);}).template cast<typename DerivedY::Scalar >();
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::ceil<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
#endif

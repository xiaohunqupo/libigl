// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2015 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "directed_edge_parents.h"
#include "colon.h"
#include "setdiff.h"
#include <algorithm>

template <typename DerivedE, typename DerivedP>
IGL_INLINE void igl::directed_edge_parents(
  const Eigen::MatrixBase<DerivedE> & E,
  Eigen::PlainObjectBase<DerivedP> & P)
{
  typedef Eigen::Matrix<typename DerivedE::Scalar, Eigen::Dynamic, 1> VectorT;

  VectorT I = VectorT::Constant(E.maxCoeff()+1,1,-1);
  //I(E.col(1)) = 0:E.rows()-1
  I(E.col(1).eval()) = colon<typename DerivedE::Scalar>(0, E.rows()-1);
  VectorT roots,_;
  setdiff(E.col(0).eval(),E.col(1).eval(),roots,_);
  std::for_each(roots.data(),roots.data()+roots.size(),[&](typename VectorT::Scalar r){I(r)=-1;});
  P = I(E.col(0).eval());
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::directed_edge_parents<Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
#endif

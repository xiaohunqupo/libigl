// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2015 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "winding_number.h"
#include "WindingNumberAABB.h"
#include "signed_angle.h"
#include "parallel_for.h"
#include "solid_angle.h"
#include "PI.h"

#include <cmath>

template <
  typename DerivedV,
  typename DerivedF,
  typename DerivedO,
  typename DerivedW>
IGL_INLINE void igl::winding_number(
  const Eigen::MatrixBase<DerivedV> & V,
  const Eigen::MatrixBase<DerivedF> & F,
  const Eigen::MatrixBase<DerivedO> & O,
  Eigen::PlainObjectBase<DerivedW> & W)
{
  // make room for output
  W.resize(O.rows(),1);
  switch(F.cols())
  {
    case 2:
    {
      igl::parallel_for(O.rows(),[&](const int o)
      {
        W(o) = winding_number(V,F,O.row(o));
      },10000);
      return;
    }
    case 3:
    {
      WindingNumberAABB<
        typename DerivedV::Scalar,
        typename DerivedF::Scalar>
        hier(V,F);
      hier.grow();
      // loop over origins
      igl::parallel_for(O.rows(),[&](const int o)
        {
          W(o) = hier.winding_number(O.row(o));
        },10000);
      break;
    }
    default: assert(false && "Bad simplex size"); break;
  }
}

template <
  typename DerivedV,
  typename DerivedF,
  typename Derivedp>
IGL_INLINE typename DerivedV::Scalar igl::winding_number(
  const Eigen::MatrixBase<DerivedV> & V,
  const Eigen::MatrixBase<DerivedF> & F,
  const Eigen::MatrixBase<Derivedp> & p)
{
  typedef typename DerivedV::Scalar wType;
  const int ss = F.cols();
  const int m = F.rows();
  wType w = 0;
  for(int f = 0;f<m;f++)
  {
    switch(ss)
    {
      case 2:
      {
        w += igl::signed_angle( V.row(F(f,0)),V.row(F(f,1)),p);
        break;
      }
      case 3:
      {
        w += igl::solid_angle(V.row(F(f,0)), V.row(F(f,1)), V.row(F(f,2)),p);
        break;
      }
      default: assert(false); break;
    }
  }
  return w;
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template Eigen::Matrix<double, -1, -1, 0, -1, -1>::Scalar igl::winding_number<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, 1, 2, 1, 1, 2> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 2, 1, 1, 2> > const&);
template Eigen::Matrix<double, -1, -1, 0, -1, -1>::Scalar igl::winding_number<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<double, -1, -1, 0, -1, -1>::Scalar igl::winding_number<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, 3, 1, 0, 3, 1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 3, 1, 0, 3, 1> > const&);
template Eigen::Matrix<double, -1, 2, 0, -1, 2>::Scalar igl::winding_number<Eigen::Matrix<double, -1, 2, 0, -1, 2>, Eigen::Matrix<int, -1, 2, 0, -1, 2>, Eigen::Matrix<double, 1, 2, 1, 1, 2> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 2, 0, -1, 2> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 2, 0, -1, 2> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 2, 1, 1, 2> > const&);
template Eigen::Matrix<double, -1, 3, 0, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<double, -1, 3, 1, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<double, -1, 3, 1, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, 3, 1, -1, 3>, Eigen::Matrix<double, 1, 2, 1, 1, 2> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 2, 1, 1, 2> > const&);
template Eigen::Matrix<float, -1, -1, 0, -1, -1>::Scalar igl::winding_number<Eigen::Matrix<float, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<float, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<float, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<float, -1, 3, 0, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<float, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<float, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<float, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<float, -1, 3, 0, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<float, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3>, Eigen::Matrix<float, 1, 2, 1, 1, 2> >(Eigen::MatrixBase<Eigen::Matrix<float, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 1, 2, 1, 1, 2> > const&);
template Eigen::Matrix<float, -1, 3, 1, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<float, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<float, 1, 3, 1, 1, 3> >(Eigen::MatrixBase<Eigen::Matrix<float, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 1, 3, 1, 1, 3> > const&);
template Eigen::Matrix<float, -1, 3, 1, -1, 3>::Scalar igl::winding_number<Eigen::Matrix<float, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, 3, 1, -1, 3>, Eigen::Matrix<float, 1, 2, 1, 1, 2> >(Eigen::MatrixBase<Eigen::Matrix<float, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 3, 1, -1, 3> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 1, 2, 1, 1, 2> > const&);
template void igl::winding_number<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 1, 0, -1, 1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> >&);
template void igl::winding_number<Eigen::Matrix<double, -1, 2, 0, -1, 2>, Eigen::Matrix<int, -1, 2, 0, -1, 2>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 1, 0, -1, 1> >(Eigen::MatrixBase<Eigen::Matrix<double, -1, 2, 0, -1, 2> > const&, Eigen::MatrixBase<Eigen::Matrix<int, -1, 2, 0, -1, 2> > const&, Eigen::MatrixBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> >&);
#endif

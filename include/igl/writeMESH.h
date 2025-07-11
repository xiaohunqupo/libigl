// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_WRITEMESH_H
#define IGL_WRITEMESH_H
#include "igl_inline.h"

#include <string>
#include <vector>
#include <Eigen/Core>

namespace igl
{
  /// save a tetrahedral volume mesh to a .mesh file
  ///
  /// @tparam Scalar  type for positions and vectors (will be cast as double)
  /// @tparam Index  type for indices (will be cast to int)
  /// @param[in] mesh_file_name  path of .mesh file
  /// @param[in] V  double matrix of vertex positions  #V by 3
  /// @param[in] T  #T list of tet indices into vertex positions
  /// @param[in] F  #F list of face indices into vertex positions
  /// @return true on success, false on errors
  ///
  /// \bug Holes and regions are not supported
  template <typename Scalar, typename Index>
  IGL_INLINE bool writeMESH(
    const std::string mesh_file_name,
    const std::vector<std::vector<Scalar > > & V,
    const std::vector<std::vector<Index > > & T,
    const std::vector<std::vector<Index > > & F);
  /// save a tetrahedral volume mesh to a .mesh file
  ///
  /// @tparam DerivedV  real-value: i.e. from Eigen::MatrixXd
  /// @tparam DerivedT  integer-value: i.e. from Eigen::MatrixXi
  /// @tparam DerivedF  integer-value: i.e. from Eigen::MatrixXi
  /// @param[in] mesh_file_name  path of .mesh file
  /// @param[in] V  eigen double matrix #V by 3
  /// @param[in] T  eigen int matrix #T by 4
  /// @param[in] F  eigen int matrix #F by 3
  /// @return true on success, false on errors
  template <typename DerivedV, typename DerivedT, typename DerivedF>
  IGL_INLINE bool writeMESH(
    const std::string str,
    const Eigen::MatrixBase<DerivedV> & V, 
    const Eigen::MatrixBase<DerivedT> & T,
    const Eigen::MatrixBase<DerivedF> & F);
}

#ifndef IGL_STATIC_LIBRARY
#  include "writeMESH.cpp"
#endif

#endif

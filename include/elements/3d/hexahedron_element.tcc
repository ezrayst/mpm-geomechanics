// 8-node (Trilinear) Hexahedron Element
//!        3               2
//!          0_ _ _ _ _ _0
//!         /|           /|
//!        / |          / |
//!     7 0_ |_ _ _ _ _0 6|
//!       |  |         |  |
//!       |  |         |  |
//!       |  0_ _ _ _ _|_ 0
//!       | / 0        | / 1
//!       |/           |/
//!       0_ _ _ _ _ _ 0
//!     4               5

//! Return shape function of a 8-noded hexahedron, with particle size and
//! deformation gradient
//! \param[in] xi Coordinates of point of interest \retval
//! shapefn Shape function of a given cell
template <>
inline Eigen::VectorXd mpm::HexahedronElement<3, 8>::shapefn(
    const Eigen::Matrix<double, 3, 1>& xi,
    Eigen::Matrix<double, 3, 1>& particle_size,
    const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  // 8-noded
  Eigen::Matrix<double, 8, 1> shapefn;
  shapefn(0) = 0.125 * (1 - xi(0)) * (1 - xi(1)) * (1 - xi(2));
  shapefn(1) = 0.125 * (1 + xi(0)) * (1 - xi(1)) * (1 - xi(2));
  shapefn(2) = 0.125 * (1 + xi(0)) * (1 + xi(1)) * (1 - xi(2));
  shapefn(3) = 0.125 * (1 - xi(0)) * (1 + xi(1)) * (1 - xi(2));
  shapefn(4) = 0.125 * (1 - xi(0)) * (1 - xi(1)) * (1 + xi(2));
  shapefn(5) = 0.125 * (1 + xi(0)) * (1 - xi(1)) * (1 + xi(2));
  shapefn(6) = 0.125 * (1 + xi(0)) * (1 + xi(1)) * (1 + xi(2));
  shapefn(7) = 0.125 * (1 - xi(0)) * (1 + xi(1)) * (1 + xi(2));
  return shapefn;
}

//! Return gradient of shape functions of a 8-noded hexahedron, with particle
//! size and deformation gradient
//! \param[in] xi Coordinates of point of interest
//! \retval grad_shapefn Gradient of shape function of a given cell
template <>
inline Eigen::MatrixXd mpm::HexahedronElement<3, 8>::grad_shapefn(
    const Eigen::Matrix<double, 3, 1>& xi,
    Eigen::Matrix<double, 3, 1>& particle_size,
    const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  Eigen::Matrix<double, 8, 3> grad_shapefn;
  grad_shapefn(0, 0) = -0.125 * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(1, 0) = 0.125 * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(2, 0) = 0.125 * (1 + xi(1)) * (1 - xi(2));
  grad_shapefn(3, 0) = -0.125 * (1 + xi(1)) * (1 - xi(2));
  grad_shapefn(4, 0) = -0.125 * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(5, 0) = 0.125 * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(6, 0) = 0.125 * (1 + xi(1)) * (1 + xi(2));
  grad_shapefn(7, 0) = -0.125 * (1 + xi(1)) * (1 + xi(2));

  grad_shapefn(0, 1) = -0.125 * (1 - xi(0)) * (1 - xi(2));
  grad_shapefn(1, 1) = -0.125 * (1 + xi(0)) * (1 - xi(2));
  grad_shapefn(2, 1) = 0.125 * (1 + xi(0)) * (1 - xi(2));
  grad_shapefn(3, 1) = 0.125 * (1 - xi(0)) * (1 - xi(2));
  grad_shapefn(4, 1) = -0.125 * (1 - xi(0)) * (1 + xi(2));
  grad_shapefn(5, 1) = -0.125 * (1 + xi(0)) * (1 + xi(2));
  grad_shapefn(6, 1) = 0.125 * (1 + xi(0)) * (1 + xi(2));
  grad_shapefn(7, 1) = 0.125 * (1 - xi(0)) * (1 + xi(2));

  grad_shapefn(0, 2) = -0.125 * (1 - xi(0)) * (1 - xi(1));
  grad_shapefn(1, 2) = -0.125 * (1 + xi(0)) * (1 - xi(1));
  grad_shapefn(2, 2) = -0.125 * (1 + xi(0)) * (1 + xi(1));
  grad_shapefn(3, 2) = -0.125 * (1 - xi(0)) * (1 + xi(1));
  grad_shapefn(4, 2) = 0.125 * (1 - xi(0)) * (1 - xi(1));
  grad_shapefn(5, 2) = 0.125 * (1 + xi(0)) * (1 - xi(1));
  grad_shapefn(6, 2) = 0.125 * (1 + xi(0)) * (1 + xi(1));
  grad_shapefn(7, 2) = 0.125 * (1 - xi(0)) * (1 + xi(1));
  return grad_shapefn;
}

//! Return nodal coordinates of a unit cell
template <>
inline Eigen::MatrixXd mpm::HexahedronElement<3, 8>::unit_cell_coordinates()
    const {
  // Coordinates of a unit cell
  Eigen::Matrix<double, 8, 3> unit_cell;
  // clang-format off
  unit_cell << -1., -1., -1.,
                1., -1., -1.,
                1.,  1., -1.,
               -1.,  1., -1.,
               -1., -1.,  1.,
                1., -1.,  1.,
                1.,  1.,  1.,
    // cppcheck-suppress *
               -1.,  1.,  1.;
  // clang-format on
  return unit_cell;
}

// 20-node (Serendipity) Hexahedron Element
//!        3       13          2
//!          0_ _ _ 0 _ _ _  0
//!          /|             / |
//!      15 0 |         14 0  |
//!        /  0 9         /   |
//!     7 0_ _| _ 0 _ _ _ 0 6 0 11
//!       |   |   19     |    |
//!       |   |      8   |    |
//!       | 0 0_ _ _ 0 _ |_ _ 0  1
//!    17 0  /           0 18 /
//!       | 0 10         |  0 12
//!       |/             | /
//!       0_ _ _ 0 _ _ _ 0
//!     4        16         5

//! Return the shape function of a 20-noded hexahedron, with particle
//! size and deformation gradient
//! \param[in] xi Coordinates of point of interest
//! \retval shapefn Shape function of a given cell
template <>
inline Eigen::VectorXd mpm::HexahedronElement<3, 20>::shapefn(
    const Eigen::Matrix<double, 3, 1>& xi,
    Eigen::Matrix<double, 3, 1>& particle_size,
    const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  Eigen::Matrix<double, 20, 1> shapefn;
  shapefn(0) = -0.125 * (1 - xi(0)) * (1 - xi(1)) * (1 - xi(2)) *
               (2 + xi(0) + xi(1) + xi(2));
  shapefn(1) = -0.125 * (1 + xi(0)) * (1 - xi(1)) * (1 - xi(2)) *
               (2 - xi(0) + xi(1) + xi(2));
  shapefn(2) = -0.125 * (1 + xi(0)) * (1 + xi(1)) * (1 - xi(2)) *
               (2 - xi(0) - xi(1) + xi(2));
  shapefn(3) = -0.125 * (1 - xi(0)) * (1 + xi(1)) * (1 - xi(2)) *
               (2 + xi(0) - xi(1) + xi(2));
  shapefn(4) = -0.125 * (1 - xi(0)) * (1 - xi(1)) * (1 + xi(2)) *
               (2 + xi(0) + xi(1) - xi(2));
  shapefn(5) = -0.125 * (1 + xi(0)) * (1 - xi(1)) * (1 + xi(2)) *
               (2 - xi(0) + xi(1) - xi(2));
  shapefn(6) = -0.125 * (1 + xi(0)) * (1 + xi(1)) * (1 + xi(2)) *
               (2 - xi(0) - xi(1) - xi(2));
  shapefn(7) = -0.125 * (1 - xi(0)) * (1 + xi(1)) * (1 + xi(2)) *
               (2 + xi(0) - xi(1) - xi(2));

  shapefn(8) = 0.25 * (1 - xi(0) * xi(0)) * (1 - xi(1)) * (1 - xi(2));
  shapefn(11) = 0.25 * (1 - xi(1) * xi(1)) * (1 + xi(0)) * (1 - xi(2));
  shapefn(13) = 0.25 * (1 - xi(0) * xi(0)) * (1 + xi(1)) * (1 - xi(2));
  shapefn(9) = 0.25 * (1 - xi(1) * xi(1)) * (1 - xi(0)) * (1 - xi(2));
  shapefn(10) = 0.25 * (1 - xi(2) * xi(2)) * (1 - xi(0)) * (1 - xi(1));
  shapefn(12) = 0.25 * (1 - xi(2) * xi(2)) * (1 + xi(0)) * (1 - xi(1));
  shapefn(14) = 0.25 * (1 - xi(2) * xi(2)) * (1 + xi(0)) * (1 + xi(1));
  shapefn(15) = 0.25 * (1 - xi(2) * xi(2)) * (1 - xi(0)) * (1 + xi(1));
  shapefn(16) = 0.25 * (1 - xi(0) * xi(0)) * (1 - xi(1)) * (1 + xi(2));
  shapefn(18) = 0.25 * (1 - xi(1) * xi(1)) * (1 + xi(0)) * (1 + xi(2));
  shapefn(19) = 0.25 * (1 - xi(0) * xi(0)) * (1 + xi(1)) * (1 + xi(2));
  shapefn(17) = 0.25 * (1 - xi(1) * xi(1)) * (1 - xi(0)) * (1 + xi(2));
  return shapefn;
}

//! Return gradient of shape functions of a 20-noded hexahedron, with particle
//! size and deformation gradient
//! \param[in] xi Coordinates of point of interest
//! \retval grad_shapefn Gradient of shape function of a given cell
template <>
inline Eigen::MatrixXd mpm::HexahedronElement<3, 20>::grad_shapefn(
    const Eigen::Matrix<double, 3, 1>& xi,
    Eigen::Matrix<double, 3, 1>& particle_size,
    const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  Eigen::Matrix<double, 20, 3> grad_shapefn;

  grad_shapefn(0, 0) =
      0.125 * (2 * xi(0) + xi(1) + xi(2) + 1) * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(1, 0) =
      -0.125 * (-2 * xi(0) + xi(1) + xi(2) + 1) * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(2, 0) =
      -0.125 * (-2 * xi(0) - xi(1) + xi(2) + 1) * (1 + xi(1)) * (1 - xi(2));
  grad_shapefn(3, 0) =
      0.125 * (2 * xi(0) - xi(1) + xi(2) + 1) * (1 + xi(1)) * (1 - xi(2));
  grad_shapefn(4, 0) =
      0.125 * (2 * xi(0) + xi(1) - xi(2) + 1) * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(5, 0) =
      -0.125 * (-2 * xi(0) + xi(1) - xi(2) + 1) * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(6, 0) =
      -0.125 * (-2 * xi(0) - xi(1) - xi(2) + 1) * (1 + xi(1)) * (1 + xi(2));
  grad_shapefn(7, 0) =
      0.125 * (2 * xi(0) - xi(1) - xi(2) + 1) * (1 + xi(1)) * (1 + xi(2));
  grad_shapefn(8, 0) = -0.5 * xi(0) * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(9, 0) = -0.25 * (1 - xi(1) * xi(1)) * (1 - xi(2));
  grad_shapefn(10, 0) = -0.25 * (1 - xi(2) * xi(2)) * (1 - xi(1));
  grad_shapefn(11, 0) = 0.25 * (1 - xi(1) * xi(1)) * (1 - xi(2));
  grad_shapefn(12, 0) = 0.25 * (1 - xi(2) * xi(2)) * (1 - xi(1));
  grad_shapefn(13, 0) = -0.5 * xi(0) * (1 + xi(1)) * (1 - xi(2));
  grad_shapefn(14, 0) = 0.25 * (1 - xi(2) * xi(2)) * (1 + xi(1));
  grad_shapefn(15, 0) = -0.25 * (1 - xi(2) * xi(2)) * (1 + xi(1));
  grad_shapefn(16, 0) = -0.5 * xi(0) * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(18, 0) = 0.25 * (1 - xi(1) * xi(1)) * (1 + xi(2));
  grad_shapefn(19, 0) = -0.5 * xi(0) * (1 + xi(1)) * (1 + xi(2));
  grad_shapefn(17, 0) = -0.25 * (1 - xi(1) * xi(1)) * (1 + xi(2));

  grad_shapefn(0, 1) =
      0.125 * (xi(0) + 2 * xi(1) + xi(2) + 1) * (1 - xi(0)) * (1 - xi(2));
  grad_shapefn(1, 1) =
      0.125 * (-xi(0) + 2 * xi(1) + xi(2) + 1) * (1 + xi(0)) * (1 - xi(2));
  grad_shapefn(2, 1) =
      -0.125 * (-xi(0) - 2 * xi(1) + xi(2) + 1) * (1 + xi(0)) * (1 - xi(2));
  grad_shapefn(3, 1) =
      -0.125 * (xi(0) - 2 * xi(1) + xi(2) + 1) * (1 - xi(1)) * (1 - xi(2));
  grad_shapefn(4, 1) =
      0.125 * (xi(0) + 2 * xi(1) - xi(2) + 1) * (1 - xi(0)) * (1 + xi(2));
  grad_shapefn(5, 1) =
      0.125 * (-xi(0) + 2 * xi(1) - xi(2) + 1) * (1 + xi(0)) * (1 + xi(2));
  grad_shapefn(6, 1) =
      -0.125 * (-xi(0) - 2 * xi(1) - xi(2) + 1) * (1 + xi(0)) * (1 + xi(2));
  grad_shapefn(7, 1) =
      -0.125 * (xi(0) - 2 * xi(1) - xi(2) + 1) * (1 - xi(1)) * (1 + xi(2));
  grad_shapefn(8, 1) = -0.25 * (1 - xi(0) * xi(0)) * (1 - xi(2));
  grad_shapefn(9, 1) = -0.5 * xi(1) * (1 - xi(0)) * (1 - xi(2));
  grad_shapefn(10, 1) = -0.25 * (1 - xi(2) * xi(2)) * (1 - xi(0));
  grad_shapefn(11, 1) = -0.5 * xi(1) * (1 + xi(0)) * (1 - xi(2));
  grad_shapefn(12, 1) = -0.25 * (1 - xi(2) * xi(2)) * (1 + xi(0));
  grad_shapefn(13, 1) = 0.25 * (1 - xi(0) * xi(0)) * (1 - xi(2));
  grad_shapefn(14, 1) = 0.25 * (1 - xi(2) * xi(2)) * (1 + xi(0));
  grad_shapefn(15, 1) = 0.25 * (1 - xi(2) * xi(2)) * (1 - xi(0));
  grad_shapefn(16, 1) = -0.25 * (1 - xi(0) * xi(0)) * (1 + xi(2));
  grad_shapefn(18, 1) = -0.5 * xi(1) * (1 + xi(0)) * (1 + xi(2));
  grad_shapefn(19, 1) = 0.25 * (1 - xi(0) * xi(0)) * (1 + xi(2));
  grad_shapefn(17, 1) = -0.5 * xi(1) * (1 - xi(0)) * (1 + xi(2));

  grad_shapefn(0, 2) =
      0.125 * (xi(0) + xi(1) + 2 * xi(2) + 1) * (1 - xi(0)) * (1 - xi(1));
  grad_shapefn(1, 2) =
      0.125 * (-xi(0) + xi(1) + 2 * xi(2) + 1) * (1 + xi(0)) * (1 - xi(1));
  grad_shapefn(2, 2) =
      0.125 * (-xi(0) - xi(1) + 2 * xi(2) + 1) * (1 + xi(0)) * (1 + xi(1));
  grad_shapefn(3, 2) =
      0.125 * (xi(0) - xi(1) + 2 * xi(2) + 1) * (1 - xi(1)) * (1 + xi(1));
  grad_shapefn(4, 2) =
      -0.125 * (xi(0) + xi(1) - 2 * xi(2) + 1) * (1 - xi(0)) * (1 - xi(1));
  grad_shapefn(5, 2) =
      -0.125 * (-xi(0) + xi(1) - 2 * xi(2) + 1) * (1 + xi(0)) * (1 - xi(1));
  grad_shapefn(6, 2) =
      -0.125 * (-xi(0) - xi(1) - 2 * xi(2) + 1) * (1 + xi(0)) * (1 + xi(1));
  grad_shapefn(7, 2) =
      -0.125 * (xi(0) - xi(1) - 2 * xi(2) + 1) * (1 - xi(1)) * (1 + xi(1));
  grad_shapefn(8, 2) = -0.25 * (1 - xi(0) * xi(0)) * (1 - xi(1));
  grad_shapefn(9, 2) = -0.25 * (1 - xi(1) * xi(1)) * (1 - xi(0));
  grad_shapefn(10, 2) = -0.5 * xi(2) * (1 - xi(0)) * (1 - xi(1));
  grad_shapefn(11, 2) = -0.25 * (1 - xi(1) * xi(1)) * (1 + xi(0));
  grad_shapefn(12, 2) = -0.5 * xi(2) * (1 + xi(0)) * (1 - xi(1));
  grad_shapefn(13, 2) = -0.25 * (1 - xi(0) * xi(0)) * (1 + xi(1));
  grad_shapefn(14, 2) = -0.5 * xi(2) * (1 + xi(0)) * (1 + xi(1));
  grad_shapefn(15, 2) = -0.5 * xi(2) * (1 - xi(0)) * (1 + xi(1));
  grad_shapefn(16, 2) = 0.25 * (1 - xi(0) * xi(0)) * (1 - xi(1));
  grad_shapefn(18, 2) = 0.25 * (1 - xi(1) * xi(1)) * (1 + xi(0));
  grad_shapefn(19, 2) = 0.25 * (1 - xi(0) * xi(0)) * (1 + xi(1));
  grad_shapefn(17, 2) = 0.25 * (1 - xi(1) * xi(1)) * (1 - xi(0));
  return grad_shapefn;
}

//! Return local shape functions of a Hexahedron Element at a given local
//! coordinate, with particle size and deformation gradient
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::VectorXd mpm::HexahedronElement<Tdim, Tnfunctions>::shapefn_local(
    const Eigen::Matrix<double, Tdim, 1>& xi,
    Eigen::Matrix<double, Tdim, 1>& particle_size,
    const Eigen::Matrix<double, Tdim, Tdim>& deformation_gradient) const {
  return this->shapefn(xi, particle_size, deformation_gradient);
}

//! Compute Jacobian
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::Matrix<double, Tdim, Tdim>
    mpm::HexahedronElement<Tdim, Tnfunctions>::jacobian(
        const Eigen::Matrix<double, 3, 1>& xi,
        const Eigen::MatrixXd& nodal_coordinates,
        Eigen::Matrix<double, 3, 1>& particle_size,
        const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  // Get gradient shape functions
  const Eigen::MatrixXd grad_shapefn =
      this->grad_shapefn(xi, particle_size, deformation_gradient);
  try {
    // Check if dimensions are correct
    if ((grad_shapefn.rows() != nodal_coordinates.rows()) ||
        (xi.size() != nodal_coordinates.cols()))
      throw std::runtime_error(
          "Jacobian calculation: Incorrect dimension of xi and "
          "nodal_coordinates");
  } catch (std::exception& exception) {
    console_->error("{} #{}: {}\n", __FILE__, __LINE__, exception.what());
    return Eigen::Matrix<double, Tdim, Tdim>::Zero();
  }

  // Jacobian
  return (grad_shapefn.transpose() * nodal_coordinates);
}

//! Compute Jacobian local with particle size and deformation gradient
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::Matrix<double, Tdim, Tdim>
    mpm::HexahedronElement<Tdim, Tnfunctions>::jacobian_local(
        const Eigen::Matrix<double, 3, 1>& xi,
        const Eigen::MatrixXd& nodal_coordinates,
        Eigen::Matrix<double, 3, 1>& particle_size,
        const Eigen::Matrix<double, 3, 3>& deformation_gradient) const {
  // Jacobian dx_i/dxi_j
  return this->jacobian(xi, nodal_coordinates, particle_size,
                        deformation_gradient);
}

//! Compute Jacobian
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::MatrixXd mpm::HexahedronElement<Tdim, Tnfunctions>::dn_dx(
    const VectorDim& xi, const Eigen::MatrixXd& nodal_coordinates,
    VectorDim& particle_size, const MatrixDim& deformation_gradient) const {
  // Get gradient shape functions
  Eigen::MatrixXd grad_sf =
      this->grad_shapefn(xi, particle_size, deformation_gradient);

  // Jacobian dx_i/dxi_j
  Eigen::Matrix<double, Tdim, Tdim> jacobian =
      (grad_sf.transpose() * nodal_coordinates);

  // Gradient shapefn of the cell
  // dN/dx = [J]^-1 * dN/dxi
  return grad_sf * (jacobian.inverse()).transpose();
}

//! Compute Bmatrix
template <unsigned Tdim, unsigned Tnfunctions>
inline std::vector<Eigen::MatrixXd>
    mpm::HexahedronElement<Tdim, Tnfunctions>::bmatrix(
        const VectorDim& xi, const Eigen::MatrixXd& nodal_coordinates,
        VectorDim& particle_size, const MatrixDim& deformation_gradient) const {
  // Get gradient shape functions
  Eigen::MatrixXd grad_sf =
      this->grad_shapefn(xi, particle_size, deformation_gradient);

  // B-Matrix
  std::vector<Eigen::MatrixXd> bmatrix;
  bmatrix.reserve(Tnfunctions);

  try {
    // Check if matrices dimensions are correct
    if ((grad_sf.rows() != nodal_coordinates.rows()) ||
        (xi.rows() != nodal_coordinates.cols()))
      throw std::runtime_error(
          "BMatrix - Jacobian calculation: Incorrect dimension of xi and "
          "nodal_coordinates");
  } catch (std::exception& exception) {
    console_->error("{} #{}: {}\n", __FILE__, __LINE__, exception.what());
    return bmatrix;
  }

  // Jacobian dx_i/dxi_j
  Eigen::Matrix<double, Tdim, Tdim> jacobian =
      (grad_sf.transpose() * nodal_coordinates);

  // Gradient shapefn of the cell
  // dN/dx = [J]^-1 * dN/dxi
  Eigen::MatrixXd grad_shapefn = grad_sf * (jacobian.inverse()).transpose();

  for (unsigned i = 0; i < Tnfunctions; ++i) {
    // clang-format off
    Eigen::Matrix<double, 6, Tdim> bi;
    bi(0, 0) = grad_shapefn(i, 0); bi(0, 1) = 0.;                 bi(0, 2) = 0.;
    bi(1, 0) = 0.;                 bi(1, 1) = grad_shapefn(i, 1); bi(1, 2) = 0.;
    bi(2, 0) = 0.;                 bi(2, 1) = 0.;                 bi(2, 2) = grad_shapefn(i, 2);
    bi(3, 0) = grad_shapefn(i, 1); bi(3, 1) = grad_shapefn(i, 0); bi(3, 2) = 0.;
    bi(4, 0) = 0.;                 bi(4, 1) = grad_shapefn(i, 2); bi(4, 2) = grad_shapefn(i, 1);
    bi(5, 0) = grad_shapefn(i, 2); bi(5, 1) = 0.;                 bi(5, 2) = grad_shapefn(i, 0);
    // clang-format on
    bmatrix.push_back(bi);
  }
  return bmatrix;
}

//! Return ni_nj_matrix of a Hexahedron Element
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::MatrixXd mpm::HexahedronElement<Tdim, Tnfunctions>::ni_nj_matrix(
    const std::vector<VectorDim>& xi_s) const {
  // Zeros
  Eigen::Matrix<double, Tdim, 1> zeros = Eigen::Matrix<double, Tdim, 1>::Zero();
  Eigen::Matrix<double, Tdim, Tdim> zero_matrix =
      Eigen::Matrix<double, Tdim, Tdim>::Zero();

  // Ni Nj matrix
  Eigen::Matrix<double, Tnfunctions, Tnfunctions> ni_nj_matrix;
  ni_nj_matrix.setZero();
  for (const auto& xi : xi_s) {
    const Eigen::Matrix<double, Tnfunctions, 1> shape_fn =
        this->shapefn(xi, zeros, zero_matrix);
    ni_nj_matrix.noalias() += (shape_fn * shape_fn.transpose());
  }
  return ni_nj_matrix;
}

//! Return the laplace_matrix of a Hexahedron Element
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::MatrixXd
    mpm::HexahedronElement<Tdim, Tnfunctions>::laplace_matrix(
        const std::vector<VectorDim>& xi_s,
        const Eigen::MatrixXd& nodal_coordinates) const {

  try {
    // Check if matrices dimensions are correct
    if ((this->nfunctions() != nodal_coordinates.rows()) ||
        (xi_s.at(0).size() != nodal_coordinates.cols()))
      throw std::runtime_error(
          "Jacobian calculation: Incorrect dimension of xi & nodes");
  } catch (std::exception& exception) {
    console_->error("{} #{}: {}\n", __FILE__, __LINE__, exception.what());
  }

  // Zeros
  Eigen::Matrix<double, Tdim, 1> zeros = Eigen::Matrix<double, Tdim, 1>::Zero();
  Eigen::Matrix<double, Tdim, Tdim> zero_matrix =
      Eigen::Matrix<double, Tdim, Tdim>::Zero();

  // Laplace matrix
  Eigen::Matrix<double, Tnfunctions, Tnfunctions> laplace_matrix;
  laplace_matrix.setZero();
  for (const auto& xi : xi_s) {
    // Get gradient shape functions
    const Eigen::MatrixXd grad_sf = this->grad_shapefn(xi, zeros, zero_matrix);

    // Jacobian dx_i/dxi_j
    const Eigen::Matrix<double, Tdim, Tdim> jacobian =
        (grad_sf.transpose() * nodal_coordinates);

    // Gradient shapefn of the cell
    // dN/dx = [J]^-1 * dN/dxi
    const Eigen::MatrixXd grad_shapefn = grad_sf * jacobian.inverse();

    laplace_matrix.noalias() += (grad_shapefn * grad_shapefn.transpose());
  }
  return laplace_matrix;
}

//! Return the degree of element
//! 8-noded hexahedron
template <>
inline mpm::ElementDegree mpm::HexahedronElement<3, 8>::degree() const {
  return mpm::ElementDegree::Linear;
}

//! Return the degree of shape function
//! 8-noded hexahedron
template <>
inline mpm::ElementDegree mpm::HexahedronElement<3, 20>::degree() const {
  return mpm::ElementDegree::Quadratic;
}

//! Return nodal coordinates of a unit cell
template <>
inline Eigen::MatrixXd mpm::HexahedronElement<3, 20>::unit_cell_coordinates()
    const {
  // Coordinates of a unit cell
  Eigen::Matrix<double, 20, 3> unit_cell;
  // clang-format off
  unit_cell << -1., -1., -1.,
                1., -1., -1.,
                1.,  1., -1.,
               -1.,  1., -1.,
               -1., -1.,  1.,
                1., -1.,  1.,
                1.,  1.,  1.,
               -1.,  1.,  1.,
                0., -1., -1.,
               -1.,  0., -1.,
               -1., -1.,  0.,
                1.,  0., -1.,
                1., -1.,  0.,
                0.,  1., -1.,
                1.,  1.,  0.,
               -1.,  1.,  0.,
                0., -1.,  1.,
               -1.,  0.,  1.,
                1.,  0.,  1.,
    // cppcheck-suppress *
                0.,  1.,  1.;
  // clang-format on
  return unit_cell;
}

// 27-node (Triquadratic) Hexahedron Element
//! Check with GMSH
//!          7           18             6
//!            0_ _ _ _ _ 0 _ _ _ _ _ 0
//!            /|                     /|
//!           / |                    / |
//!          /  |    25             /  |
//!      19 0   |     0         17 0   |
//!        /    |      23 0       /    |
//!       /  15 0                /     0 14
//!      /      |               /      |
//!  4  0_ _ _ _|_ 0 _ _ _ _ _ 0 5     |
//!     |       | 16           |       |
//!     |  0 24 |              |   0 22|
//!     |       |          8   |       |
//!     |     0 0_ _ _ _ _ 0_ _|_ _ _  0  1
//!     |      /               |      /
//!  17 0     /    0 25        0 18  /
//!     |    /                 |    /
//!     |10 0         0        |   0 12
//!     |  /         21        |  /
//!     | /                    | /
//!     |/                     |/
//!     0_ _ _ _ _ 0 _ _ _ _ _ 0
//!   4           16            5

//! Return the indices of a cell sides
//! \retval indices Sides that form the cell
//! \tparam Tdim Dimension
//! \tparam Tnfunctions Number of shape functions
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::MatrixXi
    mpm::HexahedronElement<Tdim, Tnfunctions>::sides_indices() const {
  Eigen::Matrix<int, 12, 2> indices;
  // clang-format off
  indices << 0, 1,
             1, 2,
             2, 3,
             3, 0,
             4, 5,
             5, 6,
             6, 7,
             7, 4,
             0, 4,
             1, 5,
             2, 6,
    // cppcheck-suppress *
             3, 7;
  // clang-format on
  return indices;
}

//! Return the corner indices of a cell to calculate the cell volume
//! \retval indices Outer-indices that form the cell
//! \tparam Tdim Dimension
//! \tparam Tnfunctions Number of shape functions
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::VectorXi
    mpm::HexahedronElement<Tdim, Tnfunctions>::corner_indices() const {
  Eigen::Matrix<int, 8, 1> indices;
  // cppcheck-suppress *
  indices << 0, 1, 2, 3, 4, 5, 6, 7;
  return indices;
}

//! Return indices of a face of the element
//! 8-noded hexahedron
template <>
inline Eigen::VectorXi mpm::HexahedronElement<3, 8>::face_indices(
    unsigned face_id) const {

  //! Face ids and its associated nodal indices
  const std::map<unsigned, Eigen::Matrix<int, 4, 1>> face_indices_hexahedron{
      {0, Eigen::Matrix<int, 4, 1>(0, 1, 5, 4)},
      {1, Eigen::Matrix<int, 4, 1>(5, 1, 2, 6)},
      {2, Eigen::Matrix<int, 4, 1>(7, 6, 2, 3)},
      {3, Eigen::Matrix<int, 4, 1>(0, 4, 7, 3)},
      {4, Eigen::Matrix<int, 4, 1>(1, 0, 3, 2)},
      {5, Eigen::Matrix<int, 4, 1>(4, 5, 6, 7)}};

  return face_indices_hexahedron.at(face_id);
}

//! Return indices of a face of the element
//! 20-noded hexahedron
template <>
inline Eigen::VectorXi mpm::HexahedronElement<3, 20>::face_indices(
    unsigned face_id) const {

  //! Face ids and its associated nodal indices
  // clang-format off
  const std::map<unsigned, Eigen::Matrix<int, 8, 1>> face_indices_hexahedron{
      {0, (Eigen::Matrix<int, 8, 1>() << 0, 1, 5, 4,  8, 12, 16, 10).finished()},
      {1, (Eigen::Matrix<int, 8, 1>() << 5, 1, 2, 6, 12, 11, 14, 18).finished()},
      {2, (Eigen::Matrix<int, 8, 1>() << 7, 6, 2, 3, 19, 14, 13, 15).finished()},
      {3, (Eigen::Matrix<int, 8, 1>() << 0, 4, 7, 3, 10, 17, 15,  9).finished()},
      {4, (Eigen::Matrix<int, 8, 1>() << 1, 0, 3, 2,  8,  9, 13, 11).finished()},
      {5, (Eigen::Matrix<int, 8, 1>() << 4, 5, 6, 7, 16, 18, 19, 17).finished()}};
  // clang-format on

  return face_indices_hexahedron.at(face_id);
}

//! Return quadrature
template <unsigned Tdim, unsigned Tnfunctions>
inline std::shared_ptr<mpm::Quadrature<Tdim>>
    mpm::HexahedronElement<Tdim, Tnfunctions>::quadrature(
        unsigned nquadratures) const {
  switch (nquadratures) {
    case 1:
      return Factory<mpm::Quadrature<Tdim>>::instance()->create("QHEX1");
      break;
    case 2:
      return Factory<mpm::Quadrature<Tdim>>::instance()->create("QHEX2");
      break;
    case 3:
      return Factory<mpm::Quadrature<Tdim>>::instance()->create("QHEX3");
      break;
    case 4:
      return Factory<mpm::Quadrature<Tdim>>::instance()->create("QHEX4");
      break;
    default:
      return Factory<mpm::Quadrature<Tdim>>::instance()->create("QHEX1");
      break;
  }
}

//! Compute volume
//! \param[in] nodal_coordinates Coordinates of nodes forming the cell
//! \retval volume Return the volume of cell
template <unsigned Tdim, unsigned Tnfunctions>
inline double mpm::HexahedronElement<Tdim, Tnfunctions>::compute_volume(
    const Eigen::MatrixXd& nodal_coordinates) const {
  // Node numbering as read in by mesh file
  //        d               c
  //          *_ _ _ _ _ _*
  //         /|           /|
  //        / |          / |
  //     a *_ |_ _ _ _ _* b|
  //       |  |         |  |
  //       |  |         |  |
  //       |  *_ _ _ _ _|_ *
  //       | / h        | / g
  //       |/           |/
  //       *_ _ _ _ _ _ *
  //     e               f
  //
  // Calculation of hexahedron volume from
  // https://arc.aiaa.org/doi/pdf/10.2514/3.9013

  const Eigen::Matrix<double, Tdim, 1> a = nodal_coordinates.row(7);
  const Eigen::Matrix<double, Tdim, 1> b = nodal_coordinates.row(6);
  const Eigen::Matrix<double, Tdim, 1> c = nodal_coordinates.row(2);
  const Eigen::Matrix<double, Tdim, 1> d = nodal_coordinates.row(3);
  const Eigen::Matrix<double, Tdim, 1> e = nodal_coordinates.row(4);
  const Eigen::Matrix<double, Tdim, 1> f = nodal_coordinates.row(5);
  const Eigen::Matrix<double, Tdim, 1> g = nodal_coordinates.row(1);
  const Eigen::Matrix<double, Tdim, 1> h = nodal_coordinates.row(0);

  const double volume =
      (1.0 / 12) * (a - g).dot(((b - d).cross(c - a)) + ((e - b).cross(f - a)) +
                               ((d - e).cross(h - a))) +
      (1.0 / 12) *
          (b - g).dot(((b - d).cross(c - a)) + ((c - g).cross(c - f))) +
      (1.0 / 12) *
          (e - g).dot(((e - b).cross(f - a)) + ((f - g).cross(h - f))) +
      (1.0 / 12) * (d - g).dot(((d - e).cross(h - a)) + ((h - g).cross(h - c)));

  return volume;
}

//! Compute natural coordinates of a point (analytical)
template <unsigned Tdim, unsigned Tnfunctions>
inline Eigen::Matrix<double, Tdim, 1>
    mpm::HexahedronElement<Tdim, Tnfunctions>::natural_coordinates_analytical(
        const VectorDim& point,
        const Eigen::MatrixXd& nodal_coordinates) const {
  // Local point coordinates
  Eigen::Matrix<double, Tdim, 1> xi;
  xi.fill(std::numeric_limits<double>::max());
  throw std::runtime_error(
      "Analytical solution for Hex<Tdim, Tnfunctions> has not been "
      "implemented");
  return xi;
}

//! Assign nodal connectivity property for bspline elements
template <unsigned Tdim, unsigned Tnfunctions>
void mpm::HexahedronElement<Tdim, Tnfunctions>::
    initialise_bspline_connectivity_properties(
        const Eigen::MatrixXd& nodal_coordinates,
        const std::vector<std::vector<unsigned>>& nodal_properties) {
  throw std::runtime_error(
      "Function to initialise bspline connectivity is not implemented for "
      "Hex<Tdim, Tnfunctions> ");
}

//! Assign nodal connectivity property for LME elements
template <unsigned Tdim, unsigned Tnfunctions>
void mpm::HexahedronElement<Tdim, Tnfunctions>::
    initialise_lme_connectivity_properties(
        double beta, double radius, bool anisotropy,
        const Eigen::MatrixXd& nodal_coordinates) {
  throw std::runtime_error(
      "Function to initialise lme connectivity is not implemented for "
      "Hex<Tdim, Tnfunctions> ");
}

#ifndef MPM_HEXAHEDRON_ELEMENT_H_
#define MPM_HEXAHEDRON_ELEMENT_H_

#include "element.h"
#include "logger.h"

//! MPM namespace
namespace mpm {

//! Hexahedron element class derived from Element class
//! \brief Hexahedron element
//! \details 8-noded and 20-noded hexahedron element \n
//! Shape function, gradient shape function, B-matrix, indices \n
//! 8-node (Trilinear) Hexahedron Element \n
//! <pre>
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
//!
//!
//! </pre>
//! 20-node (Serendipity) Hexahedron Element \n
//! <pre>
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
//!
//! </pre>
//!
//! 27-node (Triquadratic) Hexahedron Element \n
//! Check with GMSH \n
//! <pre>
//!          3           13             2
//!            0_ _ _ _ _ 0 _ _ _ _ _ 0
//!            /|                     /|
//!           / |                    / |
//!          /  |    24             /  |
//!      15 0   |     0         14 0   |
//!        /    |      20 0       /    |
//!       /   9 0                /     0 11
//!      /      |               /      |
//!  7  0_ _ _ _|_ 0 _ _ _ _ _ 0 6     |
//!     |       | 19           |       |
//!     |  0 22 |              |   0 23|
//!     |       |    0 26  8   |       |
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
//!
//!
//! </pre>
//!
//! Face numbering for 8-node, 20-node and 27-node Hexaheron Element \n
//!
//! <pre>
//!            Behind: F4
//!        3      F2       2
//!          0_ _ _ _ _ _0
//!         /|           /|
//!        / |          / |
//!     7 0_ |_ _ _ _ _0 6|
//!       |  |         |  |
//!    F3 |  |         |  |   F1
//!       |  0_ _ _ _ _|_ 0
//!       | / 0        | / 1
//!       |/     F0    |/
//!       0_ _ _ _ _ _ 0
//!     4               5
//!         Front: F5
//!
//!
//! Bottom face: F0, Right face: F1, Top face: F2,
//! Left face: F3, Rear face: F4, Front face: F5
//! </pre>
//!
//! \tparam Tdim Dimension
//! \tparam Tnfunctions Number of functions
template <unsigned Tdim, unsigned Tnfunctions>
class HexahedronElement : public Element<Tdim> {

 public:
  //! Define a vector of size dimension
  using VectorDim = Eigen::Matrix<double, Tdim, 1>;

  //! Define a matrix of size dimension
  using MatrixDim = Eigen::Matrix<double, Tdim, Tdim>;

  //! constructor with number of shape functions
  HexahedronElement() : mpm::Element<Tdim>() {
    static_assert(Tdim == 3, "Invalid dimension for a hexahedron element");
    static_assert((Tnfunctions == 8 || Tnfunctions == 20),
                  "Specified number of shape functions is not defined");
    //! Logger
    std::string logger = "hexahedron::<" + std::to_string(Tdim) + ", " +
                         std::to_string(Tnfunctions) + ">";
    console_ = std::make_unique<spdlog::logger>(logger, mpm::stdout_sink);
  }

  //! Return number of functions
  unsigned nfunctions() const override { return Tnfunctions; }

  //! Evaluate shape functions at given local coordinates
  //! \param[in] xi given local coordinates
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval shapefn Shape function of a given cell
  Eigen::VectorXd shapefn(const VectorDim& xi, VectorDim& particle_size,
                          const MatrixDim& deformation_gradient) const override;

  //! Evaluate local shape functions at given local coordinates
  //! \param[in] xi given local coordinates
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval shapefn Shape function of a given cell
  Eigen::VectorXd shapefn_local(
      const VectorDim& xi, VectorDim& particle_size,
      const MatrixDim& deformation_gradient) const override;

  //! Evaluate gradient of shape functions
  //! \param[in] xi given local coordinates
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval grad_shapefn Gradient of shape function of a given cell
  Eigen::MatrixXd grad_shapefn(
      const VectorDim& xi, VectorDim& particle_size,
      const MatrixDim& deformation_gradient) const override;

  //! Compute Jacobian
  //! \param[in] xi given local coordinates
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval jacobian Jacobian matrix
  Eigen::Matrix<double, Tdim, Tdim> jacobian(
      const Eigen::Matrix<double, 3, 1>& xi,
      const Eigen::MatrixXd& nodal_coordinates,
      Eigen::Matrix<double, 3, 1>& particle_size,
      const Eigen::Matrix<double, 3, 3>& deformation_gradient) const override;

  //! Compute Jacobian local
  //! \param[in] xi given local coordinates
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval jacobian Jacobian matrix
  Eigen::Matrix<double, Tdim, Tdim> jacobian_local(
      const Eigen::Matrix<double, 3, 1>& xi,
      const Eigen::MatrixXd& nodal_coordinates,
      Eigen::Matrix<double, 3, 1>& particle_size,
      const Eigen::Matrix<double, 3, 3>& deformation_gradient) const override;

  //! Return the dN/dx at a given local coord
  //! \param[in] xi given local coordinates
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  Eigen::MatrixXd dn_dx(const VectorDim& xi,
                        const Eigen::MatrixXd& nodal_coordinates,
                        VectorDim& particle_size,
                        const MatrixDim& deformation_gradient) const override;

  //! Evaluate the B matrix at given local coordinates for a real cell
  //! \param[in] xi given local coordinates
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] particle_size Particle size
  //! \param[in] deformation_gradient Deformation gradient
  //! \retval bmatrix B matrix
  std::vector<Eigen::MatrixXd> bmatrix(
      const VectorDim& xi, const Eigen::MatrixXd& nodal_coordinates,
      VectorDim& particle_size,
      const MatrixDim& deformation_gradient) const override;

  //! Evaluate the Ni Nj matrix
  //! \param[in] xi_s Vector of local coordinates
  //! \retval ni_nj_matrix Ni Nj matrix
  Eigen::MatrixXd ni_nj_matrix(
      const std::vector<VectorDim>& xi_s) const override;

  //! Evaluate the Laplace matrix at given local coordinates for a real cell
  //! \param[in] xi_s Vector of local coordinates
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \retval laplace_matrix Laplace matrix
  Eigen::MatrixXd laplace_matrix(
      const std::vector<VectorDim>& xi_s,
      const Eigen::MatrixXd& nodal_coordinates) const override;

  //! Return the degree of shape function
  mpm::ElementDegree degree() const override;

  //! Return the type of shape function
  mpm::ShapefnType shapefn_type() const override {
    return mpm::ShapefnType::NORMAL_MPM;
  }

  //! Return nodal coordinates of a unit cell
  Eigen::MatrixXd unit_cell_coordinates() const override;

  //! Return the side indices of a cell to calculate the cell length
  //! \retval indices Outer-indices that form the sides of the cell
  Eigen::MatrixXi sides_indices() const override;

  //! Return the corner indices of a cell to calculate the cell volume
  //! \retval indices Outer-indices that form the cell
  Eigen::VectorXi corner_indices() const override;

  //! Return indices of a face of an element
  //! \param[in] face_id given id of the face
  //! \retval indices Indices that make the face
  Eigen::VectorXi face_indices(unsigned face_id) const override;

  //! Return the number of faces in a hexahedron
  unsigned nfaces() const override { return 6; }

  //! Return unit element length
  double unit_element_length() const override { return 2.; }

  //! Return quadrature of the element
  std::shared_ptr<mpm::Quadrature<Tdim>> quadrature(
      unsigned nquadratures = 1) const override;

  //! Compute volume
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \retval volume Return the volume of cell
  double compute_volume(
      const Eigen::MatrixXd& nodal_coordinates) const override;

  //! Return if natural coordinates can be evaluates
  bool isvalid_natural_coordinates_analytical() const override { return false; }

  //! Compute Natural coordinates of a point (analytical)
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] point Location of the point in cell
  //! \retval xi Return the local coordinates
  VectorDim natural_coordinates_analytical(
      const VectorDim& point,
      const Eigen::MatrixXd& nodal_coordinates) const override;

  //! Assign nodal connectivity property for bspline elements
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  //! \param[in] nodal_properties Vector determining node type for each
  //! dimension
  void initialise_bspline_connectivity_properties(
      const Eigen::MatrixXd& nodal_coordinates,
      const std::vector<std::vector<unsigned>>& nodal_properties) override;

  //! Assign nodal connectivity property for LME elements
  //! \param[in] beta Coldness function of the system in the range of [0,inf)
  //! \param[in] radius Support radius of the kernel
  //! \param[in] anisotropy Shape function anisotropy (F^{-T}F^{-1})
  //! \param[in] nodal_coordinates Coordinates of nodes forming the cell
  void initialise_lme_connectivity_properties(
      double beta, double radius, bool anisotropy,
      const Eigen::MatrixXd& nodal_coordinates) override;

 private:
  //! Logger
  std::unique_ptr<spdlog::logger> console_;
};

}  // namespace mpm
#include "hexahedron_element.tcc"

#endif  // MPM_HEXAHEDRON_ELEMENT_H_

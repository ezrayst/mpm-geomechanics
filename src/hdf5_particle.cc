#include "hdf5_particle.h"
namespace mpm {
namespace hdf5 {
namespace particle {
const size_t dst_offset[NFIELDS] = {
    HOFFSET(HDF5Particle, id),
    HOFFSET(HDF5Particle, mass),
    HOFFSET(HDF5Particle, volume),
    HOFFSET(HDF5Particle, pressure),
    HOFFSET(HDF5Particle, coord_x),
    HOFFSET(HDF5Particle, coord_y),
    HOFFSET(HDF5Particle, coord_z),
    HOFFSET(HDF5Particle, displacement_x),
    HOFFSET(HDF5Particle, displacement_y),
    HOFFSET(HDF5Particle, displacement_z),
    HOFFSET(HDF5Particle, nsize_x),
    HOFFSET(HDF5Particle, nsize_y),
    HOFFSET(HDF5Particle, nsize_z),
    HOFFSET(HDF5Particle, velocity_x),
    HOFFSET(HDF5Particle, velocity_y),
    HOFFSET(HDF5Particle, velocity_z),
    HOFFSET(HDF5Particle, acceleration_x),
    HOFFSET(HDF5Particle, acceleration_y),
    HOFFSET(HDF5Particle, acceleration_z),
    HOFFSET(HDF5Particle, stress_xx),
    HOFFSET(HDF5Particle, stress_yy),
    HOFFSET(HDF5Particle, stress_zz),
    HOFFSET(HDF5Particle, tau_xy),
    HOFFSET(HDF5Particle, tau_yz),
    HOFFSET(HDF5Particle, tau_xz),
    HOFFSET(HDF5Particle, strain_xx),
    HOFFSET(HDF5Particle, strain_yy),
    HOFFSET(HDF5Particle, strain_zz),
    HOFFSET(HDF5Particle, gamma_xy),
    HOFFSET(HDF5Particle, gamma_yz),
    HOFFSET(HDF5Particle, gamma_xz),
    HOFFSET(HDF5Particle, epsilon_v),
    HOFFSET(HDF5Particle, status),
    HOFFSET(HDF5Particle, cell_id),
    HOFFSET(HDF5Particle, material_id),
    HOFFSET(HDF5Particle, nstate_vars),
    HOFFSET(HDF5Particle, svars[0]),
    HOFFSET(HDF5Particle, svars[1]),
    HOFFSET(HDF5Particle, svars[2]),
    HOFFSET(HDF5Particle, svars[3]),
    HOFFSET(HDF5Particle, svars[4]),
    HOFFSET(HDF5Particle, svars[5]),
    HOFFSET(HDF5Particle, svars[6]),
    HOFFSET(HDF5Particle, svars[7]),
    HOFFSET(HDF5Particle, svars[8]),
    HOFFSET(HDF5Particle, svars[9]),
    HOFFSET(HDF5Particle, svars[10]),
    HOFFSET(HDF5Particle, svars[11]),
    HOFFSET(HDF5Particle, svars[12]),
    HOFFSET(HDF5Particle, svars[13]),
    HOFFSET(HDF5Particle, svars[14]),
    HOFFSET(HDF5Particle, svars[15]),
    HOFFSET(HDF5Particle, svars[16]),
    HOFFSET(HDF5Particle, svars[17]),
    HOFFSET(HDF5Particle, svars[18]),
    HOFFSET(HDF5Particle, svars[19]),
};

// Get size of particle
HDF5Particle particle;
const size_t dst_sizes[NFIELDS] = {
    sizeof(particle.id),
    sizeof(particle.mass),
    sizeof(particle.volume),
    sizeof(particle.pressure),
    sizeof(particle.coord_x),
    sizeof(particle.coord_y),
    sizeof(particle.coord_z),
    sizeof(particle.displacement_x),
    sizeof(particle.displacement_y),
    sizeof(particle.displacement_z),
    sizeof(particle.nsize_x),
    sizeof(particle.nsize_y),
    sizeof(particle.nsize_z),
    sizeof(particle.velocity_x),
    sizeof(particle.velocity_y),
    sizeof(particle.velocity_z),
    sizeof(particle.acceleration_x),
    sizeof(particle.acceleration_y),
    sizeof(particle.acceleration_z),
    sizeof(particle.stress_xx),
    sizeof(particle.stress_yy),
    sizeof(particle.stress_zz),
    sizeof(particle.tau_xy),
    sizeof(particle.tau_yz),
    sizeof(particle.tau_xz),
    sizeof(particle.strain_xx),
    sizeof(particle.strain_yy),
    sizeof(particle.strain_zz),
    sizeof(particle.gamma_xy),
    sizeof(particle.gamma_yz),
    sizeof(particle.gamma_xz),
    sizeof(particle.epsilon_v),
    sizeof(particle.status),
    sizeof(particle.cell_id),
    sizeof(particle.material_id),
    sizeof(particle.nstate_vars),
    sizeof(particle.svars[0]),
    sizeof(particle.svars[1]),
    sizeof(particle.svars[2]),
    sizeof(particle.svars[3]),
    sizeof(particle.svars[4]),
    sizeof(particle.svars[5]),
    sizeof(particle.svars[6]),
    sizeof(particle.svars[7]),
    sizeof(particle.svars[8]),
    sizeof(particle.svars[9]),
    sizeof(particle.svars[10]),
    sizeof(particle.svars[11]),
    sizeof(particle.svars[12]),
    sizeof(particle.svars[13]),
    sizeof(particle.svars[14]),
    sizeof(particle.svars[15]),
    sizeof(particle.svars[16]),
    sizeof(particle.svars[17]),
    sizeof(particle.svars[18]),
    sizeof(particle.svars[19]),
};

// Define particle field information
const char* field_names[NFIELDS] = {
    "id",
    "mass",
    "volume",
    "pressure",
    "coord_x",
    "coord_y",
    "coord_z",
    "displacement_x",
    "displacement_y",
    "displacement_z",
    "nsize_x",
    "nsize_y",
    "nsize_z",
    "velocity_x",
    "velocity_y",
    "velocity_z",
    "acceleration_x",
    "acceleration_y",
    "acceleration_z",
    "stress_xx",
    "stress_yy",
    "stress_zz",
    "tau_xy",
    "tau_yz",
    "tau_xz",
    "strain_xx",
    "strain_yy",
    "strain_zz",
    "gamma_xy",
    "gamma_yz",
    "gamma_xz",
    "epsilon_v",
    "status",
    "cell_id",
    "material_id",
    "nstate_vars",
    "svars_0",
    "svars_1",
    "svars_2",
    "svars_3",
    "svars_4",
    "svars_5",
    "svars_6",
    "svars_7",
    "svars_8",
    "svars_9",
    "svars_10",
    "svars_11",
    "svars_12",
    "svars_13",
    "svars_14",
    "svars_15",
    "svars_16",
    "svars_17",
    "svars_18",
    "svars_19",
};

// Initialize field types
const hid_t field_type[NFIELDS] = {
    H5T_NATIVE_LLONG,  H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_HBOOL,  H5T_NATIVE_LLONG,  H5T_NATIVE_UINT,
    H5T_NATIVE_UINT,   H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE, H5T_NATIVE_DOUBLE,
    H5T_NATIVE_DOUBLE};
}  // namespace particle
}  // namespace hdf5
}  // namespace mpm

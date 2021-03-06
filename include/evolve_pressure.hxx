#pragma once
#ifndef EVOLVE_PRESSURE_H
#define EVOLVE_PRESSURE_H

#include <field3d.hxx>

#include "component.hxx"

struct EvolvePressure : public Component {
  EvolvePressure(std::string name, Options &options, Solver *solver);

  /// Sets
  /// - species
  ///   - <name>
  ///     - pressure
  ///     - temperature   Requires density
  ///
  void transform(Options &state) override;

  ///
  /// Optional inputs
  ///
  /// - species
  ///   - <name>
  ///     - velocity. Must have sound_speed or temperature
  ///     - energy_source
  ///     - collision_rate  (needed if thermal_conduction on)
  /// - fields
  ///   - phi      Electrostatic potential -> ExB drift
  /// 
  void finally(const Options &state) override;
private:
  std::string name; // Short name of the species e.g. h+
  
  Field3D P;     // Pressure (normalised) 
  Field3D T, N;  // Temperature, density

  bool bndry_flux;
  bool poloidal_flows;
  bool thermal_conduction;
};

namespace {
RegisterComponent<EvolvePressure> registercomponentevolvepressure("evolve_pressure");
}

#endif // EVOLVE_PRESSURE_H


# PHT-106 — Lab Exam (Charged Particle Spectroscopy)

Geant4 simulations submitted for the lab examination of **PHT-106 — Experimental Techniques in Charged Particle Spectroscopy**.

| Field             | Value                                  |
|-------------------|----------------------------------------|
| Name              | Daksh Pandey                           |
| Enrollment No.    | 23123013                               |
| Branch            | B.Tech (Engineering Physics)           |
| Course            | PHT-106 — Experimental Techniques in Charged Particle Spectroscopy |
| Course Coordinator| Prof. Anil Kumar Gourishetty           |
| Institute         | Indian Institute of Technology Roorkee |

## Problems

Each problem is a self-contained Geant4 project with its own `src/`, `include/`, `main.cc`, run macros, plotting script, and README documenting geometry, run instructions, and results.

### [Problem 1 — Cs-137 Beta Deposition in NaI(Tl)](problem_1/README.md)

Energy deposition of Cs-137 β⁻ particles in a 1″ × 1″ cylindrical NaI crystal, with and without a 0.5 mm aluminium casing. Source 5 mm from the crystal front face. Compares interaction fraction and mean energy deposit per event between the two configurations.

### [Problem 2 — Bragg Curves of 4–8 MeV Alphas](problem_2/README.md)

Bragg (energy-deposition vs depth) curves for monoenergetic alpha particles at 4, 5, 6, 7, and 8 MeV in two absorbers — air (100 mm) and silicon (80 µm). Five curves per material, with a finite step-size cap inside the absorber so the Bragg peak is well-resolved.

### [Problem 3 — Spectrum of a Mixed 4–8 MeV Alpha Source](problem_3/README.md)

Energy spectrum recorded by a 100 µm silicon detector placed 10 mm in air from a point source emitting equally at 4, 5, 6, 7, and 8 MeV. ≈ 10⁵ events per source line, producing five Gaussian-like peaks shifted below the source energies by air loss.

## Building Any Problem

Every problem follows the same build pattern:

```bash
cd problem_N
mkdir -p build && cd build
cmake ..
make -j$(nproc)
./problem_N <macro>
```

Geant4 11.4.0 with the `FTFP_BERT` reference list and `G4EmStandardPhysics_option4` is used throughout. Plotting uses Python (`numpy`, `pandas`, `matplotlib`).

## Repository Layout

```
lab_exam/
├── README.md           — this file
├── problem_1/          — Cs-137 β⁻ in NaI ± Al casing
├── problem_2/          — Bragg curves in air and silicon
└── problem_3/          — mixed 4–8 MeV α source spectrum
```

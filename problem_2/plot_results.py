from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

here = Path(__file__).parent
results = here / "results"
results.mkdir(exist_ok=True)

energies = [4, 5, 6, 7, 8]


def load(material, energy):
    path = results / f"bragg_{material}_{energy}MeV.csv"
    df = pd.read_csv(path, comment="#", header=None,
                     names=["depth_mm", "edep_keV"])
    return df["depth_mm"].to_numpy(), df["edep_keV"].to_numpy()


def plot_set(material, depth_unit_label, depth_scale, title, fname):
    fig, ax = plt.subplots(figsize=(9, 5.5))
    cmap = plt.cm.viridis(np.linspace(0.1, 0.85, len(energies)))
    for color, e in zip(cmap, energies):
        depth_mm, edep = load(material, e)
        ax.plot(depth_mm * depth_scale, edep, color=color,
                linewidth=1.4, label=f"{e} MeV")
    ax.set_xlabel(f"Depth in {material.replace('si', 'Si').replace('air', 'Air')}"
                  f" [{depth_unit_label}]")
    ax.set_ylabel("Energy deposited per primary [keV / bin]")
    ax.set_title(title)
    ax.legend(title=r"$\alpha$ energy")
    ax.grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig(results / fname, dpi=150)
    plt.close(fig)


plot_set("air", "mm", 1.0,
         r"Bragg Curves of $\alpha$ Particles in Air",
         "bragg_air.png")

plot_set("si", r"$\mu$m", 1000.0,
         r"Bragg Curves of $\alpha$ Particles in Silicon",
         "bragg_si.png")

fig, axes = plt.subplots(1, 2, figsize=(13, 5))
cmap = plt.cm.viridis(np.linspace(0.1, 0.85, len(energies)))

for color, e in zip(cmap, energies):
    d, edep = load("air", e)
    axes[0].plot(d, edep, color=color, linewidth=1.4, label=f"{e} MeV")
axes[0].set_xlabel("Depth in Air [mm]")
axes[0].set_ylabel("Energy deposited per primary [keV / bin]")
axes[0].set_title("Air")
axes[0].legend(title=r"$\alpha$ energy")
axes[0].grid(alpha=0.3)

for color, e in zip(cmap, energies):
    d, edep = load("si", e)
    axes[1].plot(d * 1000.0, edep, color=color, linewidth=1.4, label=f"{e} MeV")
axes[1].set_xlabel(r"Depth in Silicon [$\mu$m]")
axes[1].set_ylabel("Energy deposited per primary [keV / bin]")
axes[1].set_title("Silicon")
axes[1].legend(title=r"$\alpha$ energy")
axes[1].grid(alpha=0.3)

fig.suptitle(r"Bragg Curves of 4 - 8 MeV $\alpha$ Particles", fontsize=13)
fig.tight_layout()
fig.savefig(results / "bragg_combined.png", dpi=150)
plt.close(fig)

print("Saved: bragg_air.png, bragg_si.png, bragg_combined.png")
print("\nPeak Edep / bin and peak depth:")
print(f"{'Material':<10} {'E [MeV]':<8} {'peak depth':<14} {'peak Edep [keV]':<15}")
for material, unit, scale in [("air", "mm", 1.0), ("si", "um", 1000.0)]:
    for e in energies:
        d_mm, edep = load(material, e)
        i_max = int(np.argmax(edep))
        peak_depth = d_mm[i_max] * scale
        print(f"{material:<10} {e:<8} {peak_depth:>8.3f} {unit:<5} {edep[i_max]:>10.2f}")

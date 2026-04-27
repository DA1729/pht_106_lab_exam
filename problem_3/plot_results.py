from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

here = Path(__file__).parent
results = here / "results"
results.mkdir(exist_ok=True)

df = pd.read_csv(results / "spectrum_nt_spectrum.csv",
                 comment="#", header=None,
                 names=["edep_keV", "e_source_MeV"])

edep = df["edep_keV"].to_numpy()
e_source = df["e_source_MeV"].to_numpy()

energies = [4, 5, 6, 7, 8]
bins = np.linspace(0, 8500, 851)
bin_width = bins[1] - bins[0]

n_total = len(edep)
print(f"Total events: {n_total}")
for e in energies:
    mask = np.isclose(e_source, e, atol=0.01)
    print(f"  {e} MeV : {mask.sum()} events")

print("\nMeasured peak (mean Edep) per source line:")
print(f"{'Source [MeV]':<14}{'Mean Edep [keV]':<18}{'FWHM [keV]':<12}{'Air loss [keV]':<16}")
for e in energies:
    mask = np.isclose(e_source, e, atol=0.01)
    sub = edep[mask]
    if len(sub) == 0:
        continue
    mean = sub.mean()
    std = sub.std()
    fwhm = 2.355 * std
    loss = e * 1000 - mean
    print(f"{e:<14}{mean:<18.1f}{fwhm:<12.1f}{loss:<16.1f}")

fig, ax = plt.subplots(figsize=(10, 5.5))
ax.hist(edep, bins=bins, histtype="step", color="black", linewidth=1.4,
        label=f"All events (N = {n_total:,})")
for e in energies:
    ax.axvline(e * 1000, color="grey", linestyle=":", alpha=0.6)
    ax.text(e * 1000, ax.get_ylim()[1] * 0.95, f"{e} MeV",
            rotation=90, ha="right", va="top", fontsize=8, color="grey")
ax.set_xlabel("Energy deposited in Si detector [keV]")
ax.set_ylabel("Counts per 10 keV bin")
ax.set_title(r"Combined Spectrum of 4–8 MeV $\alpha$ Source after 10 mm Air")
ax.legend()
ax.grid(alpha=0.3)
fig.tight_layout()
fig.savefig(results / "spectrum_combined.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(10, 5.5))
cmap = plt.cm.viridis(np.linspace(0.1, 0.85, len(energies)))
for color, e in zip(cmap, energies):
    mask = np.isclose(e_source, e, atol=0.01)
    ax.hist(edep[mask], bins=bins, histtype="step", color=color,
            linewidth=1.4, label=f"{e} MeV source")
    ax.axvline(e * 1000, color=color, linestyle=":", alpha=0.4)
ax.set_xlabel("Energy deposited in Si detector [keV]")
ax.set_ylabel("Counts per 10 keV bin")
ax.set_title(r"Per-Energy Decomposition of the Spectrum")
ax.legend(title="Source line", loc="upper left")
ax.grid(alpha=0.3)
fig.tight_layout()
fig.savefig(results / "spectrum_per_energy.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(10, 5.5))
for color, e in zip(cmap, energies):
    mask = np.isclose(e_source, e, atol=0.01)
    ax.hist(edep[mask], bins=bins, histtype="stepfilled", color=color,
            alpha=0.55, label=f"{e} MeV source")
ax.set_xlabel("Energy deposited in Si detector [keV]")
ax.set_ylabel("Counts per 10 keV bin")
ax.set_title(r"Stacked Spectrum by Source Energy")
ax.legend(title="Source line", loc="upper left")
ax.grid(alpha=0.3)
fig.tight_layout()
fig.savefig(results / "spectrum_stacked.png", dpi=150)
plt.close(fig)

print("\nSaved: spectrum_combined.png, spectrum_per_energy.png, spectrum_stacked.png")

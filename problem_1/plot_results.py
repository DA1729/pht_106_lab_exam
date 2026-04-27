from pathlib import Path
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

here = Path(__file__).parent
results = here / "results"
results.mkdir(exist_ok=True)


def load(name):
    path = results / f"{name}_nt_edep.csv"
    df = pd.read_csv(path, comment="#", header=None)
    return df.iloc[:, 0].to_numpy()


with_al = load("results_with_al")
without_al = load("results_without_al")

n_with = len(with_al)
n_without = len(without_al)
threshold_kev = 1.0

interacting_with = with_al[with_al > threshold_kev]
interacting_without = without_al[without_al > threshold_kev]

frac_with = len(interacting_with) / n_with
frac_without = len(interacting_without) / n_without
mean_with = interacting_with.mean() if len(interacting_with) else 0.0
mean_without = interacting_without.mean() if len(interacting_without) else 0.0

print(f"Primaries per run: with_al={n_with}, without_al={n_without}")
print(f"Fraction depositing > {threshold_kev} keV:")
print(f"  Without Al : {frac_without:.4f}")
print(f"  With    Al : {frac_with:.4f}")
print(f"Mean Edep per interacting event:")
print(f"  Without Al : {mean_without:.2f} keV")
print(f"  With    Al : {mean_with:.2f} keV")

bins = np.linspace(0, 1200, 121)
label_no = "Bare crystal (no Al)"
label_yes = "With 0.5 mm Al casing"
colors = ["tab:blue", "tab:orange"]

fig, ax = plt.subplots(figsize=(8, 5))
ax.hist(interacting_without, bins=bins, histtype="step",
        linewidth=1.6, color=colors[0],
        label=f"{label_no}  (N = {len(interacting_without):,})")
ax.hist(interacting_with, bins=bins, histtype="step",
        linewidth=1.6, color=colors[1],
        label=f"{label_yes}  (N = {len(interacting_with):,})")
ax.set_xlabel("Energy deposited in NaI [keV]")
ax.set_ylabel("Counts per 10 keV bin")
ax.set_title(r"$^{137}$Cs $\beta^-$ Energy Deposition in 1$''\times$1$''$ NaI Crystal")
ax.legend()
ax.grid(alpha=0.3)
fig.tight_layout()
fig.savefig(results / "spectrum.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(8, 5))
ax.hist(interacting_without, bins=bins, histtype="step",
        linewidth=1.6, color=colors[0], label=label_no)
ax.hist(interacting_with, bins=bins, histtype="step",
        linewidth=1.6, color=colors[1], label=label_yes)
ax.set_yscale("log")
ax.set_xlabel("Energy deposited in NaI [keV]")
ax.set_ylabel("Counts per 10 keV bin (log scale)")
ax.set_title(r"$^{137}$Cs $\beta^-$ Deposition Spectrum (Log Scale)")
ax.legend()
ax.grid(alpha=0.3, which="both")
fig.tight_layout()
fig.savefig(results / "spectrum_log.png", dpi=150)
plt.close(fig)

fig, axes = plt.subplots(1, 2, figsize=(10, 4.5))
bar_labels = ["Without Al", "With 0.5 mm Al"]

axes[0].bar(bar_labels, [frac_without, frac_with], color=colors)
axes[0].set_ylabel(r"Fraction of $\beta^-$ depositing $>$ 1 keV")
axes[0].set_title("Interaction Fraction")
axes[0].grid(alpha=0.3, axis="y")
for i, v in enumerate([frac_without, frac_with]):
    axes[0].text(i, v, f"{v:.3f}", ha="center", va="bottom")

axes[1].bar(bar_labels, [mean_without, mean_with], color=colors)
axes[1].set_ylabel("Mean Edep per interacting event [keV]")
axes[1].set_title("Mean Energy Deposit")
axes[1].grid(alpha=0.3, axis="y")
for i, v in enumerate([mean_without, mean_with]):
    axes[1].text(i, v, f"{v:.1f}", ha="center", va="bottom")

fig.suptitle(r"Effect of 0.5 mm Al Casing on $^{137}$Cs $\beta^-$ Detection",
             fontsize=12)
fig.tight_layout()
fig.savefig(results / "comparison.png", dpi=150)
plt.close(fig)

fig, ax = plt.subplots(figsize=(8, 5))
ax.hist(without_al, bins=bins, histtype="step",
        linewidth=1.6, color=colors[0],
        label=f"{label_no} (incl. 0-Edep)")
ax.hist(with_al, bins=bins, histtype="step",
        linewidth=1.6, color=colors[1],
        label=f"{label_yes} (incl. 0-Edep)")
ax.set_yscale("log")
ax.set_xlabel("Energy deposited in NaI [keV]")
ax.set_ylabel("Counts per 10 keV bin (log scale)")
ax.set_title("All Primaries (Zero-Edep Events Included)")
ax.legend()
ax.grid(alpha=0.3, which="both")
fig.tight_layout()
fig.savefig(results / "spectrum_all.png", dpi=150)
plt.close(fig)

print("\nSaved: spectrum.png, spectrum_log.png, comparison.png, spectrum_all.png")

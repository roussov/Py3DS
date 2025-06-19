# 📘 Guide d'utilisation — PlatonPy3DS

PlatonPy3DS est un éditeur de texte et un interpréteur Python ultra-léger conçu pour la Nintendo 3DS (ou en mode SDL pour PC), intégrant un affichage ASCII, un clavier tactile, et une exécution d'expressions Python de base via un interpréteur en C.

---

## 🚀 Lancement

### 🧱 Compilation (Nintendo 3DS avec devkitARM)

Assurez-vous que devkitARM et citro3d sont installés.

```bash
make

* Cela génère le fichier PlatonPy.3dsx dans le répertoire build/ (si configuré).

*Lancez-le via Homebrew Launcher sur votre 3DS :

```bash
./PlatonPy.3dsx

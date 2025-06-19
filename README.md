# 3DS - Éditeur & Interpréteur Python Minimaliste

Py3DS est un projet d'éditeur de code Python embarqué sur 3DS accompagné d’un interpréteur minimaliste entièrement écrit en C.
Il vise à fournir un environnement simple pour éditer, analyser et exécuter du code Python via un parsing manuel, AST et évaluation.

---

## Fonctionnalités principales

- **Éditeur de texte en terminal** : interface simple pour écrire et modifier du code Python
- **Interpréteur Python** : lexer, parser, génération d'AST et évaluation runtime
- **Support de types** : entiers, flottants, chaînes, variables, fonctions
- **Contrôle de flux** : conditions, boucles, appels de fonctions
- **Mode REPL** : saisie interactive avec exécution immédiate
- **Exécution de scripts** : lancer un fichier Python via l’interpréteur
- **Gestion des erreurs** : détection et affichage des erreurs syntaxiques et runtime

---

## Only for Dev

## Compilation et exécution

1. Compiler le projet :

```bash
make

2. Lancer l’interpréteur en mode interactif (REPL) :

```bash
./3ds

3. Exécuter un script Python :

```bash
./3ds examples/test_script.py

Commandes utiles avec Makefile

```bash
make run : exécute le programme compilé

```bash
make clean : supprime les fichiers temporaires et l’exécutable

```bash
make test : lance les tests unitaires (pytest)

```bash
make valgrind : analyse mémoire avec valgrind

```bash
make test-valgrind : test sous valgrind avec un script exemple

```bash
make repl : lance le REPL interactif


```text
3ds/
├── src/
│   ├── main.c            # Point d’entrée principal (initialisation, boucle)
│   ├── editor.c          # Éditeur texte terminal (saisie, affichage)
│   ├── lexer.c           # Analyse lexicale (tokens)
│   ├── parser.c          # Analyse syntaxique (génération AST)
│   ├── ast.c             # Structure et manipulation AST
│   ├── eval.c            # Évaluation/exécution AST
│   ├── env.c             # Environnement (variables, portée)
│   ├── error.c           # Gestion des erreurs
│   ├── utils.c           # Fonctions utilitaires diverses
│   ├── include/          # Headers (.h) pour chaque module
│   └── tests/            # Tests unitaires
│
├── Makefile              # Script de compilation
├── README.md
└── LICENSE

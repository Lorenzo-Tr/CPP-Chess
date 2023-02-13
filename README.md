# 👋 Présentation

Ce projet est un projet de formation en CPP. 

Réalisé en collaboration avec Romain.

L'objectif du projet était de recréer un moteur de jeux d'échecs en CPP.
  
# 🚀 Développer avec
`C++` `Makefile` `g++`

# 📖 L'architecture
```
.
├── incude        # Répertoire contenant les déclarion
├── src          
│   └── (...).cpp       # Répertoire contenant les Implémentation
└── ...
```

# 📜 Comment compiler
Pour compiler le programme il vous faut `g++` ainsi que `make`

Le **Makefile** contient les règles suivantes : 
- `make` Créer le binnaire
- `make clean` Pour supprimer les .o
- `make fclean` Pour supprimer les .o générer ainsi que le binaire
- `make re` Combinaison de fclean et de all

Si le projet ne contient pas de répertoire `obj/` veuillez le créer à l'aide de la commande suivante :
`mkdir obj`

Pour résumé :
```bash
git clone https://github.com/Lorenzo-Tr/CPP-Chess
cd CPP-Chess
mkdir obj/
make re
```

Deuxième solution via `cmake`
```bash
git clone https://github.com/Lorenzo-Tr/CPP-Chess
cd CPP-Chess
mkdir build/
cd build/
cmake
make install
```

Ensuite pour lancer le programme `../bin/Chess`

# 📜 Bilan
Le projet était bien casse-tête, mais à la fois très instructif. Je serais ravi de recommencer le projet depuis zéro afin d'éviter les erreurs que j'ai faites et également avoir un code plus propre

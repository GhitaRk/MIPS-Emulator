# Projet C : Émulation du processeur MIPS

## Description

Ce projet est une émulation basique du processeur MIPS, codée en C. L'objectif est de simuler certaines instructions du processeur MIPS, permettant de comprendre le fonctionnement interne de ce processeur et de manipuler directement les registres et la mémoire.

Le programme principal, contenu dans `main.c`, utilise des fonctions définies dans `fonctions.h` et implémentées dans `fonction.c`. Ces fonctions permettent d'exécuter des opérations spécifiques au processeur MIPS.

## Structure du projet

- `main.c` : Ce fichier contient la fonction principale qui pilote l'émulation. Il initialise la mémoire et les registres du processeur MIPS, et appelle les fonctions d'émulation des instructions. C'est ici que le flux principal de l'exécution est contrôlé.
  
- `fonction.c` : Ce fichier implémente les différentes instructions et fonctionnalités du processeur MIPS simulé. Chaque fonction représente une instruction ou une opération MIPS, telles que les opérations arithmétiques, logiques, ou de gestion de la mémoire.

- `fonctions.h` : Ce fichier d'en-tête contient les déclarations de toutes les fonctions d'émulation. Il contient également les définitions des structures de données importantes, comme les registres et la mémoire, qui sont utilisées pour simuler l'environnement MIPS.

## Prérequis

- Compilateur C (GCC recommandé)
- Connaissances de base sur l'architecture MIPS et ses instructions
- Système Linux, Mac ou Windows avec un terminal compatible

## Compilation

Pour compiler le projet, utilisez la commande suivante :

```bash
gcc -o emulateur_mips main.c fonction.c

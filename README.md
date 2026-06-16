# mywatch
Redévelopper la commande watch à partir de zéro en utilisant le langage C.

# mywatch2

> Réimplementation de la commande `watch` de Linux en langage C pur avec appels système directs (syscall).

## Table des matières
1. [Description générale](#description)
2. [Statut du projet](#statut)
3. [Technologies utilisées](#technologies)
4. [Installation](#installation)
5. [Utilisation](#utilisation)
6. [Options](#options)
7. [Contrôles clavier](#clavier)
8. [Exemples](#exemples)
9. [Equipe](#equipe)
10. [Bugs connus](#bugs)
11. [Licence](#licence)

---

## Description

`mywatch2` est une réimplementation complète de la commande `watch` de Linux.
Il execute une commande de manière répétée et affiche son résultat en plein écran,
en se rafraichissant automatiquement a intervalle régulier.

**Ce qui nous différencie de la commande originale :**
- Tous les appels système sont faits directement avec `syscall()` sans utiliser les fonctions Linux toutes faites
- Gestion des erreurs claire et colorée en rouge
- Commande `--help` détaillée
- Contrôles clavier interactifs (q, espace, s)
- Screenshots du terminal en fichier texte

---

## Statut

Le projet est en cours de développement actif.

**Fonctionnalités implémentées :** toutes les options principales de `watch`
**En cours :** tests finaux et documentation

---

## Technologies

- **Langage :** C (standard C99)
- **Compilateur :** GCC avec flags `-Wall -Wextra -Werror`
- **Systeme :** Linux (Ubuntu/Debian/Kali)
- **Versioning :** Git / GitHub
- **Appels systeme :** syscall() direct (fork, pipe, execve, read, write, ioctl...)

---

## Installation

### Prérequis

- Linux (Ubuntu, Debian, Kali)
- GCC installe (`sudo apt install build-essential -y`)

### Cloner le depot

```bash
git clone https://github.com/OpenSecureFoundation/mywatch.git
cd mywatch
```

### Compiler

```bash
make
```

### Recompiler depuis zero

```bash
make re
```

### Supprimer le programme compile

```bash
make clean
```

---

## Utilisation

```bash
./mywatch2 [options] commande
```

---

## Options

| Option | Description | Exemple |
|--------|-------------|---------|
| `-n <sec>` | Intervalle de rafraichissement (défaut: 2s) | `./mywatch2 -n 1 date` |
| `-d` | Surligner les différences | `./mywatch2 -d ls` |
| `-t` | Masquer l en-tête | `./mywatch2 -t date` |
| `-e` | Quitter si erreur | `./mywatch2 -e make` |
| `-g` | Quitter si output change | `./mywatch2 -g date` |
| `-b` | Bip si erreur | `./mywatch2 -b make` |
| `-p` | Intervalle précis | `./mywatch2 -p -n 1 date` |
| `-q <n>` | Quitter si identique pendant n cycles | `./mywatch2 -q 3 echo bonjour` |
| `-w` | Couper les longues lignes | `./mywatch2 -w cat /etc/passwd` |
| `-c` | Interpréter les couleurs ANSI | `./mywatch2 -c ls --color=always` |
| `-C` | Supprimer les couleurs ANSI | `./mywatch2 -C ls --color=always` |
| `-f` | Scroll au lieu d effacer l'écran | `./mywatch2 -f date` |
| `-x` | Exécuter sans passer par le shell | `./mywatch2 -x date` |
| `--help` | Afficher l aide | `./mywatch2 --help` |
| `-v` | Afficher la version | `./mywatch2 -v` |

---

## Controles clavier

| Touche | Action |
|--------|--------|
| `q` | Quitter proprement |
| `espace` | Relancer la commande immédiatement |
| `s` | Prendre un screenshot (sauvegarde en .txt) |

---

## Exemples

```bash
# Surveiller la date toutes les secondes
./mywatch2 -n 1 date

# Surveiller l espace disque avec différences surlignées
./mywatch2 -d df -h

# Surveiller les processus sans en-tête
./mywatch2 -t ps aux

# Quitter automatiquement si l output change
./mywatch2 -g ls /tmp

# Utiliser une variable d environnement
export WATCH_INTERVAL=5
./mywatch2 date
```

---

## Variables d environnement

| Variable | Description |
|----------|-------------|
| `WATCH_INTERVAL` | Definit l intervalle par defaut de maniere persistante |

---

## Codes de sortie

| Code | Signification |
|------|---------------|
| `0` | Succes |
| `1` | Erreur option ou argument invalide |
| `2` | Erreur execution de la commande |

---

## Architecture du projet
---

## Equipe

| Membre | Role |
|--------|------|
| Belvira | args.c, main.c — lecture des options et boucle principale |
| Christelle | display.c — affichage et couleurs |
| Selihe | executor.c, error.c, help.c — execution et gestion des erreurs système |
| Gregory | utils.c — signaux et gestion du temps |
| Grace | executor.c, error.c — execution et gestion des erreurs d'exécution |

---

## Bugs connus

- Le bip (`-b`) peut ne pas fonctionner sur certains terminaux selon leur configuration
- Les captures d'écran ou screenshots sauvegardent le texte brut sans les couleurs ANSI

---

## Licence

Projet académique — Institut Universitaire Saint Jean
Année académique 2025-2026
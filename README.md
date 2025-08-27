# 📝 README

## 🖥️ Démarrage pour Windows (recommandé)

- Allez dans la release **1.3.0** ou supérieure  
- Installez l’installateur puis **exécutez-le**

Cela crée une nouvelle application (un lanceur) sur votre bureau.  
Lance cette application pour démarrer plus facilement et rapidement le programme, avec la possibilité d’effectuer des réglages si nécessaire.

### 🔄 Alternatives

1. Clone ce dépôt sur ton ordinateur  
2. Double-clique sur le fichier `raccourcigraph.bat`

---

## 🍎 Démarrage sous macOS *(en théorie, ça fonctionne)*

1. Clonez le répertoire sur votre ordinateur  
2. Allez dans le dossier `beat` et lancez le script `beatMAC.sh`  
3. Pour modifier les paramètres, éditez le fichier `.sh` avec un éditeur de texte (comme TextEdit) et ajustez les valeurs désirées

---

## 📞 Communication avec le microcontrôleur

| Paramètre         | Description                                                                 |
|-------------------|-----------------------------------------------------------------------------|
| `--port COM7`     | 🚪 Port de communication avec le microcontrôleur. À adapter selon la connexion |
| `--baudrate 115200` | 🐇 Vitesse de transfert (modifier uniquement si nécessaire)                   |

---

## 🎯 Sensibilité à la détection des kicks

| Paramètre     | Description                                                                 |
|---------------|-----------------------------------------------------------------------------|
| `--k-high`    | 💥 Sensibilité aux pics. Plus la valeur est basse, plus le système est sensible. Exemple : `1.3` |
| `--k-low`     | 🔁 Hystérésis pour le réarmement. Plus proche de `k-high`, plus le système se réarme vite. Exemple : `0.8` |

---

## ⏱️ Intervalle minimal entre deux détections

| Paramètre         | Description                                                                 |
|-------------------|-----------------------------------------------------------------------------|
| `--min-interval`  | ⏳ Temps minimal entre deux kicks détectés. Exemple : `0.18` (180 ms). Augmente à `0.3` ou plus pour ralentir |

---

## 🎵 Fréquences d’analyse (filtre passe-bande)

| Paramètre       | Description                                                                 |
|-----------------|-----------------------------------------------------------------------------|
| `--bp-low`      | 🔊 Fréquence minimale analysée. Exemple : `40.0 Hz`                         |
| `--bp-high`     | 🔊 Fréquence maximale analysée. Exemple : `80.0 Hz`                         |
| `--bp-order`    | 🔧 Précision du filtre. Ordre plus élevé = filtre plus “pointu”. Valeurs typiques : `1` ou `2` |

📌 Ces trois paramètres déterminent la zone du spectre audio ciblée pour la détection des kicks.  
Typiquement, les kicks se situent entre **40 et 100 Hz**.  
Adapte `bp-low` et `bp-high` selon le type de son que tu souhaites capter.

---

## 🚀 Pour aller plus loin

Le dossier `esp32` contient un programme pour ESP32 que tu peux modifier ou compiler selon tes besoins.

Le programme envoie par communication série deux messages différents :

- `"1"` pour un beat détecté  
- `"0"` lorsque le beat n’est plus détecté  

Cela permet de gérer facilement des lumières ou autres effets en fonction des beats.

Il est possible d’ajouter des paramètres supplémentaires.  
Pour voir tous les paramètres disponibles, ouvre un terminal, rends-toi dans le dossier `beat` et tape :

```bash
python beat.py --help

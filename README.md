#  **Polo 9N3 Dash-OS** : Système d'Instrumentation Embarqué 

### 🎯 Motivation & Contexte
Jeune diplômé en Systèmes Embarqués, j'ai choisi de mettre à profit ma période de recherche d'emploi pour concevoir un écosystème complet de control et monitoring pour mon véhicule personnel (Volkswagen Polo IV 9N3).

Pourquoi ce projet ?	

-  Montée en compétences : Maîtriser le framework **Qt 6** et le développement d'IHM modernes en **C++/QML**.

-  Ingénierie Inverse : Comprendre les protocoles propriétaires du groupe VAG et décoder le bus **CAN** (Controller Area Network).
  
-  Concrétisation : Appliquer les principes académiques des systèmes temps-réels à un environnement physique complexe et exigeant.



------
<img width="1276" height="720" alt="image" src="https://github.com/user-attachments/assets/4db662ac-0abb-4c48-9115-0f30fe962cd3" />

### 💎 Philosophie du Design : L'expérience Tesla sur Polo 9N3

L'objectif central de ce projet est de transposer les codes de l'interface utilisateur de Tesla (Minimalisme, High-Tech, Fluidité) sur une architecture automobile analogique des années 2000.

Les piliers de l'interface :

- Visualisation 3D/2D Contextuelle : Au lieu de simples voyants, l'état du véhicule est représenté par une silhouette interactive centrale qui réagit dynamiquement aux événements du bus CAN.

- Typographie & Contraste : Utilisation de polices sans-serif modernes et d'un mode sombre (Dark Mode) profond pour minimiser la fatigue visuelle nocturne.

- Performance 60 FPS : Optimisation du moteur QML pour garantir une fluidité parfaite des animations (mouvement des roues, ouverture des portes), égalant la réactivité des systèmes d'infodivertissement premium. 

------


# 🛠️ Architecture Technique


## 🔌 Hardware

- Véhicule : Volkswagen Polo IV (9N3) - Plateforme PQ24.
  
- Interface CAN : Adaptateur USB2CAN (Protocole SLCAN).
  
- Unité de calcul : Raspberry Pi 5  (Cible embarquée finale) / thinkpad T450 & MacBook air M2 (Développement & Reverse Engineering)
  
- Connectivité : Pontage direct sur le connecteur 32 broches (Tyco MQS) du combiné d'instruments pour accéder aux bus Traction (500 kbps) et Confort (100 kbps).

## 💻 Software Stack
- Framework : Qt 6.10 (C++ / QML).
  
- Analyse de données : SavvyCAN & Wireshark (Reverse engineering des IDs propriétaires).
  
- Graphismes : Design personnalisé avec gestion dynamique des modes Jour/Nuit et silhouettes de véhicule interactives.
  
- OS Cible : ubuntu avec SocketCAN.

### 🚀 Fonctionnalités Actuelles

1. Extraction des donnés de propulsion
   
- Real-time Performance : Lecture du régime moteur (RPM - ID 0x280) et de la charge moteur pour calculer la puissance délivrée en temps réel.
- Engine State : differents etats du moteurs 
	<img width="1276" height="716" alt="image" src="https://github.com/user-attachments/assets/7edc4973-7d8d-45d9-8a0d-64da8c0ca145" />


2. Visualisation Châssis & Dynamique

- Angle de braquage : Animation en temps réel des roues sur le modèle 2D en fonction des données de l'ID 0x0C2.
- Vitesse des roues : Monitoring individuel des 4 capteurs ABS (0x4A0).
- Systèmes de sécurité : Indicateurs visuels d'intervention de l'ABS, de l'ESP et de l'antipatinage avec effets de clignotement critique.

  <img width="1273" height="717" alt="image" src="https://github.com/user-attachments/assets/648809aa-f6b0-42b1-9cfd-dfe882ce7420" />

3. Consommation
   
- Autonomie : evaluation du reste à parcourir en fonction de reste du reservoir
- Thermique avancée : Monitoring de la température de liquide de refroidissement et d'huile  avec alertes dynamiques en cas de dépassement de seuil, inspiré du système de gestion thermique des batteries Tesla.
- donnée batterie:
  <img width="1277" height="718" alt="image" src="https://github.com/user-attachments/assets/13dca677-7d28-49d9-ba16-900345d1400a" />

  
4. Gestion de l'Habitacle (Body Control)
   
- Etat A/C  
- Gestion des vitres : Affichage du pourcentage d'ouverture des vitres électriques.
- État des ouvrants : Visualisation interactive des portes, coffre et capot ouverts/fermés.
- Sécurité passive : Monitoring des capteurs de présence sur les sièges et verrouillage des ceintures de sécurité.
- Central Locking : Statut en temps réel du verrouillage centralisé avec animations de pulsation.
  <img width="1275" height="717" alt="image" src="https://github.com/user-attachments/assets/4fe7ebe9-a1a4-484c-8f62-018eafa45aeb" />



5. Diagnostic

	<img width="1273" height="719" alt="image" src="https://github.com/user-attachments/assets/946652de-5c18-4506-a3ee-1ae33a3d1806" />



## 📈 Compétences Validées
- C++ / QML : Création de composants réutilisables, logique de binding de données et optimisation des performances graphiques.

- UI/UX Design : Conception d'une interface scannable et ergonomique pour la conduite.

- Systèmes Linux : Configuration d'interfaces réseau CAN (SocketCAN) et gestion des ports série sous macOS/Linux.


## 🚧 Roadmap & Évolutions

- Protocoles de communication : Analyse, filtrage et décodage de trames CAN brutes.
  
- Portage sur écran tactile 14" via Raspberry Pi et intégration au tableau de bord.



Projet réalisé par **Ian Kenny** - Jeune Ingénieur en Systèmes Embarqués et transports intelligents.

#!/bin/bash

# =================================================================
# Script de configuration Dual CAN HAT pour Raspberry Pi 5
# Auteur: Gemini Collaboration
# Date: 2026
# =================================================================

echo "--- Début de la configuration du CAN HAT ---"

# 1. Mise à jour du fichier config.txt
echo "[1/4] Configuration des Overlays dans /boot/firmware/config.txt..."
CONFIG_FILE="/boot/firmware/config.txt"

# On vérifie si l'overlay existe déjà pour éviter les doublons
if grep -q "mcp2515-can0" "$CONFIG_FILE"; then
    echo "L'overlay CAN est déjà présent dans $CONFIG_FILE."
else
    sudo tee -a "$CONFIG_FILE" <<EOF

# Configuration CAN HAT (Ajouté par script)
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25
dtoverlay=mcp2515-can1,oscillator=16000000,interrupt=24
EOF
    echo "Overlays ajoutés avec succès."
fi

# 2. Installation des outils can-utils
echo "[2/4] Installation de can-utils..."
sudo apt update && sudo apt install can-utils -y

# 3. Création du script d'activation automatique
echo "[3/4] Création du script d'initialisation des interfaces..."
sudo tee /usr/local/bin/setup-can.sh <<EOF
#!/bin/bash
# Configuration des vitesses et des files d'attente
/sbin/ip link set can0 up type can bitrate 500000
/sbin/ip link set can0 txqueuelen 1000
/sbin/ip link set can1 up type can bitrate 500000
/sbin/ip link set can1 txqueuelen 1000
EOF

# Rendre le script exécutable
sudo chmod +x /usr/local/bin/setup-can.sh

# 4. Création du service Systemd pour le démarrage
echo "[4/4] Création du service systemd..."
sudo tee /etc/systemd/system/can-interfaces.service <<EOF
[Unit]
Description=Auto-activation des interfaces CAN
After=network.target

[Service]
Type=oneshot
ExecStart=/usr/local/bin/setup-can.sh
RemainAfterExit=yes

[Install]
WantedBy=multi-user.target
EOF

# Activation du service
sudo systemctl daemon-reload
sudo systemctl enable can-interfaces.service

echo "--- Configuration terminée ! ---"
echo "Veuillez redémarrer votre Pi avec : sudo reboot"
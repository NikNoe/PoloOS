#!/bin/bash
# Script de déploiement Thinkpad USB-CAN-A

INSTALL_DIR="$HOME/USB-CAN-A"
BIN_NAME="canusb"

echo "--- Préparation du matériel ---"

# 1. Création de la règle UDEV (Fixe le nom du port)
# Basé sur ton lsusb (ID 1a86:7523)
sudo tee /etc/udev/rules.d/99-usb-can.rules <<EOF
SUBSYSTEM=="tty", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", SYMLINK+="waveshare_can", MODE="0666"
EOF

# Recharger les règles
sudo udevadm control --reload-rules && sudo udevadm trigger
echo "Port fixe /dev/waveshare_can créé."

# 2. Création du service Systemd
echo "Configuration du service de démarrage..."
sudo tee /etc/systemd/system/usb-can.service <<EOF
[Unit]
Description=Service de lecture USB-CAN Waveshare
After=network.target

[Service]
# On utilise le lien symbolique fixe et le chemin complet du binaire
ExecStart=$INSTALL_DIR/$BIN_NAME -t -d /dev/waveshare_can -s 1000000 -t
Restart=always
RestartSec=5
User=$USER
WorkingDirectory=$INSTALL_DIR
StandardOutput=inherit
StandardError=inherit

[Install]
WantedBy=multi-user.target
EOF

# 3. Activation
sudo systemctl daemon-reload
sudo systemctl enable usb-can.service
sudo systemctl restart usb-can.service

echo "--- Terminé ! ---"
echo "L'adaptateur démarre maintenant tout seul sur /dev/waveshare_can."
#!/bin/bash

# Couleurs ANSI
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Fonction de barre de progression améliorée
show_progress() {
    local current=$1
    local total=$2
    local message=${3:-"Chargement"}
    local bar_length=50
    
    # Validation des paramètres
    if [[ $total -le 0 ]]; then
        echo "Erreur: total doit être > 0"
        return 1
    fi
    
    # Calcul du pourcentage (limité à 100)
    local percent=$((current * 100 / total))
    if [[ $percent -gt 100 ]]; then
        percent=100
    fi
    
    # Calcul du nombre de caractères remplis (sécurisé)
    local filled=$((current * bar_length / total))
    if [[ $filled -gt $bar_length ]]; then
        filled=$bar_length
    fi
    
    # Création de la barre avec une méthode plus rapide
    local bar=$(printf "█%.0s" $(seq 1 $filled))
    local empty=$(printf "░%.0s" $(seq 1 $((bar_length - filled))))
    
    # Choix de la couleur selon le pourcentage
    local color=$RED
    if [[ $percent -ge 25 ]]; then color=$YELLOW; fi
    if [[ $percent -ge 50 ]]; then color=$BLUE; fi
    if [[ $percent -ge 80 ]]; then color=$GREEN; fi
    
    # Affichage de la barre
    printf "\r${BOLD}${message}:${NC} [${color}${bar}${empty}${NC}] ${BOLD}%3d%%${NC}" $percent
}

# Démonstration de la barre de progression
echo -e "${BOLD}${BLUE}Démarrage de la simulation...${NC}"
echo

total_steps=100

for ((i=0; i<=total_steps; i++)); do
    show_progress $i $total_steps "Chargement"
    sleep 0.05  # Plus fluide
done

printf "\n\n"
echo -e "${BOLD}${GREEN}✓ Terminé avec succès !${NC}"

# # Exemple avec différents messages
# echo
# echo -e "${BOLD}${BLUE}Test avec différentes étapes :${NC}"

# steps=("Initialisation" "Compilation" "Tests" "Finalisation")
# for ((j=0; j<${#steps[@]}; j++)); do
#     for ((i=0; i<=25; i++)); do
#         show_progress $i 25 "${steps[$j]}"
#         sleep 0.03
#     done
#     printf "\n"
# done

# echo -e "${BOLD}${GREEN}🎉 Tous les tests terminés !${NC}"
#!/bin/bash

# Script simple pour calculer le temps entre le dernier repas et la mort
# Usage: ./simple_death_calc.sh [args_for_philo]

if [ $# -lt 4 ]; then
    echo "Usage: $0 nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]"
    exit 1
fi

echo "Test: ./philo $@"

# Exécuter le programme et capturer la sortie
OUTPUT=$(./philo "$@" 2>&1)

# Trouver la ligne de mort
DEATH_LINE=$(echo "$OUTPUT" | grep " died" | head -1)

if [ -z "$DEATH_LINE" ]; then
    echo "Aucun philosophe n'est mort dans cette simulation."
    exit 0
fi

# Extraire les informations de mort
DEATH_TIME=$(echo "$DEATH_LINE" | awk '{print $1}')
PHILO_ID=$(echo "$DEATH_LINE" | awk '{print $2}')

echo "Philosophe $PHILO_ID est mort à: $DEATH_TIME"

# Trouver le dernier repas de ce philosophe
LAST_MEAL_LINE=$(echo "$OUTPUT" | grep "$PHILO_ID is eating" | tail -1)

if [ -n "$LAST_MEAL_LINE" ]; then
    LAST_MEAL_TIME=$(echo "$LAST_MEAL_LINE" | awk '{print $1}')
    echo "Dernier repas à: $LAST_MEAL_TIME"
    
    # Calculer la différence
    TIME_DIFF=$((DEATH_TIME - LAST_MEAL_TIME))
    
    echo "Différence (temps sans manger): $TIME_DIFF ms"
    echo "Temps de survie autorisé: $2 ms"
    
    if [ $TIME_DIFF -ge $2 ]; then
        echo "Résultat: Mort correcte (≥ time_to_die)"
    else
        echo "Résultat: Mort prématurée (< time_to_die)"
    fi
else
    echo "Erreur: Aucun repas trouvé pour le philosophe $PHILO_ID"
fi
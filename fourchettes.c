#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_PHILOSOPHES 5

// Chaque fourchette est un mutex
pthread_mutex_t fourchettes[NB_PHILOSOPHES];

// Fonction pour un philosophe
void *philosophe(void *arg) {
    int id = *(int*)arg;
    int fourchette_gauche = id;
    int fourchette_droite = (id + 1) % NB_PHILOSOPHES;
    
    for (int i = 0; i < 3; i++) {  // Chaque philosophe mange 3 fois
        
        // 1. PENSER
        printf("Philosophe %d pense...\n", id);
        sleep(1);
        
        // 2. PRENDRE LES FOURCHETTES
        printf("Philosophe %d a faim, essaie de prendre les fourchettes\n", id);
        
        // Prendre la fourchette de gauche
        pthread_mutex_lock(&fourchettes[fourchette_gauche]);
        printf("Philosophe %d a pris la fourchette gauche (%d)\n", id, fourchette_gauche);
        
        // Prendre la fourchette de droite
        pthread_mutex_lock(&fourchettes[fourchette_droite]);
        printf("Philosophe %d a pris la fourchette droite (%d)\n", id, fourchette_droite);
        
        // 3. MANGER
        printf("🍽️  Philosophe %d MANGE (repas %d/3)\n", id, i + 1);
        sleep(2);  // Temps pour manger
        
        // 4. REPOSER LES FOURCHETTES
        pthread_mutex_unlock(&fourchettes[fourchette_droite]);
        printf("Philosophe %d repose la fourchette droite (%d)\n", id, fourchette_droite);
        
        pthread_mutex_unlock(&fourchettes[fourchette_gauche]);
        printf("Philosophe %d repose la fourchette gauche (%d)\n", id, fourchette_gauche);
        
        printf("Philosophe %d a fini de manger\n\n", id);
    }
    
    printf("✅ Philosophe %d est rassasié et part!\n", id);
    return NULL;
}

int main() {
    printf("=== Système de fourchettes (Problème des philosophes) ===\n\n");
    
    // 1. Initialiser les fourchettes (mutex)
    for (int i = 0; i < NB_PHILOSOPHES; i++) {
        pthread_mutex_init(&fourchettes[i], NULL);
        printf("Fourchette %d initialisée\n", i);
    }
    
    printf("\n🪑 Table ronde avec %d philosophes et %d fourchettes\n", NB_PHILOSOPHES, NB_PHILOSOPHES);
    printf("Chaque philosophe a besoin de 2 fourchettes pour manger\n\n");
    
    // 2. Créer les philosophes (threads)
    pthread_t philosophes[NB_PHILOSOPHES];
    int ids[NB_PHILOSOPHES];
    
    for (int i = 0; i < NB_PHILOSOPHES; i++) {
        ids[i] = i + 1;
        pthread_create(&philosophes[i], NULL, philosophe, &ids[i]);
        printf("Philosophe %d créé\n", i);
    }
    
    printf("\n--- Les philosophes commencent à penser et manger ---\n\n");
    
    // 3. Attendre que tous les philosophes finissent
    for (int i = 0; i < NB_PHILOSOPHES; i++) {
        pthread_join(philosophes[i], NULL);
    }
    
    // 4. Nettoyer les fourchettes
    for (int i = 0; i < NB_PHILOSOPHES; i++) {
        pthread_mutex_destroy(&fourchettes[i]);
    }
    
    printf("\n🎉 Tous les philosophes ont fini de manger!\n");
    printf("Toutes les fourchettes sont nettoyées.\n");
    
    return 0;
}
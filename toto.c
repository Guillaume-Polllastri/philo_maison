#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Variables globales simples
pthread_mutex_t mutex;
int compteur = 0;

// Fonction simple pour le thread
void *ma_fonction(void *arg) {
    int num = *(int*)arg;
    
    printf("Thread %d commence\n", num);
    
    // Lock le mutex
    pthread_mutex_lock(&mutex);
    compteur++;
    printf("Thread %d: compteur = %d\n", num, compteur);
    pthread_mutex_unlock(&mutex);
    
    printf("Thread %d fini\n", num);
    return NULL;
}

int main() {
    printf("=== Exemple pthread simple ===\n");
    
    // 1. Initialiser le mutex
    pthread_mutex_init(&mutex, NULL);
    
    // 2. Créer 2 threads
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;
    
    pthread_create(&thread1, NULL, ma_fonction, &id1);
    pthread_create(&thread2, NULL, ma_fonction, &id2);
    
    // 3. Attendre les threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // 4. Détruire le mutex
    pthread_mutex_destroy(&mutex);
    
    printf("Fini! Compteur final: %d\n", compteur);
    return 0;
}
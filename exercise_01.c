/*
Implementare un programma in cui un processo padre genera N processi figli.

Il Processo Padre assegna ad ogni figlio un indirizzo (intero > 1) e a se stesso 1.

Ciclicamente (per X volte) il processo padre interroga ogni figlio richiedendo un valore indicante il 
numero di richieste e il figlio risponde al padre che lo stampa a video.

Dopo X richieste il padre ivia un comando di terminazione ai figli e ne attende la terminazione.

Utilizzare una coda di messaggi per la comunicazione tra padre e figli.
*/

// LIBRERIE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// COSTANTI, VARIABILI GLOBALI
#define CMD_RICHIESTA       1
#define CMD_RISPOSTA        2
#define CMD_TERMINAZIONE    3
#define N 5
#define X 10

// PROTOTIPI
void figlio(int indir, int msgid);

// STRUTTURA DELLA PARTE DATI DEL MESSAGGIO DA INVIARE
struct dati {
    int cmd;
    int val;
};

// STRUTTURA DEL MESSAGGIO DA INVIARE
struct messaggio {
    long mtype;
    struct dati mtext;
};

// MAIN
int main() {
    pid_t pid;
    int msg_id, 
	int i, 
	int j, 
	int res;
    struct messaggio msg;

    // Creazione della Coda Di Messaggi
    msg_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if(mrg_id = -1){
    	perror("msgget");
    	exit(EXIT_FAILURE);
	}
	
	// Fulcro del Programma
    for(i=0; i < N; i++) {
        pid = fork();
        switch(pid) {
            case -1:
                perror("Errore fork");
                exit(EXIT_FAILURE);
            case 0:
                figlio(i+2, msgid);
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    for(j=0; j<X; j++) {
        for(i=0; i<N; i++) {
            msg.mtype = i+2;
            msg.mtext.cmd = CMD_RICHIESTA;
            if(msgsnd(msgid, &msg, sizeof(struct dati), 0) == 0) {
                printf("P: Messaggio inviato\n");
                res = msgrcv(msgid, &msg, sizeof(struct dati), 1, 0);
                if(res < 0) {
                    perror("Errore receive");
                } else if (res > 0) {
                    if(msg.mtext.cmd == CMD_RISPOSTA) {
                        printf("Ricevuta risposta da %ld, val: %d\n",
                            msg.mtype, msg.mtext.val);
                    }
                }
            }
        }
        sleep(1);
    }

    /* inviamo il comando di terminazione a tutti i figli */
    msg.mtext.cmd = CMD_TERMINAZIONE;
    for(i=0; i<N; i++) {
        msg.mtype = i+2;
        if(msgsnd(msgid, &msg, sizeof(struct dati), 0) == 0) {
            /** attendiamo la terminazione */
            wait(NULL);
        }
    }

    // Cancellazione della Coda Di Messaggi
    result = msgctl(msgid, IPC_RMID, NULL);
    if(result == -1){
    	perror("msgctl");
    	exit(EXIT_FAILURE);
	}

}

// FUNZIONI
void figlio(int indir, int msgid) {
    struct messaggio msg;
    int cnt = 0;
    do {
        if(msgrcv(msgid, &msg, sizeof(struct dati), indir, 0) >= 0) {
            printf("F: Messaggio ricevuto\n");
            if(msg.mtext.cmd == CMD_RICHIESTA) {
                cnt++;
                msg.mtext.cmd = CMD_RISPOSTA;
                msg.mtype = 1;
                msg.mtext.val = cnt;
                printf("F: Messaggio inviato\n");
                msgsnd(msgid, &msg, sizeof(struct dati), 0);
            }
        } else {
            perror("Errore ricezione\n");
        }
    } while(msg.mtext.cmd != CMD_TERMINAZIONE);
}
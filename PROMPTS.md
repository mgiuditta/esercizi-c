# Prompt pronti

Questi prompt vanno copiati e incollati in una chat con Claude, nel progetto "Matematica e Programmazione".
Sostituisci le parti tra `[parentesi quadre]`.
Ogni README di cartella ha anche dei prompt specifici per il suo argomento, nella sezione "Prompt pronti per questo argomento".

---

## Mentre fai un esercizio

### 1. Suggerimento progressivo (senza la soluzione)
```
Sto facendo l'esercizio [es04] della cartella [09-puntatori-vettori] della mia repo esercizi-c.
Il testo è questo: [incolla il testo dal README].
Sono bloccato qui: [descrivi dove ti sei fermato].
Dammi UN solo suggerimento, il più piccolo che mi sblocca. Non scrivermi codice.
Se te lo chiedo di nuovo, dammi il suggerimento successivo.
```

### 2. Correggi il mio codice (senza riscriverlo)
```
Questa è la mia soluzione per [es07] di [12-memoria-dinamica]:
[incolla il codice]
L'output del test è questo: [incolla l'output di make test, se fallisce].
Dimmi:
1) se è corretta, e se no qual è il primo errore e perché;
2) eventuali errori di memoria o comportamento indefinito, anche se il test passa;
3) cosa direbbe il prof sullo stile.
Non riscrivermi la soluzione intera: indicami le righe da cambiare.
```

### 3. Spiegami il messaggio di errore
```
Compilando/eseguendo [es05] di [12-memoria-dinamica] ottengo questo:
[incolla il messaggio di cc o di AddressSanitizer]
Spiegami riga per riga cosa dice il messaggio, quale riga del mio codice lo causa e perché.
Il mio codice: [incolla]
```

### 4. Ho sbagliato un "Cosa stampa?"
```
Nell'esercizio [es03] di [09-puntatori-vettori] avevo previsto questo output:
[la tua previsione]
L'output vero è questo:
[output reale]
Il codice: [incolla]
Spiegami esattamente dove il mio ragionamento è sbagliato, simulando l'esecuzione
con la tabella delle variabili (e della memoria, se ci sono puntatori) riga per riga.
```

---

## Per studiare un argomento

### 5. Interrogazione
```
Interrogami sull'argomento [puntatori e vettori] del corso Programmazione e Algoritmi I,
usando le trascrizioni e le slide del progetto.
Fammi 8 domande, UNA alla volta, e aspetta la mia risposta prima di passare alla successiva.
Mescola domande di teoria, "cosa stampa questo codice?" e "trova l'errore".
Dopo ogni risposta dimmi se è giusta, cosa manca e il perché.
Alla fine dammi un voto in trentesimi e gli argomenti da ripassare.
```

### 6. Nuovi esercizi dello stesso tipo
```
Generami 3 esercizi nuovi simili a [es07] di [10-strutture-union] (testo nel README),
ma diversi nei dati e nel contesto, con difficoltà crescente.
Per ognuno: testo, esempio di input/output, suggerimento.
Le soluzioni dammele solo quando te le chiedo.
```

### 7. Spiegami una parte della teoria
```
Nel README di [11-puntatori-avanzati-file], nella Teoria flash, non ho capito questo punto:
[incolla il pezzo]
Spiegamelo con un esempio concreto e un disegno della memoria (celle e indirizzi),
collegandolo a quello che ho già visto nelle cartelle precedenti.
```

---

## Verso l'esame

### 8. Correzione "da professore"
```
Fai finta di essere il prof. Anisetti che corregge il compito.
Questa è la mia soluzione per l'esercizio [es04] della simulazione d'esame (cartella 15):
[incolla il codice]
Dammi un voto da 0 a 10 per l'esercizio, con i punti tolti voce per voce
(correttezza, gestione degli errori, memoria, leggibilità, uso corretto dei costrutti visti a lezione).
```

### 9. Simulazione d'appello completa
```
Preparami un appello simulato di Programmazione e Algoritmi I sulla parte in C:
3 esercizi da svolgere in 2 ore (uno su puntatori/vettori, uno su struct + memoria dinamica,
uno su ricorsione o file), diversi da quelli della mia repo esercizi-c.
Dammi solo i testi. Quando ti mando le soluzioni, correggile come un prof.
```

### 10. Ripasso dei miei errori
```
Questi sono gli esercizi della repo esercizi-c in cui ho sbagliato o sono rimasto bloccato:
[elenco: cartella/esercizio + cosa è andato storto]
Trova lo schema comune nei miei errori, dimmi quali concetti non ho ancora capito
e preparami un mini-percorso di ripasso (quali esercizi rifare, in che ordine).
```

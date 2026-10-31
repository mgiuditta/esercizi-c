# esercizi-c

Esercizi di C di Programmazione e Algoritmi I (prof. Anisetti, UniMi SecAI). Copia autonoma della cartella
`anno-1/programmazione-1/esercizi/c` della repo `universita`, che è la copia di riferimento: le modifiche si fanno lì
e si riallineano qui (`rsync -rc --exclude .DS_Store --exclude /README.md --exclude /PROMPTS.md`; README e PROMPTS
di questa repo parlano di "repo esercizi-c", aggiornare a mano solo i conteggi).

Tutto in italiano. Fonti del corso: trascrizioni e slide nella repo `universita`, niente ricerca web.

## Regole
- Leggere `README.md` e `PROMPTS.md` prima di lavorare.
- Formato di un esercizio: starter con `TODO` + `soluzioni/` commentata + `tests/` (almeno 3 casi `.in`/`.out`),
  fonte citata nel README della cartella.
- Mai dire corretto un esercizio nuovo senza `make sol T=NN` verde.
- Test di uno studente: `make test T=09 E=es03`. Non dare la soluzione subito: suggerimento, poi domanda.
- Pratica in stile esame (scritto su carta): prevedere l'output, trovare il bug, scrivere la funzione.

## Skill (utente, in `~/.claude/skills`)
| Richiesta | Skill |
|---|---|
| sessione di studio guidata | `teach-me` (workspace in `universita/anno-1/programmazione-1/learning/`) |
| "sono bloccato su questo esercizio" | `socratic-tutor` |
| "esaminami", "ho finito il blocco X" | `revision-tutor` |

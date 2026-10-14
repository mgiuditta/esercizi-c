# Comandi rapidi. Esempi:
#   make test                 -> testa tutti i TUOI esercizi
#   make test T=03            -> testa solo la cartella 03-...
#   make test T=03 E=es02     -> testa solo l'esercizio es02 della cartella 03
#   make sol                  -> testa le soluzioni (devono passare tutte)
#   make sol T=09             -> testa le soluzioni della cartella 09
#   make nosan T=03           -> come test, ma senza AddressSanitizer (più veloce)

T ?=
E ?=

.PHONY: test sol nosan help

help:
	@sed -n '1,8p' Makefile

test:
	@bash scripts/run_tests.sh $(T) $(E)

sol:
	@SOL=1 bash scripts/run_tests.sh $(T) $(E)

nosan:
	@SAN=0 bash scripts/run_tests.sh $(T) $(E)

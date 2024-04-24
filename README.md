- [ABYSS e Bloom Filters](#abyss-e-bloom-filters)
  - [Installazione](#installazione)
    - [Prerequisiti](#prerequisiti)
  - [Utilizzo](#utilizzo)
    - [Funzioni Hash](#funzioni-hash)
    - [Bloom Filter](#bloom-filter)

# ABYSS e Bloom Filters

Repository per il progetto di Strumenti Formali per la Bioinformatica di Pietro Negri e Francesco Maddaloni.

## Installazione

### Prerequisiti

- <https://github.com/google/cityhash>
- <https://github.com/bcgsc/ntHash>
- e relative dipendenze!

In breve, si tratta di installare entrambe le funzioni hash attraverso l'installazione delle rispettive librerie, in modo che sia possibile linkarle durante la compilazione dei nostri test.

Se entrambe le librerie saranno state installate correttamente sul proprio sistema, basterà scrivere nella shell:

```sh
make all
```

>[!WARNING]
>Se ci sono problemi durante la compilazione, modificare con il proprio compilatore il parametro CXX del makefile.

>[!TIP]
La compilazione manuale può essere fatta ricordando che al sorgente di ogni eseguibile va affiancato il sorgente di Murmurhash3 e ricordando che la compilazione usando le librerie installate necessita di specificare i seguenti flag:
``` sh
-std=c++17 -lnthash -lcityhash
```

Dopo la compilazione gli eseguibili potranno essere lanciati singolarmente, oppure pilotati attraverso gli script shell presenti nella repository.

>[!TIP]
>In particolare, ogni shell script necessita dei permessi di esecuzione:
```sh
chmod +x nomescript.sh
```

## Utilizzo

### Funzioni Hash

A questo punto se si è interessati al benchmark delle prestazioni basta lanciare:

```sh
./benchmarks.h <base_pair> <iterations> <k> <num_hashes> <output_file>
```

Chiaramente sostituendo i parametri con quelli desiderati.
Se si è interessati alla generazione dei valori per valutare la distribuzione delle 3 funzioni hash considerate:

```sh
./distribution.sh <base_pair> <iterations> <k> <num_hashes> <output_file>
```

Se si è interessati a lanciare entrambi i benchmark sequenzialmente:

```sh
./test_suite.sh <base_pair> <iterations> <num_sequences> <k> [num_hash_values...]
```

Dove basta sostituire a "[num_hash_values...]" una sequenza di valori che si vuole avere come hash function count.
Per esempio:

```sh
./test_suite.sh <base_pair> <iterations> <num_sequences> <k> 1 3 5 7
```

Testerà le prestazioni e la distribuzione dei valori quando ogni k-mer viene hashato 1, 3, 5, e 7 volte. Si possono inserire quanti valori quanti si vogliano.

### Bloom Filter
*Questa sezione verrà aggiornata quando avremo terminato il lavoro sull'interfaccia del filtro.*

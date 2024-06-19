# ABYSS e Bloom Filters

- [ABYSS e Bloom Filters](#abyss-e-bloom-filters)
  - [Installazione](#installazione)
    - [Prerequisiti](#prerequisiti)
  - [Utilizzo](#utilizzo)
    - [Funzioni Hash](#funzioni-hash)
    - [Bloom Filter](#bloom-filter)

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

Abbiamo implementato anche un semplice bloom filter, che può essere modificato e osservato in BloomFilter.h.
Ulteriori dettagli sono reperibili [qui](./src/BloomFilter.h).
Per riassumere brevemente, il filtro può essere istanziato con tutte e 3 le funzioni prerequisito, basta utilizzare una sintassi di questo tipo:

```c++
    Bloomfilter<CityHash<string>>* cityFilter = new Bloomfilter<CityHash<string>>(filter_size);
    Bloomfilter<MurmurHash3<string>>* murmurFilter = new Bloomfilter<MurmurHash3<string>>(filter_size);
    Bloomfilter<NtHashFunction<string>>* ntFilter = new Bloomfilter<NtHashFunction<string>>(filter_size, numHashes, k);
```

Il filtro consente di effettuare la insert e la query per un elemento presente al suo interno, in modo molto semplice, come si può vedere qui (estratto dal [test](./src/BloomTest.cpp)):

```c++
    cityFilter->insert(sequence);
    cityFilter->contains(sequence)
```

Ulteriori miglioramenti possono prevedere l'uso di più funzioni hash, o di più funzioni hash simultaneamente, o l'implementazione di alcune delle varianti del filtro viste [qui](./docs/paper/A_Review_on_Role_of_Bloom_Filter_on_DNA_Assembly.pdf).

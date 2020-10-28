# PTR : Labo 3

**Thomas Rieder**

## Etape 1

Le nombre d'itération par seconde ne change pas par rapport au laboratoire précédent

## Etape 2



```shell
# Sans 'dohell' :
---------------------------------------------- summary1.c -----
  Total of 30 values 
    Minimum  = 38.000000 (position = 19) 
    Maximum  = 113.000000 (position = 26) 
    Sum      = 1715.000000 
    Mean     = 57.166667 
    Variance = 201.405556 
    Std Dev  = 14.191743 
    CoV      = 0.248252 
---------------------------------------------------------------
```

```shell
# Avec 'dohell' : 
---------------------------------------------- summary1.c -----
  Total of 90 values 
    Minimum  = 8.000000 (position = 48) 
    Maximum  = 440.000000 (position = 13) 
    Sum      = 2560.000000 
    Mean     = 28.444444 
    Variance = 2077.869136 
    Std Dev  = 45.583650 
    CoV      = 1.602550 
---------------------------------------------------------------
```

On remarque que la variance est environ **10** fois supérieur en lançant le programme avec le `dohell`


## Etape 3

```shell
# sans dohell
---------------------------------------------- summary1.c -----
  Total of 3000 values 
    Minimum  = 4934315.000000 (position = 1321) 
    Maximum  = 5063550.000000 (position = 2061) 
    Sum      = 15000071298.000000 
    Mean     = 5000023.766000 
    Variance = 133839237.687500 
    Std Dev  = 11568.890945 
    CoV      = 0.002314 
---------------------------------------------------------------

```

```shell
# avec dohell
---------------------------------------------- summary1.c -----
  Total of 15000 values 
    Minimum  = 4952735.000000 (position = 14970) 
    Maximum  = 5044975.000000 (position = 14971) 
    Sum      = 75000046694.000000 
    Mean     = 5000003.112933 
    Variance = 2844985.324219
    Std Dev  = 1686.708429 
    CoV      = 0.000337 
---------------------------------------------------------------

```

En moyenne, la gigue reste pratiquement la même avec ou sans le `dohell`, nous avons juste une plus grosse variance sans le `dohell` (**47** fois plus grande).


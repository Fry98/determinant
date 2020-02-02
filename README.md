# Determinant
## Implementace
Tento program využívá **Gaussovu Eliminační Metodu** pro výpočet determinantu čtvercové matice. Matice je nejprve upravena na horní trujúhelníkový tvar a poté je vypočítán součin prvnků na hlavní diagonále, který se rovná determinantu. Časová komplexita tohoto algoritmu je O(n^3). Pro velké matice *(např. 1000 x 1000)* však nastává problém s ukládáním výpočtu a proto je využitý datový typ `long double`. Ten se však svojí implementací liší na různých platformách a například při kompilaci přes **MSVC** *(kde se `long double` chová identicky jako `double`)*, tak některé velké matice vrací determinant o hodnotě `inf`, případně `-inf`. Nenarazil jsme však na žádné problémy při kompilaci přes **gcc** na **Linuxu**.

Pokud jde o datovou reprezentaci samotné matice, tak jsem vytvořil třídu `Matrix`, která si vkládaná data ukládá do vektoru a poskytuje API pro přístup k souřadnicím matice. Díky tomu, že program předem nealokuje skutečné dvourozměrné pole tak není potřeba, aby byly dimenze matice dopředu zadané uživatelem. Tato třída také kontroluje, zda je matice opravdu čtvercová a stará se o samotný výpočet determinantu. Pro účely testování rovněž umožňuje výpis do `std::ostream`.

Aplikace také využívá vlákna a to pro zpracování několika vstupních souborů najednou. Výkonnostní benefity jsou tak vidět pouze při hromadném výpočtu determinantu z několika matic.
## Použítí
Vstupní data programu jsou určena flagem `--input` nebo mohou být vepsána do `stdin` *(umožňuje výpočet pouze jedné matice)*. Příklady použítí vypadjí takto:
```
determinant --input soubor1.txt;soubor2.txt;soubor3.txt
```
```
determinant < soubor1.txt
```
Vstupní matice musí být zapsaná ve formátu, kdy jednotlivá čísla v řádku jsou oddělené jakýmkoliv nenumerickým znakem *(číslice, mínus a tečka)* a řádky matice jsou oddělené novým řádkem *(`\n`)*. Příklad vstupních dat *(kde je jako oddělovcí znak použítá mezera)*:
```
5 7 4 2
6 2 8 1
3 5 2 7
9 8 1 0
```
&nbsp;

Program také umoňuje výpis výsledků do souboru pomocí flagu `--output`. Pokud neni flag specifikován, tak jsou výsledky vypsány do `stdout`. Příklad použítí vypadá takto:
```
determinant --output vystup.txt
```
&nbsp;

Další dostupné flagy potom jsou:
- `--no-index`
  - Vypne indexování u vypisovaných výsledků
- `--single-thread`
  - Aplikace poběží pouze v jednom vlákně a vstupní soubory budou zpracovány sekvenčně *(tento flag je ignorován pokud je také zadaný `--perf-comp`)*
- `--pref-comp`
  - Spustí vypočet determinantu jak v paralelním, tak i jednovláknovém módu. Během toho si měří délku zpracování a na konci běhu vypíše porovnání těchto módů. *(Není dostupné pro vstup z `stdin`, jelikož je možné vložit pouze jednu matici a paralelní zpracování tak nenabídne žádný benefit)*
- `--help`
  - Vypíše seznamn dostupných příkazů

## Výkon
### Výkon pro jednu matici
- **Matice 10x10**: 0 ms
- **Matice 100x100**: 3 ms
- **Matice 500x500**: 340 ms
- **Matice 1000x1000**: 5 748 ms
### Výkon při paralelním zpracování
- **3x Matice 10x10**
  - Single-threaded: 0 ms
  - Multi-threaded: 11 ms *(pro takto malé matice je cena spouštění vláken větší než samotný výpočet)*
- **3x Matice 100x100**
  - Single-threaded: 15 ms
  - Multi-threaded: 12 ms
- **3x Matice 500x500**
  - Single-threaded: 1 215 ms
  - Multi-threaded: 525 ms
- **3x Matice 1000x1000**
  - Single-threaded: 14 473 ms
  - Multi-threaded: 5 515 ms

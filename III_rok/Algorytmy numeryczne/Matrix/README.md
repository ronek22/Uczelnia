# Instrukcja

## Początek
Mamy dwa programy:

* ***c++ :*** `eig.cpp`
* ***Java:*** `Main.java, Matrix.java, Fraction.java`

Zaczynamy od **c++**, bo tam generuje macierze i obliczam je z pomocą **Eigena**,
następnie eksportuje dane z macierzami do pliku `danecpp.txt`, a wyniki z eigena do `wynikicpp.txt`

### Eig.cpp
Pierwsze sprawa kompilacji, kompilujemy za pomocą komendy:
`g++ -I pathToEigen -std=c++11 -O3`, flaga `-O3` zapewnia najlepsza optymalizacje dzięki temu program sie bardzo szybko wykonuje, aczkolwiek dłuzej kompiluje.

Zacznijmy od funkcji `main`. Chce wygenerowac ulamki zwykle typu: `2/4, 3/4`, nie dziesietne. Tworze **vector** do licznika i mianownika. Tworze generator liczb pseudolosowych, za pomocą
```cpp
uniform_int_distribution<> dist_num{ -100, 100}
uniform_int_distribution<> dist_den{ 1, 100}
```
Czyli w liczniku generuje `inty` od `-100 do 100`, a w mianowniku od `1 do 100`, aby uniknąc problemu dzielenia przez `0`.

Otwieram pliki do zapisu:
```cpp
ofstream dane ("danecpp.txt");
ofstream wyniki("wynikicpp.txt");
```

Pierwsza petla wykona sie tyle razy dla ilu rozmiarow macierzy chcemy np. `od 2 do 20`
Druga petla decyduje o tym ile wykonac testow dla macierzy tego samego rozmiaru.

Zapisuje rozmiar macierzy do pliku, nastepnie generuje liczniki i mianowniki dla calej macierzy.
```cpp
dane << i << endl;
for (int j = 0; j < i*i; j++) {
    numerators.push_back(dist_num(generator));
    denominators.push_back(dist_den(generator));
}
```
 Tworze **macierz eigenowska**, do pliku z danymi wprowadzam kolejne elementy macierzy po spacji, tak więc w jednym wierszu bedzie zapisana cala macierz w takim stylu: `2/4 1/9 2/1 3/7`, a do Macierzy Eigenowskiej wprowadzam te wartosci konwertujac licznik na `double` i dzielac przez mianownik.
 ```cpp
 int ind = 0;
 MatrixXd A(i, i);
 for (int row = 0; row < i; row++) {
     for (int col = 0; col < i; col++) {
         dane << numerators[ind] << "/" << denominators[ind] << " "; // do pliku
         A(row, col) = (double)numerators[ind] / denominators[ind]; // do eigena
         ind++;
     }
 }
 ```

 Czyszcze wektory z licznikiem i mianownikiem i analogicznie uzupelniam **Macierz B i C**.

 Nastepnie przechodze do generowania wektorow **X i B**. Teraz generuje tylko tyle licznikow i mianowniku jaki jest rozmiar macierzy. Wypelniam eigenowski wektor tymi wartosciami tak samo jak przy macierzy, i zapisuje do pliku.
 ```cpp
 // GENEROWANIE WEKTOROW
 for (int j = 0; j < i; j++) {
     numerators.push_back(dist_num(generator));
     denominators.push_back(dist_den(generator));
 }

 ind = 0;
 VectorXd vX(i);
 for (int j = 0; j < i; j++) {
     dane << numerators[ind] << "/" << denominators[ind] << " ";
     vX(j) = (double)numerators[ind] / denominators[ind];
     ind++;
 }
 ```

 Wygenerowalismy wszystkie macierze i wektory w pierwszej petli, czas odpalic dzialania, ktore mielismy wykonac.

 Napisalem dwie funkcje do testowania, ktore roznia sie sposobem liczenia czasu wybieramy funkcje `test`, ktora mierzy za pomoca biblioteki `chrono`.
 `IOFormat` powoduje, ze zapisujemy wyniki obliczen z dokladnoscia `16` cyfr po przecinku, wyniki zapisywane sa po spacji, ulatwi to pozniej odczytanie tego w `Javie`.
 Tworze testowa macierz `pr`, do pliku z wynikami **zapisuje wielkosc macierzy**. Kazdy test wykonuje `1000` razy i biore sredni czas. Do pliku zapisuje wynik dzialania w ten sposob: `1.21241 2.532 4.2112 1.1211|21212`, to co znajduje sie po `|` jest to czas dzialania, a przed rezultaty obliczen.

## Java
### Matrix.java

Jest to klasa generyczna, czyli tworzac obiekt tej klasy mozemy ja wywolac z dowolnym typem*. Klasa przechowuje trzy pola:
* `N` - *wielkosc macierzy*
* `data[][]` - *macierz jako tablica dwuwymiarowa*
* `val[]` - *tablica przechowujaca dane macierzy z pliku, za pomoca `val` uzpelniamy macierz wartosciami z pliku*

Metody `fill` sluza do wypelnienia macierzy lub wektora(po prostu tablica jednowymiarowa) za pomoca tablicy jednowymiarowej.

Metody ***dodawania*** i ***mnozenia*** opisane w kodzie komentarzami.

#### Metody Gaussa
* `solve` - Gaussa podstawowa, kopiuje wartosci Wektora B i Macierzy do tablic tymczasowych, aby nie zmieniac ich wartosci (pozniejsze testy wykonywane sa na tych samych macierzach.) *Poszczegolne operacje opisane komentarzami w kodzie.*
* `solvePartial` - Gaussa z czesciowym wyborem. Analogiczne kopiowanie do tablic tymczasowych, szukamy najwiekszej wartosci w kolumnie, jak znajdziemy zamieniamy wiersza najwiekszego z dotychczasowym i zerujemy nizsze kolumny za pomoca operacji na wierszach.
* `solveFull` - z pełnym wyborem, tym razem nie szukamy maxa tylko w kolumnie, ale takze w wierszach. Jednak jesli zamieniamy kolumne to kolejnosc zmiennych nam sie zmienia. Dlatego tworzymy osobna tablice to zapamietania kolejnosci zmiennych, po rozwiazaniu ukladu sortujemy.

[Przyklady jak to dziala ](http://mathfaculty.fullerton.edu/mathews/n2003/pivoting/PivotingMod/Links/PivotingMod_lnk_3.html)

#### Jak jest zaimplementowana generycznosc?
Java slabo wspiera generycznosc, nie da sie przeciazyc operatorow, dlatego zamiast dodawania macierzy w stylu: `a+b`, mamy `a.add(b)`
Dla każdej operacji takiej jak `dodawanie, mnozenie, dzielenie, odejmowanie, wieksze, mniejsze, wartosc bezwzgledna, wypelnianie zerami`, musimy recznie konwertowac typy, z ktorych chcemy korzystac do typu generycznego: Przyklad dodawania dwoch liczb. Takze w klasie Matrix mozemy korzystac tylko z `Float, Double i Fraction`
```cpp
@SuppressWarnings("unchecked")
private <T> T add(T one, T two){
    if(one.getClass() == Float.class){
        return (T) Float.valueOf(((Float) one).floatValue() + ((Float) two).floatValue());
    }
    if(one.getClass() == Double.class){
        return (T) Double.valueOf(((Double) one).doubleValue() + ((Double) two).doubleValue());
    }
    if(one.getClass() == Fraction.class){
        return (T) ((Fraction) one).add(((Fraction) two));
    }
    throw new RuntimeException("NIEOBSLUGIWANY TYP");
}
```
Analogicznie napisane sa pozostale operacje.

### Fraction.java
Implementacja ułamka za pomocą typu `BigInteger`

Mamy dwa pola typu `BigInteger` numerator(licznik) i denominator(mianownik). Mamy `3` konstruktory, aby łatwiej tworzyc ulamki.

```Java
Fraction a = new Fraction(4); // 4/1
Fraction b = new Fraction(3,7); // 3/7
Fraction c = new Fraction("4/7"); // 4/7
```

Podczas tworzenia ulamka za kazdym razem wywolujemy funkcje `init`, ktora sprawdza czy w mianowniku nie mamy zera, przywracamy ulamek do kanonicznej formy( jesli w mianowniku mamy -, to zmieniamy, zeby w liczniku byl -) i skracamy ulamek. Ułamek skracamy rowniez w kazdej metodzie. Kod, ktory skraca ulamek:
```Java
BigInteger gcd = num.gcd(den);
if (!gcd.equals(BigInteger.ONE)) {
    num = num.divide(gcd);
    den = den.divide(gcd);
}
```

Operacje na ulamkach sa na tyle proste, ze nie bede tego tlumaczyl.
Metody `toFloat` i `toDouble` konwertuja ulamek do typu `Float` i `Double`

### Main.java
Tu przeprowadzane sa wszystkie testy. Wynik testow bedzie zapisany do pliku `bledy.csv`. Pierwsza linijka tego pliku to nazwy kolumn.
`n` - to rozmiar macierzy, `fr|fl|d|e` - to typy, `1-6` to po kolei obliczenia do wykonania.

Dla kazdego typu potrzebuje `3` macierzy i `2` wektorow. Mamy `3` typy do przetestowania, takze na poczatku deklarujemy 15 obiektow z ktorych bedziemy korzystac.

Do zmiennej `size` zapisuje wielkosc macierzy z pliku z danymi. Wykonuje petle dopoki nie skonczy sie plik z danymi. Ustawiam `switcha` z `5` case'ami. Gdy `case = 0`, mam pierwsza linijke(po rozmiarze macierzy) pliku z danymi, czyli Macierz A, a wiec generuje z tej linijki `3` Macierze A. Przechodze do nastepnej iteracji petli teraz `case = 1`, a wiec generuje `3` Macierze B z drugiej linijki itd. Az dojdziemy do `case = 5`, czyli mamy juz wygenerowane `3` Macierze i `2` Wektory.

 Do pliku z bledami dopisujemy rozmiar macierzy i stawiamy przecinek. Za pomoca `System.nanoTime` liczymy blad w nanosekundach. Za pomoca funkcji `liczBlad` obliczamy blad w stosunku do Eigena. Do pliku z bledami dopisujemy: `blad,czas,` Przed obliczeniem kazdej operacji(`A*X`, `(A+B+C)*X`...) pobieramy linie z wynikami z pliku `wynikicpp.txt`, wyniki wrzucamy do tablicy typu `Double`, a czas Eigena do zmiennej `czas_eig` typu `Double`.

# KONIEC :D

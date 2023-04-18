# Program z windami

## Założenia

Program sterujący działaniem wind w systemie, w którym panele wyboru pięter
umieszczone są na piętrach, nie w samych windach.

## Główne klasy

### Pasażer

Pasażer będzie wsiadał do windy, która będzie jechała na piętro, na które się on udaje.

Sprawdza więc, na jakie piętro jedzie winda i czy jest dość miejsca, by do niej wsiąść.

Kiedy zaś jest w windzie, a bieżące piętro jest jego piętrem docelowym, wtedy wysiada z windy.

### Winda

Winda wie, na jakim piętrze się znajduje, i informuje o tym swoich pasażerów. Dzięki temu
mogą oni wysiąść na odpowiednim piętrze.

Winda jedzie z piętra na piętro, a na każdym piętrze sprawdza, czy jest to piętro,
na którym powinna się zatrzymać. Jeśli tak, zatrzymuje się, wtedy mogą do niej wsiadać 
i z niej wysiadać pasażerowie.

Jeśli się zatrzymuje, to usuwa z listy swoich przystanków bieżące piętro.

Winda przestaje jechać, jeśli nie ma w niej żadnych pasażerów i żadnych 
miejsc na liście przystanków.

### Dyspozytor

Dyspozytor, zwany też menedżerem, otrzymuje informację od pasażera, który stojąc na jakimś
piętrze naciska guzik z numerem piętra docelowego.

Wtedy dyspozytor sprawdza, czy jakaś winda nie jedzie już do tego przystanku. Jeśli tak, 
nie robi nic. Jeśli żadna winda tego nie robi, to on wybiera windę, której wpisuje numer
piętra (piętra pasażera i jego piętra docelowego ) na listę przystanków. Robi to w najprostszy
sposób: losując windę.

## Rodzaje wind

### Winda klasyczna

Mówi o sobie: *Jestem windą klasyczną, jeżdżę zawsze w tym samym kierunku do końca*.
I dodaje: 
wezwana najpierw skończę swoją drogę, pasażerów odbiorę w drodze powrotnej.


### Winda nowoczesna

Dumna jest z tego, że może zmieniać kierunek w czasie jazdy. Gdy jest pusta i stoi,
a otrzyma od dyspozytora wezwanie, to od razu jedzie w kierunku właściwego piętra.

### Winda pospieszna

Nie wiadomo, czy nazwać ją windą supernowoczesną czy superstaroświecką. Jeśli do niej
wsiądziemy, to już się nie zatrzymamy po drodze i dojedziemy do wskazanego piętra.

Niestety, ta ostatnia winda, choć chwali się że *dowozi bez zbędnych przystanków*,
w rzeczywistości zachowuje się jeszcze bardzo niestabilnie. 

## Piętro

Cóż, piętro potrzebne jest chyba tylko jako parametr dla windy, dyspozytora i pasażera.
Chociaż pisząc niniejszy program można się było zastanowić, czy pasażer nie będzie
na przykład zastanawiał się, czy nie pozostać w windzie, jeżeli na piętrze 
będą na niego czekali ludzie, których nie chce spotkać. 

Również samo wsiadanie do windy nie jest takie proste. Pasażer może zastanowić się, 
do której windy wsiąść - jeśli na tym samym zatrzymają się i otworzą różne windy.
Ale też może mieć pierwszeństwo przy wsiadaniu, co może znaczyć, że inni pasażerowie
muszą go widzieć i wiedzieć, że mogą wsiąść dopiero wtedy, gdy wejdzie do windy
osoba uprzywilejowana.

Dlatego piętro się przyda. Na razie jednak nie rozróżniamy pasażerów (ani np. wind
bagażowych) i nie pozwalamy im obserwować innych osób na tym samym piętrze. Wiedzą tylko,
czy zmieszczą się w windzie.

## Paradoksy programu

Program był ćwiczeniem w języku C++. Mieliśmy dwa ważne zadania: przećwiczyć *dziedziczenie* i 
*szablony*. I oczywiście były z tym trudności.

- Ze zwykłym programowaniem, bez tych zagdnień, nie zanosiło się na trudności. 
Ale kiedy się okazuje, że pasażerowie muszą coś wiedzieć o wszystkich windach,
a winda o wszystkich pasażerach, którzy do niej weszli... kiedy trzeba umieścić obiekty
klasy A w polach przynależnych klasie B, jednocześnie przypisując tej klasie B obiekty typu A...
Cóż, rozwiązanie się znalazło i nazywa się *deklaracją wstępną* (forward declaration). 
Polega na deklarowaniu czegoś, czego nie ma, i to nie zawsze wiadomo czy w nagłówku
czy w pliku cpp. Nawet kompilator nie do końca wie, jakie miejsce jest najwłaściwsze. 

- *Dziedziczenie* to taka niewinna zabawa programistów, którzy wiedzą, co to jest klasa 
abstrakcyjna. Co za okazja do sprawdzenia, czy wzorzec projektowy *strategia* jest 
rzeczywiście "królową wszystkich wzorców" (pewnie że jest!). Ale można wiele powiedzieć
o tym, ile to kompilator ma zastrzeżeń przy budowaniu destruktorów wirtualnych.
Są przecież dziedziczone i pozwalają ratować się przed wyciekami pamięci klas pochodnych
Zastrzega, że muszą być, a potem zastrzega, że powodują problemy których by bez nich nie było.

- *Szablony*. Można westchnąć i powiedzieć: przecież szablony są podstawą posługiwania się
naszą ulubioną biblioteką STL, zatem użycie czegokolwiek z tej biblioteki jest już spełnieniem
wymogu "użyj szablonu". No, nie tak do końca. Co prawda sposób posługiwania się tą biblioteką
pozwala z dumą patrzeć w lustro ("jestem mistrzem!"), a różne tajemnicze operacje z użyciem
dwukropka dowodzą, że język C++ jest coraz bardziej podobny do ukochanego Pythona. 
Lecz nie na tym to polega. Nie na tym też polega użycie szablonu, by zapełniać program różnymi 
wskaźnikami (i potem martwić się, czy usuniemy z pamięci te wszystkie anonimowe obiekty).
Tutaj udało się wreszcie, zgodnie z wszelakim książkowym przeznaczeniem, zastosować szablon
do najważniejszej rzeczy, to znaczy do tworzenia obiektów. Trzeba było wpaść na to, że 
szablony służą właśnie takim konstrukcjom. Konstrukcjom i konstruktorom. Tych różnych rodzajów 
wind, a w przyszłości pasażerów, a może nawet i dyspozytorów.

```
T *p = new T();
```


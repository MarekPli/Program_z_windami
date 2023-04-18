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

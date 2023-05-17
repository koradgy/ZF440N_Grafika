# Féléves feladat leírása

A feladat célja egy kisebb lakóterület létrehozása, amely a W, A, S, D billentyűk segítségével navigálható.
Két sorban helyeztem el összesen 4 házat, ezek között kell majd az állatokat megkeresni.
A házak azonos modellt és textúrát használnak, a területen 2-2 ház található egymás mellett.

A játék története, hogy az egyik lakos két háziállata elszökött, egy kacsa és egy nyúl.
Ezekért indul a házak közé, hogy megkeresse őket, viszont elbújtak. 
A játékos ezt a személyt irányítja, és feladata megtalálni a két kiskedvencet.
Közben egy raptor járkál a házak között, ha a játékos nekimegy, akkor a raptor elkapja és vége a játéknak.

A két állat fix pontokon lett elhelyezve a házak között, saját tengelyük körül forogva jelzik, hogy begyűjtheőek.

## Irányítás
* W,A,S,D - mozgás irányítása
* F1 - help menú
* F11 - fényerő le
* F12 - fényerő fel
* Esc - játék bezárása

## A játék hangjai
A játékban megjelenik két hangeffekt. Az egyik jelzi a játékosnak, hogy sikeresen begyűjtött egy állatot, illetve egy ami a játék végét jelzi,
ezzel együtt megjelenik egy kép is, ami gratulál a játékosnak.
A hangokat az SDL_mixer könyvtár segítségével implementáltam.

# Féléves feladat leírása

A feladat célja egy egyszerű 3 dimenziós falu létrehozása, amely a W, A, S, D billentyűk segítségével navigálható.

A játék története, hogy egy embernek elszökött két háziállata, egy kacsa és egy nyúl.
Ezekért indul a faluba, hogy megkeresse őket, viszont elbújtak. A játékos feladata megtalálni a két kiskedvencet.

A két állat fix pontokon lett elhelyezve a faluban, saját tengelyük körül forogva jelzik, hogy begyűjtheőek.

## Irányítás
* W,A,S,D - mozgás irányítása
* F1 - help menú
* F11 - fényerő le
* F12 - Fényerő fel
* Esc - játék bezárása

## A játék hangjai
A játékban megjelenik két hangeffekt. Az egyik jelzi a játékosnak, hogy sikeresen begyűjtött egy állatot, illetve egy ami a játék végét jelzi,
ezzel együtt megjelenik egy kép is, ami gratulál a játékosnak.
A hangokat az SDL_mixer könyvtár segítségével implementáltam.

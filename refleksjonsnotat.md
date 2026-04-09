# Refleksjonsnotat
Til å begynne med laget jeg en verden som kunne tegnes. Spilleren var en egen tiletype. Jeg fant etter hvert ut at det lønte seg å lage en egen Player-class som var adskilt fra selve "brettet". I steden for at jeg flyttet spilleren ved å bytte plass på tiles så endret jeg det til at spilleren ble tegnet over verdenen og spilleren flyttet på seg fordi spillerklassen hadde rad- og kollonneindekser som ble endret.

I forbindelse med knappeinput så støtte jeg på problemet om at spilleren flyttet seg i forhold til hvor lenge en knapp ble holdt nede. Jeg ønsket at lengden på et knappetrykk skulle være irrelevant. Dette løste jeg ved å lage bools for knappene som sa om de allerede var trykket.

I utviklingen av handle_input()-funksjonen hadde jeg til å begynne med ingen hjelpefunksjoner. Det gjorde koden tidvis vanskelig å lese og debuge. Funksjonene i PlayerRules og PlayerActions gjorde ting betydelig mer oversiktlig.

Først etter at jeg hadde en verden, med en spiller som kunne grave seg rundt som den skulle la jeg til ting som liv, hjerter og gull. Etter at gull var på plass la jeg til mulighet for å komme til nye levler. Etter det la jeg til flammer som skadet spilleren. Deretter ble game over tegnet på skjermen med hvilket level som var oppnådd. Til slutt lagde jeg filer for å lagre highscore og tegnet topp 10 sammen med game over.

Utviklingsprosessen var iterativ. Jeg fikk på plass ny funksjonalitet, så at det fungerte, og måtte deretter rydde opp i koden ved flere anledninger. Jeg brukte git underveis og commita hver gang en ny feature fungerte.

Til slutt var det viktig å sette en så høy rekord at ingen slår meg i etterkant :)
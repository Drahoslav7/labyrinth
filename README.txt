/*! \mainpage Labyrint
 


Projekt do předmětu ICP

LABYRINT
==============

client-server hra


Autoři:
Drahoslav Bednář - xbedna55
Jiří Kunčák - xkunca07

ZÁKLADNÍ INFORMACE
==============

Hra je rozdělena na dva spustitelné soubory. Server a klient. Zdrojové kódy jsou přeložitelné jak na platformě Windows tak na platformě Linux.

SPUŠTĚNÍ
==============
MAKE (nutný pro vytvoření spustitelných souborů)
Jedná se o kompilaci zdrojových, která je přizpůsobena pro Linux i Windows. 
Výčet přikazů pro script make: 
	make - zkompiluje server a klienta
	make doxygen - vytvoří dokumentaci projektu, která je automaticky generovaná pomocí programu doxygen
	make doc - stejné jako 'make doxygen'
	make run - spustí server na portu 1620
	make runclient - spustí klienta s hostname localhost a portem 1620

SERVER
--------------
Server se spouští jako labyrinth2015-server s jedním parametrem a to je šíslo portu. Server běží nadále sám a není u něj potřeba žádná obsluha.

KLIENT
--------------
Klient se spouští jako labyrinth2015 se dvěma parametry a to jsou hostame serveru a port na které server běží. Klient se ovládá kombinací příkazů a parametrů. Příkaz a parametry jsou odděleny vždy jednou mezerou. Seznam použitelných příkazů si můžete vypsat pomocí příkazu 'HELP' (psáno bez uvozovek).

KLIENT
==============
PŘÍKLADY SPUŠTĚNÍ
--------------
	
SEZNAM PŘÍKAZŮ PRO ZALOŽENÍ NOVÉ HRY
- IAM [nickname] --> CREATE --> INVITE [nickname] --> NEWGAME --> NEW [A-E][0/1] --> začátek hry

SEZNAM PŘÍKAZŮ PRO ZALOŽENÍ ULOŽENÉ HRY
- IAM [nickname] --> CREATE --> INVITE [nickname] --> LOADGAME --> LOAD [nazev hry] --> začátek hry

SEZNAM PŘÍKAZŮ PRO PŘIPOJENÍ SE DO HRY
- IAM [nickname] --> ACCEPT --> začátek hry

HERNÍ PRINCIP
--------------

SEZNAM PŘÍKAZŮ PRO HERNÍ TAH
ROTATE --> SHIFT [0-3][A-E] --> MOVE [A-M][A-M] --> na tahu je další hráč
- Počet zadání příkazu ROTATE je neomezen.
- Příkaz SHIFT je možné zadat pouze jednou a po zadání už nemůžete použít příkaz ROTATE. 
- Po zadání příkazu MOVE je na tahu automaticky další hráč.

OSTATNÍ
- Hru může uložit každý hráč který je na tahu příkazem SAVE [název hry].
- Do hry vás může pozvat hráč, který hru vytváří. Čekající hráč se do hry samovolně připojit nemůže.
- Pozvánku do hry je možno přijmout i zamítnout příkazy ACCEPT a DECLINE.

SEZNAM PŘÍKAZŮ
==============
IAM [nickname]			
	- vyberete si přezdívku
	- nickname - vaše vybraná přezdívka (smí obsahovat pouze malá a velká písmena a čísla)

CREATE			
	- vyberete možnost založit hry

WHOISTHERE
	- vypíše seznam hráčů čekajících na pozvánku do hry

INVITE [nickname hrace]
	- pozve hráče do vaší hry
	- nickname hrace - přezdívka hráče, kterého chcete pozvat

ACCEPT
	- přijmete pozvánku do hry

DECLINE
	- odmítnete pozvánku do hry

NEWGAME 
	- vybere možnost založení nové hry

NEW [A-E][0/1]	
	- prikaz pro konfiguraci hry
	- [A-E] - znak pro vyber velikosti herni desky - A = 5x5 ... F = 13x13
	- [0/1] - znak pro vyber poctu karet v balicku - 0 = 12, 1 = 24
LOADGAME
	- vyberete možnost nahrání uložené hry a vypíše hry ze kterých můžete vybírat

LOAD [nazev hry]
	- vyberete uloženou hru která bude nahrána
	[nazev hry] - nazev vybrané hry 			

ROTATE
	- otočí blok který je navíc o jedna do prava

SHIFT [0-3][A-F]
	- vloží blok do jednoho z šipkou označených řádků/sloupců a blok na druhé straně bude vytlačen ven
	- [0-3] - znak pro výběr z jaké strany chcete blok zasunout - 0 = shora, 1 = zprava, 2 = zespod, 3 = zleva
	- [A-F] - znak pro výběr řádku/sloupce označeného šipkou - označeno zleva doprava, shora dolů

MOVE [A-F][A-F] 
	- pohne figurkou na určené pole a předá tah dalšímu hráči
	- [A-F] - znak pro výběr řádku/sloupce - označeno zleva doprava, shora dolů

SAVE [nazev hry]			
	- uloží hru 
	- [nazev hry] - název pod kterým bude hra uložena

ZABEZPEČENÍ
==============
Veškeré výpočty a logické operace jsou prováděny na serveru a klientům je posílaná pouze informace o provedených změnách. Tyto změny si poté zpracují a upraví so podle nich herní plochu a tabulku skóre ve svoji paměti. Ty se poté zobrazují klientovi v konsoli.

PERLIČKY
==============
Místo příkazu IAM je možní zadat příkaz GODMODE, který mí přístupný některé další příkazy ať udělá cokoliv. Určeno pouze k testování. Příkazem KILL [nick] může ukončit klienta jakémukoliv hráči.

 */
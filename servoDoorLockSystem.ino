#include <Adafruit_LiquidCrystal.h> // Knižnica pre LCD displej
#include <Servo.h> // Knižnica pre servo motor
#include <Keypad.h> // Knižnica pre klávesnicu

Servo servo; // Vytvorenie objektu servo

const byte ROWS = 4; // Počet riadkov na klávesnici
const byte COLS = 4; // Počet stĺpcov na klávesnici
char keys[ROWS][COLS] = { // Definícia tlačidiel na klávesnici
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; // Piny pripojené na riadky klávesnice
byte colPins[COLS] = {3, 2, 1, 0}; // Piny pripojené na stĺpce klávesnice

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Vytvorenie objektu pre klávesnicu

Adafruit_LiquidCrystal lcd(0); // Vytvorenie objektu pre LCD displej

const char aktualneHeslo[] = "0000"; // Preddefinované heslo
int dlzkaHesla = sizeof(aktualneHeslo) - 1; // Dĺžka hesla
char *zadaneHeslo = (char*)malloc(sizeof(char) * (dlzkaHesla + 1)); // Dynamická alokácia pamäte pre zadané heslo
int pocet = 0; // Počet zadaných znakov

bool dvereZatvorene = true; // Stav dverí (zatvorené/otvorené)

void setup(){
  servo.attach(12); // Pripojenie serva na pin 12
  lcd.begin(16,2); // Inicializácia LCD displeja s veľkosťou 16x2
  lcd.print("Zadajte heslo"); // Zobrazenie uvítacej správy na displeji
  servo.write(0); // Nastavenie serva na počiatočnú pozíciu (zatvorené)
  lcd.setCursor(0, 1); // Nastavenie kurzora na druhý riadok LCD displeja
}

void loop(){
  char stlacenyZnak = keypad.getKey(); // Získanie stlačeného znaku z klávesnice

  if(dvereZatvorene) zatvorene(stlacenyZnak); // Ak sú dvere zatvorené, volaj funkciu zatvorene()
  else otvorene(stlacenyZnak); // Ak sú dvere otvorené, volaj funkciu otvorene()
}

void zatvorene(char znak){
  if(znak){ // Ak je stlačený nejaký znak
    if(znak >= '0' && znak <= '9'){ // Ak je stlačený znak číslo
      if(pocet < dlzkaHesla){ // Ak ešte neboli zadané všetky znaky hesla
        lcd.print('*'); // Zobrazenie hviezdičky na displeji namiesto čísla
        zadaneHeslo[pocet] = znak; // Uloženie znaku do zadaného hesla
        pocet++; // Zvýšenie počtu zadaných znakov
      }
    }
    else if(znak == 'D'){ // Ak je stlačené tlačidlo 'D'
      if(pocet == dlzkaHesla){ // Ak bolo zadané celé heslo
        if(hesloJeSpravne()) otvorDvere(); // Ak je heslo správne, otvor dvere
        else zleHeslo(); // Ak je heslo nesprávne, zobraz chybu
      }
    }
  }
}

void otvorene(char znak){
  if(znak == 'C') zatvorDvere(); // Ak sú dvere otvorené a je stlačené 'C', zatvor dvere
}

bool hesloJeSpravne(){
  for(int i = 0; i < dlzkaHesla; i++){ // Porovnanie každého znaku zadaného hesla s aktuálnym heslom
    if(zadaneHeslo[i] != aktualneHeslo[i]) return false; // Ak sa niektorý znak nezhoduje, heslo je nesprávne
  }
  return true; // Ak sa všetky znaky zhodujú, heslo je správne
}

void otvorDvere(){
  lcd.clear(); // Vyčistenie displeja
  lcd.print("Spravne heslo"); // Zobrazenie správy o správnom hesle
  delay(2000); // Pauza na 2 sekundy
  lcd.clear(); // Vyčistenie displeja
  lcd.print("Dvere otvorene"); // Zobrazenie správy o otvorení dverí
  lcd.setCursor(0, 1); // Nastavenie kurzora na druhý riadok
  lcd.print("<C>=> Zatvorenie"); // Zobrazenie správy o zatvorení dverí
  servo.write(90); // Nastavenie serva na pozíciu otvorenia
  dvereZatvorene = false; // Zmena stavu dverí na otvorené
}

void zatvorDvere(){
  servo.write(0); // Nastavenie serva na pozíciu zatvorenia
  resetHesla(); // Resetovanie zadaného hesla
  lcd.clear(); // Vyčistenie displeja
  lcd.print("Zadajte heslo"); // Zobrazenie správy o zadávaní hesla
  lcd.setCursor(0, 1); // Nastavenie kurzora na druhý riadok
  dvereZatvorene = true; // Zmena stavu dverí na zatvorené
}

void zleHeslo(){
  lcd.clear(); // Vyčistenie displeja
  lcd.print("Zle heslo"); // Zobrazenie správy o nesprávnom hesle
  lcd.setCursor(0, 1); // Nastavenie kurzora na druhý riadok
  lcd.print("Skuste znova"); // Zobrazenie správy o opätovnom pokuse
  delay(2000); // Pauza na 2 sekundy
  resetHesla(); // Resetovanie zadaného hesla
  lcd.clear(); // Vyčistenie displeja
  lcd.print("Zadajte heslo"); // Zobrazenie správy o zadávaní hesla
  lcd.setCursor(0, 1); // Nastavenie kurzora na druhý riadok
}

void resetHesla(){
  pocet = 0; // Resetovanie počtu zadaných znakov
  memset(zadaneHeslo, 0, sizeof(zadaneHeslo)); // Vymazanie obsahu zadaného hesla
}

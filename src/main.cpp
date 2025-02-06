#include <Arduino.h>

#define BUTTON1_PIN PC1 //Attack
#define BUTTON2_PIN PC2 //Defense
#define BUTTON3_PIN PC3 //Special
#define BUTTON4_PIN PC4 //Heal

#define LED_VIDA1_PIN PD3
#define LED_VIDA2_PIN PD1
#define LED_VIDA3_PIN PC6

#define LED_ATTACK_PIN PD2
#define LED_DEFENSE_PIN PC7
#define LED_SPECIAL_PIN PC5

//LOS INFRARROJOS TANTO EMISOR COMO RECEPTOR TIENEN 3 PINS
#define INFRARED_SENSOR_PIN PA0


//private functions
unsigned long attack();
unsigned long defend(int vidas);
unsigned long special();
void check_health(int vidas);


void setup() {
    //Botones
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
    pinMode(BUTTON3_PIN, INPUT_PULLUP);
    pinMode(BUTTON4_PIN, INPUT_PULLUP);

    //Vidas
    pinMode(LED_VIDA1_PIN, OUTPUT);
    pinMode(LED_VIDA2_PIN, OUTPUT);
    pinMode(LED_VIDA3_PIN, OUTPUT);

    //Estados
    pinMode(LED_ATTACK_PIN, OUTPUT);
    pinMode(LED_DEFENSE_PIN, OUTPUT);
    pinMode(LED_SPECIAL_PIN, OUTPUT);
    
    Serial.begin(9600);
}


void loop() {

    int vidas = 3;
    unsigned long cooldown_defend = millis();
    unsigned long cooldown_heal = millis();
    unsigned long cooldown_special = millis();
    unsigned long cooldown_attack = millis();

    check_health(vidas);

    //ATAQUE
    if(digitalRead(BUTTON1_PIN)==LOW && (millis()-cooldown_attack>1000)){
        //enciende el led de ataque
        digitalWrite(LED_ATTACK_PIN, HIGH);
        cooldown_attack = attack();
    }
    else{
        digitalWrite(LED_ATTACK_PIN, LOW);
    }

    //DEFENSA
    if(digitalRead(BUTTON2_PIN)==LOW && (millis()-cooldown_defend>3000)){
        //enciende el led de defensa
        digitalWrite(LED_DEFENSE_PIN, HIGH);
        cooldown_defend = defend(vidas);
    }
    else{
        digitalWrite(LED_DEFENSE_PIN, LOW);
    }

    //ESPECIAL
    if(digitalRead(BUTTON3_PIN)==LOW && (millis()-cooldown_special>7000)){
        //enciende el led de especial
        digitalWrite(LED_SPECIAL_PIN, HIGH);
        cooldown_special = special();
    }
    else{
        digitalWrite(LED_SPECIAL_PIN, LOW);
    }

    //CURAR
    if(digitalRead(BUTTON4_PIN)==LOW && (millis()-cooldown_heal>10000)){
        //si tienes menos de 3 vidas te curas una
        vidas = (vidas < 3) ? vidas + 1 : vidas;
        cooldown_heal = millis();
    }



}


unsigned long attack(){
    //mandar una señal de infrared de ataque
}

unsigned long defend(int vidas){
    
    unsigned long tiempo;

    //si durante 3 segundos recibo una señal de ataque no recibo daño
    tiempo = millis();
    while(millis()-tiempo<3000){
        //si recibo una señal de ataque dejo de esperar y enciendo tanto el led de ataque como el de defensa
        if(digitalRead(INFRARED_SENSOR_PIN)==HIGH){
            digitalWrite(LED_ATTACK_PIN, HIGH);
            digitalWrite(LED_DEFENSE_PIN, HIGH);

            //he pensado que si bloqueas un ataque puedes curarte una vida
            //vidas = (vidas < 3) ? vidas + 1 : vidas;
            break;
        }
    }
    //devuelve el momento en el que acaba para poder hacer el cooldown
    return millis();

}

unsigned long special(){
    //mandar una señal de infrared de ataque
}


void check_health(int vidas){
    switch (vidas)
    {
    case 3:
        digitalWrite(LED_VIDA1_PIN, HIGH);
        digitalWrite(LED_VIDA2_PIN, HIGH);
        digitalWrite(LED_VIDA3_PIN, HIGH);
        break;
    case 2:
        digitalWrite(LED_VIDA1_PIN, HIGH);
        digitalWrite(LED_VIDA2_PIN, HIGH);
        digitalWrite(LED_VIDA3_PIN, LOW);
        break;
    case 1:
        digitalWrite(LED_VIDA1_PIN, HIGH);
        digitalWrite(LED_VIDA2_PIN, LOW);
        digitalWrite(LED_VIDA3_PIN, LOW);
        break;
    default:
        digitalWrite(LED_VIDA1_PIN, LOW);
        digitalWrite(LED_VIDA2_PIN, LOW);
        digitalWrite(LED_VIDA3_PIN, LOW);


        //cuando te quedas sin vidas se tiene que acabar el juego pero no se como todavía
        break;
    }
}

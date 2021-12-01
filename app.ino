
// Range Variables

/* Define range of action */
int rangeMin = 10, rangeMax = 1000, rangeSteps = 200, rangeStop = 0, 
    arraySteps = rangeMax / rangeSteps;

/*Define output UX*/
char *stepsNames[] = {
  "Super Cerca 1",
  "Cerca 2",
  "Distancia Media 3",
  "Distancia Media 4",
  "Rango lejano 5",
  "Rango lejano 6"
};

/* Define Array steps = rangeMax/rangeSteps -1;
 * 20 is the max division in range of 1000/50 
 */
 
int stepsArray[20];

void setup() {
  Serial.begin(115200);
  while (! Serial) { delay(1); }
  
  /*PinConfig*/
  pinMode(LED_BUILTIN, OUTPUT);


  /**/
  Serial.println("Encendido");
  digitalWrite(LED_BUILTIN, HIGH); // HIGH = OFF

  /*Setup Functions*/
  if (!rangeStop) {
    distanceRange(rangeMin, rangeMax, rangeSteps);
  }

}

void loop() {

  /*  Samples generator  :  replace after*/
  float measure = random(rangeMin, rangeMax-rangeMin-rangeSteps);
  Serial.print("Midiendo : "); Serial.print(measure);Serial.print(" mm.");
  measureFunction(measure); /*  Replace for VL53L0X measure.RangeMilliMeter*/
  
  delay(2500);

}

void measureFunction(int measureData){
  for(int i = 0; i <= arraySteps - 1; i++){
    if(measureData >= stepsArray[i] && measureData <= stepsArray[i+1]){
      Serial.println(" "); Serial.print("El rango es : "); Serial.println(stepsNames[i]);
      Serial.print("La distancia es : "); Serial.print(measureData/10, DEC); Serial.println(" cm."); Serial.println(" ");
      outputSignal(i+1);
    }
    else if (measureData >= stepsArray[arraySteps-1]){
      Serial.println(" "); Serial.print("El rango es : "); Serial.println("a la chucha.");
      Serial.print("La distancia es : "); Serial.print(measureData/10); Serial.println(" cm.");
      Serial.print("Nuestra distancia máxima es de : "); Serial.print(stepsArray[arraySteps-1]/10); Serial.println(" cm."); Serial.println(" ");
      outputSignal(10);
    }
  }
}

/*  Steps generator  */
void distanceRange(int rangeMin, int rangeMax, int rangeSteps) {
  int x = -1;
  for (int i = rangeMin; i <= rangeMax; i = i + rangeSteps) {
    x = x + 1; stepsArray[x] = i;
    if (x >= arraySteps - 1) { rangeStop = 1; break; }
  }
}

/*  Example of output UX  */
void outputSignal(int shakes) {
  for(int i = 0; i <= shakes; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

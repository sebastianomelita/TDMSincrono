// definizione dei pin di ciascun segmento TX
#define NSTEP  10000
#define TBASE  125

unsigned long tbase = TBASE;
unsigned long prec = 0;
byte btn1 = 4;
byte btn2 = 5;
byte btn3 = 6;
byte btn4 = 7;
unsigned long step=0;
byte slots[4];
byte dataport = 3;
byte syncport = 2;
byte i;

void setup()
{
  Serial.begin(19200);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);  
  pinMode(btn4, INPUT);
  pinMode(syncport, OUTPUT);
  pinMode(dataport, OUTPUT);
  i=0;
}

void doFrame(){   
	//legge valore attuale dell'ingresso
	slots[0] = digitalRead(btn1);
	slots[1] = digitalRead(btn2);
	slots[2] = digitalRead(btn3);		
	slots[3] = digitalRead(btn4);
}

void printFrame(){  
    Serial.println("Frame corrente: "); 
	for(int ii=0;ii<4;ii++){
		Serial.print(slots[ii]);
		Serial.print(", ");
	}
	Serial.println();
	Serial.println("----------------------------------");
}
 
void loop()
{
	if((millis()-prec) > tbase) //schedulatore
	{
		prec = millis(); 
		step = (step + 1) % NSTEP;
		
		if(!(step%2)){			
			doFrame();	
			digitalWrite(dataport, slots[i]);
			digitalWrite(syncport, HIGH);
			i++;
			if(i > 3){ // fine cifra (trama)
				i = 0;
				printFrame();
			}	
		}else{
			digitalWrite(syncport, LOW); // ripristina passaggio per lo zero (generazione del clock)
		}
	}
}




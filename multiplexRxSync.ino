// definizione dei pin di ciascun segmento RX
#define NSTEP  1000
#define TBASE  250

unsigned long tbase = TBASE;
unsigned long prec = 0;
byte led1 = 10;
byte led2 = 11;
byte led3 = 12;
byte led4 = 13;
unsigned long step=0;
byte slots[4];
volatile static bool triggered;
byte dataport = 3;
byte syncport = 2;
byte i;

void ISRFunc(){ // legge fronte di salita (recupera il clock)
  triggered=true;
  // other fast simple response code here, no library calls, no delay(),
}


void setup()
{
  Serial.begin(19200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(dataport,INPUT);
  pinMode(syncport,INPUT);
  attachInterrupt(digitalPinToInterrupt(2),ISRFunc,RISING); 
  i=0;
}
 
void doMulplexing(){   
	digitalWrite(led1, slots[0]);
	digitalWrite(led2, slots[1]);
	digitalWrite(led3, slots[2]);
	digitalWrite(led4, slots[3]);
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
	if(triggered){ // loop sincronizzato col clock esterno
		triggered = false; // reset flag
			
		slots[i] = digitalRead(dataport);
		i++;
		if(i > 3){ // fine cifra (trama)
			i = 0;
			printFrame();
			doMulplexing();
		}
	}
}




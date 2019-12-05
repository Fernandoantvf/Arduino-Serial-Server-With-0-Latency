//Fernando Figueiredo 
//SMILE.TECH - ROBÓTICA LDA. www.smlt.pt
//ISPGAYA - Instituto Superior Politécnico www.ispgaya.pt



//Configures Serial Port to 0 Timeout and buffers received bytes until message is complete
//Once "CR" Char is received, it calls a function to process the complete message.

//Auxiliary Receive Buffer
byte bPendingMessage[40];
int iPendingBytes;
char bRecievedBytes [40];
int iMessageLength;
String sRecievedMessage;



void setup() {
  //Setup Serial Port and define timeout to 0
  //Timeout generates latency in responses
  Serial.begin(115200);
  Serial.setTimeout(0);
}

void loop() {
  CheckSerialPort();
}


void CheckSerialPort() {
  //Check if there is info available in serial Port
  if (Serial.available()) {
    iMessageLength = Serial.readBytes(bRecievedBytes, 12);
    if (iPendingBytes + iMessageLength <= 100) {
      for (int i = 0; i < iMessageLength; i++) {

        if (bRecievedBytes[i] == (byte)'\n') {
          //clear buffer
          iPendingBytes = 0;
        }
        else if (bRecievedBytes[i] == (byte)'\r') {
          //process message and clear buffer
          ProcessMessage(iPendingBytes, bPendingMessage);
          iPendingBytes = 0;
        }
        else{
          //Add new bytes to buffer
          bPendingMessage[iPendingBytes] = bRecievedBytes[i];
          iPendingBytes ++;
        }
      }
    }
    else {
      iPendingBytes = 0;
    }
  }
}


void ProcessMessage(int iPendingBytes, byte bPendingMessage[]) {
  String sRecievedMessage = String((char *)bPendingMessage); 
  sRecievedMessage = sRecievedMessage.substring(0, iPendingBytes);
  int iGTSignPos = sRecievedMessage.indexOf('>');
  int iSTSignPos = sRecievedMessage.indexOf('<');
  if (iGTSignPos >=0 && iSTSignPos >=0){
    Serial.println("Encontrado texto delimitado: " + sRecievedMessage.substring(iSTSignPos + 1, iGTSignPos));
  }
  else{
    Serial.println("Texto delimitado não encontrado.");
  }
}

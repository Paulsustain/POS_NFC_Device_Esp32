void Led_processing1(){
  digitalWrite(Yellow,HIGH);
  digitalWrite(Green,LOW);
  digitalWrite(Red,LOW);
}
void Led_processing(){
  digitalWrite(Yellow,HIGH);
  vTaskDelay(pdMS_TO_TICKS(100));
   digitalWrite(Yellow,LOW);
   vTaskDelay(pdMS_TO_TICKS(100));
}
void Led_processing_end(){
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
  digitalWrite(Red,LOW);
}


void Indicator_initialize(){
  pinMode(Red,OUTPUT);
  pinMode(Yellow,OUTPUT);
  pinMode(Green,OUTPUT);
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
}

void Led_failed(){
  digitalWrite(Red,HIGH); 
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW); 
}

void Led_success(){
  digitalWrite(Red,LOW); 
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,HIGH); 
}
void Led_failed_end(){
  digitalWrite(Red,HIGH);  
}

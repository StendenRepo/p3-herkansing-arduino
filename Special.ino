// This code used to be implemented in the Escape room
// but due to hardware errors was removed

const int micro1 = 36;
const int micro0 = 39;

int escaped = 0;

void setup() 
{
  pinMode(micro1, OUTPUT);
  pinMode(micro0, OUTPUT);
}

void loop()
{
  if (escaped)
  {
    digitalWrite(micro1, HIGH);  
    digitalWrite(micro0, LOW);
  }
  else
  {
    digitalWrite(micro0, HIGH);
  }
}

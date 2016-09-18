int room_one_input = 2;
int room_two_input = 3;

int room_one_output = 4;
int room_two_output = 5;

int limit = 0;
int room_one_counter = 0;
int room_two_counter = 0;

int corridor_one_input = A0;
int corridor_two_input = A1;
int corridor_three_input = A2;
int corridor_four_input = A3;

int corridor_one_output = 8;
int corridor_two_output = 9;
int corridor_three_output = 10;
int corridor_four_output = 11;

int corridor_limit = 100;
int corridor_one_counter = 0;
int corridor_two_counter = 0;
int corridor_three_counter = 0;
int corridor_four_counter = 0;

int ldr_one_idle_value = 0;
int ldr_two_idle_value = 0;
int ldr_three_idle_value = 0;
int ldr_four_idle_value = 0;

int output_sensitivity = 0;

boolean is_idle_set = false;

void setup() {
  pinMode(room_one_input, INPUT);
  pinMode(room_two_input, INPUT);
  pinMode(room_one_output, OUTPUT);
  pinMode(room_two_output, OUTPUT);

  pinMode(corridor_one_input, INPUT);
  pinMode(corridor_two_input, INPUT);
  pinMode(corridor_three_input, INPUT);
  pinMode(corridor_four_input, INPUT);
//  pinMode(main_ldr_input, INPUT);
  
  pinMode(corridor_one_output, OUTPUT);
  pinMode(corridor_two_output, OUTPUT);
  pinMode(corridor_three_output, OUTPUT);
  pinMode(corridor_four_output, OUTPUT);
  
  Serial.begin(9600);
}

int handle_room_light_glowing(int inputPin, int outputPin, int counter) {
  int value = digitalRead(inputPin);
  if(value == HIGH){
    digitalWrite(outputPin, HIGH);
  }else if(counter >= limit){
    counter = 0;
    digitalWrite(outputPin, LOW);
  }
  return counter;
}

void increment_counters() {
  room_one_counter++;
  room_two_counter++;

  corridor_one_counter++;
  corridor_two_counter++;
  corridor_three_counter++;
  corridor_four_counter++;
}

int get_idle_value_for_ldr(int ldr_input){
  int value = 0;
  int count = 100;
  int reading[count]; 
  for(int i = 0; i < count; i++){
    value = value + analogRead(ldr_input);
  }
  value = value/count;
  return (int)value;
}

void set_idle_value_for_all_ldrs() {
  ldr_one_idle_value = get_idle_value_for_ldr(corridor_one_input);
  ldr_two_idle_value = get_idle_value_for_ldr(corridor_two_input);
  ldr_three_idle_value = get_idle_value_for_ldr(corridor_three_input);
  ldr_four_idle_value = get_idle_value_for_ldr(corridor_four_input);
}

int handle_corridor_light_glowing(int corridor_input, int corridor_output, int idle_value, int counter){
  int sensed_value = analogRead(corridor_input);
  if((idle_value + 5 < sensed_value) || (idle_value - 5 > sensed_value)){
    digitalWrite(corridor_output, HIGH);
  }else if(counter >= corridor_limit){
    counter = 0;
    digitalWrite(corridor_output, LOW);
  }
  return counter;
}
  
void loop() {
  increment_counters();
  if(!is_idle_set){
    set_idle_value_for_all_ldrs();
    is_idle_set = true;
  }

 
  Serial.println(analogRead(corridor_one_input));

  room_one_counter = handle_room_light_glowing(room_one_input, room_one_output, room_one_counter);
  room_one_counter = handle_room_light_glowing(room_two_input, room_two_output, room_two_counter);
  
  corridor_one_counter = handle_corridor_light_glowing(corridor_one_input, corridor_one_output, ldr_one_idle_value, corridor_one_counter);
  corridor_two_counter = handle_corridor_light_glowing(corridor_two_input, corridor_two_output, ldr_two_idle_value, corridor_two_counter);
  corridor_three_counter = handle_corridor_light_glowing(corridor_three_input, corridor_three_output, ldr_three_idle_value, corridor_three_counter);
  corridor_four_counter = handle_corridor_light_glowing(corridor_four_input, corridor_four_output, ldr_four_idle_value, corridor_four_counter);
}

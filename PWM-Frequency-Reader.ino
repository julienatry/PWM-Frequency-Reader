#define pwm_in 2

int RPM;
float pwm_freq, pwm_period;
unsigned long pwm_start_time, pwm_stop_time;

const int pwm_num_periods = 25;
int pwm_periods [pwm_num_periods];
int pwm_read_index;
float pwm_total;

void setup()
{
  Serial.begin(115200);
  pinMode(pwm_in, INPUT);
  attachInterrupt(digitalPinToInterrupt(pwm_in), pwm_start, RISING);
}

void loop()
{

}

void pwm_start() {
  pwm_start_time = micros();

  attachInterrupt(digitalPinToInterrupt(pwm_in), pwm_stop, RISING);
}

void pwm_stop() {
  pwm_stop_time = micros();

  pwm_period = pwm_stop_time - pwm_start_time;
  Serial.print("Period : ");
  Serial.println(pwm_period_smooth());

  pwm_freq = 1.0 / pwm_period_smooth() * 1000000.0;
  Serial.print("Frequency : ");
  Serial.println(pwm_freq);

  attachInterrupt(digitalPinToInterrupt(pwm_in), pwm_start, RISING);
}


float pwm_period_smooth() {
  float pwm_smooth_average;
  
  pwm_total = pwm_total - pwm_periods[pwm_read_index];
  pwm_periods[pwm_read_index] = pwm_period;
  pwm_total = pwm_total + pwm_periods[pwm_read_index];
  
  pwm_read_index++;
  if (pwm_read_index >= pwm_num_periods) {
    pwm_read_index = 0;
  }

  pwm_smooth_average = pwm_total / pwm_num_periods;

  return pwm_smooth_average;
}

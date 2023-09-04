void batteryBarTask(void *pvParameters)
{
  float batteryVoltage = 0;
  int percentage = 0;
  int fill = 0;
  
  while (true)
  {
    
    // Read the ADC value and calculate the battery voltage
    int sensorValue = analogRead(sensorPin);
    batteryVoltage = ((float)sensorValue / 4095.0) * 3.3 / k;
    batteryVoltage = max(batteryVoltage, 0.0f);

    // Calculate the percentage of battery life remaining
    percentage = map(batteryVoltage * 1000, 3400, 4200, 0, 100);
    percentage = constrain(percentage, 0, 100);

    // Clear the OLED display
    //if (xSemaphoreTake(xSemaphoreOled, portMAX_DELAY) == pdTRUE)
    //{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.println("KORENSI");
    if (percentage < 100 && percentage > 9)
    {
      display.setCursor(81, 0);
     // display.println(String(percentage) + "%");
    }

    if (percentage >= 100)
    {
      display.setCursor(75, 0);
     // display.println(String(percentage) + "%");
    }

    else
    {
      display.setCursor(86, 0);
      //display.println(String(percentage) + "%");
    }

    // draw the battery outline
    display.drawRect(barX, barY, barWidth + 2, barHeight, WHITE);

    // draw the filled battery bar
    fill = map(percentage, 0, 100, 0, barWidth);
    display.fillRect(barX + 1, barY + 1, fill, barHeight - 2, WHITE);

    // Update the OLED display
    display.display();
    //xSemaphoreGive(xSemaphoreOled);
    //}
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

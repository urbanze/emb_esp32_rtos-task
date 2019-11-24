#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>

void t1(void*z)
{//Tarefa que simula PWM para observar no analisador logico
    while (1)
    {
        gpio_set_level(GPIO_NUM_2, 1);
        ets_delay_us(25);
        gpio_set_level(GPIO_NUM_2, 0);
        ets_delay_us(25);
    }
}

void t2(void*z)
{//Tarefa que simula PWM para observar no analisador logico
    while (1)
    {
        gpio_set_level(GPIO_NUM_4, 1);
        ets_delay_us(25);
        gpio_set_level(GPIO_NUM_4, 0);
        ets_delay_us(25);
    }
}

void t3(void*z)
{//Tarefa que simula PWM para observar no analisador logico
    while (1)
    {
        for (uint8_t i = 0; i < 200; i++)
        {
            gpio_set_level(GPIO_NUM_15, 1);
            ets_delay_us(500);
            gpio_set_level(GPIO_NUM_15, 0);
            ets_delay_us(500);
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}



void app_main()
{
    //Seleciona os pinos que serao usados
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_pad_select_gpio(GPIO_NUM_4);
    gpio_pad_select_gpio(GPIO_NUM_15);

    //Configura os pinos para OUTPUT
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_OUTPUT);


    //Cria as tarefas
    xTaskCreatePinnedToCore(t1, "task1", 2048, NULL, 1, NULL, 0);//Tarefa 1 com prioridade UM (1) no core 0
    xTaskCreatePinnedToCore(t2, "task2", 2048, NULL, 1, NULL, 0);//Tarefa 2 com prioridade UM (1) no core 0
    xTaskCreatePinnedToCore(t3, "task3", 2048, NULL, 2, NULL, 0);//Tarefa 3 com prioridade DOIS (2) no core 0
}
